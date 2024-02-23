#pragma once
#include "./vxl_layer.hpp"

namespace vxl {
	using Layers = std::vector<Layer*>;
	class VXL_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		/// 
		/// Pushes a layer on top of previous layers, but below the overlays.
		/// 
		void PushLayer(Layer* layer);
		/// 
		/// Pushes an overlay on top everything else.
		/// 
		void PushOverlay(Layer* overlay);
		Layer* PopLayer(Layer* layer);
		Layer* PopOverlay(Layer* overlay);

		Layers::iterator begin() { return m_Layers.begin(); }
		Layers::iterator end() { return m_Layers.end(); }

		Layers::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		Layers::reverse_iterator rend() { return m_Layers.rend(); }
	private:
		 Layers m_Layers;
		 uint32_t m_InsertIndex = 0;
	};
}