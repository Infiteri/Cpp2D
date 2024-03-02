#pragma once

#include "Base.h"
#include "Shader/Shader.h"
#include "Shader/ShaderSystem.h"
#include "Buffer/VertexArray.h"
#include "Buffer/FrameBuffer.h"

namespace Core
{
    struct GPUScreen
    {
        FrameBuffer *ScreenFrameBuffer;
        VertexArray *ScreenVertexArray;
        Shader *ScreenShader;

        GPUScreen();
        ~GPUScreen();
        void Init();
        void BeginFrame();
        void EndFrame();
        void RenderGPUImage();
    };

}