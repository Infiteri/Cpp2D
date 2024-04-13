#pragma once

#include "Base.h"

#define CE_PI 3.14
#define CE_DEG_TO_RAD CE_PI / 180
#define CE_RAD_TO_DEG 180 / CE_PI

namespace Core
{
    namespace Math
    {
        CE_API float Positive(float x);
        CE_API float Clamp(float value, float min, float max);
        CE_API float Sqrt(float x);
        CE_API float Pow(float x, float y);
        CE_API float Abs(float x);
    };
}