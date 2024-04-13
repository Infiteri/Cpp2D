#include "ForceRegistry.h"

namespace Core
{
    ForceRegistry::ForceRegistry()
    {
    }

    ForceRegistry::~ForceRegistry()
    {
        for (auto gen : generators)
            delete gen;

        generators.clear();
    }

    void ForceRegistry::AddForceGenerator(ForceGenerator *generator)
    {
        generators.push_back(generator);
    }

    void ForceRegistry::UpdateWithBody(PhysicsBody *body, float dt)
    {
        for (auto it : generators)
            it->Integrate(body, dt);
    }

    ForceGenerator *ForceRegistry::GetGeneratorAt(int index)
    {
        if (index > generators.size())
        {
            return nullptr;
        }

        return generators[index];
    }
}