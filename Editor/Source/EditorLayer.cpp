#include "EditorLayer.h"
#include "EditorSettingsSerializer.h"

#define CE_DEFINE_COLOR_EDITABLE(name, color) state.editorSettings.editableColors.push_back({name, color});

namespace Core
{
    static EditorLayer *inst;

    void EditorLayer::OnAttach()
    {
        inst = this;

        state.editorAssets.PlayButtonTexture = new Texture("EngineResources/Images/Icons/PlayButton.png");
        state.editorAssets.StopButtonTexture = new Texture("EngineResources/Images/Icons/StopButton.png");
        state.editorScene = nullptr;

        LoadSettings();
        SetupFromSettings();
        RegisterColors();

        World::Create("New Scene");
        World::Activate("New Scene");
        SceneSerializer serializer(World::GetActive());
        serializer.Deserialize("EngineResources/Scenes/Main.ce_scene");
        state.sceneSaveFilePath = "EngineResources/Scenes/Main.ce_scene";

        sceneState = SceneStatePlay;
        StopSceneRuntime();
    }

    void EditorLayer::OnUpdate()
    {
        switch (sceneState)
        {
        case SceneStateStop:
            UpdateEditor();
            break;

        case SceneStatePlay:
            UpdateRuntime();
            break;
        }
    }

    void EditorLayer::LoadSettings()
    {
        EditorSettingsSerializer ser(&state.editorSettings);
        ser.Deserialize("EditorSettings.ce_ed_set");
    }

    void EditorLayer::SetupFromSettings()
    {
        state.editorCamera.SetupFromSetings(&state.editorSettings);
    }

    void EditorLayer::RegisterColors()
    {
        CE_DEFINE_COLOR_EDITABLE("Background", ImGuiCol_WindowBg);
        CE_DEFINE_COLOR_EDITABLE("Header", ImGuiCol_Header);
        CE_DEFINE_COLOR_EDITABLE("HeaderHovered", ImGuiCol_HeaderHovered);
        CE_DEFINE_COLOR_EDITABLE("HeaderActive", ImGuiCol_HeaderActive);
        CE_DEFINE_COLOR_EDITABLE("Button", ImGuiCol_Button);
        CE_DEFINE_COLOR_EDITABLE("ButtonHovered", ImGuiCol_ButtonHovered);
        CE_DEFINE_COLOR_EDITABLE("ButtonActive", ImGuiCol_ButtonActive);
        CE_DEFINE_COLOR_EDITABLE("FrameBg", ImGuiCol_FrameBg);
        CE_DEFINE_COLOR_EDITABLE("FrameBgHovered", ImGuiCol_FrameBgHovered);
        CE_DEFINE_COLOR_EDITABLE("FrameBgActive", ImGuiCol_FrameBgActive);
        CE_DEFINE_COLOR_EDITABLE("Tab", ImGuiCol_Tab);
        CE_DEFINE_COLOR_EDITABLE("TabHovered", ImGuiCol_TabHovered);
        CE_DEFINE_COLOR_EDITABLE("TabActive", ImGuiCol_TabActive);
        CE_DEFINE_COLOR_EDITABLE("TabUnfocused", ImGuiCol_TabUnfocused);
        CE_DEFINE_COLOR_EDITABLE("TabUnfocusedActive", ImGuiCol_TabUnfocusedActive);
        CE_DEFINE_COLOR_EDITABLE("TitleBg", ImGuiCol_TitleBg);
        CE_DEFINE_COLOR_EDITABLE("TitleBgActive", ImGuiCol_TitleBgActive);
        CE_DEFINE_COLOR_EDITABLE("TitleBgCollapsed", ImGuiCol_TitleBgCollapsed);
    }

    void EditorLayer::OnImGuiRender()
    {
        if (state.canUpdateCamera)
            state.editorCamera.Update(); // TODO: change
        state.editorCamera.UpdateExitRightButton();

        BeginDockspace();

        state.hierarchyPanel.OnImGuiRender();

        UI_DrawTopBar();
        UI_DrawSettingsMenu();
        UI_DrawPlayStopBar();

        RenderSceneViewport();
        EndDockspace();
    }

    void EditorLayer::StartSceneRuntime()
    {
        if (sceneState != SceneStateStop)
            return;

        state.editorScene = Scene::From(World::GetActive());
        World::StartActiveScene();
        ResizeViewport();

        sceneState = SceneStatePlay;
    }

    void EditorLayer::StopSceneRuntime()
    {
        if (sceneState != SceneStatePlay)
            return;

        World::StopActiveScene();

        if (state.editorScene != nullptr)
        {
            World::CopyToActive(state.editorScene);

            delete state.editorScene;
        }

        state.editorCamera.Activate();

        sceneState = SceneStateStop;
    }

    void EditorLayer::UpdateRuntime()
    {
        World::UpdateActiveScene();
    }

    void EditorLayer::UpdateEditor()
    {
    }

