#include "Test.h"

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::OnStart()
{
}

void TestActor::OnUpdate()
{
    auto c = Owner->GetComponent<Core::RigidBody2DComponent>();
    Core::Vector2 *velocity = &c->Velocity;

    if (Core::Input::GetKey(Core::Keys::W))
    {
        velocity->y = 981.0f;
    }
}
