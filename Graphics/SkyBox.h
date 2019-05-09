#pragma once
#include "Camera.h"
#include "Mesh.h"


//http://www.custommapmakers.org/skyboxes.php free skybox texture

namespace yuh {
	namespace graphics {


		struct GRAPHICS_API PathSkyBox {
				std::string right;
				std::string left;
				std::string top;
				std::string bottom;
				std::string front;
				std::string back;
		};

		class GRAPHICS_API SkyBox
		{
		public:
			SkyBox();
			~SkyBox();

			/* set once texture
			 *			 top
			 *			  |
			 *	left -- front -- right -- back
			 *			  |
			 *			bottom
			 */
			void setOneTexture(const char * path, unsigned int size);
			
			void setMultiTexture(const PathSkyBox& path);
			
			void setShader(Shader* shader);
			void setCamera(const Camera& camera);
			void setView(const math::Mat4f& view);
			void setProjection(const math::Mat4f& proj);

			math::Mat4f getView();
			math::Mat4f getProjection();
			GLuint		getIDCubeTexture();

			void draw();

		private:
			Shader      *m_shader;
			Mesh		 m_mesh;
			math::Mat4f	 m_view;
			math::Mat4f	 m_proj;
			GLuint		 m_textureID;

			void    initingShader();
			void	initingMultiTexture(const PathSkyBox& m_path);
			void    initingOneTexture(const char* path, unsigned int size);
			void	initingMesh();

		};

	}
}

