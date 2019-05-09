#pragma once
#include "Vector3D.h"

namespace yuh {
	namespace math {

		class Plane
		{
		public:
			Plane();

			/* Ax + By + Cz + D = 0
			 * 
			 */
			Plane(const Vec3f& normal, float D);


			/* Ax + By + Cz + D = 0
			 *
			 */
			Plane(float A, float B, float C, float D);
			
			~Plane();

			void  set(const Vec3f& normal, float D);
			void  set(float A, float B, float C, float D);
			Vec3f getNormal();
			float getD();

			void normalize();
			void computeWithPoint(const Vec3f& a, const Vec3f& b, const Vec3f& c);

			// Test poin on plane
			bool testPointIn(const Vec3f& point);

			// Plane * Point (normal*point + d)
			float operator* (const Vec3f& point);

		private:
			Vec3f m_normal;		// A, B, C	|						|
			float m_d;			// D		| Ax + By + Cz - D = 0  |  D = Vec(a, b, c)*Point In Plane
		};

	}
}

