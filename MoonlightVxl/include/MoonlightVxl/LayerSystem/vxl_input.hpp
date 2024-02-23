#pragma once

#include "core.h"
#include "vxl_glfw3_macros.h"

namespace vxl {
	using MousePosition = std::pair<double, double>;
	class VXL_API GlobalInput {
		GlobalInput();
	public:
		static bool GetKey(int32_t keycode);
		static bool GetMouseButton(int32_t id);

		inline static void GetMousePosition(double& _x, double& _y) { _GetMousePosition(); _x = std::get<0>(sm_Pos); _y = std::get<1>(sm_Pos); }
		inline static const MousePosition& GetMousePosition() { _GetMousePosition(); return sm_Pos; }
		inline static double GetMouseX() { _GetMousePosition(); return std::get<0>(sm_Pos); }
		inline static double GetMouseY() { _GetMousePosition(); return std::get<1>(sm_Pos); }
		static void _GetMousePosition();
	private:
		static MousePosition sm_Pos;
	};

	using KeysArray = std::array<bool, GLFW_KEY_LAST>;
	using MouseButtonsArray = std::array<bool, GLFW_MOUSE_BUTTON_LAST>;

	class VXL_API Input {
	public:
		Input(bool value = false);
		virtual ~Input();
	public:
		inline KeysArray& GetKeys() { return m_Keys; }
		inline bool& GetKey(uint32_t index) { return m_Keys[index]; }
		inline void SetKey(uint32_t index, bool value) { m_Keys[index] = value; }

		inline MouseButtonsArray& GetMouseButtons() { return m_MouseButtons; }
		inline bool& GetMouseButton(uint32_t index) { return m_MouseButtons[index]; }
		inline void SetMouseButton(uint32_t index, bool value) { m_MouseButtons[index] = value; }
	private:
		KeysArray m_Keys;
		MouseButtonsArray m_MouseButtons;
	};

}