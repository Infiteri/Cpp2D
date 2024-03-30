#pragma once

#include "Core.h"
#include <string>

namespace Core
{
    struct EditorSettings;

    class EditorCamera
    {
    private:
        std::string cameraName;
        OrthographicCamera *camera;

    public:
        bool isRightClicking;
        float movementUnits = 1.0f;

        EditorCamera();
        ~EditorCamera();

        void SetupFromSetings(EditorSettings *settings);

        void Activate();

        void Update();
        void UpdateExitRightButton();
    };
}