#pragma once
#include "../Config.h"

#ifdef NETWORK_API_EXPORT
	#define NETWORK_API YUH_API_EXPORT
#else
	#define NETWORK_API YUH_API_IMPORT
#endif
