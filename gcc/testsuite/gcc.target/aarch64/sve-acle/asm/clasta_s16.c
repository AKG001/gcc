/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** clasta_x0_x0_s16:
**	clasta	w0, p0, w0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_x0_x0_s16, int16_t, svint16_t,
		x0 = svclasta_n_s16 (p0, x0, z2),
		x0 = svclasta (p0, x0, z2))

/*
** clasta_x0_x1_s16:
**	mov	w0, w1
**	clasta	w0, p0, w0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_x0_x1_s16, int16_t, svint16_t,
		x0 = svclasta_n_s16 (p0, x1, z2),
		x0 = svclasta (p0, x1, z2))

/*
** clasta_x0_d0_s16:
**	umov	w0, v0\.h\[0\]
**	clasta	w0, p0, w0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_x0_d0_s16, int16_t, svint16_t,
		x0 = svclasta_n_s16 (p0, d0, z2),
		x0 = svclasta (p0, d0, z2))

/*
** clasta_x0_d1_s16:
**	umov	w0, v1\.h\[0\]
**	clasta	w0, p0, w0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_x0_d1_s16, int16_t, svint16_t,
		x0 = svclasta_n_s16 (p0, d1, z2),
		x0 = svclasta (p0, d1, z2))

/*
** clasta_d0_x0_s16:
**	dup	v0\.4h, w0
**	clasta	h0, p0, h0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_d0_x0_s16, int16_t, svint16_t,
		d0 = svclasta_n_s16 (p0, x0, z2),
		d0 = svclasta (p0, x0, z2))

/*
** clasta_d0_x1_s16:
**	dup	v0\.4h, w1
**	clasta	h0, p0, h0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_d0_x1_s16, int16_t, svint16_t,
		d0 = svclasta_n_s16 (p0, x1, z2),
		d0 = svclasta (p0, x1, z2))

/*
** clasta_d0_d0_s16:
**	clasta	h0, p0, h0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_d0_d0_s16, int16_t, svint16_t,
		d0 = svclasta_n_s16 (p0, d0, z2),
		d0 = svclasta (p0, d0, z2))

/*
** clasta_d0_d1_s16:
**	dup	h0, v1\.h\[0\]
**	clasta	h0, p0, h0, z2\.h
**	ret
*/
TEST_FOLD_LEFT (clasta_d0_d1_s16, int16_t, svint16_t,
		d0 = svclasta_n_s16 (p0, d1, z2),
		d0 = svclasta (p0, d1, z2))

/*
** clasta_s16_tied1:
**	clasta	z0\.h, p0, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (clasta_s16_tied1, svint16_t,
		z0 = svclasta_s16 (p0, z0, z1),
		z0 = svclasta (p0, z0, z1))

/*
** clasta_s16_tied2:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	clasta	z0\.h, p0, z0\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (clasta_s16_tied2, svint16_t,
		z0 = svclasta_s16 (p0, z1, z0),
		z0 = svclasta (p0, z1, z0))

/*
** clasta_s16_untied:
**	movprfx	z0, z1
**	clasta	z0\.h, p0, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (clasta_s16_untied, svint16_t,
		z0 = svclasta_s16 (p0, z1, z2),
		z0 = svclasta (p0, z1, z2))
