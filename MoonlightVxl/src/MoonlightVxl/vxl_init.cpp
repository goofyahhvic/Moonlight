#include "vxl_pch.hpp"
#include "vxl_init.hpp"

namespace vxl {
	Version     Engine::sm_Version;
	std::string Engine::sm_Name;

	void Engine::Init() {
		mlt::Log::Init();
		MOONLOIT_SET_VERSION(sm_Version, 0, 1, 0, 0);
		sm_Name = "Moonlight by ELECTROWAVE";
	}
}