#pragma once

#include "Core.h"

class TestActor : public Core::ActorScript
{
public:
    TestActor();
    ~TestActor();

    void OnStart();
    void OnUpdate();
};

CE_ACTOR_SCRIPT_DEFINE(TestActor);