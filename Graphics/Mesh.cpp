#include "Mesh.h"

namespace yuh {
	namespace graphics {

		Mesh::Mesh()
		{
			m_hasSetting = false;
			m_numTexture = 0;
		}


		Mesh::Mesh(const Vertex * vertices, uint numVertex, const uint * indices, uint numIndices, uint primitiveType, bool coverBox)
		{
			m_hasSetting = false;
			set(vertices, numVertex, indices, numIndices, primitiveType, coverBox);
		}

		Mesh::~Mesh()
		{
		}

		void Mesh::setTextures(const std::vector<Texture>& textures)
		{
			m_texture = textures;
			m_numTexture = textures.size();
		}

		void Mesh::setPrimitiveType(uint primitiveType)
		{
			m_primitiveType = primitiveType;
		}

		void Mesh::set(const Vertex * vertices, uint numVertex, const uint * indices, uint numIndices, uint primitiveType, bool coverBox)
		{
			if (m_hasSetting) {
				std::cerr << "Mesh da cai dat truoc do!" << std::endl;
				return;
			}

			if (coverBox) {
				computeCoverAABB(vertices, numVertex);
				computeCoverSphere(vertices, numVertex);
			}

			// mesh set 
			m_hasSetting = true;
			m_numIndices = numIndices;
			m_primitiveType = primitiveType;

			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			glGenBuffers(1, &m_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, MEM_VERTEX * numVertex, vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, MEM_VERTEX, (void*)MEM_POS_POS);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, MEM_VERTEX, (void*)MEM_NORMAL_POS);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, MEM_VERTEX, (void*)MEM_UV_POS);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, MEM_VERTEX, (void*)MEM_COLOR_POS);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glGenBuffers(1, &m_ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * numIndices, indices, GL_STATIC_DRAW);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		std::vector<Texture>* Mesh::getTextures()
		{
			return &m_texture;
		}

		//void Mesh::draw()
		//{
		//	Renderable::draw();

		//	//Copy Source LearnOpenGL
		//	for (unsigned int i = 0; i < m_numTexture; i++)
		//	{
		//		glActiveTexture(GL_TEXTURE0 + i);
		//		Shader::getShaderCurrent()->uniformInt(GLSL_YUH_TEXTURE_NAME + std::to_string(i), i);
		//		m_texture[i].bind();
		//	}

		//	//YUH Code
		//	glBindVertexArray(m_vao);
		//	glDrawElements(m_primitiveType, m_numIndices, GL_UNSIGNED_INT, 0);

		//	glActiveTexture(0);
		//}

		void Mesh::drawWithOutShader()
		{
			//Copy Source LearnOpenGL
			for (unsigned int i = 0; i < m_numTexture; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				Shader::getShaderCurrent()->uniformInt(GLSL_YUH_TEXTURE_NAME + std::to_string(i), i);
				m_texture[i].bind();
			}

			//YUH Code
			glBindVertexArray(m_vao);
			glDrawElements(m_primitiveType, m_numIndices, GL_UNSIGNED_INT, 0);

			glActiveTexture(0);
		}


		uint Mesh::getPrimitiveType()
		{
			return m_primitiveType;
		}

		uint Mesh::getNumIndices()
		{
			return m_numIndices;
		}

		void Mesh::bind()
		{
			glBindVertexArray(m_vao);
		}

		void Mesh::free()
		{
			//<-----update------>
			glDeleteBuffers(1, &m_vbo);
			glDeleteBuffers(1, &m_ibo);
			glDeleteVertexArrays(1, &m_vao);
			m_hasSetting = false;

		}
	}
}