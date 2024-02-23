#include "vxl_pch.hpp"
#include "LayerSystem/vxl_imgui_layer.hpp"

#include "vxl_window.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

namespace vxl {
	ImguiLayer::ImguiLayer() : Layer("Imgui") {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(Window::GetBound()->GetGlfwWindow(), true);
		//ImGui_ImplOpenGL3_Init("#version 410");
	}

	ImguiLayer::~ImguiLayer() {
		//ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::ImguiBegin() {
		//ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImguiLayer::ImguiFinish() {
		ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	static bool show = true;
	void ImguiLayer::Draw() {
		ImGui::ShowDemoWindow(&show);
	}
}