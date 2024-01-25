#pragma once
#include "core.h"

namespace vxl {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // window related event types
		KeyPressed, KeyReleased, // key pressing related event types
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled // mouse related event types
	};
	enum EventCategory {
		None = 0,
		EventCategoryApplication  = BIT(0),
		EventCategoryInput	      = BIT(1),
		EventCategoryKeyboard	  = BIT(2),
		EventCategoryMouse	      = BIT(3),
		EventCategoryMouseButton  = BIT(4)
	};

#define GET_EVENT_TYPE e.get_event_type()
#define _GET_EVENT_TYPE(e) e.get_event_type()

#define EVENT_TYPE_IS(x) (e.get_event_type() == vxl::EventType::x)
#define EVENT_IS_IN_CATEGORY(x) (e.is_in_category(vxl::EventCategory##x))
#define EVENT_IS_IN(x) (e.is_in_category(vxl::x))

#define _EVENT_TYPE_IS(e, x) (e.get_event_type() == vxl::EventType::x)
#define _EVENT_IS_IN_CATEGORY(e, x) (e.is_in_category(vxl::EventCategory##x))
#define _EVENT_IS_IN(e, x) (e.is_in_category(vxl::x))


#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
					virtual EventType get_event_type() const override { return get_static_type(); }\
					virtual const char* get_name() const override { return #type;}
#define EVENT_CLASS_CATEGORY(category) virtual int32_t get_category_flags() const override { return category; }

	class VXL_API Event {
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int32_t get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name(); }

		inline bool is_in_category(EventCategory category) const { return get_category_flags() & category; }
		bool handled = false;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		return os << e.to_string();
	}

}