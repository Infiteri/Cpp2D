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

        ImGui::End();
    }
}
