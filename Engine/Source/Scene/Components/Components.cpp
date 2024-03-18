#include "Components.h"
#include "Core/Logger.h"
#include "Scene/Actor.h"

namespace Core
{
    Component::Component()
    {
    }

    MeshComponent::MeshComponent()
    {
        mesh = new Mesh();
        type = ComponentTypes::Mesh;
    }

    MeshComponent::~MeshComponent()
    {
        Destroy();
    }

    void MeshComponent::Render()
    {
        if (!mesh)
            return;

        mesh->Render();
    }

    void MeshComponent::SetMaterial(const std::string &filename)
    {
        mesh->SetMaterial(filename);
    }

    void MeshComponent::SetMaterial(Material::Configuration *config)
    {
        mesh->SetMaterial(config);
    }

    void MeshComponent::From(MeshComponent *other)
    {
        auto mat = other->mesh->GetMaterial();
        auto geo = other->mesh->GetGeometry();

        if (mat->GetFileName().empty())
        {
            Material::Configuration config;
            config.Name = other->mesh->GetMaterial()->GetName();
            config.Color = *other->mesh->GetMaterial()->GetColor();
            config.TexturePath = other->mesh->GetMaterial()->GetTexture()->GetImagePath();
            // config.TextureConfiguration = other->mesh->GetMaterial()->GetTexture()->GetC();
            mesh->SetMaterial(&config);
        }
        else
        {
            mesh->SetMaterial(mat->GetFileName());
        }

        switch (geo->GetType())
        {
        case Geometry::Square:
            auto sq = geo->As<SquareGeometry>();
            mesh->SetGeometry(new SquareGeometry(sq->Width, sq->Height));
            break;
        }
    }

    void MeshComponent::Destroy()
    {
        delete mesh;
        mesh = nullptr;
    }

    CameraComponent::CameraComponent()
    {
        type = ComponentTypes::Camera;
        camera = new OrthographicCamera(1024, 576, -100, 100);
        camera->SetTransformationType(Camera::TransformationType::Matrix);
    }

    CameraComponent::~CameraComponent()
    {
        Destroy();
    }

    void CameraComponent::Update()
    {
        switch (camera->GetTransformationType())
        {
        case Camera::TransformationType::Matrix:
            camera->SetTransformMatrix(Owner->GetWorldMatrix());
            break;
        }
    }

    void CameraComponent::From(CameraComponent *o)
    {
        camera->SetOriginPoint(o->camera->GetOriginPoint());
        camera->SetType(o->camera->GetType());
        camera->SetZoom(o->camera->GetZoom());
        camera->SetTransformationType(o->camera->GetTransformationType());

        camera->GetTransform()->Position = o->camera->GetTransform()->Position;
        camera->GetTransform()->Rotation = o->camera->GetTransform()->Rotation;
        camera->GetTransform()->Scale = o->camera->GetTransform()->Scale;
    }

    void CameraComponent::Destroy()
    {
        delete camera;
    }

    SpriteComponent::SpriteComponent()
    {
        sprite = new Sprite();
    }

    SpriteComponent::~SpriteComponent()
    {
        delete sprite;
    }

    void SpriteComponent::Render()
    {
        if (!sprite)
            return;

        sprite->Render();
    }

    void SpriteComponent::From(SpriteComponent *o)
    {
        sprite->SetSize(o->sprite->GetSize());

        auto mat = o->sprite->GetMaterial();

        if (mat->GetFileName().empty())
        {
            Material::Configuration config;
            config.Name = o->sprite->GetMaterial()->GetName();
            config.Color = *o->sprite->GetMaterial()->GetColor();
            config.TexturePath = o->sprite->GetMaterial()->GetTexture()->GetImagePath();
            // config.TextureConfiguration = other->mesh->GetMaterial()->GetTexture()->GetC();
            sprite->SetMaterial(&config);
        }
        else
        {
            sprite->SetMaterial(mat->GetFileName());
        }
    }

    void SpriteComponent::Destroy()
    {
    }
}