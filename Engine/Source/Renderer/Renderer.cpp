#include "Renderer.h"
#include "Camera/CameraSystem.h"
#include "Core/Logger.h"
#include "Color.h"
#include "Shader/ShaderSystem.h"
#include "Texture/TextureSystem.h"
#include "Material/MaterialSystem.h"
#include "Resources/Loader/MaterialLoader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
    static Renderer::State state;

    void Renderer::Init()
    {
        if (state.init)
            return;
        state.init = true;

        // Load GLAD
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CE_DEFINE_LOG_CATEGORY("Renderer", "CE_RENDER");
        CE_LOG("CE_RENDER", Info, "Initialized.");

        ShaderSystem::Init({"EngineResources/Shaders/Object", "EngineResources/Shaders/Screen"});
        state.objectShader = ShaderSystem::Get("EngineResources/Shaders/Object");

        CameraSystem::Init();
        CameraSystem::CreateOrtho("Main");
        CameraSystem::Activate("Main");

        // ! Texture system before material, otherwise material will not have a default texture reference.
        TextureSystem::Init();
        MaterialSystem::Init();

        state.screen.Init();
    }

    void Renderer::Shutdown()
    {
        if (!state.init)
            return;
        state.init = false;

        delete state.objectShader;
        CameraSystem::Shutdown();
        MaterialSystem::Shutdown();
        TextureSystem::Shutdown();

        CE_LOG("CE_RENDER", Info, "Shutdown.");
    }

    void Renderer::BeginFrame()
    {
        if (!state.init)
            return;

        state.screen.BeginFrame();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Render()
    {
        if (!state.init)
            return;

        Color normalized = state.bgColor.Normalized();
        glClearColor(normalized.R, normalized.G, normalized.B, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CameraSystem::UpdateActive();

        state.objectShader->Use();

        auto camera = CameraSystem::GetActive();
        if (camera)
        {
            state.objectShader->Mat4(camera->GetProjection(), "uProjection");
            state.objectShader->Mat4(camera->GetInvertedView(), "uView");
        }
        else
        {
            state.objectShader->Mat4(Matrix4::Empty(), "uProjection");
            state.objectShader->Mat4(Matrix4::Empty(), "uView");
        }
    }

    void Renderer::EndFrame()
    {
        if (!state.init)
            return;

        glDisable(GL_DEPTH_TEST);
        state.screen.EndFrame();
    }

    void Renderer::RenderScreenTexture()
    {
        if (!state.init)
            return;

        state.screen.RenderGPUImage();
    }

    void Renderer::Viewport(int width, int height)
    {
        CameraSystem::Viewport(width, height);
        if (state.screen.ScreenFrameBuffer)
            state.screen.ScreenFrameBuffer->Resize(width, height);
        glViewport(0, 0, width, height);
    }

    void Renderer::SetClearColor(float r, float g, float b)
    {
        state.bgColor.Set(r, g, b, 255);
    }

    Color Renderer::GetClearColor()
    {
        return Color(state.bgColor);
    }

    FrameBuffer *Renderer::GetFrameBuffer()
    {
        return state.screen.ScreenFrameBuffer;
    }
}