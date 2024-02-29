#include "Buffer.h"
#include <glad/glad.h>

namespace Core
{
    Buffer::Buffer(Type _type)
    {
        id = 0;
        stride = 0;
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

        switch (type)
        {
        case Vertex:

            glBindBuffer(GL_ARRAY_BUFFER, id);
            for (CeU32 i = 0; i < layouts.size(); i++)
            {
                CeU32 l = layouts[i].location;
                CeU32 o = layouts[i].offset;
                CeU32 s = layouts[i].size;
                glEnableVertexAttribArray(l);
                glVertexAttribPointer(l, s, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(o * sizeof(float)));
            }
            break;

        case Index:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
            break;
        }
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
            glDrawArrays(GL_TRIANGLES, 0, size / stride);
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

    void Buffer::AddLayout(int location, int offset, int size)
    {
        if (type != Vertex)
            return;

        stride += size;
        layouts.push_back({location, offset, size});
    }
}