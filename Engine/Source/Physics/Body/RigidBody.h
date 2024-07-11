#pragma once

#include "PhysicsBody.h"
#include "BaseBodyConfiguration.h"

namespace Core
{
    struct RigidBodyConfiguration : public BaseBodyConfigurations
    {
        float Mass = 1.0f;
        float Damp = 0.5f;
        float GravityScale = 1.0f;

        RigidBodyConfiguration(){};
        ~RigidBodyConfiguration(){};

        void From(RigidBodyConfiguration *Configuration);
    };

    class CE_API RigidBody : public PhysicsBody
    {
    private:
        // friend class SceneHierarchyPanel; // TODO: Needed?

        RigidBodyConfiguration config;

        Vector2 velocity;
        Vector2 acceleration{0, 0};
        Vector2 totalImpulse;

        float angularVelocity = 0;     /// @brief In degrees
        float angularAcceleration = 0; /// @brief In degrees
        float totalTorque = 0;         /// @brief In degrees

        void _CalculateData();

    public:
        RigidBody(RigidBodyConfiguration *Configuration);
        ~RigidBody();

        void Update();

        // -- Getters / Setters
        inline float GetMass() { return config.Mass; };
        inline void SetMass(float mass) { config.Mass = mass; };

        inline float GetDamp() { return config.Damp; };
        inline void SetDamp(float damp) { config.Damp = damp; };

        inline float GetGravityScale() { return config.GravityScale; };
        inline void SetGravityScale(float gravityScale) { config.GravityScale = gravityScale; };

        inline Vector2 *GetAcceleration() { return &acceleration; };

        inline RigidBodyConfiguration *GetConfiguration() { return &config; };

        void ApplyImpulse(const Vector2 &impulse);

        /// @brief Will apply a once-on-frame impulse to the total torque acceleration accumulated (rotation velocity).
        /// @param impulse The impulse to use (divided by mass and expected to be used in degrees)
        void ApplyTorque(float impulse);
    };
}