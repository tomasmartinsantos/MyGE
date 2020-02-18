#pragma once

#include "Core.h"
#include "Window.h"
#include "MyGE/LayerStack.h"
#include "MyGE/Events/Event.h"
#include "MyGE/Events/ApplicationEvent.h"
#include "MyGE/ImGui/ImGuiLayer.h"

#include "MyGE/Renderer/Shader.h"
#include "MyGE/Renderer/Buffer.h"


namespace MyGE {

    class MYGE_API Application
    {
        // Methods
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& E);

            void PushLayer(Layer* Layer);
            void PushOverlay(Layer* Overlay);

            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }
        private:
            bool OnWindowCloseEvent(WindowCloseEvent& Event);

        // Variables
        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;

            unsigned int m_VertexArray;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;
            std::unique_ptr<IndexBuffer> m_IndexBuffer;

            static Application* s_Instance;
    };

    // To de defined on client
    Application* CreateApplication();
}