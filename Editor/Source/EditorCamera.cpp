#include "EditorCamera.h"
#include "EditorLayer.h"

namespace Core
{
    EditorCamera::EditorCamera()
    {
        cameraName = "Editor Camera Name";
        camera = CameraSystem::CreateOrtho(cameraName);
        camera->SetTransformationType(Camera::TransformationType::Transform);
        Activate();
    }

    EditorCamera::~EditorCamera() {}

    void EditorCamera::SetupFromSetings(EditorSettings *settings)
    {
        camera->SetZoom(settings->CameraZoom);
    }

    void EditorCamera::Activate()
    {
        camera->CalculateProjection();
        camera->CalculateView();
        CameraSystem::Activate(cameraName);
    }

    void EditorCamera::Update()
    {
        // TODO: Movement
        if (Input::GetButton(Buttons::Right))
        {
            isRightClicking = true;
            Input::SetMouseMode(MouseMode::Locked);

            auto mouseDelta = Input::GetMouseDelta();
            camera->GetTransform()->Position.x += mouseDelta.x;
            camera->GetTransform()->Position.y += mouseDelta.y;
        }

        float mouseDelta = Input::GetMouseWheelDelta();
        if (Input::GetKey(Keys::LeftControl) && mouseDelta != 0)
        {
            camera->AddZoom(mouseDelta * 0.01);
            camera->CalculateProjection();
        }

        camera->SetZoom(Math::Clamp(camera->GetZoom(), 0.1f, 100.0f));
    }

    void EditorCamera::UpdateExitRightButton()
    {
        if (!Input::GetButton(Buttons::Right))
        {
            Input::SetMouseMode(MouseMode::Visible);
            isRightClicking = false;
        }
    }
}