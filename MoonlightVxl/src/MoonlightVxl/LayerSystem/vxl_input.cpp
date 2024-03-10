#include "vxl_pch.hpp"
#include "LayerSystem/vxl_input.hpp"

#include <GLFW/glfw3.h>
#include "vxl_window.hpp"

namespace vxl {
	MousePosition GlobalInput::sm_Pos;

	bool GlobalInput::GetKey(int32_t keycode) {
		int32_t state = glfwGetKey(Window::GetBound()->GetGlfwWindow(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool GlobalInput::GetMouseButton(int32_t id) {
		int32_t state = glfwGetMouseButton(Window::GetBound()->GetGlfwWindow(), id);
		return state == GLFW_PRESS;
	}
	void GlobalInput::_GetMousePosition() {
		glfwGetCursorPos(Window::GetBound()->GetGlfwWindow(), &(sm_Pos.first), &(sm_Pos.second));
	}

	Input::Input(bool value)
		: m_Keys(), m_MouseButtons() {
		for (auto key : m_Keys) {
			key = value;
		}
		for (auto mb : m_MouseButtons) {
			mb = value;
		}
	}
	Input::~Input() {}
}