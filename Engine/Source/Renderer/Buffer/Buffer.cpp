#include "Buffer.h"
#include <glad/glad.h>

namespace Core
{
    Buffer::Buffer(Type _type)
    {
        type = _type;

        glGenBuffers(1, &id);
        Bind();
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &id);
        id = 0;
    }

    void Buffer::Bind()
    {
        glBindBuffer(type == Vertex ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void Buffer::Unbind()
    {
        glBindBuffer(type == Vertex ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Buffer::Draw()
    {
        switch (type)
        {
        case Vertex:
            glDrawArrays(GL_TRIANGLES, 0, 3);
            break;

        case Index:
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
            break;
        }
    }

    void Buffer::Upload(void *data, int _size)
    {
        size = _size;
        glBufferData(type == Vertex ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, _size, data, GL_STATIC_DRAW);
    }
}