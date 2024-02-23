#pragma once
#include "./vxl_event.hpp"

namespace vxl {
	class VXL_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}
		~WindowResizeEvent() {}
	public:
		inline uint32_t get_width() const { return width; }
		inline uint32_t get_height() const { return height; }

		std::string ToString() const override { return fmt::format("WindowResizeEvent: {0}, {1}", width, height); }

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		uint32_t width, height;
	};

	class VXL_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		~WindowCloseEvent() {}
	public:
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}