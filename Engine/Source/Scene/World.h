#pragma once

#include "Base.h"
#include "Scene.h"
#include <string>

namespace Core
{
    class CE_API World
    {
    public:
        World(){};
        ~World(){};

        static void Init();
        static void Shutdown();

        static Scene *Create(const std::string &name);
        static Scene *GetActive();
        static Scene *Get(const std::string &name);
        static void Activate(const std::string &name);
        static void DeactivateActiveScene();
        static void Remove(const std::string &name);

        static void StartActiveScene();
        static void RenderActiveScene();
        static void UpdateActiveScene();
        static void StopActiveScene();
    };
}