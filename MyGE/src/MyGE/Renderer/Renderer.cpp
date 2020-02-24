#include "mgpch.h"
#include "MyGE/Renderer/Renderer.h"


namespace MyGE {

    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& VertexArray)
    {
        VertexArray->Bind();
        RenderCommand::DrawIndexed(VertexArray);
    }
}