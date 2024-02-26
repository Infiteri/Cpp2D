#pragma once

#include "Base.h"
#include "Window.h"

namespace Core
{
    class CE_API Engine
    {
    public:
        struct State
        {
            Window *window;
        };

        Engine(){};
        ~Engine(){};

        static void PreInit();
        static void Init();
        static void Render();
        static void Update();
        static void Shutdown();

        static bool ShouldRun();

        static Window* GetWindow();
    };
}