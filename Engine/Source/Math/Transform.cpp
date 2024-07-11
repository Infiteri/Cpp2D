#include "Transform.h"

namespace Core
{
    Matrix4 Transform::GetTransformMatrix()
    {
        Matrix4 pos = Matrix4::Translate(&Position);
        Matrix4 rot = Matrix4::RotationXYZ(&Rotation);
        rot = Matrix4::Invert(&rot);
        Matrix4 scl = Matrix4::Scale(&Scale);

        return (pos * rot) * scl;
    }
}