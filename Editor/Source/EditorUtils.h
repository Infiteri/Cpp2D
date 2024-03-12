#pragma once

#include "Core.h"
#include <imgui.h>
#include <string>

namespace Core
{
    namespace EditorUtils
    {
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
                    a->RemoveComponents<T>(index);
            }
        };

        void ImGuiColorEdit4(Color *color, const std::string& name);
    };
}