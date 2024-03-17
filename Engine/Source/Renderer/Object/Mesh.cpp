#include "Mesh.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderSystem.h"

namespace Core
{
    Mesh::Mesh()
    {
        material = MaterialSystem::GetDefaultMaterial();
        array = nullptr;
        geometry = new Geometry();
        SetupVertexArray();
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

    void Mesh::SetGeometry(Geometry *_geometry)
    {
        ReleaseGeometry();
        geometry = _geometry;
        SetupVertexArray();
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

    void Mesh::ReleaseGeometry()
    {
        if (geometry)
            delete geometry;

        geometry = nullptr;
    }

    void Mesh::SetupVertexArray()
    {
        if (array != nullptr)
        {
            delete array;
        }

        if (!geometry)
            return;

        array = new VertexArray();
        array->Upload(Buffer::Vertex, geometry->GetVertices(), geometry->GetVerticesSize() * sizeof(float));
        array->Upload(Buffer::Index, geometry->GetIndices(), geometry->GetIndicesSize() * sizeof(CeU32));
        array->GetVertexBuffer()->AddLayout(0, 0, 3);
        array->GetVertexBuffer()->AddLayout(1, 3, 2);
    }
}