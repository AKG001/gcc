/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** divr_u32_m_tied1:
**	udivr	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_m_tied1, svuint32_t,
		z0 = svdivr_u32_m (p0, z0, z1),
		z0 = svdivr_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (divr_u32_m_tied2, svuint32_t,
		z1 = svdivr_u32_m (p0, z0, z1),
		z1 = svdivr_m (p0, z0, z1))

/*
** divr_u32_m_untied:
**	movprfx	z0, z1
**	udivr	z0\.s, p0/m, z0\.s, z2\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_m_untied, svuint32_t,
		z0 = svdivr_u32_m (p0, z1, z2),
		z0 = svdivr_m (p0, z1, z2))

/*
** divr_w0_u32_m_tied1:
**	mov	(z[0-9]+\.s), w0
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_m_tied1, svuint32_t, uint32_t,
		 z0 = svdivr_n_u32_m (p0, z0, x0),
		 z0 = svdivr_m (p0, z0, x0))

/*
** divr_w0_u32_m_untied:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0, z1
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_m_untied, svuint32_t, uint32_t,
		 z0 = svdivr_n_u32_m (p0, z1, x0),
		 z0 = svdivr_m (p0, z1, x0))

/*
** divr_s4_u32_m_tied1:
**	mov	(z[0-9]+\.s), s4
**	udivr	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_m_tied1, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_m (p0, z1, d4),
		 z1 = svdivr_m (p0, z1, d4))

/*
** divr_s4_u32_m_untied:
**	mov	(z[0-9]+\.s), s4
**	movprfx	z1, z2
**	udivr	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_m_untied, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_m (p0, z2, d4),
		 z1 = svdivr_m (p0, z2, d4))

/*
** divr_2_u32_m_tied1:
**	mov	(z[0-9]+\.s), #2
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (divr_2_u32_m_tied1, svuint32_t,
		z0 = svdivr_n_u32_m (p0, z0, 2),
		z0 = svdivr_m (p0, z0, 2))

/*
** divr_2_u32_m_untied:
**	mov	(z[0-9]+\.s), #2
**	movprfx	z0, z1
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (divr_2_u32_m_untied, svuint32_t,
		z0 = svdivr_n_u32_m (p0, z1, 2),
		z0 = svdivr_m (p0, z1, 2))

/*
** divr_m1_u32_m:
**	mov	(z[0-9]+)\.b, #(-1|255)
**	udivr	z0\.s, p0/m, z0\.s, \1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_m1_u32_m, svuint32_t,
		z0 = svdivr_n_u32_m (p0, z0, -1),
		z0 = svdivr_m (p0, z0, -1))

/*
** divr_u32_z_tied1:
**	movprfx	z0\.s, p0/z, z0\.s
**	udivr	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_z_tied1, svuint32_t,
		z0 = svdivr_u32_z (p0, z0, z1),
		z0 = svdivr_z (p0, z0, z1))

/*
** divr_u32_z_tied2:
**	movprfx	z1\.s, p0/z, z1\.s
**	udiv	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_z_tied2, svuint32_t,
		z1 = svdivr_u32_z (p0, z0, z1),
		z1 = svdivr_z (p0, z0, z1))

/*
** divr_u32_z_untied:
**	movprfx	z0\.s, p0/z, z2\.s
**	udiv	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_z_untied, svuint32_t,
		z0 = svdivr_u32_z (p0, z1, z2),
		z0 = svdivr_z (p0, z1, z2))

/*
** divr_w0_u32_z_tied1:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, z0\.s
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_z_tied1, svuint32_t, uint32_t,
		 z0 = svdivr_n_u32_z (p0, z0, x0),
		 z0 = svdivr_z (p0, z0, x0))

/*
** divr_w0_u32_z_untied:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, \1
**	udiv	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_z_untied, svuint32_t, uint32_t,
		 z0 = svdivr_n_u32_z (p0, z1, x0),
		 z0 = svdivr_z (p0, z1, x0))

/*
** divr_s4_u32_z_tied1:
**	mov	(z[0-9]+\.s), s4
**	movprfx	z1\.s, p0/z, z1\.s
**	udivr	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_z_tied1, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_z (p0, z1, d4),
		 z1 = svdivr_z (p0, z1, d4))

/*
** divr_s4_u32_z_untied:
**	mov	(z[0-9]+\.s), s4
**	movprfx	z1\.s, p0/z, \1
**	udiv	z1\.s, p0/m, z1\.s, z2\.s
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_z_untied, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_z (p0, z2, d4),
		 z1 = svdivr_z (p0, z2, d4))

/*
** divr_u32_x_tied1:
**	udivr	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_x_tied1, svuint32_t,
		z0 = svdivr_u32_x (p0, z0, z1),
		z0 = svdivr_x (p0, z0, z1))

/*
** divr_u32_x_tied2:
**	udiv	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_x_tied2, svuint32_t,
		z1 = svdivr_u32_x (p0, z0, z1),
		z1 = svdivr_x (p0, z0, z1))

/*
** divr_u32_x_untied:
**	movprfx	z2, z1
**	udiv	z2\.s, p0/m, z2\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (divr_u32_x_untied, svuint32_t,
		z2 = svdivr_u32_x (p0, z0, z1),
		z2 = svdivr_x (p0, z0, z1))

/*
** divr_w0_u32_x_tied1:
**	mov	(z[0-9]+\.s), w0
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_x_tied1, svuint32_t, uint32_t,
		 z0 = svdivr_n_u32_x (p0, z0, x0),
		 z0 = svdivr_x (p0, z0, x0))

/*
** divr_w0_u32_x_untied:
**	mov	z1\.s, w0
**	udiv	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_ZS (divr_w0_u32_x_untied, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_x (p0, z0, x0),
		 z1 = svdivr_x (p0, z0, x0))

/*
** divr_s4_u32_x_tied1:
**	mov	(z[0-9]+\.s), s4
**	udivr	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_x_tied1, svuint32_t, uint32_t,
		 z1 = svdivr_n_u32_x (p0, z1, d4),
		 z1 = svdivr_x (p0, z1, d4))

/*
** divr_s4_u32_x_untied:
**	mov	z2\.s, s4
**	udiv	z2\.s, p0/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_ZS (divr_s4_u32_x_untied, svuint32_t, uint32_t,
		 z2 = svdivr_n_u32_x (p0, z1, d4),
		 z2 = svdivr_x (p0, z1, d4))

/*
** divr_2_u32_x_tied1:
**	mov	(z[0-9]+\.s), #2
**	udivr	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (divr_2_u32_x_tied1, svuint32_t,
		z0 = svdivr_n_u32_x (p0, z0, 2),
		z0 = svdivr_x (p0, z0, 2))

/*
** divr_2_u32_x_untied:
**	mov	z0\.s, #2
**	udiv	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (divr_2_u32_x_untied, svuint32_t,
		z0 = svdivr_n_u32_x (p0, z1, 2),
		z0 = svdivr_x (p0, z1, 2))
