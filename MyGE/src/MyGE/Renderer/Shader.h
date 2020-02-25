#pragma once
#include <string>
#include <glm/glm.hpp>

namespace MyGE {

    class Shader
    {
        // Methods
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void SetMat4(const std::string& Name, const glm::mat4& Value) = 0;

            static Shader* Create(const std::string& VertexSrc, const std::string& FragmentSrc);
    };
}