#pragma once

#include "Base.h"
#include "GPUScreen.h"
#include "Shader/Shader.h"
#include "Object/Mesh.h"

namespace Core
{
    class CE_API Renderer
    {
    public:
        struct State
        {
            bool init;

            Shader *objectShader;
            GPUScreen screen;

            /// @brief TODO: Refactor
            Color bgColor{16, 16, 16, 255};
        };

        Renderer(){};
        ~Renderer(){};

        static void Init();
        static void Shutdown();

        static void BeginFrame();
        static void Render();
        static void EndFrame();
        static void RenderScreenTexture();
        static void Viewport(int width, int height);
        static void SetClearColor(float r, float g, float b);
        static Color GetClearColor();
    };
}