/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** addv_x0_s64:
**	uaddv	(d[0-9]+), p0, z0\.d
**	fmov	x0, \1
**	ret
*/
TEST_REDUCTION_X (addv_x0_s64, int64_t, svint64_t,
		  x0 = svaddv_s64 (p0, z0),
		  x0 = svaddv (p0, z0))

/*
** addv_d0_s64_tied:
**	uaddv	d0, p0, z0\.d
**	ret
*/
TEST_REDUCTION_D (addv_d0_s64_tied, int64_t, svint64_t,
		  d0 = svaddv_s64 (p0, z0),
		  d0 = svaddv (p0, z0))

/*
** addv_d0_s64_untied:
**	uaddv	d0, p0, z1\.d
**	ret
*/
TEST_REDUCTION_D (addv_d0_s64_untied, int64_t, svint64_t,
		  d0 = svaddv_s64 (p0, z1),
		  d0 = svaddv (p0, z1))
