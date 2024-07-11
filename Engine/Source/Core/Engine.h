#pragma once

#include "Base.h"
#include "Window.h"

namespace Core
{
    class CE_API Engine
    {
    public:
        struct Configuration
        {
            Window::Configuration WindowConfig;
            bool RenderImageToScreen = true;
        };

        struct State
        {
            Window *window;
            Configuration *config;
            float lastTime;
            float deltaTime;
        };

        Engine(){};
        ~Engine(){};

        static void FeedConfiguration(Configuration *config);
        static void PreInit();
        static void Init();
        static void Render();
        static void Update();
        static void Shutdown();

        static bool ShouldRun();

        static float GetDeltaTime();

        static Window *GetWindow();
        static Configuration *CreateDefaultConfiguration();
    };
}