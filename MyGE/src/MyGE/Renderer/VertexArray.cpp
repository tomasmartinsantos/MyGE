#include "mgpch.h"
#include "VertexArray.h"
#include "MyGE/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace MyGE {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:     MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
        }

        MG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}