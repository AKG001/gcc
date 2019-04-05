/* { dg-do compile } */
/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** sub_s16_m_tied1:
**	sub	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_m_tied1, svint16_t,
		z0 = svsub_s16_m (p0, z0, z1),
		z0 = svsub_m (p0, z0, z1))

/* Bad RA choice: no preferred output sequence.  */
TEST_UNIFORM_Z (sub_s16_m_tied2, svint16_t,
		z1 = svsub_s16_m (p0, z0, z1),
		z1 = svsub_m (p0, z0, z1))

/*
** sub_s16_m_untied:
**	movprfx	z0, z1
**	sub	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_m_untied, svint16_t,
		z0 = svsub_s16_m (p0, z1, z2),
		z0 = svsub_m (p0, z1, z2))

/*
** sub_w0_s16_m_tied1:
**	mov	(z[0-9]+\.h), w0
**	sub	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_m_tied1, svint16_t, int16_t,
		 z0 = svsub_n_s16_m (p0, z0, x0),
		 z0 = svsub_m (p0, z0, x0))

/*
** sub_w0_s16_m_untied:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0, z1
**	sub	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_m_untied, svint16_t, int16_t,
		 z0 = svsub_n_s16_m (p0, z1, x0),
		 z0 = svsub_m (p0, z1, x0))

/*
** sub_h0_s16_m_tied1:
**	mov	(z[0-9]+\.h), h0
**	sub	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_m_tied1, svint16_t, int16_t,
		 z1 = svsub_n_s16_m (p0, z1, d0),
		 z1 = svsub_m (p0, z1, d0))

/*
** sub_h0_s16_m_untied:
**	mov	(z[0-9]+\.h), h0
**	movprfx	z1, z2
**	sub	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_m_untied, svint16_t, int16_t,
		 z1 = svsub_n_s16_m (p0, z2, d0),
		 z1 = svsub_m (p0, z2, d0))

/*
** sub_1_s16_m_tied1:
**	mov	(z[0-9]+)\.b, #-1
**	add	z0\.h, p0/m, z0\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_1_s16_m_tied1, svint16_t,
		z0 = svsub_n_s16_m (p0, z0, 1),
		z0 = svsub_m (p0, z0, 1))

/*
** sub_1_s16_m_untied:
**	mov	(z[0-9]+)\.b, #-1
**	movprfx	z0, z1
**	add	z0\.h, p0/m, z0\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_1_s16_m_untied, svint16_t,
		z0 = svsub_n_s16_m (p0, z1, 1),
		z0 = svsub_m (p0, z1, 1))

/*
** sub_m2_s16_m:
**	mov	(z[0-9]+\.h), #2
**	add	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_Z (sub_m2_s16_m, svint16_t,
		z0 = svsub_n_s16_m (p0, z0, -2),
		z0 = svsub_m (p0, z0, -2))

/*
** sub_s16_z_tied1:
**	movprfx	z0\.h, p0/z, z0\.h
**	sub	z0\.h, p0/m, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_z_tied1, svint16_t,
		z0 = svsub_s16_z (p0, z0, z1),
		z0 = svsub_z (p0, z0, z1))

/*
** sub_s16_z_tied2:
**	movprfx	z1\.h, p0/z, z1\.h
**	subr	z1\.h, p0/m, z1\.h, z0\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_z_tied2, svint16_t,
		z1 = svsub_s16_z (p0, z0, z1),
		z1 = svsub_z (p0, z0, z1))

/*
** sub_s16_z_untied:
**	movprfx	z0\.h, p0/z, z1\.h
**	sub	z0\.h, p0/m, z0\.h, z2\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_z_untied, svint16_t,
		z0 = svsub_s16_z (p0, z1, z2),
		z0 = svsub_z (p0, z1, z2))

/*
** sub_w0_s16_z_tied1:
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z0\.h
**	sub	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_z_tied1, svint16_t, int16_t,
		 z0 = svsub_n_s16_z (p0, z0, x0),
		 z0 = svsub_z (p0, z0, x0))

/*
** sub_w0_s16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), w0
**	movprfx	z0\.h, p0/z, z1\.h
**	sub	z0\.h, p0/m, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_z_untied, svint16_t, int16_t,
		 z0 = svsub_n_s16_z (p0, z1, x0),
		 z0 = svsub_z (p0, z1, x0))

/*
** sub_h0_s16_z_tied1:
**	mov	(z[0-9]+\.h), h0
**	movprfx	z1\.h, p0/z, z1\.h
**	sub	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_z_tied1, svint16_t, int16_t,
		 z1 = svsub_n_s16_z (p0, z1, d0),
		 z1 = svsub_z (p0, z1, d0))

/*
** sub_h0_s16_z_untied: { xfail *-*-* }
**	mov	(z[0-9]+\.h), h0
**	movprfx	z1\.h, p0/z, z2\.h
**	sub	z1\.h, p0/m, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_z_untied, svint16_t, int16_t,
		 z1 = svsub_n_s16_z (p0, z2, d0),
		 z1 = svsub_z (p0, z2, d0))

/*
** sub_s16_x_tied1:
**	sub	z0\.h, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_x_tied1, svint16_t,
		z0 = svsub_s16_x (p0, z0, z1),
		z0 = svsub_x (p0, z0, z1))

/*
** sub_s16_x_tied2:
**	sub	z1\.h, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_x_tied2, svint16_t,
		z1 = svsub_s16_x (p0, z0, z1),
		z1 = svsub_x (p0, z0, z1))

/*
** sub_s16_x_untied:
**	sub	z2\.h, z0\.h, z1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_s16_x_untied, svint16_t,
		z2 = svsub_s16_x (p0, z0, z1),
		z2 = svsub_x (p0, z0, z1))

/*
** sub_w0_s16_x_tied1:
**	mov	(z[0-9]+\.h), w0
**	sub	z0\.h, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_x_tied1, svint16_t, int16_t,
		 z0 = svsub_n_s16_x (p0, z0, x0),
		 z0 = svsub_x (p0, z0, x0))

/*
** sub_w0_s16_x_untied:
**	mov	(z[0-9]+\.h), w0
**	sub	z1\.h, z0\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_w0_s16_x_untied, svint16_t, int16_t,
		 z1 = svsub_n_s16_x (p0, z0, x0),
		 z1 = svsub_x (p0, z0, x0))

/*
** sub_h0_s16_x_tied1:
**	mov	(z[0-9]+\.h), h0
**	sub	z1\.h, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_x_tied1, svint16_t, int16_t,
		 z1 = svsub_n_s16_x (p0, z1, d0),
		 z1 = svsub_x (p0, z1, d0))

/*
** sub_h0_s16_x_untied:
**	mov	(z[0-9]+\.h), h0
**	sub	z2\.h, z1\.h, \1
**	ret
*/
TEST_UNIFORM_ZS (sub_h0_s16_x_untied, svint16_t, int16_t,
		 z2 = svsub_n_s16_x (p0, z1, d0),
		 z2 = svsub_x (p0, z1, d0))

