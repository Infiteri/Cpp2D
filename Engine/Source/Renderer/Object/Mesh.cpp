#include "Mesh.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderSystem.h"

namespace Core
{
    static float vertices[] = {
        100.0f, 100.0f, 0.0f, 1, 1,
        100.0f, -100.0f, 0.0f, 1, 0,
        -100.0f, -100.0f, 0.0f, 0, 0,
        -100.0f, 100.0f, 0.0f, 0, 1};

    static CeU32 indices[] = {
        0, 1, 3,
        1, 2, 3};

    Mesh::Mesh()
    {
        material = MaterialSystem::GetDefaultMaterial();

        array = new VertexArray();
        array->Upload(Buffer::Vertex, vertices, sizeof(vertices) * sizeof(float));
        array->Upload(Buffer::Index, indices, sizeof(indices) * sizeof(CeU32));
        array->GetVertexBuffer()->AddLayout(0, 0, 3);
        array->GetVertexBuffer()->AddLayout(1, 3, 2);
    }

    Mesh::~Mesh()
    {
        ReleaseMaterial();

        delete array;
    }

    void Mesh::Render()
    {
        if (material != nullptr)
            material->Use();

        array->Bind();
        array->GetVertexBuffer()->Bind();
        array->GetIndexBuffer()->Draw();
    }

    void Mesh::SetMaterial(Material::Configuration *config)
    {
        ReleaseMaterial();

        material = new Material();
        material->Load(config);
    }

    void Mesh::SetMaterial(const std::string &materialName)
    {
        ReleaseMaterial();
        material = MaterialSystem::Get(materialName);
    }

    void Mesh::MakeMaterialUnique()
    {
        ReleaseMaterial();
        material = new Material();
        material->SetLoadMode(Material::Config);
    }

    void Mesh::MakeMaterialDefault()
    {
        ReleaseMaterial();
        material = MaterialSystem::GetDefaultMaterial();
    }

    void Mesh::ReleaseMaterial()
    {
        if (material)
        {
            if (material->GetLoadMode() != Material::Default)
                if (material->GetFileName().empty())
                    delete material;
                else
                    MaterialSystem::Release(material->GetFileName());
        }

        material = nullptr;
    }
}