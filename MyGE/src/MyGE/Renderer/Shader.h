#pragma once
#include <string>

namespace MyGE {

    class Shader
    {
        // Methods
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            static Shader* Create(const std::string& VertexSrc, const std::string& FragmentSrc);
    };
}