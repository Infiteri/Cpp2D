#include "SceneHierarchyPanel.h"
#include "EditorUtils.h"

namespace Core
{
    struct ActorMoveDragInfo
    {
        UUID ActorUUID;
    };

    static int actorIndex = -1;
    SceneHierarchyPanel::SceneHierarchyPanel()
    {
        selectionContext = nullptr;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        auto scene = World::GetActive();

        ImGui::Begin("Scene Hierarchy");

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            ImGui::OpenPopup("RightClickHierarchy");

        if (ImGui::BeginPopup("RightClickHierarchy"))
        {
            if (ImGui::MenuItem("Add Actor") && scene != nullptr)
                scene->AddActor(new Actor());

            ImGui::EndPopup();
        }

        if (scene)
        {
            actorIndex = 0;
            for (int i = 0; i < scene->GetActors().size(); i++)
            {
                actorIndex = i;
                Actor *ctx = scene->GetActors()[i];
                RenderActorUI(ctx, false);
            }
        }
        ImGui::End();

        ImGui::Begin("Proprieties");
        if (selectionContext)
            RenderActorProps(selectionContext);
        ImGui::End();
    }

    void SceneHierarchyPanel::RenderActorUI(Actor *a, bool parentNodeOpen)
    {
        if (!a)
            return;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_AllowItemOverlap;
        if (selectionContext != nullptr)
            if (selectionContext->GetUUID()->Get() == a->GetUUID()->Get())
                flags |= ImGuiTreeNodeFlags_Selected;

        bool pop = false;
        Actor *parent = a->GetParent();
        if (!parent)
        {
            pop = ImGui::TreeNodeEx((void *)(CeU64)(CeU32)a->GetUUID()->Get(), flags, a->GetName().c_str());
            if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
                selectionContext = a;
        }
        else
        {
            if (parentNodeOpen)
            {
                pop = ImGui::TreeNodeEx((void *)(CeU64)(CeU32)a->GetUUID()->Get(), flags, a->GetName().c_str());
                if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
                    selectionContext = a;
            }
        }

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            ActorMoveDragInfo actorDG;
            actorDG.ActorUUID = *a->GetUUID();
            ImGui::SetDragDropPayload("CE_SCENE_HIERARCHY_ACTOR", &actorDG, sizeof(ActorMoveDragInfo));
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CE_SCENE_HIERARCHY_ACTOR"))
            {
                UUID *uid = (UUID *)payload->Data;
                CE_CORE_TRACE("%s to %ull", a->GetName().c_str(), uid->Get());

                // NOTE: Actor is target, data is name of the actor to move
                Actor *child = World::GetActive()->FindActorByUUIDInHierarchy(uid->Get());

                if (child)
                {
                    //? Selection context will be set to nothing
                    selectionContext = nullptr;
                    bool success = World::GetActive()->ChildActor(*a->GetUUID(), *child->GetUUID());
                    if (!success)
                        CE_ERROR("Fuck");
                }
            }

            ImGui::EndDragDropTarget();
        }

        if (!parent)
        {
            ImGui::Dummy({ImGui::GetWindowWidth(), 5});
        }
        else
        {
            if (parentNodeOpen)
                ImGui::Dummy({ImGui::GetWindowWidth(), 5});
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CE_SCENE_HIERARCHY_ACTOR"))
            {
                ActorMoveDragInfo *data = (ActorMoveDragInfo *)payload->Data;
                auto actorDrop = World::GetActive()->FindActorByUUIDInHierarchy(data->ActorUUID);
                if (actorDrop)
                {
                    if (actorDrop->GetParent() == nullptr)
                    {
                        World::GetActive()->MoveActorInHierarchy(data->ActorUUID, actorIndex);
                    }
                    else
                    {
                        Actor *parent = actorDrop->GetParent();
                        parent->MoveActorInHierarchy(data->ActorUUID, actorIndex);
                    }
                }
            }

            ImGui::EndDragDropTarget();
        }

        for (Actor *child : a->GetChildren())
            RenderActorUI(child, pop);

        if (pop)
            ImGui::TreePop();
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
