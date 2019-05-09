/////////////////////////////////////////////////////////////////////////////////
// Texture.h
//
// AUTHOR: Nguyen Gia Huy
// CREATED: 02-08-2018
// UPDATED: 05-09-2018
//
// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
// 
// Copyright (C) Nguyen Gia Huy 2018
/////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <iostream>
#include <sstream>
#include "Export.h"
#include "Stbimage.h"
#include <Window/OpenGL.h>
using namespace std;

namespace yuh {
	namespace graphics {

		class GRAPHICS_API Texture
		{
		public:
			Texture() {}
			Texture(const char *filename);
			virtual ~Texture();

			virtual void set(const char * filename);
			inline virtual void bind();

			GLuint getID();
			void   setID(GLuint id);

			void free();

			virtual int getWidth()  const;
			virtual int getHeight() const;

			static unsigned char* STBI_Load(char const *filename, int *x, int *y, int *comp, int req_comp);
			static void STBI_Free(unsigned char* data);

			string TypeName;

		private:
			string name;
			GLuint m_texture;
			int width;
			int height;
			int numComponent;
		};

	}	//end graphics
}	//end yuh
#endif