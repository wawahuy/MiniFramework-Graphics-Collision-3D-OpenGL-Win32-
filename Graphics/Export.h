#pragma once
#include "../Config.h"
#include <string>

#ifdef GRAPHICS_API_EXPORT
	#define GRAPHICS_API YUH_API_EXPORT
#else
	#define GRAPHICS_API YUH_API_IMPORT
#endif


// Name
#define GLSL_YUH_PROJECTION		std::string("projection")
#define GLSL_YUH_VIEW			std::string("view")
#define GLSL_YUH_MODEL			std::string("model")
#define GLSL_YUH_PV				std::string("PV")
#define GLSL_YUH_TEXTURE_NAME	std::string("texture")		//0->MAX
#define GLSL_YUH_TEXTURE_MAX    8

// Drawing
#define GLSL_YUH_DRAW_COLOR 	std::string("draw_color")
