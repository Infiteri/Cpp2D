#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Layer/ImGuiLayer.h"
#include "Layer/LayerStack.h"
#include "Scene/World.h"

namespace Core
{
    static Engine::State state;

    void Engine::FeedConfiguration(Configuration *config)
    {
        if (state.config)
        {
            CE_CORE_WARN("Engine::FeedConfiguration has configuration already. Will reset to new configuration and will delete the old one. Bad things MAY happen");
            delete state.config;
        }

        state.config = config;
    }

    void Engine::PreInit() //? Subsystem loading faze
    {
        // Config to use, if there is no configuration bound via FeedConfiguration the Engine will create a default configuration for it.
        Configuration *Config = nullptr;
        if (state.config)
            Config = state.config;
        else
            Config = Engine::CreateDefaultConfiguration();
        state.config = Config;

        Logger::Init();
        CE_CORE_INFO("Starting Engine...");

        // TODO: Load from file (A Lot later)
        state.window = new Window(Config->WindowConfig);
        Input::Init();
        Renderer::Init();

        Renderer::Viewport(state.window->GetState()->Width, state.window->GetState()->Height);
        ImGuiLayer::Init();
        LayerStack::Init();
        World::Init();

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
        World::RenderActiveScene();
        Renderer::EndFrame();

        if (state.config->RenderImageToScreen)
            Renderer::RenderScreenTexture(); // Will change if with editor in the future or if user doesn't want to render to screen.

        ImGuiLayer::BeginFrame();
        LayerStack::RenderImGui();
        ImGuiLayer::EndFrame();
    }

    void Engine::Update()
    {
        state.window->Update();
        World::UpdateActiveScene();
        LayerStack::Update();
        Input::InternalUpdate();
    }

    void Engine::Shutdown()
    {
        CE_CORE_INFO("Stopping Engine...");
        Renderer::Shutdown();
        ImGuiLayer::Shutdown();
        LayerStack::Destroy();
        World::Shutdown();

        delete state.window;
        Logger::Shutdown();
    }

    bool Engine::ShouldRun()
    {

        return state.window->ShouldRun();
    }

    Window *Engine::GetWindow()
    {
        return state.window;
    }

    Engine::Configuration *Engine::CreateDefaultConfiguration()
    {
        state.config = new Configuration;

        state.config->WindowConfig.X = 0;
        state.config->WindowConfig.Y = 0;
        state.config->WindowConfig.Width = 1280;
        state.config->WindowConfig.Height = 720;
        state.config->WindowConfig.Title = "Core Engine";
        state.config->WindowConfig.VSync = true;
        state.config->WindowConfig.Mode = Window::Normal;

        return state.config;
    }
}