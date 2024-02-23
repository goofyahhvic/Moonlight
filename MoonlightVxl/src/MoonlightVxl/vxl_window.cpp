#include "vxl_pch.hpp"
#include "vxl_window.hpp"

#include <GLFW/glfw3.h>
#ifdef MLT_PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
#elif MLT_PLATFORM_LINUX
	#define GLFW_EXPOSE_NATIVE_X11
#endif
#include <GLFW/glfw3native.h>

#include <Moonloit/Moonloit.hpp>
#include "EventSystem/vxl_app_event.hpp"
#include "EventSystem/vxl_key_event.hpp"
#include "EventSystem/vxl_mouse_event.hpp"

namespace vxl {
	Window* Window::sm_BoundWindow;
	Window::CloseFn Window::sm_OnBoundDestroy;
	Window::Windows Window::sm_Windows;

	Window* Window::Create(uint32_t width, uint32_t height, const char* title) {
		Window* window = new Window();
		MOONLOIT_ASSERT(window, "Failed creating window!");

		window->m_Data._width = width;
		window->m_Data._height = height;
		window->m_ShouldClose = false;
		window->m_Window = nullptr;

		window->m_Data.on_event = [window] (Event& e) {
			if (e.GetEventType() == EventType::WindowClose) {
				window->Close();
				Window::Destroy(window);
			}
		};
		window->m_OnDestroy = [](){};

		if (sm_BoundWindow) {
			sm_Windows.push_back(window);

			window->m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
			MOONLOIT_ASSERT(window->m_Window, "Failed creating GLFWwindow!");
			glfwSetWindowUserPointer(window->m_Window, &window->m_Data);
		} else {
			sm_BoundWindow = window;
			int result = glfwInit();
			MOONLOIT_ASSERT(result, "Failed initializing glfw!");
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			window->m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
			MOONLOIT_ASSERT(window->m_Window, "Failed creating GLFWwindow!");
			glfwSetWindowUserPointer(window->m_Window, &window->m_Data);

			mlt::InitInfo init;
			mlt::RenderAPI::Init(init);
		}
		
		SetGlfwCallbacks(window->m_Window);
		return window;
	}

	void Window::Destroy(Window* window) {
		if (!window) return;
		window->m_OnDestroy();
		glfwDestroyWindow(window->m_Window);
		if (window == sm_BoundWindow) {
			sm_OnBoundDestroy();
			sm_BoundWindow = nullptr;
			for (auto _window : sm_Windows) {
				_window->m_OnDestroy();
				glfwDestroyWindow(_window->m_Window);
				delete _window;
			}
			sm_Windows.clear();
			glfwTerminate();
		} else {
			sm_Windows.remove(window);
		}
		delete window;
		window = nullptr;
	}

	void Window::GlfwPollEvents() { glfwPollEvents(); }
	void Window::GlfwMakeContextCurrent(GLFWwindow* _window) { glfwMakeContextCurrent(_window); }
	void Window::GlfwSwapBuffers() const { glfwSwapBuffers(m_Window); }

	void Window::SetGlfwCallbacks(GLFWwindow* _window) {
		glfwSetWindowSizeCallback(_window, [] (GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data._width = width;
			data._height = height;

			WindowResizeEvent e(width, height);
			data.on_event(e);
		});
		glfwSetWindowCloseCallback(_window, [] (GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.on_event(event);
		});
		glfwSetKeyCallback(_window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.on_event(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.on_event(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.on_event(event);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(_window, [] (GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.on_event(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.on_event(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(_window, [] (GLFWwindow* window, double x_offset, double y_offset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(x_offset, y_offset);
			data.on_event(event);
		});
		glfwSetCursorPosCallback(_window, [] (GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(x, y);
			data.on_event(event);
		});
	}
}