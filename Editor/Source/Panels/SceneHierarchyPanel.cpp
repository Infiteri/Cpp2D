#include "SceneHierarchyPanel.h"
#include "EditorUtils.h"

#define CE_UTIL_ADD_COMPONENT(name, type) \
    if (ImGui::MenuItem(name))            \
    a->AddComponent<type>()

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

        if (selectionContext && Input::GetKeyJustNow(Keys::Delete))
        {
            World::GetActive()->RemoveActorByUUID(*selectionContext->GetUUID());
            selectionContext = nullptr;
        }

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
    void DrawCameraComponentUI(CameraComponent *component, Actor *a);

    void SceneHierarchyPanel::RenderActorProps(Actor *a)
    {
        if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Right))
            ImGui::OpenPopup("RightClickProps");

        if (ImGui::BeginPopup("RightClickProps"))
        {
            CE_UTIL_ADD_COMPONENT("Mesh Component", MeshComponent);
            CE_UTIL_ADD_COMPONENT("Camera Component", CameraComponent);

            ImGui::EndPopup();
        }

        {
            char Buffer[256];
            memset(Buffer, 0, 256);
            memccpy(Buffer, a->GetName().c_str(), a->GetName().size(), 256);
            if (ImGui::InputText("Name", Buffer, 256))
                a->SetName(Buffer);
        }

        ImGui::NewLine();

        if (ImGui::TreeNode("Transform"))
        {
            EditorUtils::TransformGUIRender(a->GetTransform());
            ImGui::TreePop();
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

        {
            int cameraIndex = -1;
            for (auto cameraComponent : a->GetComponents<CameraComponent>())
            {
                cameraIndex++;
                ImGui::NewLine();
                EditorUtils::DrawComponentBaseUI("Camera Component", cameraComponent, cameraIndex, a, DrawCameraComponentUI);
            }
        }
    }

    void DrawMeshComponentUI(MeshComponent *component, Actor *a)
    {
        if (ImGui::TreeNodeEx("Material"))
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
                {
                    char Buffer[256];
                    memset(Buffer, 0, 256);
                    memccpy(Buffer, material->GetName().c_str(), material->GetName().size(), 256);
                    if (ImGui::InputText("Name", Buffer, 256))
                        material->SetName(Buffer);
                }

                EditorUtils::ImGuiColorEdit4(material->GetColor(), "Color");

                if (ImGui::TreeNodeEx("Texture"))
                {
                    Texture *texture = material->GetTexture();
                    if (!texture->GetImagePath().empty())
                    {
                        ImGui::Image((void *)(CeU64)(CeU32)texture->GetID(), {100, 100});
                    }

                    if (ImGui::Button("Load Image"))
                    {
                        std::string filename = Platform::OpenFileDialog("Image (*.png *.jpg *.jpeg)\0*.png;*.jpg;*.jpeg\0");
                        if (!filename.empty())
                            component->mesh->GetMaterial()->SetTexture(filename);
                    }

                    ImGui::TreePop();
                }
            }
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

            ImGui::TreePop();
        }

        // WIP: Geometry
        if (ImGui::TreeNodeEx("Geometry"))
        {
            auto geometry = component->mesh->GetGeometry();

            // NOTE: selection box
            {
                const int Count = 2;
                const char *GeometryTypes[Count] = {"Empty", "Square"};
                const char *Current = GeometryTypes[(int)geometry->GetType()];
                if (ImGui::BeginCombo("Level", Current))
                {
                    for (int i = 0; i < Count; i++)
                    {
                        bool isSelected = (Current == GeometryTypes[i]);
                        if (ImGui::Selectable(GeometryTypes[i], isSelected))
                        {
                            Current = GeometryTypes[i];

                            if (i == Geometry::Empty)
                                component->mesh->SetGeometry(new Geometry());
                            else if (i == Geometry::Square)
                                component->mesh->SetGeometry(new SquareGeometry(100, 100));
                        }

                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }
            }

            switch (geometry->GetType())
            {
            case Geometry::Square:
            {
                SquareGeometry *castGeometry = geometry->As<SquareGeometry>();
                float data[2] = {castGeometry->Width, castGeometry->Height};
                if (ImGui::DragFloat2("Size", data, 0.05f))
                    component->mesh->SetGeometry(new SquareGeometry(data[0], data[1]));
            }
            break;
            }

            ImGui::TreePop();
        }
    }

    void DrawCameraComponentUI(CameraComponent *component, Actor *a)
    {
        auto c = component->camera;

        float zoomEdit = c->GetZoom();
        if (ImGui::DragFloat("Zoom", &zoomEdit, 0.01f, 0.05f))
            c->SetZoom(zoomEdit);
    }
}
