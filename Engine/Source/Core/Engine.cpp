#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "Input.h"
#include "Renderer/Renderer.h"

namespace Core
{
    static Engine::State state;

    void Engine::PreInit()
    {
        Logger::Init();
        CE_CORE_INFO("Starting Engine...");
        Input::Init();

        // TODO: Load from file (A Lot later)
        Window::Configuration WindowConfig;
        WindowConfig.X = 10;
        WindowConfig.Y = 10;
        WindowConfig.Width = 1024;
        WindowConfig.Height = 576;
        WindowConfig.Title = "Core Engine";
        WindowConfig.VSync = true;
        state.window = new Window(WindowConfig);

        Renderer::Init();

        CE_CORE_INFO("Started Engine with success");
    }

    void Engine::Init()
    {
        // TODO: Plugins, assets, other stuff... .
    }

    void Engine::Render()
    {
        Renderer::BeginFrame();
        Renderer::Render();
        // TODO: Add layer stack
        Renderer::EndFrame();

        Renderer::RenderScreenTexture(); // Will change if with editor in the future or if user doesn't want to render to screen.
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