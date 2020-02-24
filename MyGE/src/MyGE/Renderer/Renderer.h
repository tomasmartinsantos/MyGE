#pragma once
#include "RenderCommand.h"

namespace MyGE {

    class Renderer
    {
        // Methods
        public:
            static void BeginScene();
            static void EndScene();

            static void Submit(const std::shared_ptr<VertexArray>& VertexArray);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}