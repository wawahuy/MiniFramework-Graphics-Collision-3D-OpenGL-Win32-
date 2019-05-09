#include "Polygon.h"


namespace yuh {
	namespace math {

		Polygon::Polygon()
		{
		}

		Polygon::Polygon(Vec3f * vertices, size_t num)
		{
			set(vertices, num);
		}


		Polygon::~Polygon()
		{
		}

		void Polygon::set(Vec3f * vertices, size_t num)
		{
			m_vertices.resize(num);
			std::memcpy(&m_vertices[0].x, &vertices->x, num*sizeof(*vertices));
		}

		size_t Polygon::get(Vec3f *& vertices)
		{
			vertices = &m_vertices[0];
			return m_vertices.size();
		}

		bool Polygon::isConvex()
		{
			size_t num = m_vertices.size();

			if( num )

			for (int i = 0; i < num; i++) {

			}

			return false;
		}

		bool Polygon::testPolygonWithSAT(const Polygon & polygon)
		{
			return false;
		}

		bool Polygon::testPolygonWithGJK(const Polygon & polygon)
		{
			return false;
		}

	}
}
