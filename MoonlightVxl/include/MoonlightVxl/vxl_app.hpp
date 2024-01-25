#pragma once

#include "core.h"
#include "./EventSystem/vxl_event.hpp"
#include "./vxl_window.hpp"
#include "LayerSystem/vxl_imgui_layer.hpp"
#include "LayerSystem/vxl_layer_stack.hpp"

namespace vxl {
	class VXL_API App {
		using event_callback_function = std::function<void(Event& e)>;
	public:
		App(const uint32_t width = 1280, const uint32_t height = 720, const char* title = "Unnamed Window");
		virtual ~App();
	public:
		virtual void run();
	protected:
		virtual void update();

		virtual void on_event(Event& e);
		virtual void on_window_close();
	protected:
		Window window;
		ImguiLayer* imgui;
		vxl::LayerStack layers;
		bool should_close;
	};
}