#pragma once
#include "MyGE/Renderer/VertexArray.h"


namespace MyGE {

    class OpenGLVertexArray : public VertexArray
    {
        // Methods
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) override;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;

            virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
            virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

        // Variables
        private:
            uint32_t m_RendererID;
            std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}