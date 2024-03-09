#pragma once

#include "Core.h"

namespace Core
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer(){};
        ~EditorLayer(){};

        void OnImGuiRender();

        void OnAttach();
        void OnUpdate();
    };
}