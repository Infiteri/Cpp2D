#pragma once

#include "Base.h"
#include "Scene/Actor.h"

namespace Core
{
    class CE_API ActorScript
    {
    public:
        Actor *Owner;

        ActorScript();
        ~ActorScript();

        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnDestroy();

        template <typename T>
        T *GetComponent()
        {
            if (!Owner)
                return nullptr;

            return Owner->GetComponent<T>();
        };
    };
}