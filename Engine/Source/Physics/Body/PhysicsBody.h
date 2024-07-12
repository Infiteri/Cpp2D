#pragma once

#include "Base.h"
#include "Math/Vectors.h"
#include "Math/Quaternion.h"
#include "Math/Matrices.h"
#include "Math/Transform.h"

#include "Physics/Collision/Colliders.h"

namespace Core
{
    class Actor;

    enum class BodyType
    {
        Static,
        Rigid,
        Kinematic
    };

    class CE_API PhysicsBody
    {
    protected:
        Actor *owner;
        BodyType type;

        /// @brief Internal transform matrix (Todo, think if should be calculated here or body specific)
        /// @note IMPORTANT: meant to be a 4x3 Matrix
        Matrix4x3 transformMatrixInternal;
        Quaternion quaternion; // To be set by each body
        AABBCollider *collider = new AABBCollider();

    public:
        PhysicsBody(){};
        virtual ~PhysicsBody(){};

        virtual void Update() {};
        Transform *GetTransform();

        inline Actor *GetOwner() { return owner; };
        inline BodyType GetType() { return type; };

        inline AABBCollider *GetCollider() { return collider; };

        template <typename T>
        T *SetCollider()
        {
            if (collider != nullptr)
                delete collider;

            collider = new T();
            return collider->As<T>();
        };

        CE_IMPLEMENT_CAST_T_AS();
    };
}