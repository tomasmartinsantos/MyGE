#include "mgpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>


namespace MyGE {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
        }

        MG_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer)
    {
        MG_CORE_ASSERT(VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        VertexBuffer->Bind();

        uint32_t Index = 0;
        const auto& Layout = VertexBuffer->GetLayout();
        for (const auto& Element : Layout)
        {
            /*
            glEnableVertexAttribArray(GLuint Index);

            Activa la escritura por el pipeline para una variable Attribute cuya localizacion se pasa en el parametro index
            */
            glEnableVertexAttribArray(Index);

            /*
            glVertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer);

            Especifica los datos que se van a colocar en la localizacion de una variable attribute cuya escritura haya sido activada con glEnableVertexAttribArray.
            Index: localizacion de la variable en la que escribir los valores
            Size: numero de componentes a escribir por vertice (3 para posiciones y normales, 4 para colores, 2 para coords de textura)
            Type: tipo con el que le pasamos los datos (GL_FLOAT, GL_UNSIGNED_BYTE)
            Normalized: si se deben normalizar los datos enviados (por ejemplo, [0, 255]->[0, 1])
            Stride: tamano del paquete de datos completo para un vertice
            Pointer: offset dentro del buffer activo en que se encuentra el primer dato
            */
            glVertexAttribPointer(Index,
                Element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(Element.Type),
                Element.Normalized ? GL_TRUE : GL_FALSE,
                Layout.GetStride(),
                (const void*)Element.Offset);
            Index++;
        }

        m_VertexBuffers.push_back(VertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer)
    {
        glBindVertexArray(m_RendererID);
        IndexBuffer->Bind();

        m_IndexBuffer = IndexBuffer;
    }
}