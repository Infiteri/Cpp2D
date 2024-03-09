#include "Components.h"
#include "Scene/Actor.h"

namespace Core
{
    Component::Component()
    {
    }

    Component::~Component()
    {
        Destroy();
    }

    MeshComponent::MeshComponent()
    {
        mesh = new Mesh();
        type = ComponentTypes::Mesh;
    }

    void MeshComponent::Render()
    {
        if (!mesh)
            return;

        mesh->Render();
    }

    void MeshComponent::SetMaterial(const std::string &filename)
    {
        mesh->SetMaterialFromFile(filename);
    }

    void MeshComponent::SetMaterialFromName(const std::string &name)
    {
        mesh->SetMaterial(name);
    }

    void MeshComponent::From(MeshComponent *other)
    {
        auto mat = other->mesh->GetMaterial();

        if (mat->GetFileName().empty())
            mesh->SetMaterial(mat->GetName());
        else
            mesh->SetMaterialFromFile(mat->GetFileName());

        mesh->GetMaterial()->SetColor(*mat->GetColor());
    }
}