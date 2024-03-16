#include "OrthographicCamera.h"

namespace Core
{
    OrthographicCamera::OrthographicCamera(float _width, float _height, float _near, float _far)
    {
        originPoint = Middle;
        zoom = 1.0f;
        near = _near;
        far = _far;
        type = Orthographic;
        CalculateView();
        CalculateProjection(_width, _height);
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::CalculateProjection(float _width, float _height)
    {
        width = _width;
        height = _height;
        CalculateProjection();
    }

    void OrthographicCamera::CalculateProjection()
    {
        switch (originPoint)

        {
        case Middle:
        {
            float calculatedWidth = (width / 2) * (zoom / 2);
            float calculatedHeight = (height / 2) * (zoom / 2);
            projection = Matrix4::Ortho(-calculatedWidth, calculatedWidth, -calculatedHeight, calculatedHeight, near, far);
        }
        break;

        case Left:
        default:
            projection = Matrix4::Ortho(0, width * zoom, 0, height * zoom, near, far);
            break;
        }
    }
}