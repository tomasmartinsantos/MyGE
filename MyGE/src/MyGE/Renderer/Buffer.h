#pragma once


namespace MyGE {

    class VertexBuffer
    {
        // Methods
        public:
            virtual ~VertexBuffer() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            static VertexBuffer* Create(float* Vertices, uint32_t Size);
    };

    class IndexBuffer
    {
        // Methods
        public:
            virtual ~IndexBuffer() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual uint32_t GetCount() const = 0;

            static IndexBuffer* Create(uint32_t* Indices, uint32_t Count);
    };
}