#include "World.h"
#include "Core/Logger.h"
#include "SceneSerializer.h"
#include <unordered_map>

#define CE_IMPL_FUNC_ACTIVE_METHOD(name) \
    if (!activeScene)                    \
        return;                          \
    activeScene->name()

namespace Core
{
    static std::unordered_map<std::string, Scene *> scenes;
    static Scene *activeScene;

    void World::Init()
    {
        CE_DEFINE_LOG_CATEGORY("World", "WORLD");
    }

    void World::Shutdown()
    {
        for (auto it : scenes)
        {
            delete it.second;
        }

        scenes.clear();

        if (activeScene != nullptr)
        {
            CE_LOG("WORLD", Warn, "Active Scene should not be alive.");
            activeScene = nullptr;
        }
    }

    void World::Load(const std::string &filename)
    {
        if (scenes[filename])
        {
            CE_LOG("WORLD", Warn, "Scene '%s' already exists when Loading.", filename.c_str());
            return;
        }

        Scene *scene = new Scene();
        SceneSerializer ser(scene);
        ser.Deserialize(filename);
    }

    Scene *World::Create(const std::string &name)
    {
        if (scenes[name])
        {
            CE_LOG("WORLD", Warn, "Scene '%s' exists. Cannot override it.", name.c_str());
            return scenes[name];
        }

        scenes[name] = new Scene();
        scenes[name]->SetName(name);
        return scenes[name];
    }

    Scene *World::GetActive()
    {
        return activeScene;
    }

    Scene *World::Get(const std::string &name)
    {
        return scenes[name];
    }

    void World::Activate(const std::string &name)
    {
        if (!scenes[name])
        {
            CE_LOG("WORLD", Warn, "Scene '%s' doesn't exist. Cannot be activated.", name.c_str());
            return;
        }

        activeScene = scenes[name];
    }

    void World::Remove(const std::string &name)
    {
        if (!scenes[name])
        {
            CE_LOG("WORLD", Warn, "Scene '%s' doesn't exist. Cannot be removed.", name.c_str());
            return;
        }

        delete scenes[name];
        scenes.erase(name);
    }

    void World::CopyToActive(Scene *scene)
    {
        if (activeScene)
        {
            delete activeScene;
        }

        activeScene = Scene::From(scene);
    }

    void World::StartActiveScene()
    {
        CE_IMPL_FUNC_ACTIVE_METHOD(Start);
    }

    void World::RenderActiveScene()
    {
        CE_IMPL_FUNC_ACTIVE_METHOD(Render);
    }

    void World::UpdateActiveScene()
    {
        CE_IMPL_FUNC_ACTIVE_METHOD(Update);
    }

    void World::StopActiveScene()
    {
        CE_IMPL_FUNC_ACTIVE_METHOD(Stop);
    }

    void World::DeactivateActiveScene()
    {
        activeScene = nullptr;
    }
}