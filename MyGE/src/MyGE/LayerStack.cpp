#include "mgpch.h"
#include "LayerStack.h"


namespace MyGE {

    LayerStack::LayerStack()
    {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* Layer : m_Layers)
        {
            delete Layer;
        }
    }

    void LayerStack::PushLayer(Layer* Layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, Layer);
    }

    void LayerStack::PushOverlay(Layer* Overlay)
    {
        m_Layers.emplace_back(Overlay);
    }

    void LayerStack::PopLayer(Layer* Layer)
    {
        auto It = std::find(m_Layers.begin(), m_Layers.end(), Layer);
        if (It != m_Layers.end())
        {
            m_Layers.erase(It);
            m_LayerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer* Overlay)
    {
        auto It = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
        if (It != m_Layers.end())
        {
            m_Layers.erase(It);
        }
    }
}