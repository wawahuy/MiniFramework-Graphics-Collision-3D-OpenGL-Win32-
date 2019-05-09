#include "Sphere.h"


namespace yuh {
	namespace  math {

		Sphere::Sphere()
		{
			m_center = Vec3f(0, 0, 0);
			m_R = 0;
		}

		Sphere::Sphere(const Vec3f & center, float R)
		{
			m_center = center;
			m_R = R;
		}


		Sphere::~Sphere()
		{
		}

		void Sphere::setCenter(const Vec3f & center)
		{
			m_center = center;
		}

		void Sphere::setR(float R)
		{
			m_R = R;
		}

		Vec3f Sphere::getCenter()
		{
			return m_center;
		}

		float Sphere::getR()
		{
			return m_R;
		}

		bool Sphere::testCollisionSphere(const Sphere & sphere)
		{
			Vec3f vectorR1R2 = m_center - sphere.m_center;
			float totalSquareR = (m_R + sphere.m_R)*(m_R + sphere.m_R);
			float distanceSquareCenter = vectorR1R2.x*vectorR1R2.x + vectorR1R2.y*vectorR1R2.y +vectorR1R2.z*vectorR1R2.z;
			return totalSquareR <= distanceSquareCenter;
		}

	}
}
