#include "PhysicsBody.h"
#include "Core/Logger.h"
#include "PhysicsEngine.h"
#include "Core/Engine.h"
#include "Scene/Actor.h"
#include "PhysBase.h"

namespace Core
{
    PhysicsBody::PhysicsBody()
    {
        type = Rigid;

        velocity = {0, 0};
        acceleration = {0, 0};
        forcesAccumulated = {0, 0};
        material.Damping = 1.0f;
    }

    PhysicsBody::~PhysicsBody()
    {
    }

    void PhysicsBody::Update()
    {
        if (!owner)
            return;

        switch (type)
        {
        default:
        case Static:
            UpdateStatic();
            break;

        case Rigid:
            UpdateRigid();
            break;

        case Kinematic:
            UpdateKinematic();
            break;
        }
    }

    void PhysicsBody::UsePhysicsMaterial(PhysicsMaterial *mat)
    {
        material.Damping = mat->Damping;
        material.Mass = mat->Mass;
        material.AngularDamping = mat->AngularDamping;
    }

    void PhysicsBody::ApplyForce(const Vector2 &v)
    {
        forcesAccumulated += v;
    }

    void PhysicsBody::ApplyTorqueForce(float v)
    {
        torqueAccumulated += {v * ((float)CE_DEG_TO_RAD), 0};
    }

    void PhysicsBody::ClearForces()
    {
        forcesAccumulated.Set(0, 0);
        torqueAccumulated.Set(0, 0);
    }

    void PhysicsBody::SetVelocity(const Vector2 &v)
    {
        velocity = v;
    }

    void PhysicsBody::UpdateStatic()
    {
    }

    void PhysicsBody::UpdateKinematic()
    {
    }

    void PhysicsBody::UpdateRigid()
    {
        auto transform = owner->GetTransform();
        float dt = Engine::GetDeltaTime();

        transform->Position += Vector3(velocity.x, velocity.y, 0.0);
        transform->Rotation += Vector3(0, 0, angularVelocity.x);

        InternalApplyGravity();

        Vector2 resultAcceleration = acceleration;
        resultAcceleration += forcesAccumulated;

        Vector2 resultAngAcceleration = angularAcceleration;
        resultAngAcceleration += torqueAccumulated;

        velocity += resultAcceleration;
        velocity *= Math::Pow(material.Damping, CE_DELTA_PHYSICS);

        angularVelocity += resultAngAcceleration;
        angularVelocity *= Math::Pow(material.AngularDamping, CE_DELTA_PHYSICS);

        CE_TRACE("%f %F", forcesAccumulated.x, forcesAccumulated.y);

        ClearForces();
    }

    void PhysicsBody::InternalApplyGravity()
    {
        float gravity = PhysicsEngine::GetGravityScaledValue();
        ApplyForce({0, (gravity * material.Mass)});
    }
}