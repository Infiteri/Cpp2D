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
        mesh->GetMaterial()->SetColor(*mat->GetColor());
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
}