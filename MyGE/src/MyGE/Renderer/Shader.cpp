#include "mgpch.h"
#include "MyGE/Renderer/Shader.h"
#include "MyGE/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace MyGE {

    Shader* Shader::Create(const std::string& VertexSrc, const std::string& FragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:     MG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL:   return new OpenGLShader(VertexSrc, FragmentSrc);
        }

        MG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}