#include "PhysicsEngine.h"
#include "Core/Logger.h"
#include "Core/Engine.h"

namespace Core
{
    static PhysicsEngineState state;
    Spring spring;

    void PhysicsEngine::Init()
    {
        state.GravityScaled = 9.81f * CE_GRAVITY_SCALE;
    }

    void PhysicsEngine::Shutdown()
    {
    }

    void PhysicsEngine::SetGravity(float G)
    {
        state.GravityScaled = G * CE_GRAVITY_SCALE;
    }

    PhysicsBody *PhysicsEngine::CreateBody()
    {
        auto b = new PhysicsBody();
        state.bodies.push_back(b);
        return b;
    }

    void PhysicsEngine::StartRuntime()
    {
    }

    void PhysicsEngine::Update()
    {
        if (state.bodies.size() >= 2)
        {
            spring.Point = state.bodies[0];
            spring.Target = state.bodies[1];
        }
        spring.Update();

        for (auto b : state.bodies)
        {
            b->Update();
            state.ForceReg.UpdateWithBody(b, Engine::GetDeltaTime());
        }
    }

    void PhysicsEngine::StopRuntime()
    {
        for (auto it : state.bodies)
            delete it;

        state.bodies.clear();
    }

    Spring *PhysicsEngine::GetTempSpring()
    {
        return &spring;
    }

    float PhysicsEngine::GetGravityScaledValue()
    {
        return state.GravityScaled;
    }

}