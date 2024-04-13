#pragma once

#include "Base.h"

#include "BodyContact.h"

namespace Core
{
    class ContactResolver
    {
    public:
        CeU32 Iterations;
        CeU32 IterationsUsed;

        ContactResolver(CeU32 iter);
        ~ContactResolver();

        void ResolveContacts(BodyContact *contacts, CeU32 numContacts, float dt);
    };

}