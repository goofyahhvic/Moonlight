#include "vxl_pch.hpp"
#include "vxl_app.hpp"

#include "EventSystem/vxl_app_event.hpp"
#include <glad/glad.h>

namespace vxl {
	App::App(const uint32_t width, const uint32_t height, const char* title)
		: should_close(false), window(width, height, title), imgui(nullptr) {
		window.set_event_callback([this](Event& e) {
			this->on_event(e);
		});
		window.set_close_callback([this]() {
			this->on_window_close();
		});

		imgui = new ImguiLayer();
		layers.push_overlay(imgui);
	}
	App::~App() {

	}

	void App::run() {
		while (!should_close) {
			window.glfw_poll_events();
			window.clear_frame();

			update();

			window.glfw_swap_buffers();
		}
	}

	void App::update() {
		for (Layer* layer : layers)
			layer->update();

		imgui->imgui_begin();
		for (Layer* layer : layers)
			layer->draw();
		imgui->imgui_finish();
	}

	void App::on_event(Event& e) {
		if EVENT_TYPE_IS(WindowClose) {
			window.close();
		}
	}
	void App::on_window_close() {
		should_close = true;
	}
}