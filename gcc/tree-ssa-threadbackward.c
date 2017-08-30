/* SSA Jump Threading
   Copyright (C) 2005-2017 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "predict.h"
#include "tree.h"
#include "gimple.h"
#include "fold-const.h"
#include "cfgloop.h"
#include "gimple-iterator.h"
#include "tree-cfg.h"
#include "tree-ssa-threadupdate.h"
#include "params.h"
#include "tree-ssa-loop.h"
#include "cfganal.h"
#include "tree-pass.h"
#include "gimple-ssa.h"
#include "tree-phinodes.h"
#include "tree-inline.h"
#include "tree-vectorizer.h"
#include "stringpool.h"
#include "tree-vrp.h"
#include "tree-ssanames.h"
#include "ssa-range-gen.h"
#include "domwalk.h"

#include "graph.h"
#include "tree-pretty-print.h"
#include "gimple-pretty-print.h"

static int max_threaded_paths;

/* Simple helper to get the last statement from BB, which is assumed
   to be a control statement.   Return NULL if the last statement is
   not a control statement.  */

static gimple *
get_gimple_control_stmt (basic_block bb)
{
  gimple_stmt_iterator gsi = gsi_last_nondebug_bb (bb);

  if (gsi_end_p (gsi))
    return NULL;

  gimple *stmt = gsi_stmt (gsi);
  enum gimple_code code = gimple_code (stmt);
  if (code == GIMPLE_COND || code == GIMPLE_SWITCH || code == GIMPLE_GOTO)
    return stmt;
  return NULL;
}

/* Return true if the CFG contains at least one path from START_BB to END_BB.
   When a path is found, record in PATH the blocks from END_BB to START_BB.
   VISITED_BBS is used to make sure we don't fall into an infinite loop.  Bound
   the recursion to basic blocks belonging to LOOP.  */

static bool
fsm_find_thread_path (basic_block start_bb, basic_block end_bb,
		      vec<basic_block, va_gc> *&path,
		      hash_set<basic_block> *visited_bbs, loop_p loop)
{
  if (loop != start_bb->loop_father)
    return false;

  if (start_bb == end_bb)
    {
      vec_safe_push (path, start_bb);
      return true;
    }

  if (!visited_bbs->add (start_bb))
    {
      edge e;
      edge_iterator ei;
      FOR_EACH_EDGE (e, ei, start_bb->succs)
	if (fsm_find_thread_path (e->dest, end_bb, path, visited_bbs, loop))
	  {
	    vec_safe_push (path, start_bb);
	    return true;
	  }
    }

  return false;
}

/* Examine jump threading path PATH to which we want to add BBI.

   If the resulting path is profitable to thread, then return the
   final taken edge from the path, NULL otherwise.

   NAME is the SSA_NAME of the variable we found to have a constant
   value on PATH.  ARG is the constant value of NAME on that path.

   BBI will be appended to PATH when we have a profitable jump threading
   path.  Callers are responsible for removing BBI from PATH in that case.

   SPEED_P indicate that we could increase code size to improve the code path */

