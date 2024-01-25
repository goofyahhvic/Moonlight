#pragma once
#include "./vxl_event.hpp"

#define GET_EVENT_MOUSE_BUTTON ((vxl::MouseButtonEvent&)e).get_button()
#define _GET_EVENT_MOUSE_BUTTON(e) ((vxl::MouseButtonEvent&)e).get_button()

#define EVENT_MOUSE_BUTTON_IS(x) (GET_EVENT_MOUSE_BUTTON == x)
#define _EVENT_MOUSE_BUTTON_IS(x, e) (_GET_EVENT_MOUSE_BUTTON(e) == x)

#define IS_EVENT_MOUSE_BUTTON(x) EVENT_MOUSE_BUTTON_IS(x)
#define _IS_EVENT_MOUSE_BUTTON(x, e) _EVENT_MOUSE_BUTTON_IS(x, e)

namespace vxl {
	class VXL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(double x, double y) : x(x), y(y) {}
		~MouseMovedEvent() {}
	public:
		inline double get_x() const { return this->x; }
		inline double get_y() const { return this->y; }

		inline std::string to_string() const override {	return fmt::format("MouseMovedEvent: {0}, {1}", x, y); }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double x, y;
	};

	class VXL_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(double x_offset, double y_offset) : x_offset(x_offset), y_offset(y_offset) {}
		~MouseScrolledEvent() {}
	public:
		inline double get_x_offset() const { return x_offset;  }
		inline double get_y_offset() const { return y_offset;  }

		inline std::string to_string() const override { return fmt::format("MouseScrolledEvent: {0}, {1}", x_offset, y_offset); }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		double x_offset, y_offset;
	};

	class VXL_API MouseButtonEvent : public Event {
	protected:
		MouseButtonEvent(int32_t button) : button(button) {}
	public:
		inline int32_t get_button() const { return button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		int32_t button;
	};

	class VXL_API MouseButtonPressedEvent : public MouseButtonEvent {
	public: 
		MouseButtonPressedEvent(int32_t button)
			: MouseButtonEvent(button) {}
		~MouseButtonPressedEvent() {}
	public:
		inline std::string to_string() const override { return fmt::format("MouseButtonPressedEvent: {0}", button); }

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class VXL_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int32_t button) 
			: MouseButtonEvent(button) {}
		~MouseButtonReleasedEvent() {}
	public:
		inline std::string to_string() const override { return fmt::format("MouseButtonReleasedEvent: {0}", button); }

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}