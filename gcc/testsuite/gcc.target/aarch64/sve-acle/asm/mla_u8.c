/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** mla_u8_m_tied1:
**	mla	z0\.b, p0/m, z1\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_m_tied1, svuint8_t,
		z0 = svmla_u8_m (p0, z0, z1, z2),
		z0 = svmla_m (p0, z0, z1, z2))

/*
** mla_u8_m_tied2:
**	mov	(z[0-9]+)\.d, z1\.d
**	movprfx	z1, z0
**	mla	z1\.b, p0/m, \1\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_m_tied2, svuint8_t,
		z1 = svmla_u8_m (p0, z0, z1, z2),
		z1 = svmla_m (p0, z0, z1, z2))

/*
** mla_u8_m_tied3:
**	mov	(z[0-9]+)\.d, z2\.d
**	movprfx	z2, z0
**	mla	z2\.b, p0/m, z1\.b, \1\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_m_tied3, svuint8_t,
		z2 = svmla_u8_m (p0, z0, z1, z2),
		z2 = svmla_m (p0, z0, z1, z2))

/*
** mla_u8_m_untied:
**	movprfx	z0, z1
**	mla	z0\.b, p0/m, z2\.b, z3\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_m_untied, svuint8_t,
		z0 = svmla_u8_m (p0, z1, z2, z3),
		z0 = svmla_m (p0, z1, z2, z3))

/*
** mla_w0_u8_m_tied1:
**	mov	(z[0-9]+\.b), w0
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_m_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_m (p0, z0, z1, x0),
		 z0 = svmla_m (p0, z0, z1, x0))

/*
** mla_w0_u8_m_tied2:
**	mov	(z[0-9]+\.b), w0
**	mov	(z[0-9]+)\.d, z1\.d
**	movprfx	z1, z0
**	mla	z1\.b, p0/m, \2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_m_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_m (p0, z0, z1, x0),
		 z1 = svmla_m (p0, z0, z1, x0))

/*
** mla_w0_u8_m_untied:
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0, z1
**	mla	z0\.b, p0/m, z2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_m_untied, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_m (p0, z1, z2, x0),
		 z0 = svmla_m (p0, z1, z2, x0))

/*
** mla_b4_u8_m_tied1:
**	mov	(z[0-9]+\.b), b4
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_m_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_m (p0, z0, z1, d4),
		 z0 = svmla_m (p0, z0, z1, d4))

/*
** mla_b4_u8_m_tied2:
**	mov	(z[0-9]+\.b), b4
**	mov	(z[0-9]+)\.d, z1\.d
**	movprfx	z1, z0
**	mla	z1\.b, p0/m, \2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_m_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_m (p0, z0, z1, d4),
		 z1 = svmla_m (p0, z0, z1, d4))

/*
** mla_b4_u8_m_untied:
**	mov	(z[0-9]+\.b), b4
**	movprfx	z1, z0
**	mla	z1\.b, p0/m, z2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_m_untied, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_m (p0, z0, z2, d4),
		 z1 = svmla_m (p0, z0, z2, d4))

/*
** mla_2_u8_m_tied1:
**	mov	(z[0-9]+\.b), #2
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_m_tied1, svuint8_t,
		z0 = svmla_n_u8_m (p0, z0, z1, 2),
		z0 = svmla_m (p0, z0, z1, 2))

/*
** mla_2_u8_m_tied2:
**	mov	(z[0-9]+\.b), #2
**	mov	(z[0-9]+)\.d, z1\.d
**	movprfx	z1, z0
**	mla	z1\.b, p0/m, \2\.b, \1
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_m_tied2, svuint8_t,
		z1 = svmla_n_u8_m (p0, z0, z1, 2),
		z1 = svmla_m (p0, z0, z1, 2))

/*
** mla_2_u8_m_untied:
**	mov	(z[0-9]+\.b), #2
**	movprfx	z0, z1
**	mla	z0\.b, p0/m, z2\.b, \1
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_m_untied, svuint8_t,
		z0 = svmla_n_u8_m (p0, z1, z2, 2),
		z0 = svmla_m (p0, z1, z2, 2))

/*
** mla_u8_z_tied1:
**	movprfx	z0\.b, p0/z, z0\.b
**	mla	z0\.b, p0/m, z1\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_z_tied1, svuint8_t,
		z0 = svmla_u8_z (p0, z0, z1, z2),
		z0 = svmla_z (p0, z0, z1, z2))

/*
** mla_u8_z_tied2:
**	movprfx	z1\.b, p0/z, z1\.b
**	mad	z1\.b, p0/m, z2\.b, z0\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_z_tied2, svuint8_t,
		z1 = svmla_u8_z (p0, z0, z1, z2),
		z1 = svmla_z (p0, z0, z1, z2))

/*
** mla_u8_z_tied3:
**	movprfx	z2\.b, p0/z, z2\.b
**	mad	z2\.b, p0/m, z1\.b, z0\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_z_tied3, svuint8_t,
		z2 = svmla_u8_z (p0, z0, z1, z2),
		z2 = svmla_z (p0, z0, z1, z2))

/*
** mla_u8_z_untied:
**	movprfx	z0\.b, p0/z, z1\.b
**	mla	z0\.b, p0/m, z2\.b, z3\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_z_untied, svuint8_t,
		z0 = svmla_u8_z (p0, z1, z2, z3),
		z0 = svmla_z (p0, z1, z2, z3))

/*
** mla_w0_u8_z_tied1:
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0\.b, p0/z, z0\.b
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_z_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_z (p0, z0, z1, x0),
		 z0 = svmla_z (p0, z0, z1, x0))

/*
** mla_w0_u8_z_tied2:
**	mov	(z[0-9]+\.b), w0
**	movprfx	z1\.b, p0/z, z1\.b
**	mad	z1\.b, p0/m, \1, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_z_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_z (p0, z0, z1, x0),
		 z1 = svmla_z (p0, z0, z1, x0))

/*
** mla_w0_u8_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.b), w0
**	movprfx	z0\.b, p0/z, z1\.b
**	mla	z0\.b, p0/m, z2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_z_untied, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_z (p0, z1, z2, x0),
		 z0 = svmla_z (p0, z1, z2, x0))

/*
** mla_b4_u8_z_tied1:
**	mov	(z[0-9]+\.b), b4
**	movprfx	z0\.b, p0/z, z0\.b
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_z_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_z (p0, z0, z1, d4),
		 z0 = svmla_z (p0, z0, z1, d4))

/*
** mla_b4_u8_z_tied2:
**	mov	(z[0-9]+\.b), b4
**	movprfx	z1\.b, p0/z, z1\.b
**	mad	z1\.b, p0/m, \1, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_z_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_z (p0, z0, z1, d4),
		 z1 = svmla_z (p0, z0, z1, d4))

/*
** mla_b4_u8_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.b), b4
**	movprfx	z1\.b, p0/z, z0\.b
**	mla	z1\.b, p0/m, z2\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_z_untied, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_z (p0, z0, z2, d4),
		 z1 = svmla_z (p0, z0, z2, d4))

/*
** mla_u8_x_tied1:
**	mla	z0\.b, p0/m, z1\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_x_tied1, svuint8_t,
		z0 = svmla_u8_x (p0, z0, z1, z2),
		z0 = svmla_x (p0, z0, z1, z2))

/*
** mla_u8_x_tied2:
**	mad	z1\.b, p0/m, z2\.b, z0\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_x_tied2, svuint8_t,
		z1 = svmla_u8_x (p0, z0, z1, z2),
		z1 = svmla_x (p0, z0, z1, z2))

/*
** mla_u8_x_tied3:
**	mad	z2\.b, p0/m, z1\.b, z0\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_x_tied3, svuint8_t,
		z2 = svmla_u8_x (p0, z0, z1, z2),
		z2 = svmla_x (p0, z0, z1, z2))

/*
** mla_u8_x_untied:
**	movprfx	z3, z0
**	mla	z3\.b, p0/m, z1\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (mla_u8_x_untied, svuint8_t,
		z3 = svmla_u8_x (p0, z0, z1, z2),
		z3 = svmla_x (p0, z0, z1, z2))

/*
** mla_w0_u8_x_tied1:
**	mov	(z[0-9]+\.b), w0
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_x_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_x (p0, z0, z1, x0),
		 z0 = svmla_x (p0, z0, z1, x0))

/*
** mla_w0_u8_x_tied2:
**	mov	(z[0-9]+\.b), w0
**	mad	z1\.b, p0/m, \1, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_x_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_x (p0, z0, z1, x0),
		 z1 = svmla_x (p0, z0, z1, x0))

/*
** mla_w0_u8_x_untied:
**	mov	z2\.b, w0
**	mad	z2\.b, p0/m, z1\.b, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_w0_u8_x_untied, svuint8_t, uint8_t,
		 z2 = svmla_n_u8_x (p0, z0, z1, x0),
		 z2 = svmla_x (p0, z0, z1, x0))

/*
** mla_b4_u8_x_tied1:
**	mov	(z[0-9]+\.b), b4
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_x_tied1, svuint8_t, uint8_t,
		 z0 = svmla_n_u8_x (p0, z0, z1, d4),
		 z0 = svmla_x (p0, z0, z1, d4))

/*
** mla_b4_u8_x_tied2:
**	mov	(z[0-9]+\.b), b4
**	mad	z1\.b, p0/m, \1, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_x_tied2, svuint8_t, uint8_t,
		 z1 = svmla_n_u8_x (p0, z0, z1, d4),
		 z1 = svmla_x (p0, z0, z1, d4))

/*
** mla_b4_u8_x_untied:
**	mov	z2\.b, b4
**	mad	z2\.b, p0/m, z1\.b, z0\.b
**	ret
*/
TEST_UNIFORM_ZS (mla_b4_u8_x_untied, svuint8_t, uint8_t,
		 z2 = svmla_n_u8_x (p0, z0, z1, d4),
		 z2 = svmla_x (p0, z0, z1, d4))

/*
** mla_2_u8_x_tied1:
**	mov	(z[0-9]+\.b), #2
**	mla	z0\.b, p0/m, z1\.b, \1
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_x_tied1, svuint8_t,
		z0 = svmla_n_u8_x (p0, z0, z1, 2),
		z0 = svmla_x (p0, z0, z1, 2))

/*
** mla_2_u8_x_tied2:
**	mov	(z[0-9]+\.b), #2
**	mad	z1\.b, p0/m, \1, z0\.b
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_x_tied2, svuint8_t,
		z1 = svmla_n_u8_x (p0, z0, z1, 2),
		z1 = svmla_x (p0, z0, z1, 2))

/*
** mla_2_u8_x_untied:
**	mov	z0\.b, #2
**	mad	z0\.b, p0/m, z2\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (mla_2_u8_x_untied, svuint8_t,
		z0 = svmla_n_u8_x (p0, z1, z2, 2),
		z0 = svmla_x (p0, z1, z2, 2))
