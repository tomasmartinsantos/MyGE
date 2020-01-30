#include "mgpch.h"
#include "WindowsWindow.h"


namespace MyGE {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& Props)
    {
        return new WindowsWindow(Props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& Props)
    {
        Init(Props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& Props)
    {
        m_Data.Title = Props.Title;
        m_Data.Width = Props.Width;
        m_Data.Height = Props.Height;

        MG_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

        if (!s_GLFWInitialized)
        {
            int Success = glfwInit();
            MG_CORE_ASSERT(Success, "Could NOT initialized GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool Enabled)
    {
        if (Enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = Enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}