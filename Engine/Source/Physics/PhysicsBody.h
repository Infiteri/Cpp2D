#pragma once

#include "Base.h"

#include "Math/Math.h"
#include "Math/Vectors.h"

namespace Core
{
    class Actor;
    struct PhysicsMaterial
    {
        float Damping = 1.0f;
        float Mass = 1.0f;
        float AngularDamping = 1.0f;
    };

    class CE_API PhysicsBody
    {
    public:
        enum BodyType
        {
            Static,
            Kinematic,
            Rigid
        };

    private:
        Actor *owner;
        BodyType type;

        PhysicsMaterial material;

        void UpdateStatic();
        void UpdateKinematic();
        void UpdateRigid();

        void InternalApplyGravity();

        Vector2 velocity;
        Vector2 angularVelocity;

        Vector2 acceleration;
        Vector2 angularAcceleration;

        Vector2 forcesAccumulated;
        Vector2 torqueAccumulated;

    public:
        PhysicsBody();
        ~PhysicsBody();

        void Update();

        inline void SetOwner(Actor *a) { owner = a; };

        inline BodyType GetBodyType() { return type; };
        inline void SetBodyType(BodyType t) { type = t; };

        void UsePhysicsMaterial(PhysicsMaterial *mat);
        inline PhysicsMaterial *GetPhysicsMaterial() { return &material; };

        inline float GetDamping() { return material.Damping; };
        inline void SetDamping(float v) { material.Damping = v; };

        void ApplyForce(const Vector2 &v);

        /// @brief Applies a torque impulse to the body.
        /// @param v Rotation in degrees
        void ApplyTorqueForce(float v);

        void ClearForces();

        inline Vector2 GetVelocity() { return velocity; };
        inline Actor *GetOwner() { return owner; };

        inline float GetMass() { return material.Mass; };
        inline Vector2 GetAcceleration() { return acceleration; };

        void SetVelocity(const Vector2 &v);
    };
}