#pragma once

#include "Base.h"
#include "Math/Vectors.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/MaterialSystem.h"

namespace Core
{
    class CE_API Sprite
    {
    private:
        class VertexArray *array;
        Material *material;
        Vector2 size;

        Vector2 frameLayout;
        float currentFrame;

        void ReleaseMaterial();
        void SetupVertexArray();

        void SetupVertexArrayWithData(void *vertices, CeU32 vertexSize, CeU32 *indices, CeU32 indexSize);

    public:
        Sprite(const Vector2 &sizes = {100, 100});
        ~Sprite();

        void Render();

        /// @brief Will load a material under this name and release old one.
        /// Make sure that there is a material registered or created with this name in the material manager.
        /// @param materialName The material name.
        void SetMaterial(const std::string &materialName);

        /// @brief Will set material to the config, along side releasing the last.
        /// @param config The configuration.
        void SetMaterial(Material::Configuration *config);

        inline Material *GetMaterial() { return material; };

        void SetSize(const Vector2 &sizes);
        inline Vector2 GetSize() { return size; };

        void SetCurrentFrame(float frames);
        inline float GetCurrentFrame() { return currentFrame; };

        void SetFrameLayout(const Vector2 &frames);
        inline Vector2 GetFrameLayout() { return frameLayout; };

        void MakeMaterialUnique();
        void MakeMaterialDefault();
    };
}