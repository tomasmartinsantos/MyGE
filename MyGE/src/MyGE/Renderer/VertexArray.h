#pragma once
#include "MyGE/Renderer/Buffer.h"
#include <memory>


namespace MyGE {

    class VertexArray
    {
        // Methods
        public:
            virtual ~VertexArray() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) = 0;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

            virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
            virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

            static VertexArray* Create();
    };
}