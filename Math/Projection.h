#pragma once
#include "Mat4.h"

namespace yuh {
	namespace math {

		/* Projection matrix frustum (major - row)
		 *
		 */
		Mat4f FrustumMatrix(float l, float r, float b, float t, float n, float f);


		Mat4f Ortho(float l, float r, float b, float t, float n, float f);


		/* Projection matrix frustum (major - row)
		 *
		 */
		Mat4f Perspective(float fovy, float width, float height, float near, float far);


		Mat4f LookAt(Vec3f eye, Vec3f center, Vec3f up);
	}
}
