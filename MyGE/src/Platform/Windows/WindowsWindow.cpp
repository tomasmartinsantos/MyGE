#include "mgpch.h"
#include "WindowsWindow.h"
#include "MyGE/Events/ApplicationEvent.h"
#include "MyGE/Events/KeyEvent.h"
#include "MyGE/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace MyGE {

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int Error, const char* Description)
    {
        MG_CORE_ERROR("GLFW ERROR ({0}): {1}", Error, Description);
    }

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
            MG_CORE_ASSERT(Success, "Could NOT initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW events
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
            Data.Width = Width;
            Data.Height = Height;

            WindowResizeEvent Event(Width, Height);
            Data.EventCallback(Event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            WindowCloseEvent Event;
            Data.EventCallback(Event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mod)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            switch (Action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent Event(Key, 0);
                    Data.EventCallback(Event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent Event(Key);
                    Data.EventCallback(Event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent Event(Key, 1);
                    Data.EventCallback(Event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* Window, unsigned int Key)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            KeyTypedEvent Event(Key);
            Data.EventCallback(Event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, int Button, int Action, int Mod)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            switch (Action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent Event(Button);
                    Data.EventCallback(Event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent Event(Button);
                    Data.EventCallback(Event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double XOffset, double YOffset)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            MouseScrolledEvent Event((float)XOffset, (float)YOffset);
            Data.EventCallback(Event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double XPos, double YPos)
        {
            WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);

            MouseMovedEvent Event((float)XPos, (float)YPos);
            Data.EventCallback(Event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
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