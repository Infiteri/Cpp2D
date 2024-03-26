#pragma once

#include "Core.h"
#include "Panels/SceneHierarchyPanel.h"
#include "EditorCamera.h"
#include <imgui.h>
#include <vector>

namespace Core
{
    struct EditorAssets
    {
        Texture *PlayButtonTexture;
        Texture *StopButtonTexture;
    };

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
        EditorAssets editorAssets;

        Scene *editorScene;

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
        void OnDetach();
        void OnUpdate();
        void LoadSettings();
        void SetupFromSettings();
        void RegisterColors();

        void OnImGuiRender();

        // -- SCENE RUNTIME --
        enum SceneState
        {
            SceneStateStop,
            SceneStatePlay,
        };
        SceneState sceneState;

        void StartSceneRuntime();
        void StopSceneRuntime();

        void UpdateRuntime();
        void UpdateEditor();
        // -------------------

        // -- UI --
        void UI_DrawTopBar();
        void UI_DrawPlayStopBar();
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
        static EditorAssets *StaticGetEditorAssets();
    };
}