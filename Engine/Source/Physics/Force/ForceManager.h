#pragma once

#include "Base.h"
#include "ForceGenerator.h"
#include <vector>

namespace Core
{
    class ForceManager
    {
    private:
        std::vector<BodyForceGenerator*> generators;

    public:
        ForceManager();
        ~ForceManager();

        void AddGenerator( BodyForceGenerator *Generator);
        void Update(PhysicsBody *Body);
    };

}