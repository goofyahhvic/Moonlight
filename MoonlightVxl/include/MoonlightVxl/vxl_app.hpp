#pragma once

#include "core.h"
#include "./EventSystem/vxl_event.hpp"
#include "./vxl_window.hpp"
#include "LayerSystem/vxl_imgui_layer.hpp"
#include "LayerSystem/vxl_layer_stack.hpp"

namespace vxl {
	class VXL_API App {
		using EventFn = std::function<void(Event& e)>;
	public:
		App(const uint32_t width = 1280U, const uint32_t height = 720U, const char* title = "Unnamed Window");
		virtual ~App() noexcept(false);
	public:
		virtual void Run();
		inline static App* Get() { return sm_This; }

		static inline void SetVersion(
			uint32_t variant = 0,
			uint32_t major = 1,
			uint32_t minor = 0,
			uint32_t patch = 0
		) { MOONLOIT_SET_VERSION(sm_Version, variant, major, minor, patch);
			Window::SetClientMoonloitInitInfo(&sm_Version); };
	protected:
		virtual void Update();

		virtual void OnEvent(Event& e);
		virtual void OnWindowClose();
		virtual void OnBoundWindowClose();
	protected:
		Window* window;
		ImguiLayer* imgui;
		vxl::LayerStack layers;
		bool shouldClose;
		static Version sm_Version;
	private:
		static App* sm_This;
	};
}