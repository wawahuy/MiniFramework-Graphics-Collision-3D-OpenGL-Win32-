#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Mat4.h"

/* All Matrix Afine with Major - column
 * If you want get matrix major - row, have to use transponse
 *
 */

namespace yuh {
	namespace math {

		Mat4f AffineRotateX(float angle);
		Mat4f AffineRotateY(float angle);
		Mat4f AffineRotateZ(float angle);

		/* Afine rotate matrix (major - row)
		 *
		 */
		Mat4f AffineRotate(float angle, const Vec3f& vec);


		/* Afine translate matrix (major - row)
		 *
		 */
		Mat4f AffineTranslate(const Vec3f& vec);


		/* Afine scake matrix (major - row)
		 *
		 */
		Mat4f AffineScale(const Vec3f& vec);


		/* Mat4 * Vec2 ( Vec2 is Vec4 has (v0,v1,0,1)) only coord 2D Affine
		__				   __				__	   __
		|	a	b	c	d	|				|  v0	|
		|	e	f	g	h	|				|  v1	|
		|	i	j	k	l	|		*		|  0.0	|
		|	m	n	o	p	|				|  1.0	|
		--				   --				--	   --
		*/
		Vec2f operator *(const Mat4f& mL, const Vec2f& mR);



		/* Mat4 * Vec3 ( Vec3 is Vec4 has (v0,v1,v2,1.0)) only coord 3D Affine
		__				   __				__	   __
		|	a	b	c	d	|				|  v0	|
		|	e	f	g	h	|				|  v1	|
		|	i	j	k	l	|		*		|  v2	|
		|	m	n	o	p	|				|  1.0	|
		--				   --				--	   --
		*/
		Vec3f operator *(const Mat4f& mL, const Vec3f& mR);
	}
}