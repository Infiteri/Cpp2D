#pragma once

#include "Base.h"
#include "Scene.h"

#include <string>

namespace YAML
{
    class Emitter;
}

namespace Core
{
    class CE_API SceneSerializer
    {
    public:
        /// @brief The scene to serialize, can be overwritten as its public.
        Scene *scene;

        SceneSerializer(Scene *targetScene);
        ~SceneSerializer();

        void SerializeActor(Actor* a, YAML::Emitter& out);

        void Serialize(const std::string &filename);
        void Deserialize(const std::string &filename);
    };
}