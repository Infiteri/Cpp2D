#include "OrthographicCamera.h"

namespace Core
{
    OrthographicCamera::OrthographicCamera(float _width, float _height, float _near, float _far)
    {
        originPoint = Middle;
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
            projection = Matrix4::Ortho(-(width / 2), width / 2, -(height / 2), height / 2, near, far);
            break;

        case Left:
        default:
            projection = Matrix4::Ortho(0, width, 0, height, near, far);
            break;
        }
    }
}