static edge
profitable_jump_thread_path (vec<basic_block, va_gc> *&path,
			     basic_block bbi, tree name, tree arg, bool speed_p,
			     bool *creates_irreducible_loop)
{
  /* Note BBI is not in the path yet, hence the +1 in the test below
     to make sure BBI is accounted for in the path length test.  */
  int path_length = path->length ();

  /* We can get a length of 0 here when the statement that
     makes a conditional generate a compile-time constant
     result is in the same block as the conditional.

     That's not really a jump threading opportunity, but instead is
     simple cprop & simplification.  We could handle it here if we
     wanted by wiring up all the incoming edges.  If we run this
     early in IPA, that might be worth doing.   For now we just
     reject that case.  */
  if (path_length == 0)
      return NULL;

  if (path_length + 1 > PARAM_VALUE (PARAM_MAX_FSM_THREAD_LENGTH))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "FSM jump-thread path not considered: "
		 "the number of basic blocks on the path "
		 "exceeds PARAM_MAX_FSM_THREAD_LENGTH.\n");
      return NULL;
    }

  if (max_threaded_paths <= 0)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "FSM jump-thread path not considered: "
		 "the number of previously recorded FSM paths to "
		 "thread exceeds PARAM_MAX_FSM_THREAD_PATHS.\n");
      return NULL;
    }

  /* Add BBI to the path.
     From this point onward, if we decide we the path is not profitable
     to thread, we must remove BBI from the path.  */
  vec_safe_push (path, bbi);
  ++path_length;

  int n_insns = 0;
  gimple_stmt_iterator gsi;
  int j;
  loop_p loop = (*path)[0]->loop_father;
  bool path_crosses_loops = false;
  bool threaded_through_latch = false;
  bool multiway_branch_in_path = false;
  bool threaded_multiway_branch = false;
  bool contains_hot_bb = false;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Checking profitability of path (backwards): ");

  /* Count the number of instructions on the path: as these instructions
     will have to be duplicated, we will not record the path if there
     are too many instructions on the path.  Also check that all the
     blocks in the path belong to a single loop.  */
  for (j = 0; j < path_length; j++)
    {
      basic_block bb = (*path)[j];

      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " bb:%i", bb->index);
      /* Remember, blocks in the path are stored in opposite order
	 in the PATH array.  The last entry in the array represents
	 the block with an outgoing edge that we will redirect to the
	 jump threading path.  Thus we don't care about that block's
	 loop father, nor how many statements are in that block because
	 it will not be copied or whether or not it ends in a multiway
	 branch.  */
      if (j < path_length - 1)
	{
	  int orig_n_insns = n_insns;
	  if (bb->loop_father != loop)
	    {
	      path_crosses_loops = true;
	      break;
	    }

	  /* PHIs in the path will create degenerate PHIS in the
	     copied path which will then get propagated away, so
	     looking at just the duplicate path the PHIs would
	     seem unimportant.

	     But those PHIs, because they're assignments to objects
	     typically with lives that exist outside the thread path,
	     will tend to generate PHIs (or at least new PHI arguments)
	     at points where we leave the thread path and rejoin
	     the original blocks.  So we do want to account for them.

	     We ignore virtual PHIs.  We also ignore cases where BB
	     has a single incoming edge.  That's the most common
	     degenerate PHI we'll see here.  Finally we ignore PHIs
	     that are associated with the value we're tracking as
	     that object likely dies.  */
	  if (EDGE_COUNT (bb->succs) > 1 && EDGE_COUNT (bb->preds) > 1)
	    {
	      for (gphi_iterator gsip = gsi_start_phis (bb);
		   !gsi_end_p (gsip);
		   gsi_next (&gsip))
		{
		  gphi *phi = gsip.phi ();
		  tree dst = gimple_phi_result (phi);

		  /* Note that if both NAME and DST are anonymous
		     SSA_NAMEs, then we do not have enough information
		     to consider them associated.  */
		  if (dst != name
		      && (SSA_NAME_VAR (dst) != SSA_NAME_VAR (name)
			  || !SSA_NAME_VAR (dst))
		      && !virtual_operand_p (dst))
		    ++n_insns;
		}
	    }

	  if (!contains_hot_bb && speed_p)
	    contains_hot_bb |= optimize_bb_for_speed_p (bb);
	  for (gsi = gsi_after_labels (bb);
	       !gsi_end_p (gsi);
	       gsi_next_nondebug (&gsi))
	    {
	      gimple *stmt = gsi_stmt (gsi);
	      /* Do not count empty statements and labels.  */
	      if (gimple_code (stmt) != GIMPLE_NOP
		  && !(gimple_code (stmt) == GIMPLE_ASSIGN
		       && gimple_assign_rhs_code (stmt) == ASSERT_EXPR)
		  && !is_gimple_debug (stmt))
		n_insns += estimate_num_insns (stmt, &eni_size_weights);
	    }
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, " (%i insns)", n_insns-orig_n_insns);

	  /* We do not look at the block with the threaded branch
	     in this loop.  So if any block with a last statement that
	     is a GIMPLE_SWITCH or GIMPLE_GOTO is seen, then we have a
	     multiway branch on our path.

	     The block in PATH[0] is special, it's the block were we're
	     going to be able to eliminate its branch.  */
	  gimple *last = last_stmt (bb);
	  if (last && (gimple_code (last) == GIMPLE_SWITCH
		       || gimple_code (last) == GIMPLE_GOTO))
	    {
	      if (j == 0)
		threaded_multiway_branch = true;
	      else
		multiway_branch_in_path = true;
	    }
	}

      /* Note if we thread through the latch, we will want to include
	 the last entry in the array when determining if we thread
	 through the loop latch.  */
      if (loop->latch == bb)
	threaded_through_latch = true;
    }

  gimple *stmt = get_gimple_control_stmt ((*path)[0]);
  gcc_assert (stmt);

  /* We are going to remove the control statement at the end of the
     last block in the threading path.  So don't count it against our
     statement count.  */

  int stmt_insns = estimate_num_insns (stmt, &eni_size_weights);
  n_insns-= stmt_insns;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "\n  Control statement insns: %i\n"
	     "  Overall: %i insns\n",
	     stmt_insns, n_insns);

  /* We have found a constant value for ARG.  For GIMPLE_SWITCH
     and GIMPLE_GOTO, we use it as-is.  However, for a GIMPLE_COND
     we need to substitute, fold and simplify so we can determine
     the edge taken out of the last block.  */
  if (gimple_code (stmt) == GIMPLE_COND)
    {
      enum tree_code cond_code = gimple_cond_code (stmt);

      /* We know the underyling format of the condition.  */
      arg = fold_binary (cond_code, boolean_type_node,
			 arg, gimple_cond_rhs (stmt));
    }

  /* If this path threaded through the loop latch back into the
     same loop and the destination does not dominate the loop
     latch, then this thread would create an irreducible loop.

     We have to know the outgoing edge to figure this out.  */
  edge taken_edge = find_taken_edge ((*path)[0], arg);

  /* There are cases where we may not be able to extract the
     taken edge.  For example, a computed goto to an absolute
     address.  Handle those cases gracefully.  */
  if (taken_edge == NULL)
    {
      path->pop ();
      return NULL;
    }

  *creates_irreducible_loop = false;
  if (threaded_through_latch
      && loop == taken_edge->dest->loop_father
      && (determine_bb_domination_status (loop, taken_edge->dest)
	  == DOMST_NONDOMINATING))
    *creates_irreducible_loop = true;

  if (path_crosses_loops)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "FSM jump-thread path not considered: "
		 "the path crosses loops.\n");
      path->pop ();
      return NULL;
    }

  /* Threading is profitable if the path duplicated is hot but also
     in a case we separate cold path from hot path and permit optimization
     of the hot path later.  Be on the agressive side here. In some testcases,
     as in PR 78407 this leads to noticeable improvements.  */
  if (speed_p && (optimize_edge_for_speed_p (taken_edge) || contains_hot_bb))
    {
      if (n_insns >= PARAM_VALUE (PARAM_MAX_FSM_THREAD_PATH_INSNS))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "FSM jump-thread path not considered: "
		     "the number of instructions on the path "
		     "exceeds PARAM_MAX_FSM_THREAD_PATH_INSNS.\n");
	  path->pop ();
	  return NULL;
	}
    }
  else if (n_insns > 1)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "FSM jump-thread path not considered: "
		 "duplication of %i insns is needed and optimizing for size.\n",
		 n_insns);
      path->pop ();
      return NULL;
    }

  /* We avoid creating irreducible inner loops unless we thread through
     a multiway branch, in which case we have deemed it worth losing
     other loop optimizations later.

     We also consider it worth creating an irreducible inner loop if
     the number of copied statement is low relative to the length of
     the path -- in that case there's little the traditional loop
     optimizer would have done anyway, so an irreducible loop is not
     so bad.  */
  if (!threaded_multiway_branch && *creates_irreducible_loop
      && (n_insns * PARAM_VALUE (PARAM_FSM_SCALE_PATH_STMTS)
	  > path_length * PARAM_VALUE (PARAM_FSM_SCALE_PATH_BLOCKS)))

    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file,
		 "FSM would create irreducible loop without threading "
		 "multiway branch.\n");
      path->pop ();
      return NULL;
    }


  /* If this path does not thread through the loop latch, then we are
     using the FSM threader to find old style jump threads.  This
     is good, except the FSM threader does not re-use an existing
     threading path to reduce code duplication.

     So for that case, drastically reduce the number of statements
     we are allowed to copy.  */
  if (!(threaded_through_latch && threaded_multiway_branch)
      && (n_insns * PARAM_VALUE (PARAM_FSM_SCALE_PATH_STMTS)
	  >= PARAM_VALUE (PARAM_MAX_JUMP_THREAD_DUPLICATION_STMTS)))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file,
		 "FSM did not thread around loop and would copy too "
		 "many statements.\n");
      path->pop ();
      return NULL;
    }

  /* When there is a multi-way branch on the path, then threading can
     explode the CFG due to duplicating the edges for that multi-way
     branch.  So like above, only allow a multi-way branch on the path
     if we actually thread a multi-way branch.  */
  if (!threaded_multiway_branch && multiway_branch_in_path)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file,
		 "FSM Thread through multiway branch without threading "
		 "a multiway branch.\n");
      path->pop ();
      return NULL;
    }
  return taken_edge;
}

