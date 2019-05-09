#pragma once
#include "Renderable.h"
#include "Mesh.h"
#include "Shader.h"
#include "Tranformable.h"
#include "System/FunctionSystem.h"


namespace yuh {
	namespace graphics {

		class GRAPHICS_API Drawing : public Renderable, NonCopyable
		{
		public:
			Drawing();
			~Drawing();

			void draw();

			void drawDebug();

			void drawWithOutShader();

			void drawWithOutModel();

			void setFill(bool fill);
			void setLineWidth(float w);
			void setColor(const Vec3f& color);
			void setActiveLigting(bool active);

			size_t getVertex(std::vector<Vec3f> &vertices);

			void free();

		protected:
			std::vector<Vertex> m_vertices;
			std::vector<GLuint> m_indices;
			void initObject(GLuint primitiveType);

		private:
			bool  m_fill;
			bool  m_lighting;
			float m_lineWidth;
			Vec3f m_color;
			Mesh  m_mesh;

		};

	}
}

