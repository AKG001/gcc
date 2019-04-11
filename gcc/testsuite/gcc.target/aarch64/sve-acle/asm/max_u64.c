/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** max_u64_m_tied1:
**	umax	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_m_tied1, svuint64_t,
		z0 = svmax_u64_m (p0, z0, z1),
		z0 = svmax_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (max_u64_m_tied2, svuint64_t,
		z1 = svmax_u64_m (p0, z0, z1),
		z1 = svmax_m (p0, z0, z1))

/*
** max_u64_m_untied:
**	movprfx	z0, z1
**	umax	z0\.d, p0/m, z0\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_m_untied, svuint64_t,
		z0 = svmax_u64_m (p0, z1, z2),
		z0 = svmax_m (p0, z1, z2))

/*
** max_x0_u64_m_tied1:
**	mov	(z[0-9]+\.d), x0
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_m_tied1, svuint64_t, uint64_t,
		 z0 = svmax_n_u64_m (p0, z0, x0),
		 z0 = svmax_m (p0, z0, x0))

/*
** max_x0_u64_m_untied:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0, z1
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_m_untied, svuint64_t, uint64_t,
		 z0 = svmax_n_u64_m (p0, z1, x0),
		 z0 = svmax_m (p0, z1, x0))

/*
** max_d4_u64_m_tied1:
**	mov	(z[0-9]+\.d), d4
**	umax	z1\.d, p0/m, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_m_tied1, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_m (p0, z1, d4),
		 z1 = svmax_m (p0, z1, d4))

/*
** max_d4_u64_m_untied:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z1, z2
**	umax	z1\.d, p0/m, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_m_untied, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_m (p0, z2, d4),
		 z1 = svmax_m (p0, z2, d4))

/*
** max_1_u64_m_tied1:
**	mov	(z[0-9]+\.d), #1
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_m_tied1, svuint64_t,
		z0 = svmax_n_u64_m (p0, z0, 1),
		z0 = svmax_m (p0, z0, 1))

/*
** max_1_u64_m_untied:
**	mov	(z[0-9]+\.d), #1
**	movprfx	z0, z1
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_m_untied, svuint64_t,
		z0 = svmax_n_u64_m (p0, z1, 1),
		z0 = svmax_m (p0, z1, 1))

/*
** max_m1_u64_m:
**	mov	(z[0-9]+)\.b, #(-1|255)
**	umax	z0\.d, p0/m, z0\.d, \1\.d
**	ret
*/
TEST_UNIFORM_Z (max_m1_u64_m, svuint64_t,
		z0 = svmax_n_u64_m (p0, z0, -1),
		z0 = svmax_m (p0, z0, -1))

