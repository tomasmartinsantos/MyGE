#include "mgpch.h"
#include "MyGE/Renderer/Buffer.h"
#include "MyGE/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace MyGE {

    VertexBuffer* VertexBuffer::Create(float* Vertices, uint32_t Size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:     MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(Vertices, Size);
        }

        MG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t Count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:     MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(Indices, Count);
        }

        MG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}