#include "EngineLoop.h"
#include "Engine.h"

namespace Core
{
    EngineLoop::EngineLoop()
    {
        app = nullptr;
    }

    EngineLoop::~EngineLoop()
    {
    }

    void EngineLoop::FeedApplication(Application *application)
    {
        app = application;
    }

    void EngineLoop::PerformSetupStage()
    {
        Engine::PreInit();
        Engine::Init();

        if (app)
            app->OnInit();
    }

    void EngineLoop::PerformRunning()
    {
        while (Engine::ShouldRun())
        {
            Engine::Render();
            Engine::Update();
            if (app)
                app->OnUpdate();
        }
    }

    void EngineLoop::PerformShutdown()
    {
        if (app)
            app->OnShutdown();

        Engine::Shutdown();
    }
}