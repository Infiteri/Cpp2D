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
        float Clamp(float value, float min, float max)
        {
            if (value < min)
                return min;

            if (value > max)
                return max;

            return value;
        }
        float Sqrt(float x)
        {
            return sqrtf(x);
        }

        float Pow(float x, float y)
        {
            return powf(x, y);
        }
        float Abs(float x)
        {
            return fabs(x);
        }
    }
}