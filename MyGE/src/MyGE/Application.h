#pragma once

#include "Core.h"

namespace MyGE {

    class MYGE_API Application
    {
        //Methods
        public:
            Application();
            virtual ~Application();

            void Run();
    };

    // To de defined on client
    Application* CreateApplication();
}