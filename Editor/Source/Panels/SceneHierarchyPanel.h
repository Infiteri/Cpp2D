#pragma once

#include "Core.h"
#include <imgui.h>

namespace Core
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel();
        ~SceneHierarchyPanel(){};

        Actor *selectionContext = nullptr;

        void OnImGuiRender();

        void RenderActorUI(Actor *a);
        void RenderActorProps(Actor *a);
    };
}