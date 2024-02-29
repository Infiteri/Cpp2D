#pragma once

#include "Base.h"
#include <vector>

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
        struct Layout
        {
            int location;
            int offset;
            int size;

            Layout(int l, int o, int s) : location(l), offset(o), size(s) {}
        };

        Type type;
        CeU32 id;
        int size;

        std::vector<Layout> layouts;
        int stride;

    public:
        Buffer(Type type);
        ~Buffer();

        void Bind();
        void Unbind();
        void Draw();

        void Upload(void *data, int size);

        void AddLayout(int location, int offset, int size);

        inline Type GetType() { return type; };
        inline CeU32 GetId() { return id; };
    };
}