/* PATH is vector of blocks forming a jump threading path in reverse
   order.  TAKEN_EDGE is the edge taken from path[0].

   Convert that path into the form used by register_jump_thread and
   register the path.   */

static void
convert_and_register_jump_thread_path (vec<basic_block, va_gc> *path,
				       edge taken_edge)
{
  vec<jump_thread_edge *> *jump_thread_path = new vec<jump_thread_edge *> ();

  /* Record the edges between the blocks in PATH.  */
  for (unsigned int j = 0; j < path->length () - 1; j++)
    {
      basic_block bb1 = (*path)[path->length () - j - 1];
      basic_block bb2 = (*path)[path->length () - j - 2];

      edge e = find_edge (bb1, bb2);
      gcc_assert (e);
      jump_thread_edge *x = new jump_thread_edge (e, EDGE_FSM_THREAD);
      jump_thread_path->safe_push (x);
    }

  /* Add the edge taken when the control variable has value ARG.  */
  jump_thread_edge *x
    = new jump_thread_edge (taken_edge, EDGE_NO_COPY_SRC_BLOCK);
  jump_thread_path->safe_push (x);

  register_jump_thread (jump_thread_path);
  --max_threaded_paths;
}

/* Generic walker for every path from an SSA's definition to an arbitrary BB.

   Use it like this:

	class my_walker : public ssa_path_walker
	{
	 public:
	  my_walker (tree name, basic_block use_bb)
	    : ssa_path_walker (name, use_bb) { }
	  virtual void analyze_path () { do_stuff (path); }
	}
	my_walker w (x_99, some_bb);
	w.walk ();
 */

