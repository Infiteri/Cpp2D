#include "ContactResolver.h"

namespace Core
{
    ContactResolver::ContactResolver(CeU32 iter)
    {
        Iterations = iter;
        IterationsUsed = 0;
    }

    ContactResolver::~ContactResolver()
    {
    }

    void ContactResolver::ResolveContacts(BodyContact *contacts, CeU32 numContacts, float dt)
    {
        IterationsUsed = 0;
        while (IterationsUsed < Iterations)
        {
            float max;
            CeU32 maxIndex = numContacts;

            for (CeU32 i = 0; i < numContacts; i++)
            {
                float sepVal = contacts[i].CalculateSeparatingVelocity();
                if (sepVal < max)
                {
                    max = sepVal;
                    maxIndex = i;
                }
            }

            contacts[maxIndex].Resolve(dt);
            IterationsUsed++;
        }
    }
}