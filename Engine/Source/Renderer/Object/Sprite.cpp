#include "Sprite.h"
#include "Core/Logger.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderSystem.h"

#include <cmath>

namespace Core
{
    Sprite::Sprite(const Vector2 &sizes)
    {
        material = MaterialSystem::GetDefaultMaterial();
        array = nullptr;
        size = sizes;
        frameLayout = {1, 1};
        currentFrame = 0;
        SetupVertexArray();
    }

    Sprite::~Sprite()
    {
        ReleaseMaterial();
        delete array;
    }

    void Sprite::Render()
    {
        if (material != nullptr)
            material->Use();

        array->Bind();
        array->GetVertexBuffer()->Bind();
        array->GetIndexBuffer()->Draw();
    }

    void Sprite::ReleaseMaterial()
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

    void Sprite::SetupVertexArray()
    {
        if (array != nullptr)
        {
            delete array;
            array = nullptr;
        }

        std::vector<Vertex3D> vertices;
        std::vector<CeU32> indices;

        float vertexCount = 4 * 6; // 4 vertices per segment
        vertices.resize(vertexCount);
        float indexCount = 6 * 6; // 6 indices per segment
        indices.resize(indexCount);

        float min_x = -size.x / frameLayout.x;
        float min_y = -size.y / frameLayout.y;
        float max_x = size.x / frameLayout.x;
        float max_y = size.y / frameLayout.y;

        // Calculate UVs for animation frames
        float columns = frameLayout.x;
        float rows = frameLayout.y;
        float frameWidth = 1.0f / columns;
        float frameHeight = 1.0f / rows;

        // Adjust row index calculation for reversed animation
        float rowIndex = rows - floor(currentFrame / columns) - 1;
        float colIndex = fmod(currentFrame, columns);

        float min_uvx = colIndex * frameWidth;
        float max_uvx = min_uvx + frameWidth;
        float min_uvy = 1.0f - ((rowIndex + 1) * frameHeight);
        float max_uvy = 1.0f - (rowIndex * frameHeight);

        for (CeU32 i = 0; i < 6; ++i)
        {
            CeU32 v_offset = i * 4;
            CeU32 i_offset = i * 6;

            vertices[v_offset + 0].Position.Set(min_x, min_y, 0);
            vertices[v_offset + 1].Position.Set(max_x, max_y, 0);
            vertices[v_offset + 2].Position.Set(min_x, max_y, 0);
            vertices[v_offset + 3].Position.Set(max_x, min_y, 0);

            vertices[v_offset + 0].UV.Set(min_uvx, min_uvy);
            vertices[v_offset + 1].UV.Set(max_uvx, max_uvy);
            vertices[v_offset + 2].UV.Set(min_uvx, max_uvy);
            vertices[v_offset + 3].UV.Set(max_uvx, min_uvy);

            indices[i_offset + 0] = v_offset + 0;
            indices[i_offset + 1] = v_offset + 1;
            indices[i_offset + 2] = v_offset + 2;
            indices[i_offset + 3] = v_offset + 0;
            indices[i_offset + 4] = v_offset + 3;
            indices[i_offset + 5] = v_offset + 1;
        }

        SetupVertexArrayWithData(vertices.data(), vertices.size(), indices.data(), indices.size());
    }

    void Sprite::SetupVertexArrayWithData(void *vertices, CeU32 vertexSize, CeU32 *indices, CeU32 indexSize)
    {
        if (array != nullptr)
            delete array;

        array = new VertexArray();
        array->Upload(Buffer::Vertex, vertices, vertexSize * sizeof(float));
        array->Upload(Buffer::Index, indices, indexSize * sizeof(CeU32));
        array->GetVertexBuffer()->AddLayout(0, 0, 3);
        array->GetVertexBuffer()->AddLayout(1, 3, 2);
    }

    void Sprite::SetSize(const Vector2 &sizes)
    {
        size = sizes;
        SetupVertexArray();
    }

    void Sprite::SetCurrentFrame(float frames)
    {
        currentFrame = frames;
        SetupVertexArray();
    }

    void Sprite::SetFrameLayout(const Vector2 &frames)
    {
        frameLayout = frames;
        SetupVertexArray();
    }

    void Sprite::SetMaterial(const std::string &materialName)
    {
        ReleaseMaterial();
        material = MaterialSystem::Get(materialName);
    }

    void Sprite::SetMaterial(Material::Configuration *config)
    {
        ReleaseMaterial();
        material = new Material();
        material->Load(config);
    }

    void Sprite::MakeMaterialUnique()
    {
        ReleaseMaterial();
        material = new Material();
        material->SetLoadMode(Material::Config);
    }

    void Sprite::MakeMaterialDefault()
    {
        ReleaseMaterial();
        material = MaterialSystem::GetDefaultMaterial();
    }
}