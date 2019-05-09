#include "Triangles.h"


namespace yuh {
	namespace math {

		Triangles::Triangles()
		{
		}

		Triangles::Triangles(const Vec3f & v1, const Vec3f & v2, const Vec3f & v3)
		{
			set(v1, v2, v3);
		}

		Triangles::Triangles(const float * v)
		{
			set(v);
		}


		Triangles::~Triangles()
		{
		}

		void Triangles::set(const Vec3f & v1, const Vec3f & v2, const Vec3f & v3)
		{
			m_vertices[0] = v1;
			m_vertices[1] = v2;
			m_vertices[2] = v3;
		}

		void Triangles::set(const float * v)
		{
			memcpy(m_vertices, v, sizeof(m_vertices));
		}

		Vec3f * Triangles::getVertices()
		{
			return m_vertices;
		}

		bool Triangles::testPointIn(const Vec3f& point)
		{
			/* Áp dụng kỉ thuật 1: tổng 3 góc được tảo bởi từ 3 vector, PA, PB, PC
			 * http://blackpawn.com/texts/pointinpoly/
			 *
			 **/
			/*
			Vec3f pa = m_vertices[0] - point;
			Vec3f pb = m_vertices[1] - point;
			Vec3f pc = m_vertices[2] - point;
			return cosf(
				acosf(VectorCorner(pa, pb)) +
				acosf(VectorCorner(pb, pc)) +
				acosf(VectorCorner(pc, pa))
			) == 1.0f;
			*/


			/* Áp dụng kỉ thuật 2: áp dụng với sản phẩm chéo
			 *
			 **/



			/* Áp dụng kỉ thuật 3: áp dụng với hệ tọa độ barycentric
			 *
			 **/
			return true;
		}

		bool Triangles::testCollision(const Triangles & triangles)
		{
			return false;
		}

	}
}