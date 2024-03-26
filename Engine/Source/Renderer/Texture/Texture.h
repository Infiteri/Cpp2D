#pragma once

#include "Base.h"
#include "Resources/Image.h"
#include <string>

namespace Core
{
    class CE_API Texture
    {
    public:
        enum LoadedMode
        {
            Default,
            File,
            Params
        };

        enum TextureFilter
        {
            Nearest,
            Linear,
        };

        struct Configuration
        {
            TextureFilter MinFilter;
            TextureFilter MaxFilter;

            Configuration();
        };

    private:
        CeU32 id;
        int index;
        LoadedMode loadMode;
        Image *image;

        Configuration config;

        void DestroyGLTexture();
        void DestroyImageIfPresentAndSetNullptr();
        void LoadTextureWithInformation(int width, int height, char channels, CeU8 *data, Texture::Configuration *config);

    public:
        Texture();
        Texture(const std::string &name);
        Texture(const std::string &name, Configuration *cfg);
        ~Texture();

        void Load();
        void Load(const std::string &name);
        void Load(const std::string &name, Configuration *config);
        void Load(int width, int height, char channels, CeU8 *data, Configuration *cfg);

        void UpdateWithConfig(Configuration *config);

        void Bind();
        void Unbind();
        void Use();

        void SetLoadMode(LoadedMode lm) { loadMode = lm; }
        inline LoadedMode GetLoadMode() { return loadMode; };

        inline Image *GetImage() { return image; };
        inline bool HasImage() { return image != nullptr; };
        std::string GetImagePath();

        inline CeU32 GetID() { return id; };
        inline int GetIndex() { return index; };
        inline Configuration *GetConfig() { return &config; };
    };

}