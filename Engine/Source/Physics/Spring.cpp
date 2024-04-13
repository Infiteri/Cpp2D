#include "Spring.h"
#include "Scene/Actor.h"
#include "Core/Engine.h"

namespace Core
{
    Spring::Spring()
    {
        SpringConstant = RestLength = 1;
        Point = nullptr;
        Target = nullptr;
    }

    Spring::~Spring()
    {
    }

    void Spring::Update()
    {
        if (!Point || !Target)
            return;

        Vector3 force = Point->GetOwner()->GetTransform()->Position;
        force -= Target->GetOwner()->GetTransform()->Position;

        float mag = force.Mag();
        mag = Math::Abs(mag - RestLength);
        mag *= SpringConstant;

        force.Normalize();
        force *= mag;
        force *= Engine::GetDeltaTime();
        Target->ApplyForce({force.x, force.y});
    }
}