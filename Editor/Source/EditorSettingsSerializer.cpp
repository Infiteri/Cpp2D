#include "EditorSettingsSerializer.h"
#include <fstream>

#define CE_SERIALIZE_FIELD(name, value) out << YAML::Key << name << YAML::Value << value

namespace Core
{
    static YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->R << color->G << color->B << color->A << YAML::EndSeq;
        return out;
    }

    EditorSettingsSerializer::EditorSettingsSerializer(EditorSettings *s)
    {
        settings = s;
    }

    EditorSettingsSerializer::~EditorSettingsSerializer()
    {
    }

    void EditorSettingsSerializer::Serialize(const std::string &name)
    {
        if (name.empty() || !settings)
            return;

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Settings";
        out << YAML::Value << "Field";

        CE_SERIALIZE_FIELD("CameraZoom", settings->CameraZoom);

        out << YAML::Key << "Colors";
        out << YAML::Value << YAML::BeginSeq;

        for (auto it : settings->editableColors)
        {
            auto &colors = ImGui::GetStyle().Colors;
            Color color{colors[it.Color].x, colors[it.Color].y, colors[it.Color].z, colors[it.Color].w};

            out << YAML::BeginMap;
            out << YAML::Key << "Name" << YAML::Value << it.Name.c_str();
            out << YAML::Key << "Color" << YAML::Value << (int)it.Color;
            CE_SERIALIZE_FIELD("Color Value", &color);
            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(name);
        fout << out.c_str();
    }

    void EditorSettingsSerializer::Deserialize(const std::string &name)
    {
        if (name.empty() || !settings)
            return;

        std::ifstream stream(name);
        std::stringstream strStream(name);

        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());

        if (!data["Settings"])
            return;

        settings->CameraZoom = data["CameraZoom"].as<float>();

        auto colors = data["Colors"];
        if (colors)
        {
            for (auto c : colors)
            {
                auto &imColors = ImGui::GetStyle().Colors;
                int valid = c["Color"].as<int>();
                imColors[(ImGuiCol)c["Color"].as<int>()].x = c["Color Value"][0].as<float>();
                imColors[(ImGuiCol)c["Color"].as<int>()].y = c["Color Value"][1].as<float>();
                imColors[(ImGuiCol)c["Color"].as<int>()].z = c["Color Value"][2].as<float>();
                imColors[(ImGuiCol)c["Color"].as<int>()].w = c["Color Value"][3].as<float>();
            }
        }
    }
}
