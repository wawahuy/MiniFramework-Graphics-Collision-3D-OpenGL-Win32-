#include "Projection.h"
#include <iostream>

namespace yuh {
	namespace math {
		
		/* Projection matrix frustum (major - column)
		 *
		 */
		Mat4f FrustumMatrix(float l, float r, float b, float t, float n, float f)
		{
			Mat4f matrix;
			matrix.m_mtrix[0][0] = 2 * n / (r - l);
			matrix.m_mtrix[1][1] = 2 * n / (t - b);
			matrix.m_mtrix[0][2] = (r + l) / (r - l);
			matrix.m_mtrix[1][2] = (t + b) / (t - b);
			matrix.m_mtrix[2][2] = -(f + n) / (f - n);
			matrix.m_mtrix[3][2] = -1;
			matrix.m_mtrix[2][3] = -(2 * f * n) / (f - n);
			matrix.m_mtrix[3][3] = 0;
			return matrix;
		}

		 Mat4f Ortho(float l, float r, float b, float t, float n, float f)
		 {
			 Mat4f matrix;
			 matrix.m_mtrix[0][0] = 2.0f / (r - l);
			 matrix.m_mtrix[1][1] = 2.0f / (t - b);
			 matrix.m_mtrix[2][2] = -2.0f / (f - n);
			 matrix.m_mtrix[0][3] = -(r+l) / (r-l);
			 matrix.m_mtrix[1][3] = -(t+b) / (t-b);
			 matrix.m_mtrix[2][3] = -(f+n) / (f-n);
			 return matrix;
		 }


		/* Projection matrix perspective (major - column)
		 *  
		 */
		Mat4f Perspective(float fovy, float width, float height, float near, float far)
		{
			float h = 1.0f / tan(fovy / 2.0f);
			float w = h * height / width;
			float ntf = near - far;

			Mat4f mat;
			mat.m_mtrix[0][0] = w;
			mat.m_mtrix[1][1] = h;
			mat.m_mtrix[2][2] = (near + far) / ntf;
			mat.m_mtrix[2][3] = (2 * near * far) / ntf;
			mat.m_mtrix[3][2] = -1.0f;
			mat.m_mtrix[3][3] =  0.0f;

			return mat;
		}



		Mat4f LookAt(Vec3f eye, Vec3f center, Vec3f up)
		{
			Vec3f f = VectorNormalize(center - eye);
			Vec3f s = VectorNormalize(VectorCross(f, up));
			Vec3f u = VectorCross(s, f);

			Mat4f mat;
			mat.m_mtrix[0][0] = s.x;
			mat.m_mtrix[0][1] = s.y;
			mat.m_mtrix[0][2] = s.z;
			mat.m_mtrix[1][0] = u.x;
			mat.m_mtrix[1][1] = u.y;
			mat.m_mtrix[1][2] = u.z;
			mat.m_mtrix[2][0] = -f.x;
			mat.m_mtrix[2][1] = -f.y;
			mat.m_mtrix[2][2] = -f.z;
			mat.m_mtrix[0][3] = s*eye*-1;
			mat.m_mtrix[1][3] = u*eye*-1;
			mat.m_mtrix[2][3] = f*eye;

			return mat;
		}


	}
}
