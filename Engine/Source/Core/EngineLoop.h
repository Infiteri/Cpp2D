#pragma once

#include "Application.h"

namespace Core
{
    class CE_API EngineLoop
    {
    private:
        Application *app;

    public:
        EngineLoop();
        ~EngineLoop();

        void FeedApplication(Application *application);

        void PerformSetupStage();
        void PerformRunning();
        void PerformShutdown();
    };
} // namespace Core
