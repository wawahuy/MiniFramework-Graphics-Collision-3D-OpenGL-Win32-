#include "AABB.h"

namespace yuh {
	namespace math {

		AABB::AABB()
		{
		}

		AABB::AABB(const Vec3f & min, const Vec3f & max)
		{
			m_max = max;
			m_min = min;
		}

		AABB::~AABB()
		{
		}

		void AABB::set(const Vec3f & min, const Vec3f & max)
		{
			m_min = min;
			m_max = max;
		}

		void AABB::setWithOrigin(const Vec3f& origin, const Vec3f& halfsize)
		{
			m_min = origin - halfsize;
			m_max = origin + halfsize;
		}


		Vec3f AABB::getMax()
		{
			return m_max;
		}

		Vec3f AABB::getMin()
		{
			return m_min;
		}

		Vec3f AABB::getCenter()
		{
			return m_max*0.5f + m_min*0.5f;
		}

		Vec3f AABB::getSize()
		{
			return m_max - m_min;
		}

		Vec3f* AABB::getVertices()
		{
			if (!m_hasComputeVertex) {

				m_hasComputeVertex = true;

				Vec3f halfmin = m_min*0.5f;
				Vec3f halfmax = m_max*0.5f;
				Vec3f hs = halfmax - halfmin;		//half size
				Vec3f origin = halfmax + halfmin;

				m_vertices[0] = origin + Vec3f(-hs.x, hs.y, hs.z);
				m_vertices[1] = origin + Vec3f(-hs.x, -hs.y, hs.z);
				m_vertices[2] = origin + Vec3f(hs.x, -hs.y, hs.z);
				m_vertices[3] = m_max;

				m_vertices[4] = origin + Vec3f(-hs.x, hs.y, -hs.z);
				m_vertices[5] = origin + Vec3f(-hs.x, -hs.y, -hs.z);
				m_vertices[6] = origin + Vec3f(hs.x, -hs.y, -hs.z);
				m_vertices[7] = origin + Vec3f(hs.x, hs.y, -hs.z);
			}

			return m_vertices;
		}

		void AABB::translate(const Vec3f & trs)
		{
			m_min += trs;
			m_max += trs;
		}

		bool AABB::testOverlapAABB(const AABB & aabb)
		{
			if (m_max.x < aabb.m_min.x || aabb.m_max.x < m_min.x) return false;
			if (m_max.y < aabb.m_min.y || aabb.m_max.y < m_min.y) return false;
			if (m_max.z < aabb.m_min.z || aabb.m_max.z < m_min.z) return false;

			return true;
		}

		void AABB::computeWithVertices(const Vec3f * vertices, size_t num)
		{
			if (num == 0) return;

			Vec3f min = vertices[0];
			Vec3f max = vertices[0];

			for (int i = 1; i < num; i++) {
				if (min.x > vertices[i].x) min.x = vertices[i].x;
				if (min.y > vertices[i].y) min.y = vertices[i].y;
				if (min.z > vertices[i].z) min.z = vertices[i].z;

				if (max.x < vertices[i].x) max.x = vertices[i].x;
				if (max.y < vertices[i].y) max.y = vertices[i].y;
				if (max.z < vertices[i].z) max.z = vertices[i].z;
			}

			m_max = max;
			m_min = min;
		}

	}
}