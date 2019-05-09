#pragma once
#include "Vector3D.h"
#include "GeometryFunction.h"

namespace yuh {
	namespace math {

		class Triangles
		{
		public:
			Triangles();
			Triangles(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3);
			Triangles(const float *v);
			~Triangles();

			void set(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3);
			void set(const float *v);

			Vec3f* getVertices();

			bool testPointIn(const Vec3f& point);

			bool testCollision(const Triangles& triangles);

		private:
			Vec3f m_vertices[3];

		};

	}
}

