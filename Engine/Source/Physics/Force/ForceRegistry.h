#pragma once

#include "ForceGenerator.h"
#include <vector>

namespace Core
{
    class ForceRegistry
    {
    private:
        std::vector<ForceGenerator *> generators;

    public:
        ForceRegistry();
        ~ForceRegistry();

        void AddForceGenerator(ForceGenerator *generator);
        void UpdateWithBody(PhysicsBody *body, float dt);

        ForceGenerator *GetGeneratorAt(int index);

        template <typename T, typename... Args>
        T *AddForceGenerator(Args... args)
        {
            T *t = new T(args...);
            AddForceGenerator(t);
            return t;
        };
    };
}