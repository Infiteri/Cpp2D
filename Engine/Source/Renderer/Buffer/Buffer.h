#pragma once

#include "Base.h"

namespace Core
{
    class Buffer
    {
    public:
        enum Type
        {
            Vertex,
            Index
        };

    private:
        Type type;
        CeU32 id;
        int size;

    public:
        Buffer(Type type);
        ~Buffer();

        void Bind();
        void Unbind();
        void Draw();

        void Upload(void* data, int size);

        inline Type GetType() { return type; };
        inline CeU32 GetId() { return id; };
    };
}