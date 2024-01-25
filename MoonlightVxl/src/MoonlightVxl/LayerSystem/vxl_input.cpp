#include "vxl_pch.hpp"
#include "LayerSystem/vxl_input.hpp"

#include <GLFW/glfw3.h>

namespace vxl {
	MousePosition GlobalInput::pos;
	GlobalInput::GlobalInput() {}

	bool GlobalInput::get_key(int32_t keycode) {
		int32_t state = glfwGetKey(glfwGetCurrentContext(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool GlobalInput::get_mouse_button(int32_t id) {
		int32_t state = glfwGetMouseButton(glfwGetCurrentContext(), id);
		return state == GLFW_PRESS;
	}
	void GlobalInput::_get_mouse_position() {
		glfwGetCursorPos(glfwGetCurrentContext(), &(pos.first), &(pos.second));
	}

	Input::Input(bool value)
		: keys(), mouse_buttons() {
		for (auto key : keys) {
			key = value;
		}
		for (auto mb : mouse_buttons) {
			mb = value;
		}
	}
	Input::~Input() {}
}