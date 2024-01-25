#pragma once
#include "./vxl_layer.hpp"

#ifndef GLFW_WINDOW
#define GLFW_WINDOW
struct GLFWwindow;
#endif // VXL_WINDOW

namespace vxl {
	#ifndef VXL_WINDOW
	#define VXL_WINDOW
	class Window;
	#endif // VXL_WINDOW

	/// 
	/// A separate layer for imgui isn`t completly necessary, but is recommended if you use moonlightvxl`s layer system.
	/// 
	class VXL_API ImguiLayer : public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();
	public:
		virtual void draw() override;
		void imgui_begin();
		void imgui_finish();
	};
}