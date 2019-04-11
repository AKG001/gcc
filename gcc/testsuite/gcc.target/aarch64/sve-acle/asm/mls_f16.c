/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** mls_f16_m_tied1:
**	fmls	z0\.h, p0/m, z1\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_m_tied1, svfloat16_t,
		z0 = svmls_f16_m (p0, z0, z1, z2),
		z0 = svmls_m (p0, z0, z1, z2))

/*
** mls_f16_m_tied2:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, \1\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_m_tied2, svfloat16_t,
		z0 = svmls_f16_m (p0, z1, z0, z2),
		z0 = svmls_m (p0, z1, z0, z2))

/*
** mls_f16_m_tied3:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_m_tied3, svfloat16_t,
		z0 = svmls_f16_m (p0, z1, z2, z0),
		z0 = svmls_m (p0, z1, z2, z0))

/*
** mls_f16_m_untied:
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, z3\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_m_untied, svfloat16_t,
		z0 = svmls_f16_m (p0, z1, z2, z3),
		z0 = svmls_m (p0, z1, z2, z3))

/*
** mls_w0_f16_m_tied1:
**	mov	(z[0-9]+\.h), w0
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_m_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z0, z1, x0),
		 z0 = svmls_m (p0, z0, z1, x0))

/*
** mls_w0_f16_m_tied2:
**	mov	(z[0-9]+\.h), w0
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, \2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_m_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z1, z0, x0),
		 z0 = svmls_m (p0, z1, z0, x0))

/*
** mls_w0_f16_m_untied:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_m_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z1, z2, x0),
		 z0 = svmls_m (p0, z1, z2, x0))

/*
** mls_h4_f16_m_tied1:
**	mov	(z[0-9]+\.h), h4
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_m_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z0, z1, d4),
		 z0 = svmls_m (p0, z0, z1, d4))

/*
** mls_h4_f16_m_tied2:
**	mov	(z[0-9]+\.h), h4
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, \2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_m_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z1, z0, d4),
		 z0 = svmls_m (p0, z1, z0, d4))

/*
** mls_h4_f16_m_untied:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_m_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_m (p0, z1, z2, d4),
		 z0 = svmls_m (p0, z1, z2, d4))

/*
** mls_2_f16_m_tied1:
**	fmov	(z[0-9]+\.h), #2\.0(?:e\+0)?
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_m_tied1, svfloat16_t,
		z0 = svmls_n_f16_m (p0, z0, z1, 2),
		z0 = svmls_m (p0, z0, z1, 2))

/*
** mls_2_f16_m_tied2:
**	fmov	(z[0-9]+\.h), #2\.0(?:e\+0)?
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, \2\.h, \1
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_m_tied2, svfloat16_t,
		z0 = svmls_n_f16_m (p0, z1, z0, 2),
		z0 = svmls_m (p0, z1, z0, 2))

/*
** mls_2_f16_m_untied:
**	fmov	(z[0-9]+\.h), #2\.0(?:e\+0)?
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, \1
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_m_untied, svfloat16_t,
		z0 = svmls_n_f16_m (p0, z1, z2, 2),
		z0 = svmls_m (p0, z1, z2, 2))

/*
** mls_f16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	fmls	z0\.h, p0/m, z1\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_z_tied1, svfloat16_t,
		z0 = svmls_f16_z (p0, z0, z1, z2),
		z0 = svmls_z (p0, z0, z1, z2))

/*
** mls_f16_z_tied2:
**	movprfx	z0\.h, p0/z, z0\.h
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_z_tied2, svfloat16_t,
		z0 = svmls_f16_z (p0, z1, z0, z2),
		z0 = svmls_z (p0, z1, z0, z2))

/*
** mls_f16_z_tied3:
**	movprfx	z0\.h, p0/z, z0\.h
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_z_tied3, svfloat16_t,
		z0 = svmls_f16_z (p0, z1, z2, z0),
		z0 = svmls_z (p0, z1, z2, z0))

/*
** mls_f16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	fmls	z0\.h, p0/m, z2\.h, z3\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_z_untied, svfloat16_t,
		z0 = svmls_f16_z (p0, z1, z2, z3),
		z0 = svmls_z (p0, z1, z2, z3))

/*
** mls_w0_f16_z_tied1:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z0\.h
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_z_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z0, z1, x0),
		 z0 = svmls_z (p0, z0, z1, x0))

/*
** mls_w0_f16_z_tied2:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z0\.h
**	fmsb	z0\.h, p0/m, \1, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_z_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z1, z0, x0),
		 z0 = svmls_z (p0, z1, z0, x0))

/*
** mls_w0_f16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z1\.h
**	fmls	z0\.h, p0/m, z2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_z_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z1, z2, x0),
		 z0 = svmls_z (p0, z1, z2, x0))

/*
** mls_h4_f16_z_tied1:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z0\.h, p0/z, z0\.h
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_z_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z0, z1, d4),
		 z0 = svmls_z (p0, z0, z1, d4))

/*
** mls_h4_f16_z_tied2:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z0\.h, p0/z, z0\.h
**	fmsb	z0\.h, p0/m, \1, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_z_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z1, z0, d4),
		 z0 = svmls_z (p0, z1, z0, d4))

/*
** mls_h4_f16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), h4
**	movprfx	z0\.h, p0/z, z1\.h
**	fmls	z0\.h, p0/m, z2\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_z_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_z (p0, z1, z2, d4),
		 z0 = svmls_z (p0, z1, z2, d4))

/*
** mls_f16_x_tied1:
**	fmls	z0\.h, p0/m, z1\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_x_tied1, svfloat16_t,
		z0 = svmls_f16_x (p0, z0, z1, z2),
		z0 = svmls_x (p0, z0, z1, z2))

/*
** mls_f16_x_tied2:
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_x_tied2, svfloat16_t,
		z0 = svmls_f16_x (p0, z1, z0, z2),
		z0 = svmls_x (p0, z1, z0, z2))

/*
** mls_f16_x_tied3:
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_x_tied3, svfloat16_t,
		z0 = svmls_f16_x (p0, z1, z2, z0),
		z0 = svmls_x (p0, z1, z2, z0))

/*
** mls_f16_x_untied:
**	movprfx	z0, z1
**	fmls	z0\.h, p0/m, z2\.h, z3\.h
**	ret
*/
TEST_UNIFORM_Z (mls_f16_x_untied, svfloat16_t,
		z0 = svmls_f16_x (p0, z1, z2, z3),
		z0 = svmls_x (p0, z1, z2, z3))