class ssa_path_walker
{
  /* The SSA name we are interested in.  */
  tree name;
  /* The BB defining NAME.  */
  basic_block def_bb;
  /* The BB using NAME.  */
  basic_block use_bb;
  /* Visited blocks per path.  */
  hash_set<basic_block> *visited;
  /* Maximum path length we care about.  Set to 0 if we wish to
     consider all paths regardless of length. */
  unsigned max_path;
  void walk_helper (basic_block bb);

 public:
  /* The reverse path from def(NAME) to USE_BB:

	path[path.length() - 1] is DEF_BB.
	path[0] is USE_BB.
  */
  auto_vec<basic_block> path;

  tree get_name () const { return name; }
  basic_block get_use_bb () const { return use_bb; }
  ssa_path_walker (tree name_, basic_block use_bb_, unsigned max_path = 0);
  ssa_path_walker () { gcc_unreachable (); }
  ~ssa_path_walker () { delete visited; }
  /* Find all paths from BB back to DEF_BB.  */
  void walk () { walk_helper (use_bb); }
  /* Callback to call on every path.  */
  virtual void analyze_path () { }
};

/* Constructor for ssa_path_walker.

   NAME_ is the SSA name we are interested in.

   USE_BB_ is a use of NAME_.

   If nonzero, MAX_PATH_ specifies the maximum path length to consider
   when generating a path.  Any path with a length greater than this
   will be ignored.  */

ssa_path_walker::ssa_path_walker (tree name_, basic_block use_bb_,
				  unsigned max_path_)
{
  name = name_;
  use_bb = use_bb_;
  max_path = max_path_;
  gimple *def_stmt = SSA_NAME_DEF_STMT (name);
  gcc_assert (def_stmt != NULL);
  def_bb = gimple_bb (def_stmt);
  visited = new hash_set<basic_block>;
}

/* Find all paths from DEF_BB to BB.

   Every time a path is found, call analyze_path() with PATH set to
   the found path.  */

void
ssa_path_walker::walk_helper (basic_block bb)
{
  if (!def_bb)
    return;
  if (visited->add (bb))
    return;
  if (max_path && path.length () + 1 > max_path)
    return;

  path.safe_push (bb);

  edge e;
  edge_iterator ei;
  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      /* If we reached the defining block, we've reached the top, and
	 have a path.  */
      if (e->src == def_bb)
	{
	  /* Push the DEF_BB for completeness sake.  */
	  path.safe_push (def_bb);
	  analyze_path ();
	  path.pop ();
	}
      else
	walk_helper (e->src);
    }

  path.pop ();
  visited->remove (bb);
}

/* A path of BBs for an SSA name with a precomputed range of RANGE.  */

class path_with_range
{
  /* The path.  */
  vec<basic_block, va_gc> *path;
  /* The range for the SSA on this path.  */
  irange range;

 public:
  path_with_range () { }
  path_with_range (const irange &r, const auto_vec<basic_block> &p)
  {
    range = r;
    vec_alloc (path, p.length ());
    basic_block bb;
    for (unsigned i = 0; p.iterate (i, &bb); ++i)
      path->quick_push (bb);
  }
  vec<basic_block, va_gc> *get_path () const { return path; }
  irange get_range () const { return range; }
  void dump () const;
};

void
path_with_range::dump () const
{
  fprintf (stderr, "path: ");
  for (int i = path->length () - 1; i > 0; --i)
    {
      fprintf (stderr, "bb%d", (*path)[i]->index);
      edge e = find_edge ((*path)[i], (*path)[i - 1]);
      gcc_assert (e);
      fprintf (stderr, " => ");
    }
  fprintf (stderr, "bb%d\n", (*path)[0]->index);
  fprintf (stderr, "\trange: ");
  range.dump ();

  wide_int x;
  if (range.one_element_p (x))
    fprintf (stderr, "\trange is a simple constant\n");
}

