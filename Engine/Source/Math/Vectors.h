#pragma once

#include "Base.h"

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

    void operator+=(const Vector2 &o)
    {
      x += o.x;
      y += o.y;
    }

    void operator*=(const Vector2 &o)
    {
      x *= o.x;
      y *= o.y;
    }

    void operator-=(const Vector2 &o)
    {
      x -= o.x;
      y -= o.y;
    }

    void operator/=(const Vector2 &o)
    {
      x /= o.x;
      y /= o.y;
    }

    void operator+=(float scalar)
    {
      x += scalar;
      y += scalar;
    }

    void operator*=(float scalar)
    {
      x *= scalar;
      y *= scalar;
    }

    void operator-=(float scalar)
    {
      x -= scalar;
      y -= scalar;
    }

    void operator/=(float scalar)
    {
      x /= scalar;
      y /= scalar;
    }

    Vector2 operator+(float scalar)
    {
      Vector2 o;
      o.x = x + scalar;
      o.y = y + scalar;
      return o;
    }

    Vector2 operator*(float scalar)
    {
      Vector2 o;
      o.x = x * scalar;
      o.y = y * scalar;
      return o;
    }

    Vector2 operator-(float scalar)
    {
      Vector2 o;
      o.x = x - scalar;
      o.y = y - scalar;
      return o;
    }

    Vector2 operator/(float scalar)
    {
      Vector2 o;
      o.x = x / scalar;
      o.y = y / scalar;
      return o;
    }

    float Magnitude();
    void Normalize();
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
  };
}
