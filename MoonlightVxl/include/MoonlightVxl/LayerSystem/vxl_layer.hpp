#pragma once
#include "core.h"

#include "vxl_input.hpp"
#include "./EventSystem/vxl_key_event.hpp"
#include "./EventSystem/vxl_mouse_event.hpp"

namespace vxl {
	class VXL_API Layer {
	public:
		Layer(const std::string& debug_name = "Layer") : input(false)
#ifndef MLT_DISTRIBUTION
			, debugName(debug_name)
#endif
		{}
		virtual ~Layer() {}
	public:
		virtual void Update() {}
		virtual void Draw() {}
		virtual void OnEvent(Event& e) {
			switch (e.GetEventType()) {
				case EventType::KeyPressed:
				{
					input.GetKeys()[GET_EVENT_KEYCODE] = true;
					break;
				}
				case EventType::KeyReleased:
				{
					input.GetKeys()[GET_EVENT_KEYCODE] = false;
					break;
				}
				case EventType::MouseButtonPressed:
				{
					input.GetKeys()[GET_EVENT_MOUSE_BUTTON] = true;
					break;
				}
				case EventType::MouseButtonReleased:
				{
					input.GetKeys()[GET_EVENT_MOUSE_BUTTON] = false;
					break;
				}
			}
		}

#ifndef MLT_DISTRIBUTION
		inline const std::string* const GetName() const { return &debugName; }
#else
		inline const std::string* const GetName() const { return nullptr; }
#endif
	protected:
		Input input;
#ifndef MLT_DISTRIBUTION
		std::string debugName;
#endif
	};
}