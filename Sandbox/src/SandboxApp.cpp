#include <MyGE.h>
#include "imgui/imgui.h"


class ExampleLayer : public MyGE::Layer
{
    // Methods
    public:
        ExampleLayer()
            : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraMoveSpeed(0.1f), m_CameraRotation(0.0f), m_CameraRotationSpeed(1.0f)
        {
            // TRIANGLE
            m_VertexArray.reset(MyGE::VertexArray::Create());

            float Vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
            };

            std::shared_ptr<MyGE::VertexBuffer> vertexBuffer;
            vertexBuffer.reset(MyGE::VertexBuffer::Create(Vertices, sizeof(Vertices)));
            MyGE::BufferLayout layout = {
                { MyGE::ShaderDataType::Float3, "a_Position" },
                { MyGE::ShaderDataType::Float4, "a_Color" }
            };
            vertexBuffer->SetLayout(layout);
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            unsigned int Indices[3] = { 0, 1, 2 };
            std::shared_ptr<MyGE::IndexBuffer> indexBuffer;
            indexBuffer.reset(MyGE::IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
            m_VertexArray->SetIndexBuffer(indexBuffer);

            // SQUARE
            m_SquareVA.reset(MyGE::VertexArray::Create());

            float squareVertices[3 * 4] = {
                -0.75f, -0.75f, 0.0f,
                 0.75f, -0.75f, 0.0f,
                 0.75f,  0.75f, 0.0f,
                -0.75f,  0.75f, 0.0f
            };

            std::shared_ptr<MyGE::VertexBuffer> SquareVB;
            SquareVB.reset(MyGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
            SquareVB->SetLayout({
                { MyGE::ShaderDataType::Float3, "a_Position" }
                });
            m_SquareVA->AddVertexBuffer(SquareVB);

            uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
            std::shared_ptr<MyGE::IndexBuffer> SquareIB;
            SquareIB.reset(MyGE::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
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

            m_Shader.reset(MyGE::Shader::Create(VertexSrc, FragmentSrc));

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

            m_BlueShader.reset(MyGE::Shader::Create(BlueShaderVertexSrc, BlueShaderFragmentSrc));
        }

        virtual void OnUpdate() override
        {
            if (MyGE::Input::IsKeyPressed(MG_KEY_LEFT))
            {
                m_CameraPosition.x -= m_CameraMoveSpeed;
            }
            else if (MyGE::Input::IsKeyPressed(MG_KEY_RIGHT))
            {
                m_CameraPosition.x += m_CameraMoveSpeed;
            }

            if (MyGE::Input::IsKeyPressed(MG_KEY_UP))
            {
                m_CameraPosition.y += m_CameraMoveSpeed;
            }
            else if (MyGE::Input::IsKeyPressed(MG_KEY_DOWN))
            {
                m_CameraPosition.y -= m_CameraMoveSpeed;
            }

            if (MyGE::Input::IsKeyPressed(MG_KEY_A))
            {
                m_CameraRotation += m_CameraRotationSpeed;
            }
            else if (MyGE::Input::IsKeyPressed(MG_KEY_D))
            {
                m_CameraRotation -= m_CameraRotationSpeed;
            }

            MyGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            MyGE::RenderCommand::Clear();

            m_Camera.SetPosition(m_CameraPosition);
            m_Camera.SetRotation(m_CameraRotation);

            MyGE::Renderer::BeginScene(m_Camera);

            MyGE::Renderer::Submit(m_BlueShader, m_SquareVA);

            MyGE::Renderer::Submit(m_Shader, m_VertexArray);

            MyGE::Renderer::EndScene();
        }

        virtual void OnEvent(MyGE::Event& Event) override
        {

        }

        virtual void OnImGuiRender() override
        {
            //ImGui::Begin("Test");
            //ImGui::Text("Hello World");
            //ImGui::End();
        }

    // Variables
    private:
        std::shared_ptr<MyGE::Shader> m_Shader;
        std::shared_ptr<MyGE::VertexArray> m_VertexArray;

        std::shared_ptr<MyGE::Shader> m_BlueShader;
        std::shared_ptr<MyGE::VertexArray> m_SquareVA;

        MyGE::OrthographicCamera m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraMoveSpeed;

        float m_CameraRotation;
        float m_CameraRotationSpeed;
};

class Sandbox : public MyGE::Application
{
    // Methods
    public:
        Sandbox()
        {
            PushLayer(new ExampleLayer());
        }

        ~Sandbox()
        {

        }

};

MyGE::Application* MyGE::CreateApplication()
{
    return new Sandbox();
}