#pragma once
#include <MoonlightVxl/MoonlightVxl.hpp>

namespace vxp {
	class Layer : public vxl::Layer {
	public:
		Layer();
		~Layer();
	public:
		virtual void on_event(vxl::Event& e) override;
		virtual void update() override;
		virtual void draw() override;
	};

	class Voxploration : public vxl::App {
	public:
		Voxploration(const uint32_t width, const uint32_t height);
		~Voxploration();
	private:
		virtual void on_event(vxl::Event& e) override;
	private:
	};
}
