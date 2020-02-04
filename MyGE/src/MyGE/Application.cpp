#include "mgpch.h"
#include "Application.h"

#include "MyGE/Log.h"

#include <glad/glad.h>


namespace MyGE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        MG_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* Layer)
    {
        m_LayerStack.PushLayer(Layer);
        Layer->OnAttach();
    }

    void Application::PushOverlay(Layer* Overlay)
    {
        m_LayerStack.PushOverlay(Overlay);
        Overlay->OnAttach();
    }

    void Application::OnEvent(Event& E)
    {
        EventDispatcher Dispatcher(E);
        Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

        for (auto It = m_LayerStack.end(); It != m_LayerStack.begin();)
        {
            (*--It)->OnEvent(E);
            if (E.HasBeenHandled())
            {
                break;
            }
        }
    }


    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* Layer : m_LayerStack)
            {
                Layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& Event)
    {
        m_Running = false;
        return true;
    }
}