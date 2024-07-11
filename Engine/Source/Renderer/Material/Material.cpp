#include "Material.h"
#include "Core/Logger.h"
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
        mode = Material::Config;
        color.Set(config->Color);
        name = config->Name;
        filename = config->FileName;

        if (!config->TexturePath.empty())
        {
            ReleaseTexture();
            texture = TextureSystem::Get(config->TexturePath);
            texture->UpdateWithConfig(&config->TextureConfiguration);
        }
        else // No specified texture path and no textures loaded earlier
        {
            if (!texture)
                texture = TextureSystem::GetDefaultTexture();
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