#pragma once
#include "core.h"

#include <mlt_init.hpp>

namespace vxl {
	using Version = mlt::InitInfo::Version;

	VXL_API class Engine {
		Engine() {}
		~Engine() {}
	public:
		static void Init();
		static inline const Version& GetVersion() { return sm_Version; }
		static inline const std::string& to_string() { return sm_Name; }
	private:
		static Version sm_Version;
		static std::string sm_Name;
	};
}