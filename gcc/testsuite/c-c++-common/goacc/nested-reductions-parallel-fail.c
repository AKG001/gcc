/* Test erroneous cases of nested reduction loops in parallel regions.  See
   also corresponding tests in nested-reductions-kernels-fail.c and
   nested-reductions-serial-fail.c.  */

void acc_parallel (void)
{
  int i, j, k, l, sum, diff;

  #pragma acc parallel
  {
    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop collapse(2) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum) reduction(-:diff)
    for (i = 0; i < 10; i++)
      {
        #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(+:sum)
          for (k = 0; k < 10; k++)
            sum = 1;

        #pragma acc loop reduction(+:sum) // { dg-error "nested loop in reduction needs reduction clause for .diff." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(-:diff)
          for (k = 0; k < 10; k++)
            diff = 1;
      }
  }
}

/* The same tests as above, but using a combined parallel loop construct.  */

void acc_parallel_loop (void)
{
  int i, j, k, l, sum, diff;

  #pragma acc parallel loop
  for (int h = 0; h < 10; ++h)
  {
    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop collapse(2) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum) reduction(-:diff)
    for (i = 0; i < 10; i++)
      {
        #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(+:sum)
          for (k = 0; k < 10; k++)
            sum = 1;

        #pragma acc loop reduction(+:sum) // { dg-error "nested loop in reduction needs reduction clause for .diff." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(-:diff)
          for (k = 0; k < 10; k++)
            diff = 1;
      }
  }
}

/* The same tests as above, but now the outermost reduction clause is on
   the parallel region, not the outermost loop.  */
void acc_parallel_reduction (void)
{
  int i, j, k, l, sum, diff;

  #pragma acc parallel reduction(+:sum)
  {
    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop collapse(2) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(max:sum) // { dg-error "conflicting reduction operations for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(max:sum) // { dg-error "conflicting reduction operations for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      {
        #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(+:sum)
          for (k = 0; k < 10; k++)
            sum = 1;

        #pragma acc loop reduction(+:sum) // { dg-error "nested loop in reduction needs reduction clause for .diff." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(-:diff)
          for (k = 0; k < 10; k++)
            diff = 1;
      }
  }
}

/* The same tests as above, but using a combined parallel loop construct, and
   the outermost reduction clause is on that one, not the outermost loop.  */
void acc_parallel_loop_reduction (void)
{
  int i, j, k, l, sum, diff;

  #pragma acc parallel loop reduction(+:sum)
  for (int h = 0; h < 10; ++h)
  {
    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop collapse(2) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(max:sum) // { dg-error "conflicting reduction operations for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(max:sum) // { dg-error "conflicting reduction operations for .sum." }
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
    for (i = 0; i < 10; i++)
      {
        #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(+:sum)
          for (k = 0; k < 10; k++)
            sum = 1;

        #pragma acc loop reduction(+:sum) // { dg-error "nested loop in reduction needs reduction clause for .diff." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(-:diff)
          for (k = 0; k < 10; k++)
            diff = 1;
      }
  }
}

/* The same tests as above, but inside a routine construct.  */
#pragma acc routine gang
void acc_routine (void)
{
  int i, j, k, l, sum, diff;

  {
    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop collapse(2) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
          #pragma acc loop reduction(+:sum)
          for (l = 0; l < 10; l++)
            sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
        for (k = 0; k < 10; k++)
          sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum)
    for (i = 0; i < 10; i++)
      #pragma acc loop reduction(-:sum) // { dg-error "conflicting reduction operations for .sum." }
      for (j = 0; j < 10; j++)
        #pragma acc loop reduction(+:sum)
        for (k = 0; k < 10; k++)
	  #pragma acc loop reduction(*:sum) // { dg-error "conflicting reduction operations for .sum." }
	  for (l = 0; l < 10; l++)
	    sum = 1;

    #pragma acc loop reduction(+:sum) reduction(-:diff)
    for (i = 0; i < 10; i++)
      {
        #pragma acc loop reduction(-:diff) // { dg-error "nested loop in reduction needs reduction clause for .sum." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(+:sum)
          for (k = 0; k < 10; k++)
            sum = 1;

        #pragma acc loop reduction(+:sum) // { dg-error "nested loop in reduction needs reduction clause for .diff." }
        for (j = 0; j < 10; j++)
          #pragma acc loop reduction(-:diff)
          for (k = 0; k < 10; k++)
            diff = 1;
      }
  }
}
