#include "GPUScreen.h"
#include <glad/glad.h>

namespace Core
{
    static float screenQuadVertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 1.0f};

    GPUScreen::GPUScreen()
    {
        ScreenFrameBuffer = nullptr;
        ScreenVertexArray = nullptr;
        ScreenShader = nullptr;
    }

    GPUScreen::~GPUScreen()
    {
    }

    void GPUScreen::Init()
    {
        ScreenShader = ShaderSystem::Get("EngineResources/Shaders/Screen");

        FrameBuffer::Configuration frameConfig;
        frameConfig.PassConfiguration.push_back({FrameBuffer::Rgba8});
        frameConfig.PassConfiguration.push_back({FrameBuffer::Depth});
        ScreenFrameBuffer = new FrameBuffer(&frameConfig);

        ScreenVertexArray = new VertexArray();
        ScreenVertexArray->Upload(Buffer::Vertex, screenQuadVertices, sizeof(screenQuadVertices));
        ScreenVertexArray->GetVertexBuffer()->AddLayout(0, 0, 2);
        ScreenVertexArray->GetVertexBuffer()->AddLayout(1, 2, 2);
    }

    void GPUScreen::BeginFrame()
    {
        ScreenFrameBuffer->Bind();

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GPUScreen::EndFrame()
    {
        ScreenFrameBuffer->Unbind();
    }

    void GPUScreen::RenderGPUImage()
    {
        ScreenVertexArray->Bind();
        ScreenShader->Use();

        auto pass = ScreenFrameBuffer->GetRenderPass(0);
        glActiveTexture(GL_TEXTURE0 + pass->Index);
        glBindTexture(GL_TEXTURE_2D, pass->Id);
        ScreenShader->Int(pass->Index, "uScreenTexture");

        ScreenVertexArray->GetVertexBuffer()->Bind();
        ScreenVertexArray->GetVertexBuffer()->Draw();
    }
}