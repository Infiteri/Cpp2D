#pragma once

#include "Core.h"
#include "Panels/SceneHierarchyPanel.h"
#include "EditorCamera.h"
#include <imgui.h>

namespace Core
{
    struct EditorState
    {
        SceneHierarchyPanel hierarchyPanel;
        bool canUpdateCamera = false;
        EditorCamera editorCamera;

        bool dockspaceOpen = true;
        bool opt_fullscreen = true;
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImVec2 lastFrameViewportSize;
        ImVec2 viewportLeftTop;
        ImVec2 viewportRightBottom;

        std::string sceneSaveFilePath;
    };

    class EditorLayer : public Layer
    {
    public:
        EditorLayer(){};
        ~EditorLayer(){};

        EditorState state;

        void OnImGuiRender();

        // -- UI --
        void UI_DrawTopBar();
        // --------

        // -- Editor functions --
        void ResizeViewport();

        void Save();
        void SaveAs();
        void Open();
        void OpenScene(const std::string &name);
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