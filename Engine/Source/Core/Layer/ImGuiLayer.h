#pragma once

#include "Base.h"

namespace Core
{
    class CE_API ImGuiLayer
    {
    public:
        ImGuiLayer(){};
        ~ImGuiLayer(){};

        
        static void Init();
        static void SetColorsToDefaultStyle();
        static void Shutdown();
        static void BeginFrame();
        static void EndFrame();
    };
}