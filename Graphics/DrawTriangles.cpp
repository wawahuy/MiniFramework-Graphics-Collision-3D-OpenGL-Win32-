#include "DrawTriangles.h"


namespace yuh {
	namespace graphics {

		DrawTriangles::DrawTriangles(const Vec3f & p1, const Vec3f & p2, const Vec3f & p3)
		{
			Vertex vertices[] = {
				Vertex(p1),
				Vertex(p2),
				Vertex(p3)
			};

			GLuint indices[] = { 0, 1, 2 };

			CopyArrayToVector(m_vertices, vertices);
			CopyArrayToVector(m_indices, indices);
			initObject(GL_TRIANGLES);
		}

		DrawTriangles::~DrawTriangles()
		{
		}

	}
}