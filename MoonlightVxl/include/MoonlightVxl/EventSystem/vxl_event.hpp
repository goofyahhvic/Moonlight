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

#define GET_EVENT_TYPE e.GetEventType()
#define _GET_EVENT_TYPE(e) e.GetEventType()

#define EVENT_TYPE_IS(x) (e.GetEventType() == vxl::EventType::x)
#define EVENT_IS_IN_CATEGORY(x) (e.IsInCategory(vxl::EventCategory##x))
#define EVENT_IS_IN(x) (e.IsInCategory(vxl::x))

#define _EVENT_TYPE_IS(e, x) (e.GetEventType() == vxl::EventType::x)
#define _EVENT_IS_IN_CATEGORY(e, x) (e.IsInCategory(vxl::EventCategory##x))
#define _EVENT_IS_IN(e, x) (e.IsInCategory(vxl::x))


#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
					virtual EventType GetEventType() const override { return get_static_type(); }\
					virtual const char* GetName() const override { return #type;}
#define EVENT_CLASS_CATEGORY(category) virtual int32_t GetCategoryFlags() const override { return category; }

	class VXL_API Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int32_t GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }
		bool handled = false;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}