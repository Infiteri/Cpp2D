#include "ScriptEngine.h"
#include "Core/Logger.h"

#include <unordered_map>

namespace Core
{
    typedef ActorScript *(*GetActorScriptPFN)();

    static std::unordered_map<std::string, ActorScript *> scripts;
    static DynamicLibrary library;

    void ScriptEngine::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Script Engine", "CE_SCRIPT");
    }

    void ScriptEngine::Shutdown()
    {
        ClearScriptSet();
    }

    void ScriptEngine::CreateLibrary(const std::string &name)
    {
        Platform::CreateLibrary(name, &library);
    }

    DynamicLibrary *ScriptEngine::GetLibrary()
    {
        return &library;
    }

    void ScriptEngine::UnloadLibrary()
    {
        Platform::DestroyLibrary(&library);
    }

    void ScriptEngine::StartRuntime()
    {
        for (auto it : scripts)
            it.second->OnStart();
    }

    void ScriptEngine::UpdateRuntime()
    {
        for (auto it : scripts)
            it.second->OnUpdate();
    }

    void ScriptEngine::StopRuntime()
    {
        for (auto it : scripts)
            it.second->OnDestroy();

        ClearScriptSet();
    }

    void ScriptEngine::ClearScriptSet()
    {
        for (auto it : scripts)
            delete it.second;
        scripts.clear();
    }

    void ScriptEngine::RegisterActorScript(ActorScript *script, Actor *owner, const std::string &name)
    {
        script->Owner = owner;
        scripts[name] = script;

        CE_LOG("CE_SCRIPT", Trace, "Adding script: %s", name.c_str());
    }

    void ScriptEngine::RegisterActorScript(const std::string &className, Actor *owner, const std::string &name)
    {
        if (!library.Valid)
        {
            CE_LOG("CE_SCRIPT", Error, "Library invalid.");
            return;
        }

        auto pfn = Platform::LibraryGetFunction<GetActorScriptPFN>(&library, className + "Create");
        if (pfn)
            RegisterActorScript(pfn(), owner, name);
        else
            CE_LOG("CE_SCRIPT", Error, "Library invalid, unable to get function pointer.");
    }
}