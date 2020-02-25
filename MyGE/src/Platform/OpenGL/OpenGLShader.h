#pragma once
#include "MyGE/Renderer/Shader.h"


namespace MyGE {

    class OpenGLShader : public Shader
    {
        // Methods
        public:
            OpenGLShader(const std::string& VertexSrc, const std::string& FragmentSrc);
            virtual ~OpenGLShader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void SetMat4(const std::string& Name, const glm::mat4& Value) override;

            void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix);

        // Variables
        private:
            uint32_t m_RendererID;
    };
}