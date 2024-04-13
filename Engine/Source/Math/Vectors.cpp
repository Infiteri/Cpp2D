#include "Vectors.h"

namespace Core
{
    Vector2::Vector2()
    {
        Set(0, 0);
    }

    Vector2::Vector2(float x, float y)
    {
        Set(x, y);
    }

    Vector2::Vector2(const Vector2 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vector2::~Vector2()
    {
    }

    void Vector2::Set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void Vector2::Set(const Vector2 &o)
    {
        Set(o.x, o.y);
    }

    void Vector2::Set(Vector2 *o)
    {
        Set(o->x, o->y);
    }

    Vector3::Vector3()
    {
        Set(0, 0, 0);
    }

    Vector3::Vector3(float x, float y, float z)
    {
        Set(x, y, z);
    }

    Vector3::Vector3(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3::~Vector3()
    {
    }

    void Vector3::Set(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void Vector3::Set(const Vector3 &o)
    {
        Set(o.x, o.y, o.z);
    }

    void Vector3::Set(Vector3 *o)
    {
        Set(o->x, o->y, o->z);
    }

    void Vector3::Normalize()
    {
        float m = Mag();
        m = 1 / m;
        x *= m;
        y *= m;
        z *= m;
    };

    Vector4::Vector4()
    {
        Set(0, 0, 0, 0);
    }

    Vector4::Vector4(float x, float y, float z, float w)
    {
        Set(x, y, z, w);
    }

    Vector4::Vector4(const Vector4 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    Vector4::~Vector4()
    {
    }

    void Vector4::Set(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void Vector4::Set(const Vector4 &o)
    {
        Set(o.x, o.y, o.z, o.w);
    }

    void Vector4::Set(Vector4 *o)
    {
        Set(o->x, o->y, o->z, o->w);
    }
}