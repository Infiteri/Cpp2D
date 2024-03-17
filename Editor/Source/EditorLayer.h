#pragma once

#include "Core.h"
#include "Panels/SceneHierarchyPanel.h"
#include "EditorCamera.h"
#include <imgui.h>
#include <vector>

namespace Core
{
    struct EditableColorStyle
    {
        std::string Name;
        ImGuiCol Color;

        EditableColorStyle(const char *n, ImGuiCol c)
        {
            Name = n;
            Color = c;
        };
    };

    struct EditorSettings
    {
        float CameraZoom;
        std::vector<EditableColorStyle> editableColors;
    };

    struct EditorSettingsMenu
    {
        bool Render = false;
    };

    struct EditorState
    {
        EditorSettings editorSettings;
        SceneHierarchyPanel hierarchyPanel;
        EditorSettingsMenu settingsMenu;

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

        void OnAttach();
        void OnUpdate();
        void LoadSettings();
        void SetupFromSettings();
        void RegisterColors();

        void OnImGuiRender();

        // -- UI --
        void UI_DrawTopBar();
        void UI_DrawSettingsMenu();
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

        void UI_UTIL_DrawColorChanger(const char *label, int target);

        static EditorSettings *StaticGetEditorSettings();
    };
}