#pragma once
#include "Export.h"
#include <string>
#include <Window/OpenGL.h>
#include <System/FileInputStream.h>
#include <System/NonCopyable.h>
#include <Math/Vector2D.h>
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
#include <Math/Mat4.h>


namespace yuh {
	namespace graphics {

		class GRAPHICS_API Shader : NonCopyable
		{
		public:
			Shader();
			Shader(std::string contentVert, std::string contentFrag);
			Shader(FileInputStream& fileVert, FileInputStream& fileFrag);
			~Shader();

			void setWithCode(std::string contentVert, std::string contentFrag);
			
			void setWithFile(FileInputStream& fileVert, FileInputStream& fileFrag);

			void setUnitTextureName(unsigned int num = GLSL_YUH_TEXTURE_MAX);

			void bind();

			GLuint getID();
			GLuint getUniformLocation(const std::string& name);
			bool   isCompile();

			void uniformInt(const std::string& name, const int& vec1);
			void uniformFloat(const std::string& name, const float& vec1);
			void uniformBool(const std::string& name, bool select);
			void uniform(const std::string& name, const Vec2f& vec2);
			void uniform(const std::string& name, const Vec3f& vec3);
			void uniform(const std::string& name, const Vec4f& vec4);
			void uniformMat4f(const std::string& name, const float * pointer);

			static Shader* getShaderCurrent();

		private:
			GLuint createShader(const char * content, GLenum ge);

			std::string m_contentVert;
			std::string m_contentFrag;
			
			GLuint m_idVert;
			GLuint m_idFrag;
			GLuint m_idPrograme;
			bool   m_compile;
		};

	}	//end graphics
}	//end yuh