#include "SceneHierarchyPanel.h"
#include "EditorUtils.h"

namespace Core
{
    static ImGuiTreeNodeFlags TreeNodeFlags = 0;

    SceneHierarchyPanel::SceneHierarchyPanel()
    {
        selectionContext = nullptr;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        auto scene = World::GetActive();

        ImGui::Begin("Scene Hierarchy");

        if (scene)
        {
            for (auto actor : scene->GetActors())
                RenderActorUI(actor);
        }
        ImGui::End();

        ImGui::Begin("Proprieties");
        if (selectionContext)
            RenderActorProps(selectionContext);
        ImGui::End();
    }

    void SceneHierarchyPanel::RenderActorUI(Actor *a)
    {
        if (ImGui::TreeNodeEx((void *)a->GetUUID()->Get(), TreeNodeFlags, a->GetName().c_str()))
        {
            if (ImGui::IsItemClicked())
            {
                selectionContext = a;
            }

            ImGui::TreePop();
        }
    }

    void DrawMeshComponentUI(MeshComponent *component, Actor *a);

    void SceneHierarchyPanel::RenderActorProps(Actor *a)
    {
        {
            char Buffer[256];
            memset(Buffer, 0, 256);
            memccpy(Buffer, a->GetName().c_str(), a->GetName().size(), 256);
            if (ImGui::InputText("Name", Buffer, 256))
                a->SetName(Buffer);
        }

        {
            int meshIndex = -1;
            for (auto meshComponent : a->GetComponents<MeshComponent>())
            {
                meshIndex++;
                ImGui::NewLine();
                EditorUtils::DrawComponentBaseUI("Mesh Component", meshComponent, meshIndex, a, DrawMeshComponentUI);
            }
        }
    }

    void DrawMeshComponentUI(MeshComponent *component, Actor *a)
    {
        {
            auto material = component->mesh->GetMaterial();

            Material::LoadMode loadMode = material->GetLoadMode();
            switch (loadMode)
            {
            case Material::File:
                ImGui::Text("%s", material->GetFileName().c_str());
                break;

            case Material::Config:
            {
                char Buffer[256];
                memset(Buffer, 0, 256);
                memccpy(Buffer, material->GetName().c_str(), material->GetName().size(), 256);
                if (ImGui::InputText("Name", Buffer, 256))
                    material->SetName(Buffer);
            }

                EditorUtils::ImGuiColorEdit4(material->GetColor(), "Color");
                break;

            case Material::Default:
            default:
                break;
            }

            switch (loadMode)
            {
            case Material::Config:
                if (ImGui::Button("Make Default"))
                    component->mesh->MakeMaterialDefault();
                ImGui::SameLine();
                if (ImGui::Button("Load File"))
                {
                    std::string filename = Platform::OpenFileDialog("Material (*.ce_mat) \0*.ce_mat\0");
                    if (!filename.empty())
                        component->mesh->SetMaterial(filename);
                }

                break;

            case Material::File:
                if (ImGui::Button("Make Unique"))
                    component->mesh->MakeMaterialUnique();
                ImGui::SameLine();

                if (ImGui::Button("Make Default"))
                {
                    component->mesh->MakeMaterialDefault();
                }

                break;

            case Material::Default:
            default:
                if (ImGui::Button("Make Unique"))
                    component->mesh->MakeMaterialUnique();
                ImGui::SameLine();

                if (ImGui::Button("Load File"))
                {
                    std::string filename = Platform::OpenFileDialog("Material (*.ce_mat) \0*.ce_mat\0");
                    if (!filename.empty())
                        component->mesh->SetMaterial(filename);
                }
                break;
            }
        }

        {
        }
    }
}
