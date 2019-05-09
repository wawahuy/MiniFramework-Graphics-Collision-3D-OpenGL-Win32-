#pragma once
#include "Export.h"
#include "Renderable.h"
#include "Vertex.h"
#include <Window/OpenGL.h>
#include <System/NonCopyable.h>
#include <vector>
#include <memory>
#include "Texture.h"
#define uint unsigned int

namespace yuh {
	namespace graphics {

		class GRAPHICS_API Mesh : NonCopyable, public Renderable
		{
			friend class InstanceModelTBO;

		public:
			Mesh();
			Mesh(const Vertex *vertices, uint numVertex, const uint *indices, uint numIndices, uint primitiveType = GL_TRIANGLES, bool coverBox = true);
			~Mesh();

			void setTextures(const std::vector<Texture> &textures);

			void setPrimitiveType(uint primitiveType);

			void set(const Vertex *vertices, uint numVertex, const uint *indices, uint numIndices, uint primitiveType = GL_TRIANGLES, bool coverBox = true);
			
			std::vector<Texture>* getTextures();

			uint   getPrimitiveType();

			uint   getNumIndices();

			void bind();

			// Overide abstract Renderable
			void drawWithOutShader();

			void free();

		private:
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ibo;
			uint   m_numIndices;
			uint   m_primitiveType;
			bool   m_hasSetting;

			std::vector<Texture> m_texture;
			uint m_numTexture;
		};


	}
}