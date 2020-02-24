#pragma once
#include "RendererAPI.h"

namespace MyGE {

    class RenderCommand
    {
        // Methods
        public:
            inline static void SetClearColor(const glm::vec4& Color)
            {
                s_RendererAPI->SetClearColor(Color);
            }

            inline static void Clear()
            {
                s_RendererAPI->Clear();
            }

            inline static void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
            {
                s_RendererAPI->DrawIndexed(VertexArray);
            }

        // Variables
        private:
            static RendererAPI* s_RendererAPI;
    };
}