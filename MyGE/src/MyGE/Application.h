#pragma once

#include "Core.h"
#include "Window.h"
#include "MyGE/LayerStack.h"
#include "MyGE/Events/Event.h"
#include "MyGE/Events/ApplicationEvent.h"


namespace MyGE {

    class MYGE_API Application
    {
        // Methods
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& E);

            void PushLayer(Layer* Layer);
            void PushOverlay(Layer* Overlay);
        private:
            bool OnWindowCloseEvent(WindowCloseEvent& Event);

        // Variables
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            LayerStack m_LayerStack;
    };

    // To de defined on client
    Application* CreateApplication();
}