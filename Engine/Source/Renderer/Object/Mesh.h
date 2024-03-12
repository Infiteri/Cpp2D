#pragma once

#include "Base.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/MaterialSystem.h"

namespace Core
{
    class CE_API Mesh
    {
    private:
        class VertexArray *array;
        Material *material;

        void ReleaseMaterial();

    public:
        Mesh();
        ~Mesh();

        void Render();

        /// @brief Will load a material under this name and release old one.
        /// Make sure that there is a material registered or created with this name in the material manager.
        /// @param materialName The material name.
        void SetMaterial(const std::string &materialName);

        /// @brief Will set material to the config, along side releasing the last.
        /// @param config The configuration.
        void SetMaterial(Material::Configuration* config);


        inline Material *GetMaterial() { return material; };

        void MakeMaterialUnique();
        void MakeMaterialDefault();
    };
}