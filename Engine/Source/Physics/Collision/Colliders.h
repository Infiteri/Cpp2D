#pragma once

#include "Base.h"
#include "Math/Matrices.h"
#include "Math/Vectors.h"

namespace Core
{
    class PhysicsBody;
    class PrimitiveCollider
    {
    public:
        enum ColliderTypes
        {
            Primitive,
            AABB
        };

    protected:
        Matrix4x3 *transform; // Physical transform.
        friend class PhysicsBody;
        friend class RigidBody;
        ColliderTypes type;

    public:
        PrimitiveCollider() { type = Primitive; } // Most likely not to change, if so, this constructor will get re-implemented in the .cpp file
        ~PrimitiveCollider() {}

        PhysicsBody *ParentBody;
        Matrix4 Offset; // Out of the book, not sure if needed. TODO: Analyze

        Vector3 GetAxis(int i) const
        {
            return transform->GetAxisVector3(i);
        };

        /// @brief Returns a pointer to a physical transformation matrix (4x3).
        /// @return Matrix4x3 pointer.
        Matrix4x3 *GetTransformMatrix()
        {
            return transform;
        };

        inline ColliderTypes GetType()
        {
            return type;
        };

        CE_IMPLEMENT_CAST_T_AS();
    };

    class CE_API AABBCollider : public PrimitiveCollider
    {
    public:
        Vector2 Size;

        AABBCollider();
        ~AABBCollider();
    };
}