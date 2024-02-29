#pragma once

#include "Base.h"
#include "Shader/Shader.h"
#include "Buffer/VertexArray.h"
#include "Buffer/FrameBuffer.h"

namespace Core
{
    class Renderer
    {
    public:
        struct State
        {
            bool init;

            Shader *objectShader;
            Shader *screenShader;
            VertexArray *array;
            VertexArray *screenArray;
            FrameBuffer *frameBuffer;

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

        static void Viewport(int width, int height);
    };
}