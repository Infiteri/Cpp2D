#include "VertexArray.h"
#include <glad/glad.h>

namespace Core
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
        Bind();

        indexBuffer = new Buffer(Buffer::Index);
        vertexBuffer = new Buffer(Buffer::Vertex);
    }

    VertexArray::~VertexArray()
    {
        delete vertexBuffer;
        delete indexBuffer;

        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::Upload(Buffer::Type type, void *data, int size)
    {
        if (type == Buffer::Vertex)
            vertexBuffer->Upload(data, size);
        else
            indexBuffer->Upload(data, size);
    }
}