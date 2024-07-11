#pragma once

#include "Base.h"

#include "Physics/Body/PhysicsBody.h"

namespace Core
{
    class BodyForceGenerator
    {
    public:
        enum ForceType
        {
            Default,
            Spring
        };

        ForceType Type = Default;
        BodyForceGenerator(){};
        ~BodyForceGenerator(){};

        virtual void Update(PhysicsBody *Body) {};
    };

    class BodySpringForceGenerator : public BodyForceGenerator
    {
    public:
        Vector2 Location;
        float SpringConstant;
        float RestLength;
        BodySpringForceGenerator(const Vector2 &Location, float SpringConstant, float RestLength);

        void Update(PhysicsBody *Body);
    };
}