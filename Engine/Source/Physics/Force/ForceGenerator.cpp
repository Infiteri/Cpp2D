#include "ForceGenerator.h"
#include "Scene/Actor.h"
#include "Math/Math.h"
#include "Physics/PhysCore.h"

namespace Core
{
    BodySpringForceGenerator::BodySpringForceGenerator(const Vector2 &Location, float SpringConstant, float RestLength)
    {
        Type = Spring;
        this->Location = Location;
        this->SpringConstant = SpringConstant;
        this->RestLength = RestLength;
    }

    void BodySpringForceGenerator::Update(PhysicsBody *Body)
    {
        if (!Body)
            return;

        Vector2 force;
        force = {Body->GetOwner()->GetTransform()->Position.x, Body->GetOwner()->GetTransform()->Position.y};
        force -= Location;

        float magnitude = force.Magnitude();
        magnitude *= Math::Abs(magnitude - RestLength);
        magnitude *= SpringConstant;

        force.Normalize();
        force *= -magnitude;
        RigidBody *b = Body->As<RigidBody>(); // Spooky
        b->ApplyImpulse(force * CE_PHYSICS_DELTA_TIME);
    }
}