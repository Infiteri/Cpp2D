#pragma once

#include "Base.h"
#include "GPUScreen.h"
#include "Shader/Shader.h"
#include "Object/Mesh.h"

namespace Core
{
    class Renderer
    {
    public:
        struct State
        {
            bool init;

            Shader *objectShader;
            Mesh* mesh;
            GPUScreen screen;
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
    };
}