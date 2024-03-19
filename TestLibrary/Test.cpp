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
    Sprite = GetComponent<Core::SpriteComponent>();
}

void TestActor::OnUpdate()
{
    Progress += Core::Engine::GetDeltaTime();

    if (Progress >= CycleSecond)
    {
        Sprite->sprite->SetCurrentFrame(ActionIndex + ((Direction - 1) * 4));

        ActionIndex++;

        if (ActionIndex > 3)
            ActionIndex = 0;

        Progress = 0.0f;
    }

    if (Core::Input::GetKey(Core::Keys::W))
    {
        Direction = 3;
    }

    if (Core::Input::GetKey(Core::Keys::S))
    {
        Direction = 1;
    }

    if (Core::Input::GetKey(Core::Keys::D))
    {
        Direction = 2;
    }

    if (Core::Input::GetKey(Core::Keys::A))
    {
        Direction = 4;
    }
}
