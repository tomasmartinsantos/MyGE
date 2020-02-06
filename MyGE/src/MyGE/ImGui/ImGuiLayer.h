#pragma once

#include "MyGE/Layer.h"

#include "MyGE/Events/ApplicationEvent.h"
#include "MyGE/Events/KeyEvent.h"
#include "MyGE/Events/MouseEvent.h"


namespace MyGE {

    class MYGE_API ImGuiLayer : public Layer
    {
        // Methods
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnUpdate() override;
            virtual void OnEvent(Event& E) override;
        private:
            bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& E);
            bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& E);
            bool OnMouseMovedEvent(MouseMovedEvent& E);
            bool OnMouseScrolledEvent(MouseScrolledEvent& E);
            bool OnKeyPressedEvent(KeyPressedEvent& E);
            bool OnKeyReleasedEvent(KeyReleasedEvent& E);
            bool OnKeyTypedEvent(KeyTypedEvent& E);
            bool OnWindowResizeEvent(WindowResizeEvent& E);

        // Variables
        private:
            float m_Time = 0.0f;
    };
}