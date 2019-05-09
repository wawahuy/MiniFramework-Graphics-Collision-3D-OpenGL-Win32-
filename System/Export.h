#pragma once
#include "../Config.h"

#ifdef SYSTEM_API_EXPORT
	#define SYSTEM_API YUH_API_EXPORT
#else
	#define SYSTEM_API YUH_API_IMPORT
#endif