#pragma once

#include "Base.h"
#include "Physics/PhysicsBody.h"

namespace Core
{
    struct CE_API ForceGenerator
    {
        enum Types
        {
            None,
            Drag
        };

        Types type = None;

        ForceGenerator(){};
        virtual ~ForceGenerator(){};

        virtual void Integrate(PhysicsBody *body, float dt){};

        template <typename T>
        T *As()
        {
            return (T *)this;
        };
    };

    struct CE_API DragForceGenerator : ForceGenerator
    {
        float k1;
        float k2;

        DragForceGenerator(float _k1, float _k2);
        ~DragForceGenerator();

        void Integrate(PhysicsBody *b, float dt);
    };

    /// @brief UNSTABLE
    struct CE_API SpringForceGenerator : ForceGenerator
    {
        PhysicsBody *a;
        PhysicsBody *b;

        float springConstant;
        float restLength;

        SpringForceGenerator(PhysicsBody *_a, PhysicsBody *_b);
        ~SpringForceGenerator();

        void Integrate(PhysicsBody *disregard, float dt);
    };
}
