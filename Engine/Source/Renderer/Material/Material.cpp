#include "Material.h"
#include "Renderer/Shader/ShaderSystem.h"
#include "Renderer/Texture/TextureSystem.h"

namespace Core
{

    Material::Material()
    {
        texture = TextureSystem::GetDefaultTexture();
    }

    Material::~Material()
    {
        ReleaseTexture();
    }

    void Material::Load(Configuration *config)
    {
        color.Set(config->Color);
        name = config->Name;
        filename = config->FileName;

        if (!config->TexturePath.empty())
        {
            ReleaseTexture();
            texture = TextureSystem::Get(config->TexturePath);
        }
    }

    void Material::Use()
    {
        auto shd = ShaderSystem::Get("EngineResources/Shaders/Object");
        if (!shd)
            return;

        shd->Use();
        texture->Use();
        shd->Int(texture->GetIndex(), "uTexture");
        shd->Vec4(color.Normalized(), "uColor");
    }

    void Material::SetTexture(const std::string &path, Texture::Configuration *cfg)
    {
        // TODO: Handle material references and instances
        ReleaseTexture();
        texture = TextureSystem::Get(path); // TODO: With configuration
    }

    void Material::ReleaseTexture()
    {
        if (texture != nullptr)
        {
            if (texture->GetLoadMode() != Texture::Default)
            {
                TextureSystem::Release(texture->GetImagePath());
            }
        }

        texture = nullptr;
    }
}