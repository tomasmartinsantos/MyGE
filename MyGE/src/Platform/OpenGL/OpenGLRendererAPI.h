#pragma once
#include "MyGE/Renderer/RendererAPI.h"

namespace MyGE {

    class OpenGLRendererAPI : public RendererAPI
    {
        // Methods
        public:
            virtual void SetClearColor(const glm::vec4& Color) override;
            virtual void Clear() override;
            virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray) override;
    };
}