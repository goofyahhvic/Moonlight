#include "vxl_pch.hpp"
#include "vxl_window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Moonloit/mlt_exception.hpp>
#include "EventSystem/vxl_app_event.hpp"
#include "EventSystem/vxl_key_event.hpp"
#include "EventSystem/vxl_mouse_event.hpp"

namespace vxl {
	Window::Window(const uint32_t width, const uint32_t height, const char* title) {
		data.window_width = width;
		data.window_height = height;
		data.on_event = [this](Event& e) {
			if (e.get_event_type() == EventType::WindowClose) {
				close();
			}
		};
		should_close = false;
		on_close = []() {};

		int32_t result = glfwInit();
		MOONLOIT_ASSERT(result, "Could not initialize glfw!");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetErrorCallback([](int error, const char* description) {
			throw moonloit::Exception(fmt::format("GLFW error #{0}: {1}", error, description));
		});
		window = glfwCreateWindow(
			width, height,
			title,
			NULL, NULL
		);
		MOONLOIT_ASSERT(window, "Could not create the window!");
		glfwMakeContextCurrent(window);
		result = gladLoadGL();
		MOONLOIT_ASSERT(result, "Could not initiliaze glad!");
		glViewport(0, 0, width, height);

		glfwSetWindowUserPointer(window, &data);
		set_glfw_callbacks();
	}
	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::set_event_callback(event_callback on_event) {
		data.on_event = on_event;
	}
	void Window::set_close_callback(close_callback on_close) {
		this->on_close = on_close;
	}

	void Window::glfw_poll_events() const {
		glfwPollEvents();
	}
	void Window::glfw_swap_buffers() const {
		glfwSwapBuffers(window);
	}

	void Window::clear_frame(float r, float g, float b, float a) const {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool Window::get_should_close() const {
		return should_close;
	}
	void Window::close() {
		should_close = true;
		on_close();
	}

	GLFWwindow* Window::get_glfw_window() const {
		return window;
	}

	void Window::set_glfw_callbacks() {
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.window_width = width;
			data.window_height = height;

			glViewport(0, 0, width, height);

			WindowResizeEvent e(width, height);
			data.on_event(e);
		});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.on_event(event);
		});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.on_event(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.on_event(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.on_event(event);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.on_event(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.on_event(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double y_offset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(x_offset, y_offset);
			data.on_event(event);
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(x, y);
			data.on_event(event);
		});
	}
}