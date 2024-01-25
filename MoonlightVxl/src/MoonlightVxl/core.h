#include "Moonloit/mlt_core.h"

#ifdef MLT_PLATFORM_WINDOWS
	#ifdef VXL_BUILD_SHARED
		#define VXL_API __declspec(dllexport)
	#elif VXL_IMPORT_SHARED
		#define VXL_API __declspec(dllimport)
	#else // building or using static lib
		#define VXL_API 
	#endif
#elif MLT_PLATFORM_LINUX
	#ifdef VXL_SHARED_LIB
		#define VXL_API __attribute__((visibility("default")))
	#else
		#define VXL_API 
	#endif
#endif