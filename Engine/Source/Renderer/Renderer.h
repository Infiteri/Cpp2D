#pragma once

#include "Base.h"
#include "Shader/Shader.h"
#include "buffer/buffer.h"

namespace Core
{
    class Renderer
    {
    public:
        struct State
        {
            bool init;

            Shader *objectShader;
            Buffer *buffer;

            CeU32 VBA;
        };

        Renderer(){};
        ~Renderer(){};

        static void Init();
        static void Shutdown();

        static void BeginFrame();
        static void Render();
        static void EndFrame();
        static void RenderScreenTexture();
    };
}