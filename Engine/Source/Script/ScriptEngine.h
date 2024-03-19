#pragma once

#include "Base.h"
#include "ActorScript.h"
#include "Platform/Platform.h"

#include <string>

namespace Core
{
    class CE_API ScriptEngine
    {
    public:
        ScriptEngine(){};
        ~ScriptEngine(){};

        static void Init();
        static void Shutdown();

        static void CreateLibrary(const std::string &name);
        static DynamicLibrary *GetLibrary();

        static void StartRuntime();
        static void UpdateRuntime();
        static void StopRuntime();

        static void ClearScriptSet();

        static void RegisterActorScript(ActorScript *script, Actor *owner, const std::string &name);
        static void RegisterActorScript(const std::string& className, Actor *owner, const std::string &name);
    };
}