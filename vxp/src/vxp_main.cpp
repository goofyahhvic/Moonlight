#include "vxp_pch.hpp"
#include "./vxp_main.hpp"

#include <imgui/imgui.h>

namespace vxp {
	Layer::Layer()
		: vxl::Layer() {

	}
	Layer::~Layer() {

	}

	void Layer::on_event(vxl::Event& e) {
		vxl::Layer::on_event(e);
		if EVENT_TYPE_IS(KeyPressed) {
			if (EVENT_KEYCODE_IS(GLFW_KEY_0)) {
				MOONLOIT_APP_TRACE("Key 0 has been pressed!");
			}
		}
	}
	void Layer::update() {
		auto [x, y] = vxl::GlobalInput::get_mouse_position();
		if (input.get_key(GLFW_KEY_W)) {
			MOONLOIT_APP_INFO("Key W is pressed!");
		}
		if (input.get_key(GLFW_KEY_A)) {
			MOONLOIT_APP_INFO("Key A is pressed!");
		}
		if (input.get_key(GLFW_KEY_S)) {
			MOONLOIT_APP_INFO("Key S is pressed!");
		}
		if (input.get_key(GLFW_KEY_D)) {
			MOONLOIT_APP_INFO("Key D is pressed!");
		}
		//VXL_APP_INFO("x: {0}, y: {1}", x, y);
	}
	void Layer::draw() {
		ImGui::Begin("Test");
		ImGui::Text("Hello, world!");
		ImGui::End();
	}

	Voxploration::Voxploration(const uint32_t width, const uint32_t height)
		: vxl::App(width, height, "Voxploration") {
		layers.push_layer(new Layer());
	}
	Voxploration::~Voxploration() {

	}

	void Voxploration::on_event(vxl::Event& e) {
		App::on_event(e);
		for (auto layer : layers) {
			layer->on_event(e);
			if (e.handled) break;
		}
	}
}

using Vxp = vxp::Voxploration;
int main() {
	vxl::init();
	Vxp v = Vxp(1280, 720);
	v.run();
	return 0;
}