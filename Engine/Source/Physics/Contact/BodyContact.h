#pragma once

#include "Base.h"
#include "Physics/PhysicsBody.h"
#include "Math/Vectors.h"

namespace Core
{
    class BodyContact
    {
    public:
        PhysicsBody *Bodies[2];
        float Restitution;
        Vector2 ContactNormal;
        float Penetration;

        BodyContact();
        ~BodyContact();

        float CalculateSeparatingVelocity();
        void Resolve(float dt);

    private:
        void ResolveVelocity(float dt);
        void ResolveInterpenetration(float dt);
    };
}