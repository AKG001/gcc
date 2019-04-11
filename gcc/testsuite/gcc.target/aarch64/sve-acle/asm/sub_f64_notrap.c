/* { dg-do compile } */
/* { dg-additional-options "-fno-trapping-math" } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** sub_f64_m_tied1:
**	fsub	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_m_tied1, svfloat64_t,
		z0 = svsub_f64_m (p0, z0, z1),
		z0 = svsub_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (sub_f64_m_tied2, svfloat64_t,
		z0 = svsub_f64_m (p0, z1, z0),
		z0 = svsub_m (p0, z1, z0))

/*
** sub_f64_m_untied:
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_m_untied, svfloat64_t,
		z0 = svsub_f64_m (p0, z1, z2),
		z0 = svsub_m (p0, z1, z2))

/*
** sub_x0_f64_m_tied1:
**	mov	(z[0-9]+\.d), x0
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_m_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_m (p0, z0, x0),
		 z0 = svsub_m (p0, z0, x0))

/*
** sub_x0_f64_m_untied:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_m_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_m (p0, z1, x0),
		 z0 = svsub_m (p0, z1, x0))

/*
** sub_d4_f64_m_tied1:
**	mov	(z[0-9]+\.d), d4
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_m_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_m (p0, z0, d4),
		 z0 = svsub_m (p0, z0, d4))

/*
** sub_d4_f64_m_untied:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_m_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_m (p0, z1, d4),
		 z0 = svsub_m (p0, z1, d4))

/*
** sub_1_f64_m_tied1:
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_m_tied1, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z0, 1),
		z0 = svsub_m (p0, z0, 1))

/*
** sub_1_f64_m_untied:
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_m_untied, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z1, 1),
		z0 = svsub_m (p0, z1, 1))

/*
** sub_0p5_f64_m_tied1:
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_m_tied1, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z0, 0.5),
		z0 = svsub_m (p0, z0, 0.5))

/*
** sub_0p5_f64_m_untied:
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_m_untied, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z1, 0.5),
		z0 = svsub_m (p0, z1, 0.5))

/*
** sub_m1_f64_m_tied1:
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_m_tied1, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z0, -1),
		z0 = svsub_m (p0, z0, -1))

/*
** sub_m1_f64_m_untied:
**	movprfx	z0, z1
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_m_untied, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z1, -1),
		z0 = svsub_m (p0, z1, -1))

/*
** sub_m0p5_f64_m_tied1:
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_m_tied1, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z0, -0.5),
		z0 = svsub_m (p0, z0, -0.5))

/*
** sub_m0p5_f64_m_untied:
**	movprfx	z0, z1
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_m_untied, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z1, -0.5),
		z0 = svsub_m (p0, z1, -0.5))

/*
** sub_m2_f64_m:
**	fmov	(z[0-9]+\.d), #2\.0(e\+0)?
**	fadd	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (sub_m2_f64_m, svfloat64_t,
		z0 = svsub_n_f64_m (p0, z0, -2),
		z0 = svsub_m (p0, z0, -2))

/*
** sub_f64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	fsub	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_z_tied1, svfloat64_t,
		z0 = svsub_f64_z (p0, z0, z1),
		z0 = svsub_z (p0, z0, z1))

/*
** sub_f64_z_tied2:
**	movprfx	z0\.d, p0/z, z0\.d
**	fsubr	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_z_tied2, svfloat64_t,
		z0 = svsub_f64_z (p0, z1, z0),
		z0 = svsub_z (p0, z1, z0))

/*
** sub_f64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	fsub	z0\.d, p0/m, z0\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_z_untied, svfloat64_t,
		z0 = svsub_f64_z (p0, z1, z2),
		z0 = svsub_z (p0, z1, z2))

/*
** sub_x0_f64_z_tied1:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.d, p0/z, z0\.d
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_z_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_z (p0, z0, x0),
		 z0 = svsub_z (p0, z0, x0))

/*
** sub_x0_f64_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.d, p0/z, z1\.d
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_z_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_z (p0, z1, x0),
		 z0 = svsub_z (p0, z1, x0))

/*
** sub_d4_f64_z_tied1:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z0\.d, p0/z, z0\.d
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_z_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_z (p0, z0, d4),
		 z0 = svsub_z (p0, z0, d4))

/*
** sub_d4_f64_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), d4
**	movprfx	z0\.d, p0/z, z1\.d
**	fsub	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_z_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_z (p0, z1, d4),
		 z0 = svsub_z (p0, z1, d4))

/*
** sub_1_f64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_z_tied1, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z0, 1),
		z0 = svsub_z (p0, z0, 1))

/*
** sub_1_f64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_z_untied, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z1, 1),
		z0 = svsub_z (p0, z1, 1))

/*
** sub_0p5_f64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_z_tied1, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z0, 0.5),
		z0 = svsub_z (p0, z0, 0.5))

/*
** sub_0p5_f64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_z_untied, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z1, 0.5),
		z0 = svsub_z (p0, z1, 0.5))

/*
** sub_m1_f64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_z_tied1, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z0, -1),
		z0 = svsub_z (p0, z0, -1))

/*
** sub_m1_f64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_z_untied, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z1, -1),
		z0 = svsub_z (p0, z1, -1))

/*
** sub_m0p5_f64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_z_tied1, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z0, -0.5),
		z0 = svsub_z (p0, z0, -0.5))

/*
** sub_m0p5_f64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_z_untied, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z1, -0.5),
		z0 = svsub_z (p0, z1, -0.5))

/*
** sub_m2_f64_z:
**	fmov	(z[0-9]+\.d), #2\.0(e\+0)?
**	movprfx	z0\.d, p0/z, z0\.d
**	fadd	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (sub_m2_f64_z, svfloat64_t,
		z0 = svsub_n_f64_z (p0, z0, -2),
		z0 = svsub_z (p0, z0, -2))

/*
** sub_f64_x_tied1:
**	fsub	z0\.d, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_x_tied1, svfloat64_t,
		z0 = svsub_f64_x (p0, z0, z1),
		z0 = svsub_x (p0, z0, z1))

/*
** sub_f64_x_tied2:
**	fsub	z0\.d, z1\.d, z0\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_x_tied2, svfloat64_t,
		z0 = svsub_f64_x (p0, z1, z0),
		z0 = svsub_x (p0, z1, z0))

/*
** sub_f64_x_untied:
**	fsub	z0\.d, z1\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (sub_f64_x_untied, svfloat64_t,
		z0 = svsub_f64_x (p0, z1, z2),
		z0 = svsub_x (p0, z1, z2))

/*
** sub_x0_f64_x_tied1:
**	mov	(z[0-9]+\.d), x0
**	fsub	z0\.d, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_x_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_x (p0, z0, x0),
		 z0 = svsub_x (p0, z0, x0))

/*
** sub_x0_f64_x_untied:
**	mov	(z[0-9]+\.d), x0
**	fsub	z0\.d, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_x0_f64_x_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_x (p0, z1, x0),
		 z0 = svsub_x (p0, z1, x0))

/*
** sub_d4_f64_x_tied1:
**	mov	(z[0-9]+\.d), d4
**	fsub	z0\.d, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_x_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_x (p0, z0, d4),
		 z0 = svsub_x (p0, z0, d4))

/*
** sub_d4_f64_x_untied:
**	mov	(z[0-9]+\.d), d4
**	fsub	z0\.d, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_d4_f64_x_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_x (p0, z1, d4),
		 z0 = svsub_x (p0, z1, d4))

/*
** sub_1_f64_x_tied1:
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z0, 1),
		z0 = svsub_x (p0, z0, 1))

/*
** sub_1_f64_x_untied:
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_1_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z1, 1),
		z0 = svsub_x (p0, z1, 1))

/*
** sub_0p5_f64_x_tied1:
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z0, 0.5),
		z0 = svsub_x (p0, z0, 0.5))

/*
** sub_0p5_f64_x_untied:
**	movprfx	z0, z1
**	fsub	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_0p5_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z1, 0.5),
		z0 = svsub_x (p0, z1, 0.5))

/*
** sub_m1_f64_x_tied1:
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z0, -1),
		z0 = svsub_x (p0, z0, -1))

/*
** sub_m1_f64_x_untied:
**	movprfx	z0, z1
**	fadd	z0\.d, p0/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (sub_m1_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z1, -1),
		z0 = svsub_x (p0, z1, -1))

/*
** sub_m0p5_f64_x_tied1:
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z0, -0.5),
		z0 = svsub_x (p0, z0, -0.5))

/*
** sub_m0p5_f64_x_untied:
**	movprfx	z0, z1
**	fadd	z0\.d, p0/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (sub_m0p5_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z1, -0.5),
		z0 = svsub_x (p0, z1, -0.5))

/*
** sub_2_f64_x_tied1:
**	fmov	(z[0-9]+\.d), #-2\.0(e\+0)?
**	fadd	z0\.d, (z0\.d, \1|\1, z0\.d)
**	ret
*/
TEST_UNIFORM_Z (sub_2_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z0, 2),
		z0 = svsub_x (p0, z0, 2))

