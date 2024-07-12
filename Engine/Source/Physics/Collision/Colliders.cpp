#include "Colliders.h"
#include "Physics/Body/PhysicsBody.h"

namespace Core
{
    // TODO: Unused so maybe delete?
    //* Stupid to this, or the whole cpp file in general, but maybe could be useful.
    //* Compiles with all the dlls export from the .h file so maybe this is its use
    // TODO: Reconsider this files existence
    AABBCollider::AABBCollider()
    {
        type = AABB;
        Size.Set(100, 100); // TODO: Temp
    }

    AABBCollider::~AABBCollider()
    {
    }
}