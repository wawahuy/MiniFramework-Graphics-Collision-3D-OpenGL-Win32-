#pragma once
#include "Vector3D.h"

namespace yuh {
	namespace math {

		class Sphere
		{
		public:
			Sphere();
			Sphere(const Vec3f& center, float R);
			~Sphere();

			void setCenter(const Vec3f& center);
			void setR(float R);

			Vec3f getCenter();
			float getR();

			bool testCollisionSphere(const Sphere& sphere);

		private:
			Vec3f m_center;
			float m_R;
		};


	}
}