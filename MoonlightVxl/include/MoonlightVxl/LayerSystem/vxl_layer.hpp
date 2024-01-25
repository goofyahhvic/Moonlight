#pragma once
#include "core.h"

#include "vxl_input.hpp"
#include "./EventSystem/vxl_key_event.hpp"
#include "./EventSystem/vxl_mouse_event.hpp"

namespace vxl {
	class VXL_API Layer {
	public:
		Layer(const std::string& debug_name = "Layer") : input(false), debug_name(debug_name) {}
		virtual ~Layer() {}
	public:
		virtual void update() {}
		virtual void draw() {}
		virtual void on_event(Event& e) {
			switch (e.get_event_type()) {
				case EventType::KeyPressed:
				{
					input.get_keys()[GET_EVENT_KEYCODE] = true;
					break;
				}
				case EventType::KeyReleased:
				{
					input.get_keys()[GET_EVENT_KEYCODE] = false;
					break;
				}
				case EventType::MouseButtonPressed:
				{
					input.get_keys()[GET_EVENT_MOUSE_BUTTON] = true;
					break;
				}
				case EventType::MouseButtonReleased:
				{
					input.get_keys()[GET_EVENT_MOUSE_BUTTON] = false;
					break;
				}
			}
		}

		inline const std::string& get_name() const { return debug_name; }
	protected:
		Input input;
		std::string debug_name;
	};
}