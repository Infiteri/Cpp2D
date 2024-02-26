#include "Engine.h"
#include "Logger.h"

namespace Core
{
    static Engine::State state;

    void Engine::PreInit()
    {
        CE_CORE_INFO("Starting Engine...");

        Logger::Init();

        Window::Configuration WindowConfig;
        WindowConfig.X = 10;
        WindowConfig.Y = 10;
        WindowConfig.Width = 1024;
        WindowConfig.Height = 576;
        WindowConfig.Title = "Try me";
        state.window = new Window(WindowConfig);

        CE_CORE_INFO("Started Engine with success");
    }

    void Engine::Init()
    {
        // TODO: Plugins, assets, other stuff... .
    }

    void Engine::Render()
    {
    }

    void Engine::Update()
    {
        state.window->Update();
    }

    void Engine::Shutdown()
    {
        CE_CORE_INFO("Stopping Engine...");
        Logger::Shutdown();

        delete state.window;
    }

    bool Engine::ShouldRun()
    {

        return state.window->ShouldRun();
    }

    Window *Engine::GetWindow()
    {
        return state.window;
    }
}