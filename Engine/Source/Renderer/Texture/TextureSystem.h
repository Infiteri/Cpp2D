#pragma once

#include "Base.h"
#include "Texture.h"

namespace Core
{
    struct TextureReference
    {
        Texture *texture;
        int reference;
    };

    class CE_API TextureSystem
    {
    public:
        TextureSystem(){};
        ~TextureSystem(){};

        static void Init();
        static void Shutdown();

        static Texture *Get(const std::string &name);
        static Texture *Load(const std::string &name, Texture::Configuration *cfg = nullptr);
        static void Release(const std::string &name);

        static Texture *GetDefaultTexture();

        static int GetNewIndex();
        static void EraseIndex();
        static void SetIndexToZero();
    };

}