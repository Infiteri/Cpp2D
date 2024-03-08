#include "Texture.h"
#include "TextureSystem.h"
#include <glad/glad.h>

namespace Core
{
    void Texture::LoadTextureWithInformation(int width, int height, char channels, CeU8 *data, Texture::Configuration *config)
    {
        if (config)
        {
        }

        glGenTextures(1, &id);
        Bind();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // TODO: Configuration loaded type stuff
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // TODO: Configuration loaded type stuff

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    };

    Texture::Texture()
    {
        id = 0;
        index = TextureSystem::GetNewIndex();
        image = nullptr;

        Load();
    }

    Texture::Texture(const std::string &name)
    {
        id = 0;
        index = TextureSystem::GetNewIndex();
        image = nullptr;

        Load(name);
    }

    Texture::Texture(const std::string &name, Configuration *cfg)
    {
        id = 0;
        index = TextureSystem::GetNewIndex();
        image = nullptr;

        Load(name, cfg);
    }

    Texture::~Texture()
    {
        DestroyGLTexture();

        if (HasImage())
            delete image;

        image = nullptr;
        index = -1;
        TextureSystem::EraseIndex();
    }

    void Texture::Load()
    {
        if (id != 0)
            DestroyGLTexture();

        CeU8 data[4] = {255, 255, 255, 255};
        LoadTextureWithInformation(1, 1, 4, data, nullptr);
    }

    void Texture::Load(const std::string &name)
    {
        if (id != 0)
            DestroyGLTexture();

        DestroyImageIfPresentAndSetNullptr();
        image = new Image(name);
        LoadTextureWithInformation(image->GetWidth(), image->GetHeight(), image->GetChannels(), image->GetData(), nullptr);
        image->FreeData();
    }

    void Texture::Load(const std::string &name, Configuration *config)
    {
        if (id != 0)
            DestroyGLTexture();

        DestroyImageIfPresentAndSetNullptr();
        image = new Image(name);
        LoadTextureWithInformation(image->GetWidth(), image->GetHeight(), image->GetChannels(), image->GetData(), nullptr);
        image->FreeData();
    }

    void Texture::Load(int width, int height, char channels, CeU8 *data, Configuration *cfg)
    {
        if (id != 0)
            DestroyGLTexture();

        LoadTextureWithInformation(width, height, channels, data, cfg);
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0 + index); // TODO
        Bind();
    }

    void Texture::DestroyGLTexture()
    {
        glDeleteTextures(1, &id);
        id = 0;
    }

    void Texture::DestroyImageIfPresentAndSetNullptr()
    {
        if (HasImage())
            delete image;

        image = nullptr;
    }
}