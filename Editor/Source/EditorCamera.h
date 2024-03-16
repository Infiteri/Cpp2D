#pragma once

#include "Core.h"
#include <string>

namespace Core
{
    class EditorCamera
    {
    private:
        std::string cameraName;
        OrthographicCamera *camera;

    public:
        bool isRightClicking;

        EditorCamera();
        ~EditorCamera();

        void Activate();

        void Update();
        void UpdateExitRightButton();
    };
}