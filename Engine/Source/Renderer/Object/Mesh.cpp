#include "Mesh.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderSystem.h"

namespace Core
{
    static float vertices[] = {
        100.0f, 100.0f, 0.0f,
        100.0f, -100.0f, 0.0f,
        -100.0f, -100.0f, 0.0f,
        -100.0f, 100.0f, 0.0f};

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

    void Mesh::SetMaterial(const std::string &materialName)
    {
        ReleaseMaterial();
        material = MaterialSystem::Get(materialName);
    }

    void Mesh::SetMaterialFromFile(const std::string &filename)
    {
        ReleaseMaterial();
        material = MaterialSystem::GetFromFile(filename);
    }

    void Mesh::ReleaseMaterial()
    {
        if (material)
            if (material->GetFileName().empty())
                MaterialSystem::Release(material->GetName());
            else
                MaterialSystem::Release(material->GetFileName());

        material = nullptr;
    }
}