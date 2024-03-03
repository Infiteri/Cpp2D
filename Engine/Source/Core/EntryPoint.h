#pragma once

#include "EngineLoop.h"
#include "Engine.h"

extern Core::Application *Core::CreateApplication(Core::Engine::Configuration *config);

int main(int argc, char const *argv[])
{
    Core::EngineLoop EngineLoop;
    Core::Engine::Configuration EngineConfiguration;

    //? Default values
    EngineConfiguration.WindowConfig.X = 0;
    EngineConfiguration.WindowConfig.Y = 0;
    EngineConfiguration.WindowConfig.Width = 1280;
    EngineConfiguration.WindowConfig.Height = 720;
    EngineConfiguration.WindowConfig.Title = "Core Engine";
    EngineConfiguration.WindowConfig.VSync = true;
    EngineConfiguration.WindowConfig.Mode = Core::Window::Normal;

    auto App = Core::CreateApplication(&EngineConfiguration);
    Core::Engine::FeedConfiguration(&EngineConfiguration);
    EngineLoop.FeedApplication(App);
    EngineLoop.PerformSetupStage();
    EngineLoop.PerformRunning();
    EngineLoop.PerformShutdown();

    return 0;
}