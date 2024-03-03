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

        /// @brief Will load a material form file.
        /// @param filename The filename.
        void SetMaterialFromFile(const std::string& filename);

        inline Material *GetMaterial() { return material; };
    };
}