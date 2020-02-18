#pragma once

namespace MyGE {

    enum class RendererAPI
    {
        None = 0, OpenGL = 1
    };

    class Renderer
    {
        // Methods
        public:
            inline static RendererAPI GetAPI() { return s_RendererAPI; }

        // Variables
        private:
            static RendererAPI s_RendererAPI;
    };
}