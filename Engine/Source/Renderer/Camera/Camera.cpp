#include "Camera.h"

namespace Core
{
    void Camera::CalculateProjection()
    {
    }

    void Camera::CalculateView()
    {

        if (transformType == TransformationType::Transform)
            matrixTransform = transform.GetTransformMatrix();

        view.From(&matrixTransform);
    }

    void Camera::SetOriginPoint(OriginPoint o)
    {
        if (originPoint == o)
            return;

        originPoint = o;
        CalculateProjection();
    }

    void Camera::SetType(Type o)
    {
        type = o;
    }

    void Camera::SetTransformationType(TransformationType o)
    {
        if (transformType == o)
            return;

        if (transformType == TransformationType::Transform)
        {
            if (o == TransformationType::Matrix)
            {
                transform.Position = transform.Rotation = {0, 0, 0};
                transform.Scale = {1, 1, 1};
            }
        }

        transformType = o;
    }

    void Camera::SetZoom(float z)
    {
        zoom = z;
    }

    void Camera::AddZoom(float z)
    {
        zoom += z;
    }
}