#pragma once

#include "Base.h"
#include "Math.h"
#include "Vectors.h"

// NOTES: Although unusual, maths that dont change dont need to be implemented in a cpp function, this applies to also small functions that dont change but not to constructors

namespace Core
{
    class CE_API Quaternion
    {
    public:
        union
        {
            // From "Game engine physics development by Ian Millington"
            struct
            {
                float r;
                float i;
                float j;
                float k;
            };

            struct
            {
                float w;
                float x;
                float y;
                float z;
            };

            struct
            {
                float data[4];
            };
        };

        Quaternion();
        Quaternion(float r, float i, float j, float k);
        Quaternion(const Quaternion &other);
        ~Quaternion();

        void normalize()
        {
            float d = r * r + i * i + j * j + k * k;
            d = 1.0 / Math::Sqrt(d);
            r *= d;
            i *= d;
            j *= d;
            k *= d;
        }

        void operator*=(const Quaternion &multiplier)
        {
            Quaternion q = *this;
            r = q.r * multiplier.r - q.i * multiplier.i -
                q.j * multiplier.j - q.k * multiplier.k;
            i = q.r * multiplier.i + q.i * multiplier.r +
                q.j * multiplier.k - q.k * multiplier.j;
            j = q.r * multiplier.j + q.j * multiplier.r +
                q.k * multiplier.i - q.i * multiplier.k;
            k = q.r * multiplier.k + q.k * multiplier.r +
                q.i * multiplier.j - q.j * multiplier.i;
        }

        void operator+=(const Vector3 &vec)
        {
            Quaternion q(0,
                         vec.x,
                         vec.y,
                         vec.z);
            q *= *this;
            r += q.r * 0.5f;
            i += q.i * 0.5f;
            j += q.j * 0.5f;
            k += q.k * 0.5f;
        }

        void RotateToVector(const Vector3 &vector)
        {
            Quaternion q(0, vector.x, vector.y,
                         vector.z);
            (*this) *= q;
        }

        void Set(Quaternion *q) { Set(q->r, q->i, q->j, q->k); }
        void Set(const Quaternion &q) { Set(q.r, q.i, q.j, q.k); }

        void Set(float r, float i, float j, float k);
    };

}