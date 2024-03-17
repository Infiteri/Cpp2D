#pragma once

#include "Core.h"
#include "EditorLayer.h"

#include <yaml-cpp/yaml.h>
#include <string>

namespace Core
{
    class EditorSettingsSerializer
    {
    public:
        EditorSettings *settings;

        EditorSettingsSerializer(EditorSettings *s);
        ~EditorSettingsSerializer();

        void Serialize(const std::string &name);
        void Deserialize(const std::string &name);
    };

}
