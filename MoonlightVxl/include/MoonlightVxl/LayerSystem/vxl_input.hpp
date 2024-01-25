#pragma once

#include "core.h"
#include "vxl_glfw3_macros.h"

namespace vxl {
	using MousePosition = std::pair<double, double>;
	class VXL_API GlobalInput {
		GlobalInput();
	public:
		inline static bool get_key(int32_t keycode);
		inline static bool get_mouse_button(int32_t id);

		inline static void get_mouse_position(double& _x, double& _y) { _get_mouse_position(); _x = std::get<0>(pos); _y = std::get<1>(pos); }
		inline static const MousePosition& get_mouse_position() { _get_mouse_position(); return pos; }
		inline static double get_mouse_x() { _get_mouse_position(); return std::get<0>(pos); }
		inline static double get_mouse_y() { _get_mouse_position(); return std::get<1>(pos); }
	private:
		static void _get_mouse_position();
	private:
		static MousePosition pos;
	};

	using KeysArray = std::array<bool, GLFW_KEY_LAST>;
	using MouseButtonsArray = std::array<bool, GLFW_MOUSE_BUTTON_LAST>;

	class VXL_API Input {
	public:
		Input(bool value = false);
		virtual ~Input();
	public:
		inline KeysArray& get_keys() { return keys; }
		inline bool& get_key(uint32_t index) { return keys[index]; }
		inline void set_key(uint32_t index, bool value) { keys[index] = value; }

		inline MouseButtonsArray& get_mouse_buttons() { return mouse_buttons; }
		inline bool& get_mouse_button(uint32_t index) { return mouse_buttons[index]; }
		inline void set_mouse_button(uint32_t index, bool value) { mouse_buttons[index] = value; }
	private:
		KeysArray keys;
		MouseButtonsArray mouse_buttons;
	};

}