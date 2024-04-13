#include "ForceGenerator.h"
#include "Scene/Actor.h"
#include "Core/Logger.h"

namespace Core
{
    DragForceGenerator::DragForceGenerator(float _k1, float _k2)
    {
        k1 = _k1;
        k2 = _k2;
    }

    DragForceGenerator::~DragForceGenerator()
    {
    }

    void DragForceGenerator::Integrate(PhysicsBody *b, float dt)
    {
        Vector2 force;
        force = b->GetVelocity();

        float dragCoeff = force.Mag();
        dragCoeff = k1 * dragCoeff * k2 * dragCoeff;

        force.Normalize();
        force *= -dragCoeff;
        b->ApplyForce(force);
    }

    SpringForceGenerator::SpringForceGenerator(PhysicsBody *_a, PhysicsBody *_b)
    {
        a = _a;
        b = _b;
    }

    SpringForceGenerator::~SpringForceGenerator()
    {
    }

    // "disregard" is not needed, will pas in nullptr. (special kind of force generator)
    void SpringForceGenerator::Integrate(PhysicsBody *disregard, float dt)
    {
        if (!a || !b)
            return;

        Vector3 force;
        force = a->GetOwner()->GetTransform()->Position;
        force -= b->GetOwner()->GetTransform()->Position;

        // Calculate the magnitude of the force.
        float magnitude = force.Mag();
        magnitude = Math::Abs(magnitude - restLength);
        magnitude *= springConstant;

        force.Normalize();
        force *= -magnitude;
        a->ApplyForce({force.x * dt, force.y * dt});
    }
}