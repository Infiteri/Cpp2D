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
    rb = GetComponent<Core::RigidBodyComponent>();
    if (!rb)
        return;

    if (Core::Input::GetKey(Core::Keys::W))
    {
        rb->Body->ApplyTorque(10);
    }
}
