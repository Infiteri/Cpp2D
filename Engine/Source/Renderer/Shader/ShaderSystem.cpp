#include "ShaderSystem.h"
#include "Core/Logger.h"
#include <unordered_map>

namespace Core
{
    struct
    {
        std::unordered_map<std::string, Shader *> shaders;
    } state;

    void ShaderSystem::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Shader System", "CE_SHD_SYS");
    }

    void ShaderSystem::Init(std::initializer_list<std::string> preloadedFileNames)
    {
        Init();

        for (auto it : preloadedFileNames)
            Get(it);
    }

    void ShaderSystem::Shutdown()
    {
        for (auto it : state.shaders)
            delete it.second;

        state.shaders.clear();
    }

    Shader *ShaderSystem::Get(const std::string &filename)
    {
        if (!state.shaders[filename])
            return Load(filename);

        return state.shaders[filename];
    }

    Shader *ShaderSystem::Load(const std::string &filename)
    {
        if (state.shaders[filename])
        {
            CE_LOG("CE_SHD_SYS", Warn, "Shader '%s' exists", filename.c_str());
            return state.shaders[filename];
        }

        state.shaders[filename] = new Shader(filename + ".vs.glsl", filename + ".fs.glsl");
        return state.shaders[filename];
    }

    bool ShaderSystem::Remove(const std::string &filename)
    {
        if (!state.shaders[filename])
        {
            CE_LOG("CE_SHD_SYS", Warn, "Shader '%s' does not exists, not removed", filename.c_str());
            return false;
        }

        delete state.shaders[filename];
        state.shaders.erase(filename);

        return true;
    }
}