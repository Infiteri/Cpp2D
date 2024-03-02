#pragma once

#include "Base.h"

namespace Core {
    class Mesh
    {
        private:
        class VertexArray* array;
    public:
        Mesh();
        ~Mesh();

        void Render();
    };
}