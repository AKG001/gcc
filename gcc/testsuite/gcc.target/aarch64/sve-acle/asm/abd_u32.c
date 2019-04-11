/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** abd_u32_m_tied1:
**	uabd	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_m_tied1, svuint32_t,
		z0 = svabd_u32_m (p0, z0, z1),
		z0 = svabd_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (abd_u32_m_tied2, svuint32_t,
		z1 = svabd_u32_m (p0, z0, z1),
		z1 = svabd_m (p0, z0, z1))

/*
** abd_u32_m_untied:
**	movprfx	z0, z1
**	uabd	z0\.s, p0/m, z0\.s, z2\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_m_untied, svuint32_t,
		z0 = svabd_u32_m (p0, z1, z2),
		z0 = svabd_m (p0, z1, z2))

/*
** abd_w0_u32_m_tied1:
**	mov	(z[0-9]+\.s), w0
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_m_tied1, svuint32_t, uint32_t,
		 z0 = svabd_n_u32_m (p0, z0, x0),
		 z0 = svabd_m (p0, z0, x0))

/*
** abd_w0_u32_m_untied:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0, z1
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_m_untied, svuint32_t, uint32_t,
		 z0 = svabd_n_u32_m (p0, z1, x0),
		 z0 = svabd_m (p0, z1, x0))

/*
** abd_s0_u32_m_tied1:
**	mov	(z[0-9]+\.s), s0
**	uabd	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_m_tied1, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_m (p0, z1, d0),
		 z1 = svabd_m (p0, z1, d0))

/*
** abd_s0_u32_m_untied:
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1, z2
**	uabd	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_m_untied, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_m (p0, z2, d0),
		 z1 = svabd_m (p0, z2, d0))

/*
** abd_1_u32_m_tied1:
**	mov	(z[0-9]+\.s), #1
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u32_m_tied1, svuint32_t,
		z0 = svabd_n_u32_m (p0, z0, 1),
		z0 = svabd_m (p0, z0, 1))

/*
** abd_1_u32_m_untied:
**	mov	(z[0-9]+\.s), #1
**	movprfx	z0, z1
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u32_m_untied, svuint32_t,
		z0 = svabd_n_u32_m (p0, z1, 1),
		z0 = svabd_m (p0, z1, 1))

/*
** abd_u32_z_tied1:
**	movprfx	z0\.s, p0/z, z0\.s
**	uabd	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_z_tied1, svuint32_t,
		z0 = svabd_u32_z (p0, z0, z1),
		z0 = svabd_z (p0, z0, z1))

/*
** abd_u32_z_tied2:
**	movprfx	z1\.s, p0/z, z1\.s
**	uabd	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_z_tied2, svuint32_t,
		z1 = svabd_u32_z (p0, z0, z1),
		z1 = svabd_z (p0, z0, z1))

/*
** abd_u32_z_untied:
**	movprfx	z0\.s, p0/z, z1\.s
**	uabd	z0\.s, p0/m, z0\.s, z2\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_z_untied, svuint32_t,
		z0 = svabd_u32_z (p0, z1, z2),
		z0 = svabd_z (p0, z1, z2))

/*
** abd_w0_u32_z_tied1:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, z0\.s
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_z_tied1, svuint32_t, uint32_t,
		 z0 = svabd_n_u32_z (p0, z0, x0),
		 z0 = svabd_z (p0, z0, x0))

/*
** abd_w0_u32_z_untied:
**	mov	(z[0-9]+\.s), w0
**	movprfx	z0\.s, p0/z, \1
**	uabd	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_z_untied, svuint32_t, uint32_t,
		 z0 = svabd_n_u32_z (p0, z1, x0),
		 z0 = svabd_z (p0, z1, x0))

/*
** abd_s0_u32_z_tied1:
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1\.s, p0/z, z1\.s
**	uabd	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_z_tied1, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_z (p0, z1, d0),
		 z1 = svabd_z (p0, z1, d0))

/*
** abd_s0_u32_z_untied:
**	mov	(z[0-9]+\.s), s0
**	movprfx	z1\.s, p0/z, \1
**	uabd	z1\.s, p0/m, z1\.s, z2\.s
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_z_untied, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_z (p0, z2, d0),
		 z1 = svabd_z (p0, z2, d0))

/*
** abd_u32_x_tied1:
**	uabd	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_x_tied1, svuint32_t,
		z0 = svabd_u32_x (p0, z0, z1),
		z0 = svabd_x (p0, z0, z1))

/*
** abd_u32_x_tied2:
**	uabd	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_x_tied2, svuint32_t,
		z1 = svabd_u32_x (p0, z0, z1),
		z1 = svabd_x (p0, z0, z1))

/*
** abd_u32_x_untied:
**	movprfx	z2, z0
**	uabd	z2\.s, p0/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (abd_u32_x_untied, svuint32_t,
		z2 = svabd_u32_x (p0, z0, z1),
		z2 = svabd_x (p0, z0, z1))

/*
** abd_w0_u32_x_tied1:
**	mov	(z[0-9]+\.s), w0
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_x_tied1, svuint32_t, uint32_t,
		 z0 = svabd_n_u32_x (p0, z0, x0),
		 z0 = svabd_x (p0, z0, x0))

/*
** abd_w0_u32_x_untied:
**	mov	z1\.s, w0
**	uabd	z1\.s, p0/m, z1\.s, z0\.s
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u32_x_untied, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_x (p0, z0, x0),
		 z1 = svabd_x (p0, z0, x0))

/*
** abd_s0_u32_x_tied1:
**	mov	(z[0-9]+\.s), s0
**	uabd	z1\.s, p0/m, z1\.s, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_x_tied1, svuint32_t, uint32_t,
		 z1 = svabd_n_u32_x (p0, z1, d0),
		 z1 = svabd_x (p0, z1, d0))

/*
** abd_s0_u32_x_untied:
**	mov	z2\.s, s0
**	uabd	z2\.s, p0/m, z2\.s, z1\.s
**	ret
*/
TEST_UNIFORM_ZS (abd_s0_u32_x_untied, svuint32_t, uint32_t,
		 z2 = svabd_n_u32_x (p0, z1, d0),
		 z2 = svabd_x (p0, z1, d0))

/*
** abd_1_u32_x_tied1:
**	mov	(z[0-9]+\.s), #1
**	uabd	z0\.s, p0/m, z0\.s, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u32_x_tied1, svuint32_t,
		z0 = svabd_n_u32_x (p0, z0, 1),
		z0 = svabd_x (p0, z0, 1))

/*
** abd_1_u32_x_untied:
**	mov	z0\.s, #1
**	uabd	z0\.s, p0/m, z0\.s, z1\.s
**	ret
*/
TEST_UNIFORM_Z (abd_1_u32_x_untied, svuint32_t,
		z0 = svabd_n_u32_x (p0, z1, 1),
		z0 = svabd_x (p0, z1, 1))
