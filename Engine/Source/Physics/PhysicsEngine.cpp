#include "PhysicsEngine.h"
#include "Core/Logger.h"
#include "Collision/CollisionDetector.h"

namespace Core
{
    static PhysicsEngine::State state;

    void PhysicsEngine::Init()
    {
        CE_DEFINE_LOG_CATEGORY_IF_NOT_EXIST("Physics", "CE_PHYS");
        state.processStep = Initialized;

        state.valuesSet.FPS = 480;
    }

    void PhysicsEngine::Shutdown()
    {
        state.processStep = Stopped;
    }

    RigidBody *PhysicsEngine::RegisterFromConfig(RigidBodyConfiguration *Configuration)
    {
        RigidBody *rb = new RigidBody(Configuration);
        rb->Update(); // Call update
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

        for (int i = 0; i < state.bodies.size(); i++)
        {
            auto b = state.bodies[i];

            b->Update();
            state.ForcesManager.Update(b);

            for (int j = i + 1; j < state.bodies.size(); j++)
            {
                auto other = state.bodies[j];

                bool result = CollisionDetector::AABBvsAABB(b->GetCollider(), other->GetCollider());

                CE_TRACE("Result: %s", result == true ? "YES" : "NO");
            }
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