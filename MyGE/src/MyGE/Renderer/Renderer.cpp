#include "mgpch.h"
#include "MyGE/Renderer/Renderer.h"


namespace MyGE {

    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

    void Renderer::BeginScene(OrthographicCamera& Camera)
    {
        s_SceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& VertexArray)
    {
        Shader->Bind();
        Shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

        VertexArray->Bind();
        RenderCommand::DrawIndexed(VertexArray);
    }
}