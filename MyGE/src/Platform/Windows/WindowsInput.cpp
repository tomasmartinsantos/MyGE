#include "mgpch.h"
#include "WindowsInput.h"
#include "MyGE/Application.h"

#include <GLFW/glfw3.h>


namespace MyGE {

    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int Keycode)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int State = glfwGetKey(Window, Keycode);

        return State == GLFW_PRESS || State == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int Button)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int State = glfwGetMouseButton(Window, Button);

        return State == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(Window, &xPos, &yPos);

        return std::pair<float, float>((float)xPos, (float)yPos);
    }

    float WindowsInput::GetMouseXImpl()
    {
        return GetMousePositionImpl().first;
    }

    float WindowsInput::GetMouseYImpl()
    {
        return GetMousePositionImpl().second;
    }
}