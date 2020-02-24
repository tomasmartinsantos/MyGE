#include "mgpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>


namespace MyGE {

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& Color)
    {
        glClearColor(Color.r, Color.g, Color.b, Color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
    {
        /*
        glDrawElements(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid* Indices);

        Dibuja la geometria especificada por el buffer de indices y el buffer de vertices
        Mode: tipo de primitiva a dibujar (normalmente GL_TRIANGLES)
        Count: numero de indices contenido en el buffer de indices
        Type: Formato en que estan definidos los indices en el array (GL_UNSIGNED_INT, GL_UNSIGNED_SHORT)
        Indices: con Vertex Buffer Objects, el parametro es NULL
        */
        glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}