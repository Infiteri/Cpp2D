#pragma once

#include "Base.h"
#include "Math/Vectors.h"
#include "Math/Quaternion.h"
#include "Math/Matrices.h"
#include "Math/Transform.h"

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

        Matrix4 transformMatrixInternal; // Internal transform matrix (Todo, think if should be calculated here or body specific)
        Quaternion quaternion;           // To be set by each body

    public:
        PhysicsBody(){};
        virtual ~PhysicsBody(){};

        virtual void Update() {};
        Transform *GetTransform();

        inline Actor *GetOwner() { return owner; };
        inline BodyType GetType() { return type; };
    };
}