/* A class that will calculate all paths containing a range for an SSA NAME
   from its definition to a USE_BB.

   Example use:

	paths_with_ranges w (some_ssa_name, use_bb);
	w.generate ();

	path_with_range p;
	for (unsigned i = 0; w.iterate (i, p); ++i)
	  {
	    vec<basic_block, va_gc> *path = p.get_path ();
	    irange range = p.get_range ();
	    do_stuff (PATH, RANGE);
	  }
*/

class paths_with_ranges : ssa_path_walker
{
  /* A set of all the paths from def(NAME) to USE_BB that have a
     range.  This set is built as the walk is performed, so reading
     paths_with_range is only valid after the walker has finished.  */
  auto_vec<path_with_range> paths_with_range;
 public:
  paths_with_ranges (tree name, basic_block use_bb)
    : ssa_path_walker (name, use_bb,
		       PARAM_VALUE (PARAM_MAX_FSM_THREAD_LENGTH)) { }
  void generate () { walk (); }
  inline bool iterate (unsigned, path_with_range &) const;
  virtual void analyze_path ();
  void dump () const;
};

/* Iterate through all available paths.  */

inline bool
paths_with_ranges::iterate (unsigned int i, path_with_range &p) const
{
  if (i < paths_with_range.length ())
    {
      p = paths_with_range[i];
      return true;
    }
  return false;
}

/* Dump all the paths accumulated by the walker.  */

void
paths_with_ranges::dump () const
{
  if (paths_with_range.length () == 0)
    return;

  fprintf (stderr, "range path to BB%d for SSA = ", get_use_bb ()->index);
  print_generic_stmt (stderr, get_name (), 0);

  path_with_range p;
  for (unsigned i = 0; iterate (i, p); ++i)
    {
      fprintf (stderr, "\t");
      p.dump ();
    }
  fprintf (stderr, "-----------------------------\n");
}

/* Calculate the range for the current PATH and add it into the full
   set of paths.  */

void
paths_with_ranges::analyze_path ()
{
  gori g;
  irange range;
  range.set_range_for_type (TREE_TYPE (get_name ()));

  /* Calculate the range for PATH.  */
  for (unsigned i = path.length () - 1; i > 0; --i)
    {
      edge e = find_edge (path[i], path[i - 1]);
      gcc_assert (e);
      irange r;
      if (g.range_on_edge (r, get_name (), e))
	range.intersect (r);
    }
  /* Ignore ranges spanning the entire type.  */
  if (range.range_for_type_p ())
    return;
  /* Save the current path and range into the full set.  */
  path_with_range p (range, path);
  paths_with_range.safe_push (p);
}

/* While following a chain of SSA_NAME definitions, we jumped from a definition
   in LAST_BB to a definition in NEW_BB (walking backwards).

   Verify there is a single path between the blocks and none of the blocks
   in the path is already in VISITED_BBS.  If so, then update VISISTED_BBS,
   add the new blocks to PATH and return TRUE.  Otherwise return FALSE.

   Store the length of the subpath in NEXT_PATH_LENGTH.  */

static bool
check_subpath_and_update_thread_path (basic_block last_bb, basic_block new_bb,
				      hash_set<basic_block> *visited_bbs,
				      vec<basic_block, va_gc> *&path,
				      int *next_path_length)
{
  edge e;
  int e_count = 0;
  edge_iterator ei;
  vec<basic_block, va_gc> *next_path;
  vec_alloc (next_path, 10);

  FOR_EACH_EDGE (e, ei, last_bb->preds)
    {
      hash_set<basic_block> *visited_bbs = new hash_set<basic_block>;

      if (fsm_find_thread_path (new_bb, e->src, next_path, visited_bbs,
				e->src->loop_father))
	++e_count;

      delete visited_bbs;

      /* If there is more than one path, stop.  */
      if (e_count > 1)
	{
	  vec_free (next_path);
	  return false;
	}
    }

  /* Stop if we have not found a path: this could occur when the recursion
     is stopped by one of the bounds.  */
  if (e_count == 0)
    {
      vec_free (next_path);
      return false;
    }

  /* Make sure we haven't already visited any of the nodes in
     NEXT_PATH.  Don't add them here to avoid pollution.  */
  for (unsigned int i = 0; i < next_path->length () - 1; i++)
    {
      if (visited_bbs->contains ((*next_path)[i]))
	{
	  vec_free (next_path);
	  return false;
	}
    }

  /* Now add the nodes to VISISTED_BBS.  */
  for (unsigned int i = 0; i < next_path->length () - 1; i++)
    visited_bbs->add ((*next_path)[i]);

  /* Append all the nodes from NEXT_PATH to PATH.  */
  vec_safe_splice (path, next_path);
  *next_path_length = next_path->length ();
  vec_free (next_path);

  return true;
}

