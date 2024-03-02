#pragma once

#include "Base.h"
#include "Camera.h"

namespace Core
{
    class OrthographicCamera : public Camera
    {
    private:
        float width;
        float height;
        float near;
        float far;

    public:
        OrthographicCamera(float _width, float _height, float near = -1, float far = 1);
        ~OrthographicCamera();

        void CalculateProjection();
        void CalculateProjection(float _width, float _height);
    };
}