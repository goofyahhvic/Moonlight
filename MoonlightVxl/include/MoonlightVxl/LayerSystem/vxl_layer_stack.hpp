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
		void push_layer(Layer* layer);
		/// 
		/// Pushes an overlay on top everything else.
		/// 
		void push_overlay(Layer* overlay);
		Layer* pop_layer(Layer* layer);
		Layer* pop_overlay(Layer* overlay);

		Layers::iterator begin() { return layers.begin(); }
		Layers::iterator end() { return layers.end(); }

		Layers::reverse_iterator rbegin() { return layers.rbegin(); }
		Layers::reverse_iterator rend() { return layers.rend(); }
	private:
		 Layers layers;
		 uint32_t insert_index = 0;
	};
}