#include "RigidBody.h"
#include "Physics/PhysCore.h"
#include "Physics/PhysicsEngine.h"
#include "BaseBodyConfiguration.h"
#include "Scene/Actor.h"
#include "Core/Logger.h"
#include "Math/Math.h"
#include "Scene/ACtor.h"

// NOTE: Matrix multiplication might not work as expected due to the current implementation

namespace Core
{
    static inline void _CalculateTransformMatrix(Matrix4x3 *transformMatrix,
                                                 const Vector3 &position,
                                                 const Quaternion &orientation)
    {
        transformMatrix->data[0] = 1 - 2 * orientation.j * orientation.j -
                                   2 * orientation.k * orientation.k;
        transformMatrix->data[1] = 2 * orientation.i * orientation.j -
                                   2 * orientation.r * orientation.k;
        transformMatrix->data[2] = 2 * orientation.i * orientation.k +
                                   2 * orientation.r * orientation.j;
        transformMatrix->data[3] = position.x;

        transformMatrix->data[4] = 2 * orientation.i * orientation.j +
                                   2 * orientation.r * orientation.k;
        transformMatrix->data[5] = 1 - 2 * orientation.i * orientation.i -
                                   2 * orientation.k * orientation.k;
        transformMatrix->data[6] = 2 * orientation.j * orientation.k -
                                   2 * orientation.r * orientation.i;
        transformMatrix->data[7] = position.y;

        transformMatrix->data[8] = 2 * orientation.i * orientation.k -
                                   2 * orientation.r * orientation.j;
        transformMatrix->data[9] = 2 * orientation.j * orientation.k +
                                   2 * orientation.r * orientation.i;
        transformMatrix->data[10] = 1 - 2 * orientation.i * orientation.i -
                                    2 * orientation.j * orientation.j;
        transformMatrix->data[11] = position.z;
    }

    void RigidBody::_CalculateData()
    {
        type = BodyType::Rigid;

        if (!GetTransform())
            return;

        quaternion.RotateToVector(GetTransform()->Rotation);
        _CalculateTransformMatrix(&transformMatrixInternal, GetTransform()->Position, quaternion);

        collider->transform = &transformMatrixInternal;
    }

    RigidBody::RigidBody(RigidBodyConfiguration *Configuration)
    {
        config.From(Configuration);

        owner = config.Owner;

        collider = new AABBCollider();
        collider->Size.Set(100, 100);
        collider->ParentBody = this;
    }

    RigidBody::~RigidBody()
    {
        if (collider)
            delete collider;
    }

    void RigidBody::Update()
    {
        if (!owner)
            return;

        _CalculateData(); // TODO: Think about positioning this better

        //? Add velocity
        {
            auto position = &owner->GetTransform()->Position;
            auto rotation = &owner->GetTransform()->Rotation;

            position->x += velocity.x * CE_PHYSICS_DELTA_TIME;
            position->y += velocity.y * CE_PHYSICS_DELTA_TIME;

            rotation->z += angularVelocity * CE_DEG_TO_RAD * CE_PHYSICS_DELTA_TIME;
        }

        // Calculate accelerations
        Vector2 ResultAcceleration;
        ResultAcceleration += acceleration;
        ApplyImpulse({0, -PhysicsEngine::GetValueSet()->Gravity * config.GravityScale});
        ResultAcceleration += totalImpulse;

        float ResultTorque = 0; //? LMAOOOOOOOOO THIS CAUSED AN ERROR WITH ROTATIONS HEHEHEH
        ResultTorque += totalTorque;
        ResultTorque += angularAcceleration;

        velocity += ResultAcceleration;
        angularVelocity += ResultTorque;

        // Impose drag
        velocity *= Math::Pow(config.Damp, CE_PHYSICS_DELTA_TIME);
        angularVelocity *= Math::Pow(config.Damp, CE_PHYSICS_DELTA_TIME);

        totalImpulse.Set(0, 0);
        totalTorque = 0;
    }

    void RigidBody::ApplyImpulse(const Vector2 &impulse)
    {
        Vector2 v;
        v.Set(impulse);
        totalImpulse += v / config.Mass;
    }

    void RigidBody::ApplyTorque(float impulse)
    {
        totalTorque += impulse / config.Mass;
    }

    void RigidBodyConfiguration::From(RigidBodyConfiguration *Configuration)
    {
        Owner = Configuration->Owner;
        Mass = Configuration->Mass;
        Damp = Configuration->Damp;
        GravityScale = Configuration->GravityScale;
    }
}