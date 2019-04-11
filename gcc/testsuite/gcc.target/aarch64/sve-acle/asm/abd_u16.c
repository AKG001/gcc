/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** abd_u16_m_tied1:
**	uabd	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_m_tied1, svuint16_t,
		z0 = svabd_u16_m (p0, z0, z1),
		z0 = svabd_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (abd_u16_m_tied2, svuint16_t,
		z1 = svabd_u16_m (p0, z0, z1),
		z1 = svabd_m (p0, z0, z1))

/*
** abd_u16_m_untied:
**	movprfx	z0, z1
**	uabd	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_m_untied, svuint16_t,
		z0 = svabd_u16_m (p0, z1, z2),
		z0 = svabd_m (p0, z1, z2))

/*
** abd_w0_u16_m_tied1:
**	mov	(z[0-9]+\.h), w0
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_m_tied1, svuint16_t, uint16_t,
		 z0 = svabd_n_u16_m (p0, z0, x0),
		 z0 = svabd_m (p0, z0, x0))

/*
** abd_w0_u16_m_untied:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0, z1
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_m_untied, svuint16_t, uint16_t,
		 z0 = svabd_n_u16_m (p0, z1, x0),
		 z0 = svabd_m (p0, z1, x0))

/*
** abd_h4_u16_m_tied1:
**	mov	(z[0-9]+\.h), h4
**	uabd	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_m_tied1, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_m (p0, z1, d4),
		 z1 = svabd_m (p0, z1, d4))

/*
** abd_h4_u16_m_untied:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1, z2
**	uabd	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_m_untied, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_m (p0, z2, d4),
		 z1 = svabd_m (p0, z2, d4))

/*
** abd_1_u16_m_tied1:
**	mov	(z[0-9]+\.h), #1
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u16_m_tied1, svuint16_t,
		z0 = svabd_n_u16_m (p0, z0, 1),
		z0 = svabd_m (p0, z0, 1))

/*
** abd_1_u16_m_untied:
**	mov	(z[0-9]+\.h), #1
**	movprfx	z0, z1
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u16_m_untied, svuint16_t,
		z0 = svabd_n_u16_m (p0, z1, 1),
		z0 = svabd_m (p0, z1, 1))

/*
** abd_u16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	uabd	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_z_tied1, svuint16_t,
		z0 = svabd_u16_z (p0, z0, z1),
		z0 = svabd_z (p0, z0, z1))

/*
** abd_u16_z_tied2:
**	movprfx	z1\.h, p0/z, z1\.h
**	uabd	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_z_tied2, svuint16_t,
		z1 = svabd_u16_z (p0, z0, z1),
		z1 = svabd_z (p0, z0, z1))

/*
** abd_u16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	uabd	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_z_untied, svuint16_t,
		z0 = svabd_u16_z (p0, z1, z2),
		z0 = svabd_z (p0, z1, z2))

/*
** abd_w0_u16_z_tied1:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z0\.h
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_z_tied1, svuint16_t, uint16_t,
		 z0 = svabd_n_u16_z (p0, z0, x0),
		 z0 = svabd_z (p0, z0, x0))

/*
** abd_w0_u16_z_untied:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, \1
**	uabd	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_z_untied, svuint16_t, uint16_t,
		 z0 = svabd_n_u16_z (p0, z1, x0),
		 z0 = svabd_z (p0, z1, x0))

/*
** abd_h4_u16_z_tied1:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1\.h, p0/z, z1\.h
**	uabd	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_z_tied1, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_z (p0, z1, d4),
		 z1 = svabd_z (p0, z1, d4))

/*
** abd_h4_u16_z_untied:
**	mov	(z[0-9]+\.h), h4
**	movprfx	z1\.h, p0/z, \1
**	uabd	z1\.h, p0/m, z1\.h, z2\.h
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_z_untied, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_z (p0, z2, d4),
		 z1 = svabd_z (p0, z2, d4))

/*
** abd_u16_x_tied1:
**	uabd	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_x_tied1, svuint16_t,
		z0 = svabd_u16_x (p0, z0, z1),
		z0 = svabd_x (p0, z0, z1))

/*
** abd_u16_x_tied2:
**	uabd	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_x_tied2, svuint16_t,
		z1 = svabd_u16_x (p0, z0, z1),
		z1 = svabd_x (p0, z0, z1))

/*
** abd_u16_x_untied:
**	movprfx	z2, z0
**	uabd	z2\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (abd_u16_x_untied, svuint16_t,
		z2 = svabd_u16_x (p0, z0, z1),
		z2 = svabd_x (p0, z0, z1))

/*
** abd_w0_u16_x_tied1:
**	mov	(z[0-9]+\.h), w0
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_x_tied1, svuint16_t, uint16_t,
		 z0 = svabd_n_u16_x (p0, z0, x0),
		 z0 = svabd_x (p0, z0, x0))

/*
** abd_w0_u16_x_untied:
**	mov	z1\.h, w0
**	uabd	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_ZS (abd_w0_u16_x_untied, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_x (p0, z0, x0),
		 z1 = svabd_x (p0, z0, x0))

/*
** abd_h4_u16_x_tied1:
**	mov	(z[0-9]+\.h), h4
**	uabd	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_x_tied1, svuint16_t, uint16_t,
		 z1 = svabd_n_u16_x (p0, z1, d4),
		 z1 = svabd_x (p0, z1, d4))

/*
** abd_h4_u16_x_untied:
**	mov	z2\.h, h4
**	uabd	z2\.h, p0/m, z2\.h, z1\.h
**	ret
*/
TEST_UNIFORM_ZS (abd_h4_u16_x_untied, svuint16_t, uint16_t,
		 z2 = svabd_n_u16_x (p0, z1, d4),
		 z2 = svabd_x (p0, z1, d4))

/*
** abd_1_u16_x_tied1:
**	mov	(z[0-9]+\.h), #1
**	uabd	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (abd_1_u16_x_tied1, svuint16_t,
		z0 = svabd_n_u16_x (p0, z0, 1),
		z0 = svabd_x (p0, z0, 1))

/*
** abd_1_u16_x_untied:
**	mov	z0\.h, #1
**	uabd	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (abd_1_u16_x_untied, svuint16_t,
		z0 = svabd_n_u16_x (p0, z1, 1),
		z0 = svabd_x (p0, z1, 1))
