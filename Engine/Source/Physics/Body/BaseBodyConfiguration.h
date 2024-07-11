#pragma once

#include "Base.h"

namespace Core
{
    class Actor;
    struct BaseBodyConfigurations
    {
        Actor *Owner = nullptr;

        BaseBodyConfigurations(){};
        ~BaseBodyConfigurations(){};

        virtual void From(BaseBodyConfigurations *Configuration) {};
    };

}