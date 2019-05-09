#include "Shader.h"
#include <Math/Mat4.h>
#include <iostream>
#include <string>

namespace yuh {
	namespace graphics {

		Shader *shaderCurrent = 0;

		Shader::Shader()
		{
			m_idPrograme = 0;
		}

		Shader::Shader(std::string contentVert, std::string contentFrag)
		{
			setWithCode(contentVert, contentFrag);
		}

		Shader::Shader(FileInputStream & fileVert, FileInputStream & fileFrag)
		{
			setWithFile(fileVert, fileFrag);
		}

		Shader::~Shader()
		{
			glDetachShader(m_idPrograme, m_idVert);
			glDetachShader(m_idPrograme, m_idFrag);
			glDeleteShader(m_idVert);
			glDeleteShader(m_idFrag);
			glDeleteProgram(m_idPrograme);
		}

		void Shader::setWithCode(std::string contentVert, std::string contentFrag)
		{
			m_compile = false;
			m_contentVert = contentVert;
			m_contentFrag = contentFrag;

			m_idVert = createShader(contentVert.c_str(), GL_VERTEX_SHADER);
			m_idFrag = createShader(contentFrag.c_str(), GL_FRAGMENT_SHADER);

			if (!m_idFrag || !m_idVert) return;

			m_idPrograme = glCreateProgram();
			glAttachShader(m_idPrograme, m_idVert);
			glAttachShader(m_idPrograme, m_idFrag);
			glLinkProgram(m_idPrograme);

			m_compile = true;

		}

		void Shader::setWithFile(FileInputStream & fileVert, FileInputStream & fileFrag)
		{
			setWithCode(fileVert.getContent(), fileFrag.getContent());
		}

		void Shader::setUnitTextureName(unsigned int num)
		{
			bind();
			for (int i = 0; i < num; i++) {
				std::string name = GLSL_YUH_TEXTURE_NAME + std::to_string(i);
				//std::cout << "Location ID " << i << " Texture: " << getUniformLocation(name) << std::endl;
				uniformInt(name, i);
			}
			//std::cout << std::endl;
		}

		void Shader::bind()
		{
			glUseProgram(m_idPrograme);
			shaderCurrent = this;
		}

		GLuint Shader::createShader(const char * content, GLenum ge)
		{
			GLuint shader = glCreateShader(ge);
			glShaderSource(shader, 1, &content, NULL);
			glCompileShader(shader);
			
			//Log deltail
			char log[1024];
			int  success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, sizeof(log), NULL, log);
				std::cerr << "Error compile shader " << shader << ": " << log << std::endl;
				return 0;
			}

			return shader;
		}

		GLuint Shader::getID()
		{
			return m_idPrograme;
		}

		GLuint Shader::getUniformLocation(const std::string & name)
		{
			return glGetUniformLocation(m_idPrograme, name.c_str());
		}

		bool Shader::isCompile()
		{
			return m_compile;
		}

		void Shader::uniformInt(const std::string & name, const int & vec1)
		{
			glUniform1i(getUniformLocation(name), vec1);
		}

		void Shader::uniformFloat(const std::string & name, const float & vec1)
		{
			glUniform1f(getUniformLocation(name), vec1);
		}

		void Shader::uniform(const std::string & name, const Vec2f & vec2)
		{
			glUniform2f(getUniformLocation(name), vec2.x, vec2.y);
		}

		void Shader::uniform(const std::string & name, const Vec3f & vec3)
		{
			glUniform3f(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
		}

		void Shader::uniform(const std::string & name, const Vec4f & vec4)
		{
			glUniform4f(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
		}

		void Shader::uniformBool(const std::string & name, bool select)
		{
			glUniform1i(getUniformLocation(name), select);
		}

		void Shader::uniformMat4f(const std::string & name, const float * pointer)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, pointer);
		}

		Shader * Shader::getShaderCurrent()
		{
			return shaderCurrent;
		}

	}	//end graphics
}	//end yuh
