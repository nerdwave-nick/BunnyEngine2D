#pragma once

#include "bunny/Core/Core.h"
#include "bunny/Core/Layer.h"

#include <vector>

namespace bunny {
  class LayerStack {
    using ContainerType = bu_vec<Layer*>;

   public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    ContainerType::iterator begin() {
      return m_Layers.begin();
    }
    ContainerType::iterator end() {
      return m_Layers.end();
    }

   private:
    ContainerType m_Layers;
    u32 m_LayerInsertIndex = 0;
  };
}  // namespace bunny
