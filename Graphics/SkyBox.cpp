#include "SkyBox.h"

namespace yuh {
	namespace graphics {

		Shader SHADER_SKYBOX;

		SkyBox::SkyBox()
		{
			m_shader = &SHADER_SKYBOX;
			initingShader();
		}

		SkyBox::~SkyBox()
		{
		}

		void SkyBox::setMultiTexture(const PathSkyBox& path)
		{
			initingMultiTexture(path);
			initingMesh();
		}

		void SkyBox::setOneTexture(const char * path, unsigned int size)
		{
			initingOneTexture(path, size);
			initingMesh();
		}

		void SkyBox::setShader(Shader * shader)
		{
			m_shader = shader;
		}

		void SkyBox::setCamera(const Camera & camera)
		{
			// Get matrix view in "Camera Class"
			m_view = camera.getMatrixView();

			// Remove translate vector in column 4
			m_view.setCol(3, 0, 0, 0, 1);
		}

		void SkyBox::setView(const math::Mat4f & view)
		{
			m_view = view;
		}

		void SkyBox::setProjection(const math::Mat4f & proj)
		{
			m_proj = proj;
		}

		math::Mat4f SkyBox::getView()
		{
			return m_view;
		}

		math::Mat4f SkyBox::getProjection()
		{
			return m_proj;
		}

		GLuint SkyBox::getIDCubeTexture()
		{
			return m_textureID;
		}

		void SkyBox::draw()
		{
			glDepthFunc(GL_LEQUAL);
			m_shader->bind();
			m_shader->uniformMat4f(GLSL_YUH_PV, m_proj*m_view);
			m_mesh.draw();
			glDepthFunc(GL_LESS);
		}

		void SkyBox::initingShader()
		{
			if (!SHADER_SKYBOX.isCompile()) {
				std::string vert =
					"#version 130				\r\n"
					"in vec3 position;			\r\n"
					"out vec3 textcoord;		\r\n"
					"uniform mat4 "+ GLSL_YUH_PV +";		\r\n"
					"void main(){				\r\n"
					"	textcoord = position;	\r\n"
					"	gl_Position = ("+ GLSL_YUH_PV +"*vec4(position, 1.0)).xyww;	 \r\n"
					"}";

				std::string frag =
					"#version 130				\r\n"
					"in vec3 textcoord;			\r\n"
					"out vec4 color;			\r\n"
					"uniform samplerCube "+ GLSL_YUH_TEXTURE_NAME +"0;		\r\n"
					"void main(){ \r\n"\
					"	color = texture(texture0, textcoord); \r\n"
					"}";

				SHADER_SKYBOX.setWithCode(vert, frag);
			}
		}

		void SkyBox::initingMultiTexture(const PathSkyBox & m_path)
		{
			// Setting texture
			std::string pathArr[] = { m_path.right, m_path.left, m_path.top, m_path.bottom, m_path.front, m_path.back };

#pragma region  load texture, copy on learnopengl.com
			glGenTextures(1, &m_textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

			int width, height, nrChannels;
			for (unsigned int i = 0; i < 6; i++)
			{
				unsigned char *data = stbi_load(pathArr[i].c_str(), &width, &height, &nrChannels, 0);
				if (data)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
					);
					stbi_image_free(data);
				}
				else
				{
					std::cout << "Cubemap texture failed to load at path: " << pathArr[i] << std::endl;
					stbi_image_free(data);
				}
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
#pragma endregion
		}

		void SkyBox::initingOneTexture(const char * path, unsigned int size)
		{
			//Waitting for update...
			/*
			glGenTextures(1, &m_textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

			int width, height, nrChannels;
			unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

			if (width / 4.0 != size || height / 3.0 != size) {
				std::cerr << "Error size image in skybox!" << std::endl;
				stbi_image_free(data);
				return;
			}

			unsigned int   lenData = size*size;
			unsigned char *dataChild = new unsigned char[lenData];

			// Copy data on ROW 2
			GLuint target[] = {
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
			};

			int pos;
			int addXoffSet;
			int xoffset;
			int yoffset;

			for (int i = 0; i < 1; i++) {
				addXoffSet = 0;
				xoffset = size*i;
				yoffset = size;

				for (int j = 0; j < lenData; j++) {
					pos = yoffset*width + xoffset + addXoffSet;
					dataChild[j] = data[pos];
					addXoffSet++;
					if (addXoffSet >= size) {
						addXoffSet = 0;
						yoffset++;
					}
				}

				glTexImage2D(target[i], 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, dataChild);
			}

			
			delete[] dataChild;
			stbi_image_free(data);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			*/
		}

		void SkyBox::initingMesh()
		{
			std::vector<Texture> textures;
			textures.resize(1);
			textures[0].setID(m_textureID);

			// Setting mesh
			Vertex skyboxVertices[] = {
				// positions          
				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),

				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),

				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),

				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),

				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(1.0f,  1.0f, -1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f,  1.0f)),
				Vertex(Vec3f(-1.0f,  1.0f, -1.0f)),

				Vertex(Vec3f(-1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(1.0f, -1.0f, -1.0f)),
				Vertex(Vec3f(-1.0f, -1.0f,  1.0f)),
				Vertex(Vec3f(1.0f, -1.0f,  1.0f))
			};
			GLuint skyBoxIndices[] = {
				0, 1, 2, 3, 4, 5,
				6, 7, 8, 9, 10, 11,
				12, 13, 14, 15, 16, 17,
				18, 19, 20, 21, 22, 23,
				24, 25, 26, 27, 28, 29,
				30, 31, 32, 33, 34, 35
			};

			m_mesh.setTextures(textures);
			m_mesh.set(skyboxVertices, 36, skyBoxIndices, 36);
		}


	}
}