/*
** sub_1_s16_x_tied1:
**	sub	z0\.h, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (sub_1_s16_x_tied1, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 1),
		z0 = svsub_x (p0, z0, 1))

/*
** sub_1_s16_x_untied:
**	movprfx	z0, z1
**	sub	z0\.h, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (sub_1_s16_x_untied, svint16_t,
		z0 = svsub_n_s16_x (p0, z1, 1),
		z0 = svsub_x (p0, z1, 1))

/*
** sub_127_s16_x:
**	sub	z0\.h, z0\.h, #127
**	ret
*/
TEST_UNIFORM_Z (sub_127_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 127),
		z0 = svsub_x (p0, z0, 127))

/*
** sub_128_s16_x:
**	sub	z0\.h, z0\.h, #128
**	ret
*/
TEST_UNIFORM_Z (sub_128_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 128),
		z0 = svsub_x (p0, z0, 128))

/*
** sub_255_s16_x:
**	sub	z0\.h, z0\.h, #255
**	ret
*/
TEST_UNIFORM_Z (sub_255_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 255),
		z0 = svsub_x (p0, z0, 255))

/*
** sub_256_s16_x:
**	add	z0\.h, z0\.h, #65280
**	ret
*/
TEST_UNIFORM_Z (sub_256_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 256),
		z0 = svsub_x (p0, z0, 256))

/*
** sub_257_s16_x:
**	mov	(z[0-9]+\.h), #-257
**	add	z0\.h, (z0\.h, \1|\1, z0\.h)
**	ret
*/
TEST_UNIFORM_Z (sub_257_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 257),
		z0 = svsub_x (p0, z0, 257))

/*
** sub_512_s16_x:
**	add	z0\.h, z0\.h, #65024
**	ret
*/
TEST_UNIFORM_Z (sub_512_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 512),
		z0 = svsub_x (p0, z0, 512))

/*
** sub_65280_s16_x:
**	add	z0\.h, z0\.h, #256
**	ret
*/
TEST_UNIFORM_Z (sub_65280_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, 0xff00),
		z0 = svsub_x (p0, z0, 0xff00))

/*
** sub_m1_s16_x:
**	add	z0\.h, z0\.h, #1
**	ret
*/
TEST_UNIFORM_Z (sub_m1_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -1),
		z0 = svsub_x (p0, z0, -1))

/*
** sub_m127_s16_x:
**	add	z0\.h, z0\.h, #127
**	ret
*/
TEST_UNIFORM_Z (sub_m127_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -127),
		z0 = svsub_x (p0, z0, -127))

/*
** sub_m128_s16_x:
**	add	z0\.h, z0\.h, #128
**	ret
*/
TEST_UNIFORM_Z (sub_m128_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -128),
		z0 = svsub_x (p0, z0, -128))

/*
** sub_m255_s16_x:
**	add	z0\.h, z0\.h, #255
**	ret
*/
TEST_UNIFORM_Z (sub_m255_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -255),
		z0 = svsub_x (p0, z0, -255))

/*
** sub_m256_s16_x:
**	add	z0\.h, z0\.h, #256
**	ret
*/
TEST_UNIFORM_Z (sub_m256_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -256),
		z0 = svsub_x (p0, z0, -256))

/*
** sub_m257_s16_x:
**	mov	(z[0-9]+)\.b, #1
**	add	z0\.h, z0\.h, \1\.h
**	ret
*/
TEST_UNIFORM_Z (sub_m257_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -257),
		z0 = svsub_x (p0, z0, -257))

/*
** sub_m512_s16_x:
**	add	z0\.h, z0\.h, #512
**	ret
*/
TEST_UNIFORM_Z (sub_m512_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -512),
		z0 = svsub_x (p0, z0, -512))

/*
** sub_m32768_s16_x:
**	add	z0\.h, z0\.h, #32768
**	ret
*/
TEST_UNIFORM_Z (sub_m32768_s16_x, svint16_t,
		z0 = svsub_n_s16_x (p0, z0, -0x8000),
		z0 = svsub_x (p0, z0, -0x8000))
