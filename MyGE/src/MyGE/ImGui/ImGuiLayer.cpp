#include "mgpch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGl/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "MyGe/Application.h"


namespace MyGE {

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {

    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& IO = ImGui::GetIO();
        IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TEMPORARY
        IO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        IO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        IO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        IO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        IO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        IO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        IO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        IO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        IO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        IO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        IO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        IO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        IO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        IO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        IO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        IO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        IO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        IO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        IO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        IO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        IO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& IO = ImGui::GetIO();
        Application& App = Application::Get();
        IO.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight());


        float Time = (float)glfwGetTime();
        IO.DeltaTime = m_Time > 0.0f ? (Time - m_Time) : (1.0f / 60.0f);
        m_Time = Time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool Show = true;
        ImGui::ShowDemoWindow(&Show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& E)
    {

    }
}