#include "Geometry.h"

namespace Core
{
    Geometry::Geometry()
    {
    }

    Geometry::~Geometry()
    {
    }

    SquareGeometry::SquareGeometry(float width, float height)
    {
        Width = width;
        Height = height; 

        float vertexCount = 4 * 6; // 4 vertices per segment
        vertices.resize(vertexCount);
        float indexCount = 6 * 6; // 6 indices per segment
        indices.resize(indexCount);

        float min_x = -width;
        float min_y = -height;
        float max_x = width;
        float max_y = height;
        float min_uvx = 0.0f;
        float min_uvy = 0.0f;
        float max_uvx = 1;
        float max_uvy = 1;

        // Configure
        vertices[(0 * 4) + 0].Position.Set(min_x, min_y, 0);
        vertices[(0 * 4) + 1].Position.Set(max_x, max_y, 0);
        vertices[(0 * 4) + 2].Position.Set(min_x, max_y, 0);
        vertices[(0 * 4) + 3].Position.Set(max_x, min_y, 0);
        vertices[(0 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(0 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(0 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(0 * 4) + 3].UV.Set(max_uvx, min_uvy);

        // Back face
        vertices[(1 * 4) + 0].Position.Set(max_x, min_y, 0);
        vertices[(1 * 4) + 1].Position.Set(min_x, max_y, 0);
        vertices[(1 * 4) + 2].Position.Set(max_x, max_y, 0);
        vertices[(1 * 4) + 3].Position.Set(min_x, min_y, 0);
        vertices[(1 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(1 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(1 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(1 * 4) + 3].UV.Set(max_uvx, min_uvy);

        // Left
        vertices[(2 * 4) + 0].Position.Set(min_x, min_y, 0);
        vertices[(2 * 4) + 1].Position.Set(min_x, max_y, 0);
        vertices[(2 * 4) + 2].Position.Set(min_x, max_y, 0);
        vertices[(2 * 4) + 3].Position.Set(min_x, min_y, 0);
        vertices[(2 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(2 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(2 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(2 * 4) + 3].UV.Set(max_uvx, min_uvy);

        // Right face
        vertices[(3 * 4) + 0].Position.Set(max_x, min_y, 0);
        vertices[(3 * 4) + 1].Position.Set(max_x, max_y, 0);
        vertices[(3 * 4) + 2].Position.Set(max_x, max_y, 0);
        vertices[(3 * 4) + 3].Position.Set(max_x, min_y, 0);
        vertices[(3 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(3 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(3 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(3 * 4) + 3].UV.Set(max_uvx, min_uvy);

        // Bottom face
        vertices[(4 * 4) + 0].Position.Set(max_x, min_y, 0);
        vertices[(4 * 4) + 1].Position.Set(min_x, min_y, 0);
        vertices[(4 * 4) + 2].Position.Set(max_x, min_y, 0);
        vertices[(4 * 4) + 3].Position.Set(min_x, min_y, 0);
        vertices[(4 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(4 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(4 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(4 * 4) + 3].UV.Set(max_uvx, min_uvy);

        // Top face
        vertices[(5 * 4) + 0].Position.Set(min_x, max_y, 0);
        vertices[(5 * 4) + 1].Position.Set(max_x, max_y, 0);
        vertices[(5 * 4) + 2].Position.Set(min_x, max_y, 0);
        vertices[(5 * 4) + 3].Position.Set(max_x, max_y, 0);
        vertices[(5 * 4) + 0].UV.Set(min_uvx, min_uvy);
        vertices[(5 * 4) + 1].UV.Set(max_uvx, max_uvy);
        vertices[(5 * 4) + 2].UV.Set(min_uvx, max_uvy);
        vertices[(5 * 4) + 3].UV.Set(max_uvx, min_uvy);

        for (CeU32 i = 0; i < 6; ++i)
        {
            CeU32 v_offset = i * 4;
            CeU32 i_offset = i * 6;
            indices[i_offset + 0] = v_offset + 0;
            indices[i_offset + 1] = v_offset + 1;
            indices[i_offset + 2] = v_offset + 2;
            indices[i_offset + 3] = v_offset + 0;
            indices[i_offset + 4] = v_offset + 3;
            indices[i_offset + 5] = v_offset + 1;
        }

        type = Square;
    }

    SquareGeometry::~SquareGeometry()
    {
    }
}