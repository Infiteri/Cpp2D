#pragma once

#include "Base.h"
#include "Material.h"

#define CE_DEFAULT_MATERIAL_NAME "CoreDefaultMaterialName"

namespace Core
{
    struct MaterialReference
    {
        Material *material;
        int reference;
    };

    class CE_API MaterialSystem
    {
    public:
        MaterialSystem(){};
        ~MaterialSystem(){};

        static void Init();
        static void Shutdown();

        static Material *Get(const std::string &name);
        static void Load(const std::string &name);

        static void Release(const std::string &name);
        static Material *GetDefaultMaterial();
    };
}