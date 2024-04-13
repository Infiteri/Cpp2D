#include "BodyContact.h"
#include "Scene/Actor.h"

namespace Core
{
    BodyContact::BodyContact()
    {
    }

    BodyContact::~BodyContact()
    {
    }

    void BodyContact::Resolve(float dt)
    {
        ResolveVelocity(dt);
        ResolveInterpenetration(dt);
    }

    float BodyContact::CalculateSeparatingVelocity()
    {
        Vector2 relativeVelocity = Bodies[0]->GetVelocity();
        if (Bodies[1])
            relativeVelocity -= Bodies[1]->GetVelocity();

        return relativeVelocity.Dot(ContactNormal);
    }

    void BodyContact::ResolveVelocity(float dt)
    {
        auto b1 = Bodies[0];
        auto b2 = Bodies[1];

        // Find the velocity in the direction of the contact.
        float separatingVelocity = CalculateSeparatingVelocity();

        if (separatingVelocity <= 0)
            return;

        float newSepVel = separatingVelocity * Restitution;

        Vector2 accCausedVelocity = b1->GetAcceleration();
        accCausedVelocity -= b2->GetAcceleration();
        float accCausedSepVelocity = accCausedVelocity.Dot(ContactNormal * dt);

        if (accCausedSepVelocity < 0)
        {
            newSepVel += Restitution * accCausedSepVelocity;
            if (newSepVel < 0)
                newSepVel = 0;
        }

        float deltaVelocity = newSepVel - separatingVelocity;

        float totalInverseMass = -b1->GetMass();
        totalInverseMass -= b2->GetMass();

        if (-totalInverseMass < 0)
        {
            return;
        }

        float impulse = deltaVelocity / totalInverseMass;
        Vector2 impulsePerIMass = ContactNormal * impulse;
        b1->SetVelocity(b1->GetVelocity() + (impulsePerIMass * -b1->GetMass()));
        b2->SetVelocity(b2->GetVelocity() + (impulsePerIMass * b2->GetMass()));
    }

    void BodyContact::ResolveInterpenetration(float dt)
    {
        if (Penetration <= 0)
            return;

        auto b1 = Bodies[0];
        auto b2 = Bodies[1];

        float totalInverseMass = -b1->GetMass();
        totalInverseMass -= b2->GetMass();
        if (-totalInverseMass < 0)
            return;

        Vector2 movePerIMass = ContactNormal *
                               (-Penetration / totalInverseMass);

        auto b1Calc = movePerIMass * -b1->GetMass();
        auto b2Calc = movePerIMass * -b2->GetMass();

        b1->GetOwner()->GetTransform()->Position = b1->GetOwner()->GetTransform()->Position + Vector3(b1Calc.x, b1Calc.y, 0.0);
        b2->GetOwner()->GetTransform()->Position = b2->GetOwner()->GetTransform()->Position + Vector3(b2Calc.x, b2Calc.y, 0.0);
    }
}