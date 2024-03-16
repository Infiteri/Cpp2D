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
}