/*
** max_u64_z_tied1:
**	movprfx	z0\.d, p0/z, z0\.d
**	umax	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_z_tied1, svuint64_t,
		z0 = svmax_u64_z (p0, z0, z1),
		z0 = svmax_z (p0, z0, z1))

/*
** max_u64_z_tied2:
**	movprfx	z1\.d, p0/z, z1\.d
**	umax	z1\.d, p0/m, z1\.d, z0\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_z_tied2, svuint64_t,
		z1 = svmax_u64_z (p0, z0, z1),
		z1 = svmax_z (p0, z0, z1))

/*
** max_u64_z_untied:
**	movprfx	z0\.d, p0/z, z1\.d
**	umax	z0\.d, p0/m, z0\.d, z2\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_z_untied, svuint64_t,
		z0 = svmax_u64_z (p0, z1, z2),
		z0 = svmax_z (p0, z1, z2))

/*
** max_x0_u64_z_tied1:
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.d, p0/z, z0\.d
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_z_tied1, svuint64_t, uint64_t,
		 z0 = svmax_n_u64_z (p0, z0, x0),
		 z0 = svmax_z (p0, z0, x0))

/*
** max_x0_u64_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), x0
**	movprfx	z0\.d, p0/z, z1\.d
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_z_untied, svuint64_t, uint64_t,
		 z0 = svmax_n_u64_z (p0, z1, x0),
		 z0 = svmax_z (p0, z1, x0))

/*
** max_d4_u64_z_tied1:
**	mov	(z[0-9]+\.d), d4
**	movprfx	z1\.d, p0/z, z1\.d
**	umax	z1\.d, p0/m, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_z_tied1, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_z (p0, z1, d4),
		 z1 = svmax_z (p0, z1, d4))

/*
** max_d4_u64_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), d4
**	movprfx	z1\.d, p0/z, z2\.d
**	umax	z1\.d, p0/m, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_z_untied, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_z (p0, z2, d4),
		 z1 = svmax_z (p0, z2, d4))

/*
** max_1_u64_z_tied1:
**	mov	(z[0-9]+\.d), #1
**	movprfx	z0\.d, p0/z, z0\.d
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_z_tied1, svuint64_t,
		z0 = svmax_n_u64_z (p0, z0, 1),
		z0 = svmax_z (p0, z0, 1))

/*
** max_1_u64_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.d), #1
**	movprfx	z0\.d, p0/z, z1\.d
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_z_untied, svuint64_t,
		z0 = svmax_n_u64_z (p0, z1, 1),
		z0 = svmax_z (p0, z1, 1))

/*
** max_u64_x_tied1:
**	umax	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_x_tied1, svuint64_t,
		z0 = svmax_u64_x (p0, z0, z1),
		z0 = svmax_x (p0, z0, z1))

/*
** max_u64_x_tied2:
**	umax	z1\.d, p0/m, z1\.d, z0\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_x_tied2, svuint64_t,
		z1 = svmax_u64_x (p0, z0, z1),
		z1 = svmax_x (p0, z0, z1))

/*
** max_u64_x_untied:
**	movprfx	z2, z0
**	umax	z2\.d, p0/m, z2\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (max_u64_x_untied, svuint64_t,
		z2 = svmax_u64_x (p0, z0, z1),
		z2 = svmax_x (p0, z0, z1))

/*
** max_x0_u64_x_tied1:
**	mov	(z[0-9]+\.d), x0
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_x_tied1, svuint64_t, uint64_t,
		 z0 = svmax_n_u64_x (p0, z0, x0),
		 z0 = svmax_x (p0, z0, x0))

/*
** max_x0_u64_x_untied:
**	mov	z1\.d, x0
**	umax	z1\.d, p0/m, z1\.d, z0\.d
**	ret
*/
TEST_UNIFORM_ZS (max_x0_u64_x_untied, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_x (p0, z0, x0),
		 z1 = svmax_x (p0, z0, x0))

/*
** max_d4_u64_x_tied1:
**	mov	(z[0-9]+\.d), d4
**	umax	z1\.d, p0/m, z1\.d, \1
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_x_tied1, svuint64_t, uint64_t,
		 z1 = svmax_n_u64_x (p0, z1, d4),
		 z1 = svmax_x (p0, z1, d4))

/*
** max_d4_u64_x_untied:
**	mov	z2\.d, d4
**	umax	z2\.d, p0/m, z2\.d, z1\.d
**	ret
*/
TEST_UNIFORM_ZS (max_d4_u64_x_untied, svuint64_t, uint64_t,
		 z2 = svmax_n_u64_x (p0, z1, d4),
		 z2 = svmax_x (p0, z1, d4))

/*
** max_1_u64_x_tied1:
**	mov	(z[0-9]+\.d), #1
**	umax	z0\.d, p0/m, z0\.d, \1
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_x_tied1, svuint64_t,
		z0 = svmax_n_u64_x (p0, z0, 1),
		z0 = svmax_x (p0, z0, 1))

/*
** max_1_u64_x_untied:
**	mov	z0\.d, #1
**	umax	z0\.d, p0/m, z0\.d, z1\.d
**	ret
*/
TEST_UNIFORM_Z (max_1_u64_x_untied, svuint64_t,
		z0 = svmax_n_u64_x (p0, z1, 1),
		z0 = svmax_x (p0, z1, 1))
