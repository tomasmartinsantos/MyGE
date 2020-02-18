#include "mgpch.h"
#include "Application.h"

#include "MyGE/Log.h"
#include "MyGE/Input.h"

#include <glad/glad.h>


namespace MyGE {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        MG_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(MG_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, & m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float Vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        m_VertexBuffer.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));

        /*
        glEnableVertexAttribArray(GLuint Index);

        Activa la escritura por el pipeline para una variable Attribute cuya localizacion se pasa en el parametro index
        */
        glEnableVertexAttribArray(0);

        /*
        glVertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer);

        Especifica los datos que se van a colocar en la localizacion de una variable attribute cuya escritura haya sido activada con glEnableVertexAttribArray.
        Index: localizacion de la variable en la que escribir los valores
        Size: numero de componentes a escribir por vertice (3 para posiciones y normales, 4 para colores, 2 para coords de textura)
        Type: tipo con el que le pasamos los datos (GL_FLOAT, GL_UNSIGNED_BYTE)
        Normalized: si se deben normalizar los datos enviados (por ejemplo, [0, 255]->[0, 1])
        Stride: tamano del paquete de datos completo para un vertice
        Pointer: offset dentro del buffer activo en que se enceuntra el primer dato
        */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        unsigned int Indices[3] = { 0, 1, 2 };

        m_IndexBuffer.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

        std::string VertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;
            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);	
            }
        )";

        std::string FragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        m_Shader.reset(Shader::Create(VertexSrc, FragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);


            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            /*
            glDrawElements(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid* Indices);

            Dibuja la geometria especificada por el buffer de indices y el buffer de vertices
            Mode: tipo de primitiva a dibujar (normalmente GL_TRIANGLES)
            Count: numero de indices contenido en el buffer de indices
            Type: Formato en que estan definidos los indices en el array (GL_UNSIGNED_INT, GL_UNSIGNED_SHORT)
            Indices: con Vertex Buffer Objects, el parametro es NULL
            */
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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