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
        };

        struct State
        {
            Window *window;
            Configuration *config;
        };

        Engine(){};
        ~Engine(){};

        static void FeedConfiguration(Configuration* config);
        static void PreInit();
        static void Init();
        static void Render();
        static void Update();
        static void Shutdown();

        static bool ShouldRun();

        static Window *GetWindow();
        static Configuration* CreateDefaultConfiguration();
    };
}