#pragma once

#include "EngineLoop.h"

extern Core::Application *Core::CreateApplication();

int main(int argc, char const *argv[])
{
    Core::EngineLoop EngineLoop;
    EngineLoop.FeedApplication(Core::CreateApplication());
    EngineLoop.PerformSetupStage();
    EngineLoop.PerformRunning();
    EngineLoop.PerformShutdown();

    return 0;
}