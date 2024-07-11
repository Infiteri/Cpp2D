#pragma once

#include "Base.h"
#include "Vectors.h"
#include "Matrices.h"

namespace Core
{
    struct Transform
    {
        Vector3 Position;
        Vector3 Rotation;
        Vector3 Scale{1, 1, 1};

        Matrix4 GetTransformMatrix();
    };

}