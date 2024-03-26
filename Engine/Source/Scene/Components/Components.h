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
        Camera,
        Sprite,
        ActorScript,
        RigidBody2D,
        BoxCollider2D
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

        void From(ActorScriptComponent *o);
    };

    class CE_API RigidBody2DComponent : public Component
    {
    public:
        enum class BodyType
        {
            Static,
            Kinematic,
            Rigid,
        };

        BodyType Type = BodyType::Static;
        bool FixedRotation = false;

        void *RuntimeBody = nullptr;

        RigidBody2DComponent();
        ~RigidBody2DComponent();

        void From(RigidBody2DComponent *comp);

        void Destroy();
    };

    class CE_API BoxCollider2DComponent : public Component
    {
    public:
        Vector2 Offset;
        Vector2 Size;

        // TODO: move to physics material

        float Density = 1.0f;
        float Friction = 1.0f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.5f;

        void *RuntimeBody = nullptr;

        BoxCollider2DComponent();
        ~BoxCollider2DComponent();

        void From(BoxCollider2DComponent *comp);

        void Destroy();
    };

}
