#pragma once

#include "MyGE/Core.h"
#include "Layer.h"

#include <vector>

namespace MyGE {

    class MYGE_API LayerStack
    {
        // Methods
        public:
            LayerStack();
            ~LayerStack();

            void PushLayer(Layer* Layer);
            void PushOverlay(Layer* Overlay);
            void PopLayer(Layer* Layer);
            void PopOverlay(Layer* Overlay);

            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        // Variables
        private:
            std::vector<Layer*> m_Layers;
            unsigned int m_LayerInsertIndex = 0;
    };
}