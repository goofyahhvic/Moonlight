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
		Window() : m_Window(nullptr), m_Data({ 1280, 720 }), m_ShouldClose(false) {}
		~Window() {};
	public:
		using EventFn = std::function<void(Event& e)>;
		using CloseFn = std::function<void()>;

		using Windows = std::list<Window*>;

		struct WindowData {
			uint32_t _width, _height;
			EventFn on_event;
		};
	public:
		static Window* Create(uint32_t width = 1280U, uint32_t height = 720U, const char* title = "Unnamed Window");
		static void Destroy(Window* window);
		inline void Destroy() { Destroy(this); }

		static inline void Bind(Window* window) { if (sm_BoundWindow == window) return; sm_Windows.remove(window); sm_Windows.push_back(sm_BoundWindow); sm_BoundWindow = window; }
		inline void Bind() { Bind(this); }
		static inline Window* GetBound() { return sm_BoundWindow; }

		static void SetGlfwCallbacks(GLFWwindow* _window);
		static void GlfwPollEvents();
		static void GlfwMakeContextCurrent(GLFWwindow* _window);
		inline void GlfwMakeContextCurrent() const { GlfwMakeContextCurrent(m_Window); };
		inline GLFWwindow* GetGlfwWindow() const { return m_Window; }
		void GlfwSwapBuffers() const;

		inline void Close(bool value = true) { m_ShouldClose = value; }
		inline bool ShouldClose() const { return m_ShouldClose; }

		inline void SetEventCallback(const EventFn& on_event) { m_Data.on_event = on_event; }
		inline void SetDestroyCallback(const CloseFn& on_close) { m_OnDestroy = on_close; }
		static inline void SetBoundDestroyCallback(const CloseFn& on_bound_close) { sm_OnBoundDestroy = on_bound_close; }

		inline uint32_t GetWidth() const { return m_Data._width; }
		inline uint32_t GetHeight() const { return m_Data._height; }

		///
		/// Does not include the bound window.
		///
		static const Windows& GetWindows() { return sm_Windows; }
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;

		bool m_ShouldClose;
		CloseFn m_OnDestroy;

		static CloseFn sm_OnBoundDestroy;
		static Window* sm_BoundWindow;
		static Windows sm_Windows;
	};
}