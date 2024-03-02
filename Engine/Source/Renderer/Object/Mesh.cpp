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
        array = new VertexArray();
        array->Upload(Buffer::Vertex, vertices, sizeof(vertices) * sizeof(float));
        array->Upload(Buffer::Index, indices, sizeof(indices) * sizeof(CeU32));
        array->GetVertexBuffer()->AddLayout(0, 0, 3);
    }

    Mesh::~Mesh()
    {
        delete array;
    }

    void Mesh::Render()
    {
        auto shader = ShaderSystem::Get("EngineResources/Shaders/Object");
        shader->Vec4(Color(0, 125, 255, 255), "uColor");

        array->Bind();
        array->GetVertexBuffer()->Bind();
        array->GetIndexBuffer()->Draw();
    }
}