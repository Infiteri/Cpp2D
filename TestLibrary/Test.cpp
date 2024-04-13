#include "Test.h"
#include "iostream"

float CycleSecond = 0.5f;
float Progress = 0.0f;
int ActionIndex = 0;
int Direction = 1;

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
    auto c = GetComponent<Core::PhysicsBodyComponent>();
    if (!c || !c->Body)
        return;

    if (Core::Input::GetKeyJustNow(Core::Keys::A))
    {
        c->Body->ApplyTorqueForce(1);
    }
}
