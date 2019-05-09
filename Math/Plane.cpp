#include "Plane.h"


namespace yuh {
	namespace math {

		Plane::Plane()
		{
		}

		Plane::Plane(const Vec3f& normal, float D)
		{
			set(normal, D);
		}

		Plane::Plane(float A, float B, float C, float D)
		{
			set(A, B, C, D);
		}


		Plane::~Plane()
		{
		}

		void Plane::set(const Vec3f& normal, float D)
		{
			m_normal = normal;
			m_d = D;
		}

		void Plane::set(float A, float B, float C, float D)
		{
			m_normal = Vec3f(A, B, C);
			m_d = D;
		}

		Vec3f Plane::getNormal()
		{
			return m_normal;
		}

		float Plane::getD()
		{
			return m_d;
		}

		void Plane::normalize()
		{
			float dis = sqrt(m_normal.x*m_normal.x + m_normal.y*m_normal.y + m_normal.z*m_normal.z);
			m_normal.x /= dis;
			m_normal.y /= dis;
			m_normal.z /= dis;
			m_d /= dis;
		}

		void Plane::computeWithPoint(const Vec3f& a, const Vec3f& b, const Vec3f& c)
		{
			Vec3f ab = b - a;
			Vec3f ac = c - a;
			
			// ab x ac
			m_normal = VectorNormalize(VectorCross(ab, ac));

			// n*(X-A) = 0   <=>  n*X = n*A = D (factor)
			m_d = -(m_normal * a);

		}

		bool Plane::testPointIn(const Vec3f& point)
		{
			return (*this)*point == 0;
		}

		float Plane::operator*(const Vec3f& point)
		{
			return m_normal*point + m_d;
		}

	}
}