#include "ForceManager.h"

namespace Core
{
    ForceManager::ForceManager()
    {
    }

    ForceManager::~ForceManager()
    {
        for (auto g : generators)
            delete g;

        generators.clear();
    }

    void ForceManager::AddGenerator(BodyForceGenerator *Generator)
    {
        generators.push_back(Generator);
    }

    void ForceManager::Update(PhysicsBody *Body)
    {
        for (auto gen : generators)
            gen->Update(Body);
    }
}