/* If this is a profitable jump thread path, register it.

   NAME is an SSA NAME with a possible constant value of ARG on PATH.

   DEF_BB is the basic block that ultimately defines the constant.

   SPEED_P indicate that we could increase code size to improve the
   code path.
*/

static void
register_jump_thread_path_if_profitable (vec<basic_block, va_gc> *&path,
					 tree name,
					 tree arg,
					 basic_block def_bb,
					 bool speed_p)
{
  if (TREE_CODE_CLASS (TREE_CODE (arg)) != tcc_constant)
    return;

  bool irreducible = false;
  edge taken_edge = profitable_jump_thread_path (path, def_bb, name, arg,
						 speed_p, &irreducible);
  if (taken_edge)
    {
      convert_and_register_jump_thread_path (path, taken_edge);
      path->pop ();

      if (irreducible)
	vect_free_loop_info_assumptions ((*path)[0]->loop_father);
    }

}

static void fsm_find_control_statement_thread_paths (tree,
						     hash_set<basic_block> *,
						     vec<basic_block, va_gc> *&,
						     bool, bool);

/* Given PHI which defines NAME in block DEF_BB, recurse through the
   PHI's arguments searching for paths where NAME will ultimately have
   a constant value.

   VISITED_BBS tracks the blocks that have been encountered.

   PATH contains the series of blocks to traverse that will result in
   NAME having a constant value.

   SEEN_LOOP_PHI tracks if we have recursed through a loop PHI node.

   SPEED_P indicates if we are optimizing for speed over space.  */

static void
handle_phi (gphi *phi, tree name, basic_block def_bb,
	    hash_set<basic_block> *visited_bbs,
	    vec<basic_block, va_gc> *&path,
	    bool seen_loop_phi, bool speed_p)
{
  /* Iterate over the arguments of PHI.  */
  for (unsigned int i = 0; i < gimple_phi_num_args (phi); i++)
    {
      tree arg = gimple_phi_arg_def (phi, i);
      basic_block bbi = gimple_phi_arg_edge (phi, i)->src;

      /* Skip edges pointing outside the current loop.  */
      if (!arg || def_bb->loop_father != bbi->loop_father)
	continue;

      if (TREE_CODE (arg) == SSA_NAME)
	{
	  vec_safe_push (path, bbi);
	  /* Recursively follow SSA_NAMEs looking for a constant
	     definition.  */
	  fsm_find_control_statement_thread_paths (arg, visited_bbs, path,
						   seen_loop_phi, speed_p);

	  path->pop ();
	  continue;
	}

      register_jump_thread_path_if_profitable (path, name, arg, bbi, speed_p);
    }
}

/* Return TRUE if STMT is a gimple assignment we want to either directly
   handle or recurse through.  Return FALSE otherwise.

   Note that adding more cases here requires adding cases to handle_assignment
   below.  */

static bool
handle_assignment_p (gimple *stmt)
{
  if (is_gimple_assign (stmt))
    {
      enum tree_code def_code = gimple_assign_rhs_code (stmt);

      /* If the RHS is an SSA_NAME, then we will recurse through it.
	 Go ahead and filter out cases where the SSA_NAME is a default
	 definition.  There's little to be gained by trying to handle that.  */
      if (def_code == SSA_NAME
	  && !SSA_NAME_IS_DEFAULT_DEF (gimple_assign_rhs1 (stmt)))
	return true;

      /* If the RHS is a constant, then it's a terminal that we'll want
	 to handle as well.  */
      if (TREE_CODE_CLASS (def_code) == tcc_constant)
	return true;
    }

  /* Anything not explicitly allowed is not handled.  */
  return false;
}

/* Given STMT which defines NAME in block DEF_BB, recurse through the
   PHI's arguments searching for paths where NAME will ultimately have
   a constant value.

   VISITED_BBS tracks the blocks that have been encountered.

   PATH contains the series of blocks to traverse that will result in
   NAME having a constant value.

   SEEN_LOOP_PHI tracks if we have recursed through a loop PHI node.

   SPEED_P indicates if we are optimizing for speed over space.  */

static void
handle_assignment (gimple *stmt, tree name, basic_block def_bb,
		   hash_set<basic_block> *visited_bbs,
		   vec<basic_block, va_gc> *&path,
		   bool seen_loop_phi, bool speed_p)
{
  tree arg = gimple_assign_rhs1 (stmt);

  if (TREE_CODE (arg) == SSA_NAME)
    fsm_find_control_statement_thread_paths (arg, visited_bbs,
					     path, seen_loop_phi, speed_p);

  else
    {
      /* register_jump_thread_path_if_profitable will push the current
	 block onto the path.  But the path will always have the current
	 block at this point.  So we can just pop it.  */
      path->pop ();

      register_jump_thread_path_if_profitable (path, name, arg, def_bb,
					       speed_p);

      /* And put the current block back onto the path so that the
	 state of the stack is unchanged when we leave.  */
      vec_safe_push (path, def_bb);
    }
}

