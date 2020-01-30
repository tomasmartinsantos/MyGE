#pragma once

#include "Core.h"
#include "Window.h"


namespace MyGE {

    class MYGE_API Application
    {
        // Methods
        public:
            Application();
            virtual ~Application();

            void Run();
        // Variables
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    // To de defined on client
    Application* CreateApplication();
}