#include "Material.h"
#include "Renderer/Shader/ShaderSystem.h"

namespace Core
{
    Material::Material()
    {
    }

    Material::~Material()
    {
    }

    void Material::Load(Configuration *config)
    {
        color.Set(config->Color);
        name = config->Name;
        filename = config->FileName;
    }

    void Material::Use()
    {
        auto shd = ShaderSystem::Get("EngineResources/Shaders/Object");
        if (!shd)
            return;

        shd->Use();
        shd->Vec4(color.Normalized(), "uColor");
    }
}