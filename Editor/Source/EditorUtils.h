#pragma once

#include "Core.h"
#include <imgui.h>
#include <string>

namespace Core
{
    namespace EditorUtils
    {
        void ImGuiVector3StyledEdit(const char *label, Vector3 *vector, float defaultValue = 0.0f);
        void TransformGUIRender(Transform *transform);

        template <typename T, typename UIFun>
        void DrawComponentBaseUI(const std::string &name, T *component, int index, Actor *a, UIFun fun)
        {
            const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_AllowItemOverlap;
            if (component)
            {

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
                bool open = ImGui::TreeNodeEx((void *)(typeid(T).hash_code() + index), flags, name.c_str());
                bool removeComp = false;

                ImGui::PopStyleVar();

                if (open)
                {
                    fun(component, a);
                    if (ImGui::Button("Remove"))
                    {
                        removeComp = true;
                    };
                    ImGui::TreePop();
                }

                if (removeComp)
                {
                    a->RemoveComponents<T>(index);
                }
            }
        };

        void ImGuiColorEdit4(Color *color, const std::string &name);
        void RenderTextureUI(Material *material);
        void RenderTextureUIChangeFilter(Texture *texture);
     void ImGuiVector2Edit(const char *name, Vector2 *v);

    };
}