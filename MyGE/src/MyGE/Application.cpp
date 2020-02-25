#include "mgpch.h"
#include "Application.h"

#include "MyGE/Log.h"
#include "MyGE/Input.h"
#include "MyGE/Renderer/Renderer.h"


namespace MyGE {

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        MG_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(MG_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // TRIANGLE
        m_VertexArray.reset(VertexArray::Create());

        float Vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int Indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // SQUARE
        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> SquareVB;
        SquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        SquareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(SquareVB);

        uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> SquareIB;
        SquareIB.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(SquareIB);

        std::string VertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
            }
        )";

        std::string FragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(Shader::Create(VertexSrc, FragmentSrc));

        std::string BlueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
            }
        )";

        std::string BlueShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_BlueShader.reset(Shader::Create(BlueShaderVertexSrc, BlueShaderFragmentSrc));
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* Layer)
    {
        m_LayerStack.PushLayer(Layer);
    }

    void Application::PushOverlay(Layer* Overlay)
    {
        m_LayerStack.PushOverlay(Overlay);
    }

    void Application::OnEvent(Event& E)
    {
        EventDispatcher Dispatcher(E);
        Dispatcher.Dispatch<WindowCloseEvent>(MG_BIND_EVENT_FN(Application::OnWindowCloseEvent));

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
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();

            //m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
            //m_Camera.SetRotation(45.0f);

            Renderer::BeginScene(m_Camera);

            Renderer::Submit(m_BlueShader, m_SquareVA);

            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

            for (Layer* Layer : m_LayerStack)
            {
                Layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* Layer : m_LayerStack)
            {
                Layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& Event)
    {
        m_Running = false;
        return true;
    }
}