/* We trace the value of the SSA_NAME NAME back through any phi nodes looking
   for places where it gets a constant value and save the path.

   SPEED_P indicate that we could increase code size to improve the code path */

static void
fsm_find_control_statement_thread_paths (tree name,
					 hash_set<basic_block> *visited_bbs,
					 vec<basic_block, va_gc> *&path,
					 bool seen_loop_phi, bool speed_p)
{
  /* If NAME appears in an abnormal PHI, then don't try to trace its
     value back through PHI nodes.  */
  if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (name))
    return;

  gimple *def_stmt = SSA_NAME_DEF_STMT (name);
  basic_block def_bb = gimple_bb (def_stmt);

  if (def_bb == NULL)
    return;

  /* We allow the SSA chain to contains PHIs and simple copies and constant
     initializations.  */
  if (gimple_code (def_stmt) != GIMPLE_PHI
      && gimple_code (def_stmt) != GIMPLE_ASSIGN)
    return;

  if (gimple_code (def_stmt) == GIMPLE_PHI
      && (gimple_phi_num_args (def_stmt)
	  >= (unsigned) PARAM_VALUE (PARAM_FSM_MAXIMUM_PHI_ARGUMENTS)))
    return;

  if (is_gimple_assign (def_stmt)
      && ! handle_assignment_p (def_stmt))
    return;

  /* Avoid infinite recursion.  */
  if (visited_bbs->add (def_bb))
    return;

  int next_path_length = 0;
  basic_block last_bb_in_path = path->last ();

  if (loop_containing_stmt (def_stmt)->header == gimple_bb (def_stmt))
    {
      /* Do not walk through more than one loop PHI node.  */
      if (seen_loop_phi)
	return;
      seen_loop_phi = true;
    }

  /* Following the chain of SSA_NAME definitions, we jumped from a definition in
     LAST_BB_IN_PATH to a definition in DEF_BB.  When these basic blocks are
     different, append to PATH the blocks from LAST_BB_IN_PATH to DEF_BB.  */
  if (def_bb != last_bb_in_path)
    {
      /* When DEF_BB == LAST_BB_IN_PATH, then the first block in the path
	 will already be in VISITED_BBS.  When they are not equal, then we
	 must ensure that first block is accounted for to ensure we do not
	 create bogus jump threading paths.  */
      visited_bbs->add ((*path)[0]);
      if (!check_subpath_and_update_thread_path (last_bb_in_path, def_bb,
						 visited_bbs, path,
						 &next_path_length))
	return;
    }

  gcc_assert (path->last () == def_bb);

  if (gimple_code (def_stmt) == GIMPLE_PHI)
    handle_phi (as_a <gphi *> (def_stmt), name, def_bb,
		visited_bbs, path, seen_loop_phi, speed_p);
  else if (gimple_code (def_stmt) == GIMPLE_ASSIGN)
    handle_assignment (def_stmt, name, def_bb,
		       visited_bbs, path, seen_loop_phi, speed_p);

  /* Remove all the nodes that we added from NEXT_PATH.  */
  if (next_path_length)
    vec_safe_truncate (path, (path->length () - next_path_length));
}

/* Search backwards from BB looking for paths where NAME (an SSA_NAME)
   is a constant.  Record such paths for jump threading.

   It is assumed that BB ends with a control statement and that by
   finding a path where NAME is a constant, we can thread the path.
   SPEED_P indicate that we could increase code size to improve the code path */

