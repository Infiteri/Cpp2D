#pragma once

#include "Base.h"
#include "Body/PhysicsBody.h"
#include "Body/BaseBodyConfiguration.h"
#include "Body/RigidBody.h"
#include "Force/ForceManager.h"

#include <vector>

namespace Core
{
    class CE_API PhysicsEngine
    {
    public:
        enum ProcessStep
        {
            Uninitialized,
            Initialized,
            Stopped,
            Running,
        };

        struct Values
        {
            float Gravity = 981.0f; // TODO: Set from project file
            float FPS = 240.0f;
        };

        struct State
        {
            ForceManager ForcesManager;
            std::vector<PhysicsBody *> bodies;
            ProcessStep processStep = Uninitialized;
            Values valuesSet;
        };

        PhysicsEngine(){};
        ~PhysicsEngine(){};

        static void Init();
        static void Shutdown();

        // static PhysicsBody *RegisterFromConfig(StaticBodyConfiguration *Configuration);
        static RigidBody *RegisterFromConfig(RigidBodyConfiguration *Configuration);
        // static PhysicsBody *RegisterFromConfig(KinematicBodyConfiguration *Configuration);
        static Values *GetValueSet();

        static void UpdateRuntime();
        static void StopRuntime();
    };
}