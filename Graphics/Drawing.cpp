#include "Drawing.h"


namespace yuh {
	namespace graphics {

		Drawing::Drawing()
		{
			m_fill = true;
			m_lineWidth = 1;
			m_color = Vec3f(0, 0, 0);
			m_lighting = true;
		}


		Drawing::~Drawing()
		{
		}

		void Drawing::draw()
		{			
			Shader::getShaderCurrent()->bind();
			Shader::getShaderCurrent()->uniformMat4f(GLSL_YUH_MODEL, getMat4());
			drawWithOutModel();
		}

		void Drawing::drawDebug()
		{
		}

		void Drawing::drawWithOutShader()
		{
			// Setting Drawing
			if (!m_fill) glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, m_fill ? GL_FILL : GL_LINE);
			glLineWidth(m_lineWidth);

			// Draw mesh
			m_mesh.drawWithOutShader();

			// Back setting
			if (!m_fill) glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glLineWidth(1);
		}

		void Drawing::drawWithOutModel()
		{
			Shader::getShaderCurrent()->uniform(GLSL_YUH_DRAW_COLOR, m_color);
			drawWithOutShader();
			Shader::getShaderCurrent()->uniform(GLSL_YUH_DRAW_COLOR, Vec3f());
		}

		void Drawing::setLineWidth(float w)
		{
			m_lineWidth = w;
		}

		void Drawing::setColor(const Vec3f & color)
		{
			m_color = color;
		}

		void Drawing::setActiveLigting(bool active)
		{
			m_lighting = active;
		}


		size_t Drawing::getVertex(std::vector<Vec3f> &vertices)
		{
			size_t numVertex = m_indices.size();
			Mat4f  transform = this->getMat4();
			vertices.resize(numVertex);
			for (int i = 0; i < numVertex; i++) {
				vertices[i] = transform*m_vertices[m_indices[i]].position;
			}
			return numVertex;
		}

		void Drawing::free()
		{
			m_mesh.free();
		}

		void Drawing::initObject(GLuint primitiveType)
		{
			m_mesh.set(&m_vertices[0], m_vertices.size(), &m_indices[0], m_indices.size(), primitiveType, false);
		}

		void Drawing::setFill(bool fill)
		{
			m_fill = fill;
		}

	}
}
