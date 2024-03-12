#pragma once

#include "Base.h"
#include "Renderer/Object/Mesh.h"

namespace Core
{
    class Actor;
    /// @brief Represents every possible component type.
    enum class ComponentTypes
    {
        Base,
        Mesh
    };

    class CE_API Component
    {
    protected:
        ComponentTypes type;

    public:
        Component();
        ~Component();

        Actor *Owner;

        virtual void Start(){};
        virtual void Render(){};
        virtual void Update(){};
        virtual void Stop(){};
        virtual void Destroy(){};

        virtual void From(Component *other){};

        inline ComponentTypes GetType() { return type; };
    };

    class CE_API MeshComponent : public Component
    {
    public:
        Mesh *mesh;

        MeshComponent();
        void Render();

        void SetMaterial(const std::string &filename);
        void SetMaterial(Material::Configuration* config);

        void From(MeshComponent *other);
    };
}
