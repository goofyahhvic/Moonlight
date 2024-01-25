#pragma once
#include "core.h"

#ifndef GLFW_WINDOW
#define GLFW_WINDOW
struct GLFWwindow;
#endif // GLFW_WINDOW

namespace vxl {
	#ifndef VXL_EVENT
	#define VXL_EVENT
	class Event;
	#endif // VXL_EVENT

	class VXL_API Window {
		using event_callback = std::function<void(Event& e)>;
		using close_callback = std::function<void()>;
	public:
		Window(const uint32_t width = 1280, const uint32_t height = 720, const char* title = "Unnamed Window");
		~Window();
	public:
		///
		/// The function given will be called whenever any window related event is dispatched.
		/// By default, calls Window::close() if event type is WindowCloseEvent. 
		///
		void set_event_callback(event_callback on_event);
		///
		/// The function given will be called whenever Window::should_close is true, and not when a WindowCloseEvent is dispatched.
		/// Empty by default. 
		///
		void set_close_callback(close_callback on_close);

		void glfw_poll_events() const;
		void glfw_swap_buffers() const;

		void clear_frame(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;

		bool get_should_close() const;
		/// 
		/// Sets Window::should_close to true and calls Window::on_close.
		/// Window::on_close is empty by default. 
		///
		void close();

		GLFWwindow* get_glfw_window() const;
	private:
		void set_glfw_callbacks();
	private:
		GLFWwindow* window;
		struct WindowData {
			uint32_t window_width, window_height;
			event_callback on_event;
		};
		WindowData data;

		bool should_close;
		close_callback on_close;
	};
}