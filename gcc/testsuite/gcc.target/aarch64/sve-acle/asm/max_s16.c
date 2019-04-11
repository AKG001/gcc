/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** max_s16_m_tied1:
**	smax	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_m_tied1, svint16_t,
		z0 = svmax_s16_m (p0, z0, z1),
		z0 = svmax_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (max_s16_m_tied2, svint16_t,
		z1 = svmax_s16_m (p0, z0, z1),
		z1 = svmax_m (p0, z0, z1))

/*
** max_s16_m_untied:
**	movprfx	z0, z1
**	smax	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_m_untied, svint16_t,
		z0 = svmax_s16_m (p0, z1, z2),
		z0 = svmax_m (p0, z1, z2))

/*
** max_w0_s16_m_tied1:
**	mov	(z[0-9]+\.h), w0
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_m_tied1, svint16_t, int16_t,
		 z0 = svmax_n_s16_m (p0, z0, x0),
		 z0 = svmax_m (p0, z0, x0))

/*
** max_w0_s16_m_untied:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0, z1
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_m_untied, svint16_t, int16_t,
		 z0 = svmax_n_s16_m (p0, z1, x0),
		 z0 = svmax_m (p0, z1, x0))

/*
** max_h4_s16_m_tied1:
**	mov	(z[0-9]+\.h), h4
**	smax	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_m_tied1, svint16_t, int16_t,
		 z1 = svmax_n_s16_m (p0, z1, d4),
		 z1 = svmax_m (p0, z1, d4))

/*
** max_h4_s16_m_untied:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1, z2
**	smax	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_m_untied, svint16_t, int16_t,
		 z1 = svmax_n_s16_m (p0, z2, d4),
		 z1 = svmax_m (p0, z2, d4))

/*
** max_1_s16_m_tied1:
**	mov	(z[0-9]+\.h), #1
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_m_tied1, svint16_t,
		z0 = svmax_n_s16_m (p0, z0, 1),
		z0 = svmax_m (p0, z0, 1))

/*
** max_1_s16_m_untied:
**	mov	(z[0-9]+\.h), #1
**	movprfx	z0, z1
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_m_untied, svint16_t,
		z0 = svmax_n_s16_m (p0, z1, 1),
		z0 = svmax_m (p0, z1, 1))

/*
** max_m1_s16_m:
**	mov	(z[0-9]+)\.b, #(-1|255)
**	smax	z0\.h, p0/m, z0\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (max_m1_s16_m, svint16_t,
		z0 = svmax_n_s16_m (p0, z0, -1),
		z0 = svmax_m (p0, z0, -1))

/*
** max_s16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	smax	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_z_tied1, svint16_t,
		z0 = svmax_s16_z (p0, z0, z1),
		z0 = svmax_z (p0, z0, z1))

/*
** max_s16_z_tied2:
**	movprfx	z1\.h, p0/z, z1\.h
**	smax	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_z_tied2, svint16_t,
		z1 = svmax_s16_z (p0, z0, z1),
		z1 = svmax_z (p0, z0, z1))

/*
** max_s16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	smax	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_z_untied, svint16_t,
		z0 = svmax_s16_z (p0, z1, z2),
		z0 = svmax_z (p0, z1, z2))

/*
** max_w0_s16_z_tied1:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z0\.h
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_z_tied1, svint16_t, int16_t,
		 z0 = svmax_n_s16_z (p0, z0, x0),
		 z0 = svmax_z (p0, z0, x0))

/*
** max_w0_s16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z1\.h
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_z_untied, svint16_t, int16_t,
		 z0 = svmax_n_s16_z (p0, z1, x0),
		 z0 = svmax_z (p0, z1, x0))

/*
** max_h4_s16_z_tied1:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1\.h, p0/z, z1\.h
**	smax	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_z_tied1, svint16_t, int16_t,
		 z1 = svmax_n_s16_z (p0, z1, d4),
		 z1 = svmax_z (p0, z1, d4))

/*
** max_h4_s16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1\.h, p0/z, z2\.h
**	smax	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_z_untied, svint16_t, int16_t,
		 z1 = svmax_n_s16_z (p0, z2, d4),
		 z1 = svmax_z (p0, z2, d4))

/*
** max_1_s16_z_tied1:
**	mov	(z[0-9]+\.h), #1
**	movprfx	z0\.h, p0/z, z0\.h
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_z_tied1, svint16_t,
		z0 = svmax_n_s16_z (p0, z0, 1),
		z0 = svmax_z (p0, z0, 1))

/*
** max_1_s16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), #1
**	movprfx	z0\.h, p0/z, z1\.h
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_z_untied, svint16_t,
		z0 = svmax_n_s16_z (p0, z1, 1),
		z0 = svmax_z (p0, z1, 1))

/*
** max_s16_x_tied1:
**	smax	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_x_tied1, svint16_t,
		z0 = svmax_s16_x (p0, z0, z1),
		z0 = svmax_x (p0, z0, z1))

/*
** max_s16_x_tied2:
**	smax	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_x_tied2, svint16_t,
		z1 = svmax_s16_x (p0, z0, z1),
		z1 = svmax_x (p0, z0, z1))

/*
** max_s16_x_untied:
**	movprfx	z2, z0
**	smax	z2\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (max_s16_x_untied, svint16_t,
		z2 = svmax_s16_x (p0, z0, z1),
		z2 = svmax_x (p0, z0, z1))

/*
** max_w0_s16_x_tied1:
**	mov	(z[0-9]+\.h), w0
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_x_tied1, svint16_t, int16_t,
		 z0 = svmax_n_s16_x (p0, z0, x0),
		 z0 = svmax_x (p0, z0, x0))

/*
** max_w0_s16_x_untied:
**	mov	z1\.h, w0
**	smax	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_ZS (max_w0_s16_x_untied, svint16_t, int16_t,
		 z1 = svmax_n_s16_x (p0, z0, x0),
		 z1 = svmax_x (p0, z0, x0))

/*
** max_h4_s16_x_tied1:
**	mov	(z[0-9]+\.h), h4
**	smax	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_x_tied1, svint16_t, int16_t,
		 z1 = svmax_n_s16_x (p0, z1, d4),
		 z1 = svmax_x (p0, z1, d4))

/*
** max_h4_s16_x_untied:
**	mov	z2\.h, h4
**	smax	z2\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (max_h4_s16_x_untied, svint16_t, int16_t,
		 z2 = svmax_n_s16_x (p0, z1, d4),
		 z2 = svmax_x (p0, z1, d4))

/*
** max_1_s16_x_tied1:
**	mov	(z[0-9]+\.h), #1
**	smax	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_x_tied1, svint16_t,
		z0 = svmax_n_s16_x (p0, z0, 1),
		z0 = svmax_x (p0, z0, 1))

/*
** max_1_s16_x_untied:
**	mov	z0\.h, #1
**	smax	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (max_1_s16_x_untied, svint16_t,
		z0 = svmax_n_s16_x (p0, z1, 1),
		z0 = svmax_x (p0, z1, 1))
