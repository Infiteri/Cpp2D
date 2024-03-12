#pragma once

#include "Core.h"
#include "Panels/SceneHierarchyPanel.h"
#include <imgui.h>

namespace Core
{
    struct EditorState
    {
        SceneHierarchyPanel hierarchyPanel;

        bool dockspaceOpen = true;
        bool opt_fullscreen = true;
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImVec2 lastFrameViewportSize;
        ImVec2 viewportLeftTop;
        ImVec2 viewportRightBottom;
    };

    class EditorLayer : public Layer
    {
    public:
        EditorLayer(){};
        ~EditorLayer(){};

        EditorState state;

        void OnImGuiRender();

        // -- Editor functions --
        void ResizeViewport();
        // ----------------------

        // -- Dock space --
        void BeginDockspace();
        void RenderSceneViewport();
        void EndDockspace();
        // ----------------

        void OnAttach();
        void OnUpdate();
    };
}