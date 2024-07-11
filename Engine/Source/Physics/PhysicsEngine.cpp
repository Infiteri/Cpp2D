#include "PhysicsEngine.h"
#include "Core/Logger.h"

namespace Core
{
    static PhysicsEngine::State state;

    void PhysicsEngine::Init()
    {
        CE_DEFINE_LOG_CATEGORY_IF_NOT_EXIST("Physics", "CE_PHYS");
        state.processStep = Initialized;
    }

    void PhysicsEngine::Shutdown()
    {
        state.processStep = Stopped;
    }

    RigidBody *PhysicsEngine::RegisterFromConfig(RigidBodyConfiguration *Configuration)
    {
        RigidBody *rb = new RigidBody(Configuration);
        state.bodies.push_back(rb);
        return rb;
    }

    PhysicsEngine::Values *PhysicsEngine::GetValueSet()
    {
        return &state.valuesSet;
    }

    void PhysicsEngine::UpdateRuntime()
    {
        // if (state.processStep == Stopped)
        //     return;

        state.processStep = Running;

        for (auto b : state.bodies)
        {
            state.ForcesManager.Update(b);
            b->Update();
        }
    }

    void PhysicsEngine::StopRuntime()
    {
        for (auto b : state.bodies)
        {
            delete b;
        }

        state.bodies.clear();
    }
}