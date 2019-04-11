/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** lsl_u16_m_tied1:
**	lsl	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_m_tied1, svuint16_t,
		z0 = svlsl_u16_m (p0, z0, z1),
		z0 = svlsl_m (p0, z0, z1))

/*
** lsl_u16_m_untied:
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_m_untied, svuint16_t,
		z0 = svlsl_u16_m (p0, z1, z2),
		z0 = svlsl_m (p0, z1, z2))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (lsl_u16_m_tied2, svuint16_t,
		z1 = svlsl_u16_m (p0, z0, z1),
		z1 = svlsl_m (p0, z0, z1))

/*
** lsl_w0_u16_m_tied1:
**	mov	(z[0-9]+\.d), x0
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_m_tied1, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_m (p0, z0, x0),
		 z0 = svlsl_m (p0, z0, x0))

/*
** lsl_w0_u16_m_untied:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_m_untied, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_m (p0, z1, x0),
		 z0 = svlsl_m (p0, z1, x0))

/*
** lsl_d4_u16_m_tied1:
**	mov	(z[0-9]+\.d), d4
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_m_tied1, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_m (p0, z1, d4),
		 z1 = svlsl_m (p0, z1, d4))

/*
** lsl_d4_u16_m_untied:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z1, z2
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_m_untied, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_m (p0, z2, d4),
		 z1 = svlsl_m (p0, z2, d4))

/* 
** lsl_0_u16_m_tied1:
**	sel	z0\.h, p0, z0\.h, z0\.h
**	ret
*/
TEST_UNIFORM_ZS (lsl_0_u16_m_tied1, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_m (p0, z0, 0),
		 z0 = svlsl_m (p0, z0, 0))

/* 
** lsl_0_u16_m_untied:
**	sel	z0\.h, p0, z1\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (lsl_0_u16_m_untied, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_m (p0, z1, 0),
		 z0 = svlsl_m (p0, z1, 0))

/*
** lsl_1_u16_m_tied1:
**	lsl	z0\.h, p0/m, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_m_tied1, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z0, 1),
		z0 = svlsl_m (p0, z0, 1))

/*
** lsl_1_u16_m_untied:
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_m_untied, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z1, 1),
		z0 = svlsl_m (p0, z1, 1))

/*
** lsl_m1_u16_m_tied1:
**	mov	(z[0-9]+)\.b, #-1
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_m_tied1, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z0, -1),
		z0 = svlsl_m (p0, z0, -1))

/*
** lsl_m1_u16_m_untied:
**	mov	(z[0-9]+)\.b, #-1
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_m_untied, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z1, -1),
		z0 = svlsl_m (p0, z1, -1))

/*
** lsl_15_u16_m_tied1:
**	lsl	z0\.h, p0/m, z0\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_m_tied1, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z0, 15),
		z0 = svlsl_m (p0, z0, 15))

/*
** lsl_15_u16_m_untied:
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_m_untied, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z1, 15),
		z0 = svlsl_m (p0, z1, 15))

/*
** lsl_16_u16_m_tied1:
**	mov	(z[0-9]+\.d), #16
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_m_tied1, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z0, 16),
		z0 = svlsl_m (p0, z0, 16))

/*
** lsl_16_u16_m_untied:
**	mov	(z[0-9]+\.d), #16
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_m_untied, svuint16_t,
		z0 = svlsl_n_u16_m (p0, z1, 16),
		z0 = svlsl_m (p0, z1, 16))

/*
** lsl_u16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_z_tied1, svuint16_t,
		z0 = svlsl_u16_z (p0, z0, z1),
		z0 = svlsl_z (p0, z0, z1))

/*
** lsl_u16_z_untied: { xfail *-*-* }
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_z_untied, svuint16_t,
		z0 = svlsl_u16_z (p0, z1, z2),
		z0 = svlsl_z (p0, z1, z2))

/*
** lsl_u16_z_tied2:
**	movprfx	z0\.h, p0/z, z0\.h
**	lslr	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_z_tied2, svuint16_t,
		z0 = svlsl_u16_z (p0, z1, z0),
		z0 = svlsl_z (p0, z1, z0))

/*
** lsl_w0_u16_z_tied1:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_z_tied1, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_z (p0, z0, x0),
		 z0 = svlsl_z (p0, z0, x0))

/*
** lsl_w0_u16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_z_untied, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_z (p0, z1, x0),
		 z0 = svlsl_z (p0, z1, x0))

/*
** lsl_d4_u16_z_tied1:
**	mov	(z[0-9d]+\.d), d4
**	movprfx	z1\.h, p0/z, z1\.h
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_z_tied1, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_z (p0, z1, d4),
		 z1 = svlsl_z (p0, z1, d4))

/*
** lsl_d4_u16_z_untied: { xfail *-*-* }
**	mov	(z[0-9d]+\.d), d4
**	movprfx	z1\.h, p0/z, z2\.h
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_z_untied, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_z (p0, z2, d4),
		 z1 = svlsl_z (p0, z2, d4))

/*
** lsl_0_u16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, #0
**	ret
*/
TEST_UNIFORM_Z (lsl_0_u16_z_tied1, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z0, 0),
		z0 = svlsl_z (p0, z0, 0))

/*
** lsl_0_u16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, #0
**	ret
*/
TEST_UNIFORM_Z (lsl_0_u16_z_untied, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z1, 0),
		z0 = svlsl_z (p0, z1, 0))

