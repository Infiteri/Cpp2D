#include "Renderer.h"
#include "Core/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
    static Renderer::State state;

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    static float screenQuadVertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 1.0f};

    void Renderer::Init()
    {
        if (state.init)
            return;
        state.init = true;

        // Load GLAD
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CE_DEFINE_LOG_CATEGORY("Renderer", "CE_RENDER");
        CE_LOG("CE_RENDER", Info, "Initialized.");

        state.objectShader = new Shader("EngineResources/Shaders/Object.vs.glsl", "EngineResources/Shaders/Object.fs.glsl");
        state.screenShader = new Shader("EngineResources/Shaders/Screen.vs.glsl", "EngineResources/Shaders/Screen.fs.glsl");

        FrameBuffer::Configuration frameConfig;
        frameConfig.PassConfiguration.push_back({FrameBuffer::Rgba8});
        frameConfig.PassConfiguration.push_back({FrameBuffer::Depth});
        state.frameBuffer = new FrameBuffer(&frameConfig);

        state.screenArray = new VertexArray();
        state.screenArray->Upload(Buffer::Vertex, screenQuadVertices, sizeof(screenQuadVertices) * sizeof(float));
        state.screenArray->GetVertexBuffer()->AddLayout(0, 0, 2);
        state.screenArray->GetVertexBuffer()->AddLayout(1, 2, 2);

        state.array = new VertexArray();
        state.array->Upload(Buffer::Vertex, vertices, sizeof(vertices));
        state.array->Upload(Buffer::Index, indices, sizeof(indices));
        state.array->GetVertexBuffer()->AddLayout(0, 0, 3);
    }

    void Renderer::Shutdown()
    {
        if (!state.init)
            return;
        state.init = false;

        delete state.array;
        delete state.objectShader;
        delete state.frameBuffer;

        CE_LOG("CE_RENDER", Info, "Shutdown.");
    }

    void Renderer::BeginFrame()
    {
        if (!state.init)
            return;

        state.frameBuffer->Bind();
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::Render()
    {
        if (!state.init)
            return;

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        state.objectShader->Use();

        state.array->Bind();
        state.array->GetVertexBuffer()->Bind();
        state.array->GetIndexBuffer()->Draw();
    }

    void Renderer::EndFrame()
    {
        if (!state.init)
            return;

        glDisable(GL_DEPTH_TEST);
        state.frameBuffer->Unbind();
    }

    void Renderer::RenderScreenTexture()
    {
        if (!state.init)
            return;

        state.screenArray->Bind();
        state.screenShader->Use();

        auto pass = state.frameBuffer->GetRenderPass(0);
        glActiveTexture(GL_TEXTURE0 + pass->Index);
        glBindTexture(GL_TEXTURE_2D, pass->Id);
        state.screenShader->Int(pass->Index, "uScreenTexture");

        state.screenArray->GetVertexBuffer()->Bind();
        state.screenArray->GetVertexBuffer()->Draw();
    }

    void Renderer::Viewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        if (state.frameBuffer)
            state.frameBuffer->Resize(width, height);
    }
}