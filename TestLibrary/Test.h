#pragma once

#include "Core.h"

class TestActor : public Core::ActorScript
{
public:
    Core::RigidBodyComponent *rb;

    TestActor();
    ~TestActor();

    void OnStart();
    void OnUpdate();
};

CE_ACTOR_SCRIPT_DEFINE(TestActor);