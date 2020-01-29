#include "mgpch.h"
#include "Application.h"
#include "MyGE/Events/Event.h"
#include "MyGE/Events/ApplicationEvent.h"
#include "MyGE/Log.h"


namespace MyGE {

    Application::Application()
    {

    }

    Application::~Application()
    {

    }


    void Application::Run()
    {
        WindowResizeEvent E(1280, 720);
        if (E.IsInCategory(EventCategoryApplication))
        {
            MG_TRACE(E);
        }

        while (true);
    }

}