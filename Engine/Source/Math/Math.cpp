#include "Math.h"

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
    }
}