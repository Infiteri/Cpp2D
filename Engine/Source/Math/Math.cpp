#include "Math.h"
#include <cmath>

namespace Core
{
    namespace Math
    {
        float Positive(float x)
        {
            if (x == 0 || x > 0)
                return x;
            else
                return -x;
        }

        float Pow(float x, float pow)
        {
            return powf(x, pow);
        }

        float Clamp(float value, float min, float max)
        {
            if (value < min)
                return min;

            if (value > max)
                return max;

            return value;
        }

        float Sqrt(float value)
        {
            return sqrtf(value);
        }

        float Abs(float value)
        {
            return abs(value);
        }
    }
}