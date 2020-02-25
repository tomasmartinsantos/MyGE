#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"


namespace MyGE {

    class Renderer
    {
        // Methods
        public:
            static void BeginScene(OrthographicCamera& Camera);
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& VertexArray);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        // Variables
        private:
            struct SceneData
            {
                glm::mat4 ViewProjectionMatrix;
            };

            static SceneData* s_SceneData;
    };
}