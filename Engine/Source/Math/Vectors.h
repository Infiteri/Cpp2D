#pragma once

#include "Base.h"
#include "Math.h"

namespace Core
{
    class CE_API Vector2
    {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &other);
        ~Vector2();

        void Set(float x, float y);
        void Set(const Vector2 &o);
        void Set(Vector2 *o);

        float Mag()
        {
            return Math::Sqrt(x * x + y * y);
        };

        float Dot(const Vector2 &other)
        {
            return x * other.x + y * other.y;
        }

        void Normalize()
        {
            float m = Mag();
            m = 1 / m;
            Set(m, m);
        };

        Vector2 operator*(const Vector2 &o)
        {
            return {
                x * o.x,
                y * o.y};
        }

        Vector2 operator+(const Vector2 &o)
        {
            return {
                x + o.x,
                y + o.y};
        }

        Vector2 operator*(float o)
        {
            return {
                x * o,
                y * o};
        }

        void operator+=(const Vector2 &o)
        {
            x += o.x;
            y += o.y;
        }

        void operator*=(float f)
        {
            x *= f;
            y *= f;
        }

        void operator-=(const Vector2 &o)
        {
            x -= o.x;
            y -= o.y;
        }
    };

    class CE_API Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &other);
        ~Vector3();

        void Set(float x, float y, float z);
        void Set(const Vector3 &o);
        void Set(Vector3 *o);

        float Mag()
        {
            return Math::Sqrt(x * x + y * y + z * z);
        };

        void Normalize();

        Vector3 operator+(const Vector3 &o)
        {
            return {
                x + o.x,
                y + o.y,
                z + o.z};
        }

        void operator+=(const Vector3 &o)
        {
            x += o.x;
            y += o.y;
            z += o.z;
        }

        void operator-=(const Vector3 &o)
        {
            x -= o.x;
            y -= o.y;
            z -= o.z;
        }

        void operator*=(float f)
        {
            x *= f;
            y *= f;
            z *= f;
        }

        void operator-=(float f)
        {
            x -= f;
            y -= f;
            z -= f;
        }

        void operator/=(float f)
        {
            x /= f;
            y /= f;
            z /= f;
        }
    };

    class CE_API Vector4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4 &other);
        ~Vector4();

        void Set(float x, float y, float z, float w);
        void Set(const Vector4 &o);
        void Set(Vector4 *o);

        float Mag()
        {
            return Math::Sqrt(x * x + y * y + z * z + w * w);
        };

        void Normalize()
        {
            float m = Mag();
            m = 1 / m;
            Set(m, m, m, m);
        };
    };
}
