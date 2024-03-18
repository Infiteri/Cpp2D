#include "CameraSystem.h"
#include "Core/Logger.h"
#include <unordered_map>

namespace Core
{
    struct
    {
        std::unordered_map<std::string, Camera *> cameras;
        Camera *active;

        int width;
        int height;
    } state;

    void CameraSystem::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Camera System", "CE_CAM_SYS");
    }

    void CameraSystem::Shutdown()
    {
        for (auto it : state.cameras)
            delete it.second;

        state.cameras.clear();
    }

    void CameraSystem::Viewport(int width, int height)
    {
        state.width = width;
        state.height = height;

        for (auto it : state.cameras)
            if (it.second->GetType() == Camera::Orthographic)
                it.second->As<OrthographicCamera>()->CalculateProjection(width, height);

        if (state.active)
            if (state.active->GetType() == Camera::Orthographic)
                state.active->As<OrthographicCamera>()->CalculateProjection(width, height);
    }

    OrthographicCamera *CameraSystem::CreateOrtho(const std::string &name)
    {
        if (state.cameras[name])
            return state.cameras[name]->As<OrthographicCamera>();

        state.cameras[name] = new OrthographicCamera(state.width, state.height, -100, 100);
        return state.cameras[name]->As<OrthographicCamera>();
    }

    Camera *CameraSystem::Get(const std::string &name)
    {
        if (state.cameras[name] == nullptr)
            return nullptr;

        return state.cameras[name];
    }

    Camera *CameraSystem::GetActive()
    {
        return state.active;
    }

    bool CameraSystem::Activate(const std::string &name)
    {
        auto cam = Get(name);

        if (cam)
        {
            state.active = cam;
            state.active->CalculateProjection();
            state.active->CalculateView();
            return true;
        }
        else
            CE_LOG("CE_CAM_SYS", Warn, "No camera found for name: %s", name.c_str());

        return false;
    }

    void CameraSystem::Activate(OrthographicCamera *camera)
    {
        state.active = camera;
    }

    void CameraSystem::UpdateActive()
    {
        if (state.active)
            state.active->CalculateView();
    }

    void CameraSystem::Remove(const std::string &name)
    {
        if (state.cameras[name])
        {
            delete state.cameras[name];
            state.cameras.erase(name);
        }
    }
}