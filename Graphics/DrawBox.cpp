#include "DrawBox.h"



namespace yuh {
	namespace graphics {

		DrawBox::DrawBox(const Vec3f & size) : Drawing()
		{
			m_size = size;

			float hx = m_size.x / 2;
			float hy = m_size.y / 2;
			float hz = m_size.z / 2;

			Vertex vertices[] = {
				Vertex(Vec3f(-hx, hy, hz), Vec3f(-1, 1, 1)),
				Vertex(Vec3f(-hx,-hy, hz), Vec3f(-1, -1, 1)),
				Vertex(Vec3f(hx,-hy, hz), Vec3f(1,-1, 1)),
				Vertex(Vec3f(hx, hy, hz), Vec3f(1,1,1)),
				Vertex(Vec3f(-hx, hy,-hz), Vec3f(-1, 1, -1)),
				Vertex(Vec3f(-hx,-hy,-hz), Vec3f(-1, -1, -1)),
				Vertex(Vec3f(hx,-hy,-hz), Vec3f(1, -1, -1)),
				Vertex(Vec3f(hx, hy,-hz), Vec3f(1,1,-1))
			};

			GLuint indices[] = {
				0, 1, 2, 3,
				3, 2, 6, 7,
				7, 6, 5, 4,
				4, 5, 1, 0,
				4, 0, 3, 7,
				5, 1, 2, 6
			};

			CopyArrayToVector(m_vertices, vertices);
			CopyArrayToVector(m_indices, indices);
 			initObject(GL_QUADS);
		}

		DrawBox::DrawBox(AABB aabb) : Drawing()
		{
			Vec3f* poss = aabb.getVertices();
			m_vertices.resize(8);
			for (int i = 0; i < 8; i++) {
				m_vertices[i] = Vertex(poss[i]);
			}

			GLuint indices[] = {
				0, 1, 2, 3,
				3, 2, 6, 7,
				7, 6, 5, 4,
				4, 5, 1, 0,
				4, 0, 3, 7,
				5, 1, 2, 6
			};

			CopyArrayToVector(m_indices, indices);
			initObject(GL_QUADS);
		}


		DrawBox::~DrawBox()
		{
		}

	}
}