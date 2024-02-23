#pragma once
#include "./vxl_event.hpp"

#define GET_EVENT_KEYCODE ((vxl::KeyEvent&)e).get_key_code()
#define _GET_EVENT_KEYCODE(e) ((vxl::KeyEvent&)e).get_key_code()

#define EVENT_KEYCODE_IS(x) (GET_EVENT_KEYCODE == x)
#define _EVENT_KEYCODE_IS(x, e) (GET_EVENT_KEYCODE(e) == x)

#define IS_EVENT_KEYCODE(x) EVENT_KEYCODE_IS(x)
#define _IS_EVENT_KEYCODE(x, e) _EVENT_KEYCODE_IS(x, e)

namespace vxl {
	class VXL_API KeyEvent : public Event {
	public:
		KeyEvent(int32_t keycode) : keycode(keycode) {}
		~KeyEvent() {}
	public:
		inline int get_key_code() const { return keycode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		int32_t keycode;
	};

	class VXL_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int32_t keycode, uint32_t repeat_count)
			: KeyEvent(keycode), repeat_count(repeat_count) {}
		~KeyPressedEvent() {}
	public:
		std::string ToString() const override { return fmt::format("KeyPressedEvent: {0}, {1}", keycode, repeat_count); }

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint32_t repeat_count;
	};

	class VXL_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int32_t keycode)
			: KeyEvent(keycode) {}
		~KeyReleasedEvent() {}
	public:
		std::string ToString() const override { return fmt::format("KeyReleasedeEvent: {0}", keycode); }
		EVENT_CLASS_TYPE(KeyReleased)
	};

}