#include "PhysicsBody.h"
#include "Scene/Actor.h"

namespace Core
{
    Transform *PhysicsBody::GetTransform()
    {
        {
            if (!owner)
                return nullptr;

            return owner->GetTransform();
        };
    }
}