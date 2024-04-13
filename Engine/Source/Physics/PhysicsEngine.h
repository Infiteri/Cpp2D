#pragma once

#include "Base.h"
#include "PhysicsBody.h"
#include "Force/ForceRegistry.h"
#include "Spring.h"
#include "PhysBase.h"
#include <vector>

namespace Core
{
    struct PhysicsEngineState
    {
        std::vector<PhysicsBody *> bodies;

        /// @brief Gravity * CE_GRAVITY_SCALE
        float GravityScaled;

        ForceRegistry ForceReg;
    };

    class CE_API PhysicsEngine
    {
    public:
        PhysicsEngine(){};
        ~PhysicsEngine(){};

        static void Init();
        static void Shutdown();

        static void SetGravity(float G);

        static PhysicsBody *CreateBody();

        static void StartRuntime();
        static void Update();
        static void StopRuntime();

        static Spring *GetTempSpring();

        static float GetGravityScaledValue();
    };
}
