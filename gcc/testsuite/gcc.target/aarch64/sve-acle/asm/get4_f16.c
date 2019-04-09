/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** get4_f16_z0_0:
**	mov	z0\.d, z16\.d
**	ret
*/
TEST_GET (get4_f16_z0_0, svfloat16x4_t, svfloat16_t,
	  z0 = svget4_f16 (z16, 0),
	  z0 = svget4 (z16, 0))

/*
** get4_f16_z0_1:
**	mov	z0\.d, z17\.d
**	ret
*/
TEST_GET (get4_f16_z0_1, svfloat16x4_t, svfloat16_t,
	  z0 = svget4_f16 (z16, 1),
	  z0 = svget4 (z16, 1))

/*
** get4_f16_z0_2:
**	mov	z0\.d, z18\.d
**	ret
*/
TEST_GET (get4_f16_z0_2, svfloat16x4_t, svfloat16_t,
	  z0 = svget4_f16 (z16, 2),
	  z0 = svget4 (z16, 2))

/*
** get4_f16_z0_3:
**	mov	z0\.d, z19\.d
**	ret
*/
TEST_GET (get4_f16_z0_3, svfloat16x4_t, svfloat16_t,
	  z0 = svget4_f16 (z16, 3),
	  z0 = svget4 (z16, 3))

/*
** get4_f16_z16_0:
**	ret
*/
TEST_GET (get4_f16_z16_0, svfloat16x4_t, svfloat16_t,
	  z16_res = svget4_f16 (z16, 0),
	  z16_res = svget4 (z16, 0))

/*
** get4_f16_z16_1:
**	mov	z16\.d, z17\.d
**	ret
*/
TEST_GET (get4_f16_z16_1, svfloat16x4_t, svfloat16_t,
	  z16_res = svget4_f16 (z16, 1),
	  z16_res = svget4 (z16, 1))

/*
** get4_f16_z16_2:
**	mov	z16\.d, z18\.d
**	ret
*/
TEST_GET (get4_f16_z16_2, svfloat16x4_t, svfloat16_t,
	  z16_res = svget4_f16 (z16, 2),
	  z16_res = svget4 (z16, 2))

/*
** get4_f16_z16_3:
**	mov	z16\.d, z19\.d
**	ret
*/
TEST_GET (get4_f16_z16_3, svfloat16x4_t, svfloat16_t,
	  z16_res = svget4_f16 (z16, 3),
	  z16_res = svget4 (z16, 3))

/*
** get4_f16_z17_0:
**	mov	z17\.d, z16\.d
**	ret
*/
TEST_GET (get4_f16_z17_0, svfloat16x4_t, svfloat16_t,
	  z17_res = svget4_f16 (z16, 0),
	  z17_res = svget4 (z16, 0))

/*
** get4_f16_z17_1:
**	ret
*/
TEST_GET (get4_f16_z17_1, svfloat16x4_t, svfloat16_t,
	  z17_res = svget4_f16 (z16, 1),
	  z17_res = svget4 (z16, 1))

/*
** get4_f16_z17_2:
**	mov	z17\.d, z18\.d
**	ret
*/
TEST_GET (get4_f16_z17_2, svfloat16x4_t, svfloat16_t,
	  z17_res = svget4_f16 (z16, 2),
	  z17_res = svget4 (z16, 2))

/*
** get4_f16_z17_3:
**	mov	z17\.d, z19\.d
**	ret
*/
TEST_GET (get4_f16_z17_3, svfloat16x4_t, svfloat16_t,
	  z17_res = svget4_f16 (z16, 3),
	  z17_res = svget4 (z16, 3))

/*
** get4_f16_z18_0:
**	mov	z18\.d, z16\.d
**	ret
*/
TEST_GET (get4_f16_z18_0, svfloat16x4_t, svfloat16_t,
	  z18_res = svget4_f16 (z16, 0),
	  z18_res = svget4 (z16, 0))

/*
** get4_f16_z18_1:
**	mov	z18\.d, z17\.d
**	ret
*/
TEST_GET (get4_f16_z18_1, svfloat16x4_t, svfloat16_t,
	  z18_res = svget4_f16 (z16, 1),
	  z18_res = svget4 (z16, 1))

/*
** get4_f16_z18_2:
**	ret
*/
TEST_GET (get4_f16_z18_2, svfloat16x4_t, svfloat16_t,
	  z18_res = svget4_f16 (z16, 2),
	  z18_res = svget4 (z16, 2))

/*
** get4_f16_z18_3:
**	mov	z18\.d, z19\.d
**	ret
*/
TEST_GET (get4_f16_z18_3, svfloat16x4_t, svfloat16_t,
	  z18_res = svget4_f16 (z16, 3),
	  z18_res = svget4 (z16, 3))

/*
** get4_f16_z19_0:
**	mov	z19\.d, z16\.d
**	ret
*/
TEST_GET (get4_f16_z19_0, svfloat16x4_t, svfloat16_t,
	  z19_res = svget4_f16 (z16, 0),
	  z19_res = svget4 (z16, 0))

/*
** get4_f16_z19_1:
**	mov	z19\.d, z17\.d
**	ret
*/
TEST_GET (get4_f16_z19_1, svfloat16x4_t, svfloat16_t,
	  z19_res = svget4_f16 (z16, 1),
	  z19_res = svget4 (z16, 1))

/*
** get4_f16_z19_2:
**	mov	z19\.d, z18\.d
**	ret
*/
TEST_GET (get4_f16_z19_2, svfloat16x4_t, svfloat16_t,
	  z19_res = svget4_f16 (z16, 2),
	  z19_res = svget4 (z16, 2))

/*
** get4_f16_z19_3:
**	ret
*/
TEST_GET (get4_f16_z19_3, svfloat16x4_t, svfloat16_t,
	  z19_res = svget4_f16 (z16, 3),
	  z19_res = svget4 (z16, 3))
