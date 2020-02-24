#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"


namespace MyGE {

    class RendererAPI
    {
        public:
            enum class API
            {
                None = 0, OpenGL = 1
            };

        // Methods
        public:
            virtual void SetClearColor(const glm::vec4& Color) = 0;
            virtual void Clear() = 0;
            virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray) = 0;

            inline static API GetAPI() { return s_API; }

        // Variables
        private:
            static API s_API;
    };
}