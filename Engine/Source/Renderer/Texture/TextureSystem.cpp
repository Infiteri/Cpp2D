#include "TextureSystem.h"
#include "Core/Logger.h"
#include <unordered_map>

namespace Core
{
    struct
    {
        TextureReference defaultTexture;
        std::unordered_map<std::string, TextureReference *> references;
        int globalTextureIndex;
    } state;

    void TextureSystem::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Texture System", "CE_TEX_SYS");

        state.defaultTexture.texture = new Texture();
        state.defaultTexture.texture->SetLoadMode(Texture::Default);
        state.globalTextureIndex = -1;
    }

    void TextureSystem::Shutdown()
    {
        delete state.defaultTexture.texture;
        state.defaultTexture.texture = nullptr;
    }

    Texture *TextureSystem::Get(const std::string &name)
    {
        if (!state.references[name])
            Load(name);

        state.references[name]->reference++;
        return state.references[name]->texture;
    }

    Texture *TextureSystem::Load(const std::string &name, Texture::Configuration *cfg)
    {
        if (state.references[name])
            return state.references[name]->texture;

        state.references[name] = new TextureReference;
        state.references[name]->texture = new Texture(name, cfg);
        state.references[name]->reference = 0;
        state.references[name]->texture->SetLoadMode(Texture::File);

        return state.references[name]->texture;
    }

    void TextureSystem::Release(const std::string &name)
    {
        if (!state.references[name])
        {
            CE_LOG("CE_TEX_SYS", Warn, "Cannot release '%s', not found", name.c_str());
            return;
        }

        state.references[name]->reference--;

        if (state.references[name]->reference <= 0)
        {
            CE_LOG("CE_TEX_SYS", Trace, "Releasing '%s', not found", name.c_str());
            delete state.references[name]->texture;
            state.references.erase(name);
        }
    }

    Texture *TextureSystem::GetDefaultTexture()
    {
        return state.defaultTexture.texture;
    }

    int TextureSystem::GetNewIndex()
    {
        state.globalTextureIndex++;
        return state.globalTextureIndex;
    }

    void TextureSystem::EraseIndex()
    {
        state.globalTextureIndex--;
    }

    void TextureSystem::SetIndexToZero()
    {
        state.globalTextureIndex = 0;
    }
}