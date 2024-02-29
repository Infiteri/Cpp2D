#pragma once

#include "Base.h"
#include "Buffer.h"

namespace Core
{
    class VertexArray
    {
    private:
        CeU32 id;

        Buffer *vertexBuffer;
        Buffer *indexBuffer;

    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void Unbind();

        void Upload(Buffer::Type type, void *data, int size);

        inline Buffer *GetVertexBuffer() { return vertexBuffer; };
        inline Buffer *GetIndexBuffer() { return indexBuffer; };

        inline CeU32 GetID() { return id; };
    };
}