#include "mgpch.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace MyGE {

    OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
        : m_WindowHandle(WindowHandle)
    {
        MG_CORE_ASSERT(WindowHandle, "Window handle is NULL!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        MG_CORE_ASSERT(Status, "Could NOT initialize Glad!");

        MG_CORE_INFO("OpenGL Info:");
        MG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        MG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        MG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void MyGE::OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}