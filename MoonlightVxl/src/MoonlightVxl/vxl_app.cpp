#include "vxl_pch.hpp"
#include "vxl_app.hpp"

#include <Moonloit/Moonloit.hpp>
#include "EventSystem/vxl_app_event.hpp"

namespace vxl {
	App* App::sm_This;

	App::App(const uint32_t width, const uint32_t height, const char* title)
		: shouldClose(false), window(nullptr), imgui(nullptr) {
		if (sm_This) {
			throw mlt::Exception("Cannot create multiple instances of vxl::App!");
			return;
		}
		sm_This = this;

		Window::Bind(nullptr);
		Window::SetBoundDestroyCallback([](){});

		window = Window::Create(width, height, title);
		window->SetEventCallback([this] (Event& e) {
			OnEvent(e);
		});
		window->SetDestroyCallback([this] () {
			OnWindowClose();
		});
		window->SetBoundDestroyCallback([this] () {
			OnBoundWindowClose();
		});
		//imgui = new ImguiLayer();
		//layers.PushOverlay(imgui);
	}
	App::~App() {
		if (window) Window::Destroy(window);
	}

	void App::Run() {
		while (!shouldClose) {
			Update();
		}
	}

	void App::Update() {
		for (Layer* layer : layers)
			layer->Update();

		//imgui->ImguiBegin();
		for (Layer* layer : layers) layer->Draw();
		//imgui->ImguiFinish();

		Window::GlfwPollEvents();
	}

	void App::OnEvent(Event& e) {
		if (e.GetEventType() == EventType::WindowClose) {
			window->Close();
			Window::Destroy(window);
			window = nullptr;
		}

		for (auto layer : layers) {
			layer->OnEvent(e);
			if (e.handled) break;
		}
	}
	void App::OnWindowClose() {}
	void App::OnBoundWindowClose() {
		shouldClose = true;
	}
}