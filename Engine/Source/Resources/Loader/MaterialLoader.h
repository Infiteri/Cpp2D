#pragma once

#include "Base.h"
#include "Renderer/Material/Material.h"
#include <string>

namespace Core
{
    class CE_API MaterialLoader
    {
    public:
        MaterialLoader(){};
        ~MaterialLoader(){};

        static void ExposeToFile(const std::string &name, Material::Configuration *c);
        static Material::Configuration GetFromFile(const std::string &name);
    };
}