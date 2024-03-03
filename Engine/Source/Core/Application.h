#pragma once

#include "Base.h"
#include "Engine.h"

namespace Core
{
    class CE_API Application
    {
    public:
        Application();
        ~Application();

        virtual void OnInit();
        virtual void OnUpdate();
        virtual void OnShutdown();
    };

    Application *CreateApplication(Engine::Configuration *config);
}