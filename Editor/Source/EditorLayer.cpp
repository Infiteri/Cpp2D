#include "EditorLayer.h"
#include <imgui.h>

namespace Core
{
    void EditorLayer::OnImGuiRender()
    {
        ImGui::Begin("Test Window");

        {
            auto color = Renderer::GetClearColor().Normalized();
            float data[4] = {color.R, color.G, color.B, 1};
            if (ImGui::ColorEdit4("Background Color", data))
                Renderer::SetClearColor(data[0] * 255, data[1] * 255, data[2] * 255);
        }

        if (ImGui::Button("Save"))
        {
            SceneSerializer(World::GetActive()).Serialize("EngineResources/Scenes/Main.ce_scene");
        }

        if (ImGui::Button("Load"))
        {
            World::StopActiveScene();
            World::GetActive()->ClearActorSet();
            World::StartActiveScene();

            SceneSerializer(World::GetActive()).Deserialize("EngineResources/Scenes/Main.ce_scene");
        }

        ImGui::End();
    }

    void EditorLayer::OnAttach()
    {
        World::Create("New Scene");
        World::Activate("New Scene");
        // auto testActor = testScene->AddActor();

        // testActor->SetName("Mesh actor");

        // auto mesh = testActor->AddComponent<MeshComponent>();
        // mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");

        // // Hope and pray this is loaded from the file .
        // auto mesh2 = testActor->AddComponent<MeshComponent>();
        // mesh2->SetMaterialFromName("Test Mat");

        SceneSerializer serializer(World::GetActive());
        serializer.Deserialize("EngineResources/Scenes/Main.ce_scene");

        World::StartActiveScene();
    }

    void EditorLayer::OnUpdate()
    {
    }
}