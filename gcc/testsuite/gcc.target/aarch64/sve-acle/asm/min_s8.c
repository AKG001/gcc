/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** min_s8_m_tied1:
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_m_tied1, svint8_t,
		z0 = svmin_s8_m (p0, z0, z1),
		z0 = svmin_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (min_s8_m_tied2, svint8_t,
		z0 = svmin_s8_m (p0, z1, z0),
		z0 = svmin_m (p0, z1, z0))

/*
** min_s8_m_untied:
**	movprfx	z0, z1
**	smin	z0\.b, p0/m, z0\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_m_untied, svint8_t,
		z0 = svmin_s8_m (p0, z1, z2),
		z0 = svmin_m (p0, z1, z2))

/*
** min_w0_s8_m_tied1:
**	mov	(z[0-9]+\.b), w0
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_m_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_m (p0, z0, x0),
		 z0 = svmin_m (p0, z0, x0))

/*
** min_w0_s8_m_untied:
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0, z1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_m_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_m (p0, z1, x0),
		 z0 = svmin_m (p0, z1, x0))

/*
** min_b4_s8_m_tied1:
**	mov	(z[0-9]+\.b), b4
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_m_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_m (p0, z0, d4),
		 z0 = svmin_m (p0, z0, d4))

/*
** min_b4_s8_m_untied:
**	mov	(z[0-9]+\.b), b4
**	movprfx	z0, z1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_m_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_m (p0, z1, d4),
		 z0 = svmin_m (p0, z1, d4))

/*
** min_1_s8_m_tied1:
**	mov	(z[0-9]+\.b), #1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_m_tied1, svint8_t,
		z0 = svmin_n_s8_m (p0, z0, 1),
		z0 = svmin_m (p0, z0, 1))

/*
** min_1_s8_m_untied:
**	mov	(z[0-9]+\.b), #1
**	movprfx	z0, z1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_m_untied, svint8_t,
		z0 = svmin_n_s8_m (p0, z1, 1),
		z0 = svmin_m (p0, z1, 1))

/*
** min_m1_s8_m:
**	mov	(z[0-9]+\.b), #-1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_m1_s8_m, svint8_t,
		z0 = svmin_n_s8_m (p0, z0, -1),
		z0 = svmin_m (p0, z0, -1))

/*
** min_s8_z_tied1:
**	movprfx	z0\.b, p0/z, z0\.b
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_z_tied1, svint8_t,
		z0 = svmin_s8_z (p0, z0, z1),
		z0 = svmin_z (p0, z0, z1))

/*
** min_s8_z_tied2:
**	movprfx	z0\.b, p0/z, z0\.b
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_z_tied2, svint8_t,
		z0 = svmin_s8_z (p0, z1, z0),
		z0 = svmin_z (p0, z1, z0))

/*
** min_s8_z_untied:
**	movprfx	z0\.b, p0/z, z1\.b
**	smin	z0\.b, p0/m, z0\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_z_untied, svint8_t,
		z0 = svmin_s8_z (p0, z1, z2),
		z0 = svmin_z (p0, z1, z2))

/*
** min_w0_s8_z_tied1:
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0\.b, p0/z, z0\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_z_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_z (p0, z0, x0),
		 z0 = svmin_z (p0, z0, x0))

/*
** min_w0_s8_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0\.b, p0/z, z1\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_z_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_z (p0, z1, x0),
		 z0 = svmin_z (p0, z1, x0))

/*
** min_b4_s8_z_tied1:
**	mov	(z[0-9]+\.b), b4
**	movprfx	z0\.b, p0/z, z0\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_z_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_z (p0, z0, d4),
		 z0 = svmin_z (p0, z0, d4))

/*
** min_b4_s8_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.b), b4
**	movprfx	z0\.b, p0/z, z1\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_z_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_z (p0, z1, d4),
		 z0 = svmin_z (p0, z1, d4))

/*
** min_1_s8_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.b), #1
**	movprfx	z0\.b, p0/z, z1\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_z_untied, svint8_t,
		z0 = svmin_n_s8_z (p0, z1, 1),
		z0 = svmin_z (p0, z1, 1))

/*
** min_1_s8_z_tied1:
**	mov	(z[0-9]+\.b), #1
**	movprfx	z0\.b, p0/z, z0\.b
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_z_tied1, svint8_t,
		z0 = svmin_n_s8_z (p0, z0, 1),
		z0 = svmin_z (p0, z0, 1))

/*
** min_s8_x_tied1:
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_x_tied1, svint8_t,
		z0 = svmin_s8_x (p0, z0, z1),
		z0 = svmin_x (p0, z0, z1))

/*
** min_s8_x_tied2:
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_x_tied2, svint8_t,
		z0 = svmin_s8_x (p0, z1, z0),
		z0 = svmin_x (p0, z1, z0))

/*
** min_s8_x_untied:
**	movprfx	z0, z1
**	smin	z0\.b, p0/m, z0\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (min_s8_x_untied, svint8_t,
		z0 = svmin_s8_x (p0, z1, z2),
		z0 = svmin_x (p0, z1, z2))

/*
** min_w0_s8_x_tied1:
**	mov	(z[0-9]+\.b), w0
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_x_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_x (p0, z0, x0),
		 z0 = svmin_x (p0, z0, x0))

/*
** min_w0_s8_x_untied:
**	mov	z0\.b, w0
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_ZS (min_w0_s8_x_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_x (p0, z1, x0),
		 z0 = svmin_x (p0, z1, x0))

/*
** min_b4_s8_x_tied1:
**	mov	(z[0-9]+\.b), b4
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_x_tied1, svint8_t, int8_t,
		 z0 = svmin_n_s8_x (p0, z0, d4),
		 z0 = svmin_x (p0, z0, d4))

/*
** min_b4_s8_x_untied:
**	mov	z0\.b, b4
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_ZS (min_b4_s8_x_untied, svint8_t, int8_t,
		 z0 = svmin_n_s8_x (p0, z1, d4),
		 z0 = svmin_x (p0, z1, d4))

/*
** min_1_s8_x_tied1:
**	mov	(z[0-9]+\.b), #1
**	smin	z0\.b, p0/m, z0\.b, \1
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_x_tied1, svint8_t,
		z0 = svmin_n_s8_x (p0, z0, 1),
		z0 = svmin_x (p0, z0, 1))

/*
** min_1_s8_x_untied:
**	mov	z0\.b, #1
**	smin	z0\.b, p0/m, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (min_1_s8_x_untied, svint8_t,
		z0 = svmin_n_s8_x (p0, z1, 1),
		z0 = svmin_x (p0, z1, 1))
