/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */
/* { dg-additional-options "-fno-trapping-math" } */

#include "test_sve_acle.h"

/*
** max_f32_m_tied1:
**	fmax	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_m_tied1, svfloat32_t,
		z0 = svmax_f32_m (p0, z0, z1),
		z0 = svmax_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (max_f32_m_tied2, svfloat32_t,
		z1 = svmax_f32_m (p0, z0, z1),
		z1 = svmax_m (p0, z0, z1))

/*
** max_f32_m_untied:
**	movprfx	z0, z1
**	fmax	z0\.s, p0/m, z0\.s, z2\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_m_untied, svfloat32_t,
		z0 = svmax_f32_m (p0, z1, z2),
		z0 = svmax_m (p0, z1, z2))

/*
** max_w0_f32_m_tied1:
**	mov	(z[0-9]+\.s), w0
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_m_tied1, svfloat32_t, float,
		 z0 = svmax_n_f32_m (p0, z0, x0),
		 z0 = svmax_m (p0, z0, x0))

/*
** max_w0_f32_m_untied:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0, z1
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_m_untied, svfloat32_t, float,
		 z0 = svmax_n_f32_m (p0, z1, x0),
		 z0 = svmax_m (p0, z1, x0))

/*
** max_s0_f32_m_tied1:
**	mov	(z[0-9]+\.s), s0
**	fmax	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_m_tied1, svfloat32_t, float,
		 z1 = svmax_n_f32_m (p0, z1, d0),
		 z1 = svmax_m (p0, z1, d0))

/*
** max_s0_f32_m_untied:
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1, z2
**	fmax	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_m_untied, svfloat32_t, float,
		 z1 = svmax_n_f32_m (p0, z2, d0),
		 z1 = svmax_m (p0, z2, d0))

/*
** max_1_f32_m_tied1:
**	fmov	(z[0-9]+\.s), #1.0(e\+0)?
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_m_tied1, svfloat32_t,
		z0 = svmax_n_f32_m (p0, z0, 1),
		z0 = svmax_m (p0, z0, 1))

/*
** max_1_f32_m_untied:
**	fmov	(z[0-9]+\.s), #1.0(e\+0)?
**	movprfx	z0, z1
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_m_untied, svfloat32_t,
		z0 = svmax_n_f32_m (p0, z1, 1),
		z0 = svmax_m (p0, z1, 1))

/*
** max_f32_z_tied1:
**	movprfx	z0\.s, p0/z, z0\.s
**	fmax	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_z_tied1, svfloat32_t,
		z0 = svmax_f32_z (p0, z0, z1),
		z0 = svmax_z (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (max_f32_z_tied2, svfloat32_t,
		z1 = svmax_f32_z (p0, z0, z1),
		z1 = svmax_z (p0, z0, z1))

/*
** max_f32_z_untied:
**	movprfx	z0\.s, p0/z, z1\.s
**	fmax	z0\.s, p0/m, z0\.s, z2\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_z_untied, svfloat32_t,
		z0 = svmax_f32_z (p0, z1, z2),
		z0 = svmax_z (p0, z1, z2))

/*
** max_w0_f32_z_tied1:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, z0\.s
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_z_tied1, svfloat32_t, float,
		 z0 = svmax_n_f32_z (p0, z0, x0),
		 z0 = svmax_z (p0, z0, x0))

/*
** max_w0_f32_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, z1\.s
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_z_untied, svfloat32_t, float,
		 z0 = svmax_n_f32_z (p0, z1, x0),
		 z0 = svmax_z (p0, z1, x0))

/*
** max_s0_f32_z_tied1:
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1\.s, p0/z, z1\.s
**	fmax	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_z_tied1, svfloat32_t, float,
		 z1 = svmax_n_f32_z (p0, z1, d0),
		 z1 = svmax_z (p0, z1, d0))

/*
** max_s0_f32_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1\.s, p0/z, z2\.s
**	fmax	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_z_untied, svfloat32_t, float,
		 z1 = svmax_n_f32_z (p0, z2, d0),
		 z1 = svmax_z (p0, z2, d0))

/*
** max_1_f32_z_tied1:
**	fmov	(z[0-9]+\.s), #1.0(e\+0)?
**	movprfx	z0\.s, p0/z, z0\.s
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_z_tied1, svfloat32_t,
		z0 = svmax_n_f32_z (p0, z0, 1),
		z0 = svmax_z (p0, z0, 1))

/*
** max_1_f32_z_untied: { xfail *-*-* }
**	fmov	(z[0-9]+\.s), #1.0(e\+0)?
**	movprfx	z0\.s, p0/z, z1\.s
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_z_untied, svfloat32_t,
		z0 = svmax_n_f32_z (p0, z1, 1),
		z0 = svmax_z (p0, z1, 1))

/*
** max_f32_x_tied1:
**	fmax	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_x_tied1, svfloat32_t,
		z0 = svmax_f32_x (p0, z0, z1),
		z0 = svmax_x (p0, z0, z1))

/*
** max_f32_x_tied2:
**	fmax	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_x_tied2, svfloat32_t,
		z1 = svmax_f32_x (p0, z0, z1),
		z1 = svmax_x (p0, z0, z1))

/*
** max_f32_x_untied:
**	movprfx	z2, z0
**	fmax	z2\.s, p0/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (max_f32_x_untied, svfloat32_t,
		z2 = svmax_f32_x (p0, z0, z1),
		z2 = svmax_x (p0, z0, z1))

/*
** max_w0_f32_x_tied1:
**	mov	(z[0-9]+\.s), w0
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_x_tied1, svfloat32_t, float,
		 z0 = svmax_n_f32_x (p0, z0, x0),
		 z0 = svmax_x (p0, z0, x0))

/*
** max_w0_f32_x_untied:
**	mov	z1\.s, w0
**	fmax	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_ZS (max_w0_f32_x_untied, svfloat32_t, float,
		 z1 = svmax_n_f32_x (p0, z0, x0),
		 z1 = svmax_x (p0, z0, x0))

/*
** max_s0_f32_x_tied1:
**	mov	(z[0-9]+\.s), s0
**	fmax	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_x_tied1, svfloat32_t, float,
		 z1 = svmax_n_f32_x (p0, z1, d0),
		 z1 = svmax_x (p0, z1, d0))

/*
** max_s0_f32_x_untied:
**	mov	z2\.s, s0
**	fmax	z2\.s, p0/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_ZS (max_s0_f32_x_untied, svfloat32_t, float,
		 z2 = svmax_n_f32_x (p0, z1, d0),
		 z2 = svmax_x (p0, z1, d0))

/*
** max_1_f32_x_tied1:
**	fmov	(z[0-9]+\.s), #1.0(e\+0)?
**	fmax	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_x_tied1, svfloat32_t,
		z0 = svmax_n_f32_x (p0, z0, 1),
		z0 = svmax_x (p0, z0, 1))

/*
** max_1_f32_x_untied:
**	fmov	z0\.s, #1.0(e\+0)?
**	fmax	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (max_1_f32_x_untied, svfloat32_t,
		z0 = svmax_n_f32_x (p0, z1, 1),
		z0 = svmax_x (p0, z1, 1))

/*
** ptrue_max_f32_x_tied1:
**	ptrue	(p[0-7])\.s[^\n]*
**	fmax	z0\.s, \1/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (ptrue_max_f32_x_tied1, svfloat32_t,
		z0 = svmax_f32_x (svptrue_b32 (), z0, z1),
		z0 = svmax_x (svptrue_b32 (), z0, z1))

/*
** ptrue_max_f32_x_tied2:
**	ptrue	(p[0-7])\.s[^\n]*
**	fmax	z1\.s, \1/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (ptrue_max_f32_x_tied2, svfloat32_t,
		z1 = svmax_f32_x (svptrue_b32 (), z0, z1),
		z1 = svmax_x (svptrue_b32 (), z0, z1))

/*
** ptrue_max_f32_x_untied:
**	ptrue	(p[0-7])\.s[^\n]*
**	movprfx	z2, z0
**	fmax	z2\.s, \1/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (ptrue_max_f32_x_untied, svfloat32_t,
		z2 = svmax_f32_x (svptrue_b32 (), z0, z1),
		z2 = svmax_x (svptrue_b32 (), z0, z1))
