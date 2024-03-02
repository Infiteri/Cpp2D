#include "Camera.h"

namespace Core
{
    void Camera::CalculateProjection()
    {
    }

    void Camera::CalculateView()
    {
        view = Matrix4::Translate(0, 0, 0);
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
}