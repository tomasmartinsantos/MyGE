#pragma once

#include "Core.h"
#include "Window.h"
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
        private:
            bool OnWindowCloseEvent(WindowCloseEvent& Event);

        // Variables
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    // To de defined on client
    Application* CreateApplication();
}