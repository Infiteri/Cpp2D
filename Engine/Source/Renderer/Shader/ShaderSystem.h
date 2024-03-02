#pragma once

#include "Base.h"
#include "Shader.h"

namespace Core
{
    class CE_API ShaderSystem
    {
    public:
        ShaderSystem(){};
        ~ShaderSystem(){};

        static void Init();
        static void Init(std::initializer_list<std::string> preloadedFileNames);
        static void Shutdown();

        static Shader *Get(const std::string &filename);
        static Shader *Load(const std::string &filename);
        static bool Remove(const std::string &filename);
    };
}