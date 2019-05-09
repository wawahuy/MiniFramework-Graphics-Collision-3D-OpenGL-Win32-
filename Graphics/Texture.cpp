/////////////////////////////////////////////////////////////////////////////////
// Texture.cpp
//
// AUTHOR: Nguyen Gia Huy
// CREATED: 05-08-2018
// UPDATED: 05-09-2018
//
// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
// 
// Copyright (C) Nguyen Gia Huy 2018
/////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include "Texture.h"

namespace yuh {
	namespace graphics {

		std::map<std::string, GLuint> listTexture;


		bool checkHasTexture(const char *texture, GLuint & m_id) {
			if (listTexture.find(texture) == listTexture.end()) return false;
			m_id = listTexture[texture];
			return true;
		}

		void addTextureList(const char *texture, GLuint m_id) {
			std::cout << "Add texture: " << texture << std::endl;
			listTexture.insert(std::pair<string, GLuint>(texture, m_id));
		}
		
		void removeTextureList(const char *texture) {
			listTexture.erase(texture);
		}

		Texture::Texture(const char * filename)
		{
			set(filename);
		}

		Texture::~Texture()
		{
		}

		void Texture::set(const char * filename)
		{
			if (checkHasTexture(filename, m_texture))
				return;

			stringstream sc;
			sc << filename;
			name = sc.str();

			unsigned char *data = stbi_load(filename, &width, &height, &numComponent, 4);

			if (!data) {
				cerr << "Error load file image!" << endl;
			}

			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);

			glBindTexture(GL_TEXTURE_2D, 0);
			
			addTextureList(filename, m_texture);
		}

		void Texture::bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
			removeTextureList(name.c_str());
		}

		GLuint Texture::getID()
		{
			return m_texture;
		}

		void Texture::setID(GLuint id)
		{
			m_texture = id;
		}

		void Texture::free()
		{
			glDeleteTextures(1, &m_texture);
		}

		int Texture::getWidth() const
		{
			return width;
		}

		int Texture::getHeight() const
		{
			return height;
		}

		void Texture::STBI_Free(unsigned char * data)
		{
			stbi_image_free(data);
		}

		unsigned char* Texture::STBI_Load(char const * filename, int * x, int * y, int * comp, int req_comp)
		{
			return stbi_load(filename, x, y, comp, req_comp);
		}

	}
}