/*
** sub_2_f64_x_untied:
**	fmov	(z[0-9]+\.d), #-2\.0(e\+0)?
**	fadd	z0\.d, (z1\.d, \1|\1, z1\.d)
**	ret
*/
TEST_UNIFORM_Z (sub_2_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (p0, z1, 2),
		z0 = svsub_x (p0, z1, 2))

/*
** ptrue_sub_f64_x_tied1:
**	fsub	z0\.d, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_f64_x_tied1, svfloat64_t,
		z0 = svsub_f64_x (svptrue_b64 (), z0, z1),
		z0 = svsub_x (svptrue_b64 (), z0, z1))

/*
** ptrue_sub_f64_x_tied2:
**	fsub	z0\.d, z1\.d, z0\.d
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_f64_x_tied2, svfloat64_t,
		z0 = svsub_f64_x (svptrue_b64 (), z1, z0),
		z0 = svsub_x (svptrue_b64 (), z1, z0))

/*
** ptrue_sub_f64_x_untied:
**	fsub	z0\.d, z1\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_f64_x_untied, svfloat64_t,
		z0 = svsub_f64_x (svptrue_b64 (), z1, z2),
		z0 = svsub_x (svptrue_b64 (), z1, z2))

/*
** ptrue_sub_x0_f64_x_tied1:
**	mov	(z[0-9]+\.d), x0
**	fsub	z0\.d, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (ptrue_sub_x0_f64_x_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_x (svptrue_b64 (), z0, x0),
		 z0 = svsub_x (svptrue_b64 (), z0, x0))

/*
** ptrue_sub_x0_f64_x_untied:
**	mov	(z[0-9]+\.d), x0
**	fsub	z0\.d, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (ptrue_sub_x0_f64_x_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_x (svptrue_b64 (), z1, x0),
		 z0 = svsub_x (svptrue_b64 (), z1, x0))

/*
** ptrue_sub_d4_f64_x_tied1:
**	mov	(z[0-9]+\.d), d4
**	fsub	z0\.d, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (ptrue_sub_d4_f64_x_tied1, svfloat64_t, double,
		 z0 = svsub_n_f64_x (svptrue_b64 (), z0, d4),
		 z0 = svsub_x (svptrue_b64 (), z0, d4))

/*
** ptrue_sub_d4_f64_x_untied:
**	mov	(z[0-9]+\.d), d4
**	fsub	z0\.d, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (ptrue_sub_d4_f64_x_untied, svfloat64_t, double,
		 z0 = svsub_n_f64_x (svptrue_b64 (), z1, d4),
		 z0 = svsub_x (svptrue_b64 (), z1, d4))

/*
** ptrue_sub_1_f64_x_tied1:
**	ptrue	(p[0-7])\.d[^\n]*
**	fsub	z0\.d, \1/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_1_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z0, 1),
		z0 = svsub_x (svptrue_b64 (), z0, 1))

/*
** ptrue_sub_1_f64_x_untied:
**	ptrue	(p[0-7])\.d[^\n]*
**	movprfx	z0, z1
**	fsub	z0\.d, \1/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_1_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z1, 1),
		z0 = svsub_x (svptrue_b64 (), z1, 1))

/*
** ptrue_sub_0p5_f64_x_tied1:
**	ptrue	(p[0-7])\.d[^\n]*
**	fsub	z0\.d, \1/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_0p5_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z0, 0.5),
		z0 = svsub_x (svptrue_b64 (), z0, 0.5))

/*
** ptrue_sub_0p5_f64_x_untied:
**	ptrue	(p[0-7])\.d[^\n]*
**	movprfx	z0, z1
**	fsub	z0\.d, \1/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_0p5_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z1, 0.5),
		z0 = svsub_x (svptrue_b64 (), z1, 0.5))

/*
** ptrue_sub_m1_f64_x_tied1:
**	ptrue	(p[0-7])\.d[^\n]*
**	fadd	z0\.d, \1/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_m1_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z0, -1),
		z0 = svsub_x (svptrue_b64 (), z0, -1))

/*
** ptrue_sub_m1_f64_x_untied:
**	ptrue	(p[0-7])\.d[^\n]*
**	movprfx	z0, z1
**	fadd	z0\.d, \1/m, z0\.d, #1\.0
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_m1_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z1, -1),
		z0 = svsub_x (svptrue_b64 (), z1, -1))

/*
** ptrue_sub_m0p5_f64_x_tied1:
**	ptrue	(p[0-7])\.d[^\n]*
**	fadd	z0\.d, \1/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_m0p5_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z0, -0.5),
		z0 = svsub_x (svptrue_b64 (), z0, -0.5))

/*
** ptrue_sub_m0p5_f64_x_untied:
**	ptrue	(p[0-7])\.d[^\n]*
**	movprfx	z0, z1
**	fadd	z0\.d, \1/m, z0\.d, #0\.5
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_m0p5_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z1, -0.5),
		z0 = svsub_x (svptrue_b64 (), z1, -0.5))

/*
** ptrue_sub_2_f64_x_tied1:
**	fmov	(z[0-9]+\.d), #-2\.0(e\+0)?
**	fadd	z0\.d, (z0\.d, \1|\1, z0\.d)
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_2_f64_x_tied1, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z0, 2),
		z0 = svsub_x (svptrue_b64 (), z0, 2))

/*
** ptrue_sub_2_f64_x_untied:
**	fmov	(z[0-9]+\.d), #-2\.0(e\+0)?
**	fadd	z0\.d, (z1\.d, \1|\1, z1\.d)
**	ret
*/
TEST_UNIFORM_Z (ptrue_sub_2_f64_x_untied, svfloat64_t,
		z0 = svsub_n_f64_x (svptrue_b64 (), z1, 2),
		z0 = svsub_x (svptrue_b64 (), z1, 2))
