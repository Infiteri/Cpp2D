#pragma once

#include "Base.h"
#include "Colliders.h"

namespace Core
{
    class CollisionDetector
    {
    public:
        CollisionDetector() {};
        ~CollisionDetector() {};

        static bool AABBvsAABB(AABBCollider* a, AABBCollider* b);
    };

}