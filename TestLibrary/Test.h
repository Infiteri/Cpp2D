#pragma once

#include "Core.h"

class TestActor : public Core::ActorScript
{
public:
    Core::SpriteComponent *Sprite;

    TestActor();
    ~TestActor();

    void OnStart();
    void OnUpdate();
};

CE_ACTOR_SCRIPT_DEFINE(TestActor);