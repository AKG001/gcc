/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** lsr_wide_u8_m_tied1:
**	lsr	z0\.b, p0/m, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_m_tied1, svuint8_t,
	     z0 = svlsr_wide_u8_m (p0, z0, z16),
	     z0 = svlsr_wide_m (p0, z0, z16))

/*
** lsr_wide_u8_m_tied2:
**	mov	(z[0-9]+\.d), z16\.d
**	movprfx	z16, z0
**	lsr	z16\.b, p0/m, z16\.b, \1
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_m_tied2, svuint8_t,
	     z16_res = svlsr_wide_u8_m (p0, z0, z16),
	     z16_res = svlsr_wide_m (p0, z0, z16))

/*
** lsr_wide_u8_m_untied:
**	movprfx	z0, z1
**	lsr	z0\.b, p0/m, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_m_untied, svuint8_t,
	     z0 = svlsr_wide_u8_m (p0, z1, z16),
	     z0 = svlsr_wide_m (p0, z1, z16))

/*
** lsr_wide_u8_z_tied1:
**	movprfx	z0\.b, p0/z, z0\.b
**	lsr	z0\.b, p0/m, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_z_tied1, svuint8_t,
	     z0 = svlsr_wide_u8_z (p0, z0, z16),
	     z0 = svlsr_wide_z (p0, z0, z16))

/*
** lsr_wide_u8_z_tied2:
**	mov	(z[0-9]+\.d), z16\.d
**	movprfx	z16\.b, p0/z, z0\.b
**	lsr	z16\.b, p0/m, z16\.b, \1
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_z_tied2, svuint8_t,
	     z16_res = svlsr_wide_u8_z (p0, z0, z16),
	     z16_res = svlsr_wide_z (p0, z0, z16))

/*
** lsr_wide_u8_z_untied:
**	movprfx	z0\.b, p0/z, z1\.b
**	lsr	z0\.b, p0/m, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_z_untied, svuint8_t,
	     z0 = svlsr_wide_u8_z (p0, z1, z16),
	     z0 = svlsr_wide_z (p0, z1, z16))

/*
** lsr_wide_u8_x_tied1:
**	lsr	z0\.b, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_x_tied1, svuint8_t,
	     z0 = svlsr_wide_u8_x (p0, z0, z16),
	     z0 = svlsr_wide_x (p0, z0, z16))

/*
** lsr_wide_u8_x_tied2:
**	lsr	z16\.b, z0\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_x_tied2, svuint8_t,
	     z16_res = svlsr_wide_u8_x (p0, z0, z16),
	     z16_res = svlsr_wide_x (p0, z0, z16))

/*
** lsr_wide_u8_x_untied:
**	lsr	z0\.b, z1\.b, z16\.d
**	ret
*/
TEST_WIDE_Z (lsr_wide_u8_x_untied, svuint8_t,
	     z0 = svlsr_wide_u8_x (p0, z1, z16),
	     z0 = svlsr_wide_x (p0, z1, z16))
