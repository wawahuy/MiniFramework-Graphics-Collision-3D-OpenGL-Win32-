#pragma once
#include "GJK.h"
#include <vector>

namespace yuh {
	namespace math {

		class Polygon
		{
		public:
			Polygon();
			Polygon(Vec3f *vertices, size_t num);
			~Polygon();

			void	set(Vec3f *vertices, size_t num);
			size_t	get(Vec3f *&vertices);

			bool isConvex();

			bool testPolygonWithSAT(const Polygon& polygon);

			bool testPolygonWithGJK(const Polygon& polygon);

		private:
			std::vector<Vec3f> m_vertices;
			GJK m_gjk;
		};

	}
}