void  
find_jump_threads_backwards (basic_block bb, bool speed_p)
{     
  gimple *stmt = get_gimple_control_stmt (bb);
  if (!stmt)
    return;

  enum gimple_code code = gimple_code (stmt);
  tree name = NULL;
  if (code == GIMPLE_SWITCH)
    name = gimple_switch_index (as_a <gswitch *> (stmt));
  else if (code == GIMPLE_GOTO)
    name = gimple_goto_dest (stmt);
  else if (code == GIMPLE_COND)
    {
      if (TREE_CODE (gimple_cond_lhs (stmt)) == SSA_NAME
	  && TREE_CODE_CLASS (TREE_CODE (gimple_cond_rhs (stmt))) == tcc_constant
	  && (INTEGRAL_TYPE_P (TREE_TYPE (gimple_cond_lhs (stmt)))
	      || POINTER_TYPE_P (TREE_TYPE (gimple_cond_lhs (stmt)))))
	name = gimple_cond_lhs (stmt);
    }

  if (!name || TREE_CODE (name) != SSA_NAME)
    return;

  vec<basic_block, va_gc> *bb_path;
  vec_alloc (bb_path, 10);
  vec_safe_push (bb_path, bb);
  hash_set<basic_block> *visited_bbs = new hash_set<basic_block>;

  max_threaded_paths = PARAM_VALUE (PARAM_MAX_FSM_THREAD_PATHS);
  if (getenv("asdf3"))
    goto doit;
  fsm_find_control_statement_thread_paths (name, visited_bbs, bb_path, false,
					   speed_p);

 doit:
  /* If we didn't thread any paths by chasing down constant
     definitions, try threading by making use of available range
     information.  */
  if (max_threaded_paths == PARAM_VALUE (PARAM_MAX_FSM_THREAD_PATHS))
    {
      paths_with_ranges w (name, bb);
      w.generate ();
      path_with_range p;
      for (unsigned i = 0; w.iterate (i, p); ++i)
	{
	  irange range = p.get_range ();
	  wide_int c;
	  if (range.one_element_p (c))
	    {
	      vec<basic_block, va_gc> *path = p.get_path ();
	      /* register_jump_thread_path_if_profitable will push the current
		 block onto the path.  But the path will always have the current
		 block at this point.  So we can just pop it.  */
	      basic_block def_bb = path->pop ();
	      bool s=speed_p;
	      speed_p=true;
	      register_jump_thread_path_if_profitable
		(path, name, wide_int_to_tree (TREE_TYPE (name), c),
		 def_bb, speed_p);
	      speed_p=s;
	      break;
	    }
	}
    }

  delete visited_bbs;
  vec_free (bb_path);
}

namespace {

const pass_data pass_data_thread_jumps =
{
  GIMPLE_PASS,
  "thread",
  OPTGROUP_NONE,
  TV_TREE_SSA_THREAD_JUMPS,
  ( PROP_cfg | PROP_ssa ),
  0,
  0,
  0,
  TODO_update_ssa,
};

class pass_thread_jumps : public gimple_opt_pass
{
public:
  pass_thread_jumps (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_thread_jumps, ctxt)
  {}

  opt_pass * clone (void) { return new pass_thread_jumps (m_ctxt); }
  virtual bool gate (function *);
  virtual unsigned int execute (function *);
};

bool
pass_thread_jumps::gate (function *fun ATTRIBUTE_UNUSED)
{
  return flag_expensive_optimizations;
}


unsigned int
pass_thread_jumps::execute (function *fun)
{
  loop_optimizer_init (LOOPS_HAVE_PREHEADERS | LOOPS_HAVE_SIMPLE_LATCHES);

  /* Try to thread each block with more than one successor.  */
  basic_block bb;
  FOR_EACH_BB_FN (bb, fun)
    {
      if (EDGE_COUNT (bb->succs) > 1)
	find_jump_threads_backwards (bb, true);
    }
  bool changed = thread_through_all_blocks (true);

  loop_optimizer_finalize ();
  return changed ? TODO_cleanup_cfg : 0;
}

}

gimple_opt_pass *
make_pass_thread_jumps (gcc::context *ctxt)
{
  return new pass_thread_jumps (ctxt);
}

namespace {

const pass_data pass_data_early_thread_jumps =
{
  GIMPLE_PASS,
  "ethread",
  OPTGROUP_NONE,
  TV_TREE_SSA_THREAD_JUMPS,
  ( PROP_cfg | PROP_ssa ),
  0,
  0,
  0,
  ( TODO_cleanup_cfg | TODO_update_ssa ),
};

class pass_early_thread_jumps : public gimple_opt_pass
{
public:
  pass_early_thread_jumps (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_early_thread_jumps, ctxt)
  {}

  opt_pass * clone (void) { return new pass_early_thread_jumps (m_ctxt); }
  virtual bool gate (function *);
  virtual unsigned int execute (function *);
};

bool
pass_early_thread_jumps::gate (function *fun ATTRIBUTE_UNUSED)
{
  return true;
}


unsigned int
pass_early_thread_jumps::execute (function *fun)
{
  loop_optimizer_init (AVOID_CFG_MODIFICATIONS);

  /* Try to thread each block with more than one successor.  */
  basic_block bb;
  FOR_EACH_BB_FN (bb, fun)
    {
      if (EDGE_COUNT (bb->succs) > 1)
	find_jump_threads_backwards (bb, false);
    }
  thread_through_all_blocks (true);

  loop_optimizer_finalize ();
  return 0;
}

}

gimple_opt_pass *
make_pass_early_thread_jumps (gcc::context *ctxt)
{
  return new pass_early_thread_jumps (ctxt);
}