    void EditorLayer::UI_DrawTopBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("Scene"))
                ImGui::OpenPopup("ScenePopup");

            if (ImGui::MenuItem("Editor"))
                ImGui::OpenPopup("EditorPopup");

            if (ImGui::BeginPopup("ScenePopup"))
            {
                if (ImGui::MenuItem("Save..."))
                    Save();

                if (ImGui::MenuItem("Open..."))
                    Open();

                if (ImGui::MenuItem("Save As..."))
                    SaveAs();

                ImGui::EndPopup();
            }

            if (ImGui::BeginPopup("EditorPopup"))
            {
                if (ImGui::MenuItem("Settings..."))
                    state.settingsMenu.Render = true;

                ImGui::EndPopup();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EditorLayer::UI_DrawPlayStopBar()
    {
        ImGui::Begin("PlayTopBar", NULL, ImGuiWindowFlags_NoScrollbar);

        Texture *texture = sceneState == SceneStateStop ? state.editorAssets.PlayButtonTexture : state.editorAssets.StopButtonTexture;

        if (ImGui::ImageButton((void *)(CeU64)(CeU32)texture->GetID(), {10, 10}))
        {
            if (sceneState == SceneStateStop)
                StartSceneRuntime();
            else
                StopSceneRuntime();
        }

        ImGui::End();
    }

    void EditorLayer::UI_DrawSettingsMenu()
    {
        if (!state.settingsMenu.Render)
            return;

        float margin = 50.0f;

        ImGui::SetNextWindowPos({margin, margin});
        ImGui::SetNextWindowSize({Engine::GetWindow()->GetWidth() - (margin + 5), Engine::GetWindow()->GetHeight() - (margin + 5)});

        ImGui::Begin("Editor Settings Menu");

        ImGui::DragFloat("Camera Zoom", &state.editorSettings.CameraZoom, 0.05f, 0.1f, 100.0f);

        ImGui::SeparatorText("Colors");

        for (auto it : state.editorSettings.editableColors)
            UI_UTIL_DrawColorChanger(it.Name.c_str(), it.Color);

        if (ImGui::Button("Reset"))
        {
            ImGuiLayer::SetColorsToDefaultStyle();
        }

        // Create an empty space to push the button to the bottom-right
        ImGui::Dummy(ImVec2(0, 0));

        // Calculate the button size
        ImVec2 buttonSize = ImVec2(80, ImGui::GetFrameHeightWithSpacing());

        // Calculate the position to align the button to the bottom-right
        ImVec2 buttonPos = ImVec2(ImGui::GetWindowSize().x - buttonSize.x - ImGui::GetStyle().FramePadding.x * 2,
                                  ImGui::GetWindowSize().y - buttonSize.y - ImGui::GetStyle().FramePadding.y * 2);

        ImGui::SetCursorPos(buttonPos);

        if (ImGui::Button("Ok", buttonSize))
        {
            EditorSettingsSerializer ser(&state.editorSettings);
            ser.Serialize("EditorSettings.ce_ed_set");
            state.settingsMenu.Render = false;
            LoadSettings();
            SetupFromSettings();
        }

        ImGui::End();
    }

    void EditorLayer::ResizeViewport()
    {
        Renderer::Viewport(state.lastFrameViewportSize.x, state.lastFrameViewportSize.y);
    }

    void EditorLayer::Save()
    {
        if (state.sceneSaveFilePath.empty())
            SaveAs();

        SceneSerializer serializer(World::GetActive());
        serializer.Serialize(state.sceneSaveFilePath);
    }

    void EditorLayer::SaveAs()
    {
        state.sceneSaveFilePath = Platform::SaveFileDialog("Scene (*.ce_scene) \0*.ce_scene\0");

        if (!state.sceneSaveFilePath.empty())
            Save();
    }

    void EditorLayer::Open()
    {
        state.sceneSaveFilePath = Platform::OpenFileDialog("Scene (*.ce_scene) \0*.ce_scene\0");
        OpenScene(state.sceneSaveFilePath);
    }

    void EditorLayer::OpenScene(const std::string &name)
    {
        if (name.empty())
            return;

        if (!World::Get(name))
            World::Load(name);
        World::Activate(name);
    }

    void EditorLayer::BeginDockspace()
    {
        if (state.opt_fullscreen)
        {
            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            state.window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            state.window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (state.dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            state.window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &state.dockspaceOpen, state.window_flags);
        ImGui::PopStyleVar();

        if (state.opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 250.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), state.dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::PopStyleVar();
    }

    void EditorLayer::RenderSceneViewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();

        // Update renderer viewport
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        // End update renderer viewport
        if (viewportSize.x != state.lastFrameViewportSize.x || viewportSize.y != state.lastFrameViewportSize.y)
        {
            state.lastFrameViewportSize = viewportSize;
            ResizeViewport();
        }

        state.viewportLeftTop = ImGui::GetWindowPos();
        state.viewportRightBottom = ImGui::GetWindowSize();

        ImGui::Image((void *)(CeU64)(CeU32)(Renderer::GetFrameBuffer()->GetRenderPass(0)->Id), viewportSize, ImVec2{0, 1}, ImVec2{1, 0});

        {
            if (!state.editorCamera.isRightClicking)
            {
                Vector2 position = Input::GetMousePosition();
                if (position.x > state.viewportLeftTop.x &&
                    position.y > state.viewportLeftTop.y &&
                    position.x < state.viewportRightBottom.x + state.viewportLeftTop.x &&
                    position.y < state.viewportRightBottom.y + state.viewportLeftTop.y)
                    state.canUpdateCamera = true;
                else
                    state.canUpdateCamera = false;
            }
        }

        ImGui::End();
    }

    void EditorLayer::EndDockspace()
    {
        ImGui::End();
    }

    void EditorLayer::UI_UTIL_DrawColorChanger(const char *label, int target)
    {
        auto &colors = ImGui::GetStyle().Colors;

        float data[4] = {colors[target].x, colors[target].y, colors[target].z, colors[target].w};
        if (ImGui::ColorEdit4(label, data))
        {
            colors[target].x = data[0];
            colors[target].y = data[1];
            colors[target].z = data[2];
            colors[target].w = data[3];
        }
    }

    EditorSettings *EditorLayer::StaticGetEditorSettings()
    {
        if (!inst)
            return nullptr;

        return &inst->state.editorSettings;
    }

    EditorAssets *EditorLayer::StaticGetEditorAssets()
    {
        if (!inst)
            return nullptr;

        return &inst->state.editorAssets;
    }
}
