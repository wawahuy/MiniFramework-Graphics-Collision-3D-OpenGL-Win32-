#pragma once
#include "../Config.h"

#ifdef WINDOW_API_EXPORT
	#define WINDOW_API YUH_API_EXPORT
#else
	#define WINDOW_API YUH_API_IMPORT
#endif
