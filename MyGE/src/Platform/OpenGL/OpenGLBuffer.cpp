#include "mgpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include <glad/glad.h>


namespace MyGE {

    /////////////////////////////////////////////////////////////////////////////
    // VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t Size)
    {
        /*
        glGenBuffers(GLsizei N, const GLuint* Buffers);

        Genera el numero de buffers especificado por N, y coloca sus ids en el array Buffers (debe tener al menos N elementos)
        */
        glGenBuffers(1, &m_RendererID);

        /*
        glBindBuffer(GLenum Target, const GLuint* Buffer);

        Establece el buffer activo, que recibira OpenGL para dibujar
        GL_ARRAY_BUFFER: el buffer contiene info de los vertices (coords, normales, color, ...)
        GL_ELEMENT_ARRAY_BUFFER: el buffer contiene los indices a los vertices con los que se forma la geometria de los elementos a dibujar
        */
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);


        /*
        glBufferData(GLenum Target, GLsizeiptr Size, const GLvoid* Data, GLenum Usage);

        Envia los datos al buffer. Estos datos deben estar en el array apuntado por Data, y el tamano en bytes del bloque de memoria que los contiene se especifica en Size.
        - Un buffer de indices (IndexBuffer) recibira el array con los indices a los vertices.
        - Un buffer de vertices (VertexBuffer) recibira el array con los datos de los vertices(posicion, normal, color...)
        GL_STATIC_DRAW: Solicita que los datos se carguen en la memoria de video. Util cuando la info en Data no va a ser modifcada frecuentemente (mallas estaticas, buffers de indices)
        GL_DYNAMIC_DRAW: Solicitaque los datos se carguen en memoria principal. Util cuando los datos cambian frecuentemente (mallas animadas)
        GL_STREAM_DRAW: los datos no cambian a menudo y no se usan frecuentemente, con lo que se vuelcan en memoria de video cuando sea necesario
        */
        glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count)
        : m_Count(Count)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}