/*
** mls_w0_f16_x_tied1:
**	mov	(z[0-9]+\.h), w0
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_x_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z0, z1, x0),
		 z0 = svmls_x (p0, z0, z1, x0))

/*
** mls_w0_f16_x_tied2:
**	mov	(z[0-9]+\.h), w0
**	fmsb	z0\.h, p0/m, \1, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_x_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z1, z0, x0),
		 z0 = svmls_x (p0, z1, z0, x0))

/*
** mls_w0_f16_x_untied:
**	mov	z0\.h, w0
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_w0_f16_x_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z1, z2, x0),
		 z0 = svmls_x (p0, z1, z2, x0))

/*
** mls_h4_f16_x_tied1:
**	mov	(z[0-9]+\.h), h4
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_x_tied1, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z0, z1, d4),
		 z0 = svmls_x (p0, z0, z1, d4))

/*
** mls_h4_f16_x_tied2:
**	mov	(z[0-9]+\.h), h4
**	fmsb	z0\.h, p0/m, \1, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_x_tied2, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z1, z0, d4),
		 z0 = svmls_x (p0, z1, z0, d4))

/*
** mls_h4_f16_x_untied:
**	mov	z0\.h, h4
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (mls_h4_f16_x_untied, svfloat16_t, __fp16,
		 z0 = svmls_n_f16_x (p0, z1, z2, d4),
		 z0 = svmls_x (p0, z1, z2, d4))

/*
** mls_2_f16_x_tied1:
**	fmov	(z[0-9]+\.h), #2\.0(?:e\+0)?
**	fmls	z0\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_x_tied1, svfloat16_t,
		z0 = svmls_n_f16_x (p0, z0, z1, 2),
		z0 = svmls_x (p0, z0, z1, 2))

/*
** mls_2_f16_x_tied2:
**	fmov	(z[0-9]+\.h), #2\.0(?:e\+0)?
**	fmsb	z0\.h, p0/m, \1, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_x_tied2, svfloat16_t,
		z0 = svmls_n_f16_x (p0, z1, z0, 2),
		z0 = svmls_x (p0, z1, z0, 2))

/*
** mls_2_f16_x_untied:
**	fmov	z0\.h, #2\.0(?:e\+0)?
**	fmsb	z0\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (mls_2_f16_x_untied, svfloat16_t,
		z0 = svmls_n_f16_x (p0, z1, z2, 2),
		z0 = svmls_x (p0, z1, z2, 2))
