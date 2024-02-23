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
		virtual ~App();
	public:
		virtual void Run();
		inline static App* Get() { return sm_This; }
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
	private:
		static App* sm_This;
	};
}