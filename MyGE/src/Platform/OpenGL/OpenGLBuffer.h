#pragma once
#include "MyGE/Renderer/Buffer.h"


namespace MyGE {

    class OpenGLVertexBuffer : public VertexBuffer
    {
        // Methods
        public:
            OpenGLVertexBuffer(float* Vertices, uint32_t Size);
            virtual ~OpenGLVertexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual const BufferLayout& GetLayout() const override { return m_Layout; };
            virtual void SetLayout(const BufferLayout& Layout) override { m_Layout = Layout; };

        // Variables
        private:
            uint32_t m_RendererID;
            BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
        // Methods
        public:
            OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count);
            virtual ~OpenGLIndexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual uint32_t GetCount() const override { return m_Count; }

        // Variables
        private:
            uint32_t m_RendererID;
            uint32_t m_Count;
    };
}