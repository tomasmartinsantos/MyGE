#pragma once

#include "MyGe/Core.h"
#include "MyGE/Events/Event.h"


namespace MyGE {

    class MYGE_API Layer
    {
        // Methods
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate() {}
            virtual void OnEvent(Event& E) {}

            virtual void OnImGuiRender() {}

            inline const std::string& GetName() const { return m_DebugName; }

        // Variables
        protected:
            std::string m_DebugName;
    };
}