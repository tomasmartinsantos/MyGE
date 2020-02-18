#pragma once
#include <string>

namespace MyGE {

    class Shader
    {
        // Methods
        public:
            Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
            ~Shader();

            void Bind() const;
            void Unbind() const;

        // Variables
        private:
            uint32_t m_RendererID;
    };
}