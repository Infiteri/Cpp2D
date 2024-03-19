#pragma once

#include "Base.h"
#include "Renderer/Object/Mesh.h"
#include "Renderer/Object/Sprite.h"
#include "Renderer/Camera/CameraSystem.h"

namespace Core
{
    class Actor;
    /// @brief Represents every possible component type.
    enum class ComponentTypes
    {
        Base,
        Mesh,
        Camera
    };

    class CE_API Component
    {
    protected:
        ComponentTypes type;

    public:
        Component();
        virtual ~Component() { Destroy(); };

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
        ~MeshComponent();

        void Render();

        void SetMaterial(const std::string &filename);
        void SetMaterial(Material::Configuration *config);

        void From(MeshComponent *other);

        void Destroy();
    };

    class CE_API CameraComponent : public Component
    {
    public:
        OrthographicCamera *camera;

        CameraComponent();
        ~CameraComponent();

        inline float GetZoom() { return camera->GetZoom(); };
        inline void SetZoom(float z) { camera->SetZoom(z); };

        void Update();

        void From(CameraComponent *o);
        void Destroy();
    };

    class CE_API SpriteComponent : public Component
    {
    public:
        Sprite *sprite;

        SpriteComponent();
        ~SpriteComponent();

        void Render();
        void From(SpriteComponent *o);
        void Destroy();
    };

    class CE_API ActorScriptComponent : public Component
    {
    public:
        std::string ClassName;

        ActorScriptComponent();
        ~ActorScriptComponent();

        void From(ActorScriptComponent* o);
    };
}
