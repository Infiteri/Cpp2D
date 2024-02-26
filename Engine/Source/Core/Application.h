#pragma once

#include "Base.h"

namespace Core
{
    class CE_API Application
    {
    public:
        Application();
        ~Application();

        virtual void OnInit();
        virtual void OnRender();
        virtual void OnUpdate();
        virtual void OnShutdown();
    };

    Application *CreateApplication();
}