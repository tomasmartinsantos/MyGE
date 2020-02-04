#pragma once

#include "MyGE/Layer.h"


namespace MyGE {

    class MYGE_API ImGuiLayer : public Layer
    {
        // Methods
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void OnAttach() override;
            void OnDetach() override;
            void OnUpdate() override;
            void OnEvent(Event& E) override;

        // Variables
        private:
            float m_Time = 0.0f;
    };
}