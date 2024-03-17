#pragma once

#include "Base.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Material/MaterialSystem.h"

namespace Core
{
    class CE_API Mesh
    {
    private:
        class VertexArray *array;

        Material *material;
        Geometry *geometry;

        void ReleaseMaterial();
        void ReleaseGeometry();
        void SetupVertexArray();

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
        void SetMaterial(Material::Configuration *config);

        /// @brief Will set the geometry to the new one. Use "new GEOMETRY_TYPE(ARGS...)" for best results.
        /// @param _geometry An instance of the desired geometry 
        void SetGeometry(Geometry* _geometry);


        inline Material *GetMaterial() { return material; };
        inline Geometry *GetGeometry() { return geometry; };

        void MakeMaterialUnique();
        void MakeMaterialDefault();
    };
}