#include "EditorUtils.h"

namespace Core
{
    void EditorUtils::ImGuiColorEdit4(Color *color, const std::string &name)
    {
        float data[4] = {color->R / 255, color->G / 255, color->B / 255, color->A / 255};
        if (ImGui::ColorEdit4(name.c_str(), data))
            color->Set(data, 255);
    }
}