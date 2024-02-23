#pragma once
#include "./vxl_layer.hpp"

namespace vxl {
	class VXL_API ImguiLayer : public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();
	public:
		virtual void Draw() override;
		void ImguiBegin();
		void ImguiFinish();
	};
}