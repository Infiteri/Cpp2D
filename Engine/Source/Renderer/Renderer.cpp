#include "Renderer.h"
#include "Core/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
    static Renderer::State state;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    void Renderer::Init()
    {
        if (state.init)
            return;
        state.init = true;

        // Load GLAD
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        state.objectShader = new Shader("EngineResources/Shaders/Object.vs.glsl", "EngineResources/Shaders/Object.fs.glsl");
        state.buffer = new Buffer(Buffer::Vertex);

        CE_DEFINE_LOG_CATEGORY("Renderer", "CE_RENDER");
        CE_LOG("CE_RENDER", Info, "Initialized.");

        glGenVertexArrays(1, &state.VBA);
        glBindVertexArray(state.VBA);

        state.buffer->Upload(vertices, sizeof(vertices));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    void Renderer::Shutdown()
    {
        if (!state.init)
            return;
        state.init = false;

        CE_LOG("CE_RENDER", Info, "Shutdown.");
    }

    void Renderer::BeginFrame()
    {
        if (!state.init)
            return;
    }

    void Renderer::Render()
    {
        if (!state.init)
            return;

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        state.objectShader->Use();

        glBindVertexArray(state.VBA);
        state.buffer->Draw();
    }

    void Renderer::EndFrame()
    {
        if (!state.init)
            return;
    }

    void Renderer::RenderScreenTexture()
    {
        if (!state.init)
            return;
    }
}