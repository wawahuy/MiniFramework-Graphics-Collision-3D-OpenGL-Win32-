#include "Affine.h"

namespace yuh {
	namespace math {

		Mat4f AffineRotateX(float angle)
		{
			Mat4f mat;
			float cosa = cosf(angle);
			float sina = sinf(angle);

			mat.m_mtrix[1][1] = cosa;
			mat.m_mtrix[1][2] = -sina;
			mat.m_mtrix[2][1] = sina;
			mat.m_mtrix[2][2] = cosa;
			return mat;
		}

		Mat4f AffineRotateY(float angle)
		{
			Mat4f mat;
			float cosa = cosf(angle);
			float sina = sinf(angle);

			mat.m_mtrix[0][0] = cosa;
			mat.m_mtrix[0][2] = sina;
			mat.m_mtrix[2][0] = -sina;
			mat.m_mtrix[2][2] = cosa;
			return mat;
		}

		Mat4f AffineRotateZ(float angle)
		{
			Mat4f mat;
			float cosa = cosf(angle);
			float sina = sinf(angle);

			mat.m_mtrix[0][0] = cosa;
			mat.m_mtrix[0][1] = -sina;
			mat.m_mtrix[1][0] = sina;
			mat.m_mtrix[1][1] = cosa;
			return mat;
		}

		Mat4f AffineRotate(float angle, const Vec3f & vec)
		{
			return  AffineRotateX(angle*vec.x)*
					AffineRotateY(angle*vec.y)*
					AffineRotateZ(angle*vec.z);
		
		}

		Mat4f AffineTranslate(const Vec3f & vec)
		{
			Mat4f mat;
			mat.m_mtrix[0][3] = vec.x;
			mat.m_mtrix[1][3] = vec.y;
			mat.m_mtrix[2][3] = vec.z;
			return mat;
		}

		Mat4f AffineScale(const Vec3f & vec)
		{
			Mat4f mat;
			mat.m_mtrix[0][0] = vec.x;
			mat.m_mtrix[1][1] = vec.y;
			mat.m_mtrix[2][2] = vec.z;
			return mat;
		}

		Vec2f operator*(const Mat4f& mL, const Vec2f& mR)
		{
			return Vec2f(
						mL.m_mtrix[0][0] * mR.x + mL.m_mtrix[0][1] * mR.y + mL.m_mtrix[0][3],
						mL.m_mtrix[1][0] * mR.x + mL.m_mtrix[1][1] * mR.y + mL.m_mtrix[1][3]
						);
		}

		Vec3f operator*(const Mat4f& mL, const Vec3f& mR)
		{
			return Vec3f(
				mL.m_mtrix[0][0] * mR.x + mL.m_mtrix[0][1] * mR.y + mL.m_mtrix[0][2] * mR.z + mL.m_mtrix[0][3],
				mL.m_mtrix[1][0] * mR.x + mL.m_mtrix[1][1] * mR.y + mL.m_mtrix[1][2] * mR.z + mL.m_mtrix[1][3],
				mL.m_mtrix[2][0] * mR.x + mL.m_mtrix[2][1] * mR.y + mL.m_mtrix[2][2] * mR.z + mL.m_mtrix[2][3]
			);
		}

}
}
