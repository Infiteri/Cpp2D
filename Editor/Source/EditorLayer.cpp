#include "EditorLayer.h"

namespace Core
{
    void EditorLayer::OnAttach()
    {
        std::vector<UUID> uuids;
        uuids.push_back({});
        uuids.push_back({});
        uuids.push_back({});
        uuids.push_back({});
        uuids.push_back({});
        for (size_t i = 0; i < uuids.size(); ++i)
        {
            for (size_t j = i + 1; j < uuids.size(); ++j)
            {
                if (uuids[i] == uuids[j])
                {
                    CE_TRACE("Opa: %i %i", i, j);
                }
            }
        }

        World::Create("New Scene");
        World::Activate("New Scene");
        SceneSerializer serializer(World::GetActive());
        serializer.Deserialize("EngineResources/Scenes/Main.ce_scene");
        state.sceneSaveFilePath = "EngineResources/Scenes/Main.ce_scene";

        World::StartActiveScene();
    }

    void EditorLayer::OnImGuiRender()
    {
        BeginDockspace();

        state.hierarchyPanel.OnImGuiRender();

        UI_DrawTopBar();

        RenderSceneViewport();
        EndDockspace();
    }

    void EditorLayer::UI_DrawTopBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("Scene"))
                ImGui::OpenPopup("ScenePopup");

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

            ImGui::EndMainMenuBar();
        }
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
        ImGui::Image((void *)(CeU64)(CeU32)(Renderer::GetFrameBuffer()->GetRenderPass(0)->Id), viewportSize, ImVec2{0, 1}, ImVec2{1, 0});
        if (viewportSize.x != state.lastFrameViewportSize.x || viewportSize.y != state.lastFrameViewportSize.y)
        {
            state.lastFrameViewportSize = viewportSize;
            ResizeViewport();
        }

        state.viewportLeftTop = ImGui::GetWindowPos();
        state.viewportRightBottom = ImGui::GetWindowSize();

        ImGui::End();
    }

    void EditorLayer::EndDockspace()
    {
        ImGui::End();
    }

    void EditorLayer::OnUpdate()
    {
    }
}