/*
** lsl_1_u16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_z_tied1, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z0, 1),
		z0 = svlsl_z (p0, z0, 1))

/*
** lsl_1_u16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_z_untied, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z1, 1),
		z0 = svlsl_z (p0, z1, 1))

/*
** lsl_m1_u16_z_tied1:
**	mov	(z[0-9]+)\.b, #-1
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_z_tied1, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z0, -1),
		z0 = svlsl_z (p0, z0, -1))

/*
** lsl_m1_u16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+)\.b, #-1
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_z_untied, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z1, -1),
		z0 = svlsl_z (p0, z1, -1))

/*
** lsl_15_u16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_z_tied1, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z0, 15),
		z0 = svlsl_z (p0, z0, 15))

/*
** lsl_15_u16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_z_untied, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z1, 15),
		z0 = svlsl_z (p0, z1, 15))

/*
** lsl_16_u16_z_tied1:
**	mov	(z[0-9]+\.d), #16
**	movprfx	z0\.h, p0/z, z0\.h
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_z_tied1, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z0, 16),
		z0 = svlsl_z (p0, z0, 16))

/*
** lsl_16_u16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), #16
**	movprfx	z0\.h, p0/z, z1\.h
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_z_untied, svuint16_t,
		z0 = svlsl_n_u16_z (p0, z1, 16),
		z0 = svlsl_z (p0, z1, 16))

/*
** lsl_u16_x_tied1:
**	lsl	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_x_tied1, svuint16_t,
		z0 = svlsl_u16_x (p0, z0, z1),
		z0 = svlsl_x (p0, z0, z1))

/*
** lsl_u16_x_untied:
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_x_untied, svuint16_t,
		z0 = svlsl_u16_m (p0, z1, z2),
		z0 = svlsl_u16_m (p0, z1, z2))

/*
** lsl_u16_x_tied2:
**	lslr	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (lsl_u16_x_tied2, svuint16_t,
		z1 = svlsl_u16_x (p0, z0, z1),
		z1 = svlsl_x (p0, z0, z1))

/*
** lsl_w0_u16_x_tied1:
**	mov	(z[0-9]+\.d), x0
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_x_tied1, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_x (p0, z0, x0),
		 z0 = svlsl_x (p0, z0, x0))

/*
** lsl_w0_u16_x_untied:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_w0_u16_x_untied, svuint16_t, uint64_t,
		 z0 = svlsl_n_u16_x (p0, z1, x0),
		 z0 = svlsl_x (p0, z1, x0))

/*
** lsl_d4_u16_x_tied1:
**	mov	(z[0-9]+\.d), d4
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_x_tied1, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_x (p0, z1, d4),
		 z1 = svlsl_x (p0, z1, d4))

/*
** lsl_d4_u16_x_untied:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z1, z2
**	lsl	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (lsl_d4_u16_x_untied, svuint16_t, uint64_t,
		 z1 = svlsl_n_u16_x (p0, z2, d4),
		 z1 = svlsl_x (p0, z2, d4))

/*
** lsl_0_u16_x_tied1:
**	ret
*/
TEST_UNIFORM_Z (lsl_0_u16_x_tied1, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z0, 0),
		z0 = svlsl_x (p0, z0, 0))

/*
** lsl_0_u16_x_untied:
**	mov	z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_0_u16_x_untied, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z1, 0),
		z0 = svlsl_x (p0, z1, 0))

/*
** lsl_1_u16_x_tied1:
**	lsl	z0\.h, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_x_tied1, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z0, 1),
		z0 = svlsl_x (p0, z0, 1))

/*
** lsl_1_u16_x_untied:
**	lsl	z0\.h, z1\.h, #1
**	ret
*/
TEST_UNIFORM_Z (lsl_1_u16_x_untied, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z1, 1),
		z0 = svlsl_x (p0, z1, 1))

/*
** lsl_m1_u16_x_tied1:
**	mov	(z[0-9]+)\.b, #-1
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_x_tied1, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z0, -1),
		z0 = svlsl_x (p0, z0, -1))

/*
** lsl_m1_u16_x_untied:
**	mov	(z[0-9]+)\.b, #-1
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1\.d
**	ret
*/
TEST_UNIFORM_Z (lsl_m1_u16_x_untied, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z1, -1),
		z0 = svlsl_x (p0, z1, -1))

/*
** lsl_15_u16_x_tied1:
**	lsl	z0\.h, z0\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_x_tied1, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z0, 15),
		z0 = svlsl_x (p0, z0, 15))

/*
** lsl_15_u16_x_untied:
**	lsl	z0\.h, z1\.h, #15
**	ret
*/
TEST_UNIFORM_Z (lsl_15_u16_x_untied, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z1, 15),
		z0 = svlsl_x (p0, z1, 15))

/*
** lsl_16_u16_x_tied1:
**	mov	(z[0-9]+\.d), #16
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_x_tied1, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z0, 16),
		z0 = svlsl_x (p0, z0, 16))

/*
** lsl_16_u16_x_untied:
**	mov	(z[0-9]+\.d), #16
**	movprfx	z0, z1
**	lsl	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (lsl_16_u16_x_untied, svuint16_t,
		z0 = svlsl_n_u16_x (p0, z1, 16),
		z0 = svlsl_x (p0, z1, 16))
