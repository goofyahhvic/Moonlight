#include "vxl_pch.hpp"
#include "LayerSystem/vxl_layer_stack.hpp"

namespace vxl {
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack() {
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}
	Layer* LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_InsertIndex--;
		}
		return layer;
	}
	Layer* LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
		return overlay;
	}
}