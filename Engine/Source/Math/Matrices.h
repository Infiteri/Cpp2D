#pragma once

#include "Base.h"
#include "Vectors.h"

namespace Core
{
    /// @brief A 3x3 matrix used for rigid bodies.
    /// @attention THIS IS A ENGINE ONLY FEATURE, NOT MEANT TO BE USED (YET)
    class CE_API Matrix3
    {
    public:
        Matrix3();
        Matrix3(float *dataParameters);
        ~Matrix3();
        float data[9];

        float operator[](int index)
        {
            return data[index];
        };

        Matrix3 operator*(const Matrix3 &o)
        {
            Matrix3 m;

            m.data[0] = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
            m.data[1] = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
            m.data[2] = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
            m.data[3] = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
            m.data[4] = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
            m.data[5] = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
            m.data[6] = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
            m.data[7] = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
            m.data[8] = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];

            return m;
        }

        void SetInverse(const Matrix3 &m);
        Matrix3 Inverse();
        void Invert();
    };

    /// @brief A 4x3 matrix used in rigid body math, especially its transform.
    /// @attention THIS IS A ENGINE ONLY FEATURE, NOT MEANT TO BE USED (YET)
    class Matrix4x3
    {
    public:
        Matrix4x3();
        ~Matrix4x3();
        float data[12];

        float operator[](int index)
        {
            return data[index];
        };

        Matrix4x3 operator*(const Matrix4x3 &o) const
        {
            Matrix4x3 result;
            result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) +
                             (o.data[8] * data[2]);
            result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) +
                             (o.data[8] * data[6]);
            result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) +
                             (o.data[8] * data[10]);
            result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) +
                             (o.data[9] * data[2]);
            result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) +
                             (o.data[9] * data[6]);
            result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) +
                             (o.data[9] * data[10]);
            result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) +
                             (o.data[10] * data[2]);
            result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) +
                             (o.data[10] * data[6]);
            result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) +
                              (o.data[10] * data[10]);
            result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) +
                             (o.data[11] * data[2]) + data[3];
            result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) +
                             (o.data[11] * data[6]) + data[7];
            result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) +
                              (o.data[11] * data[10]) + data[11];
            return result;
        }

        Vector3 GetAxisVector3(int i) const
        {
            return Vector3(data[i], data[i + 4], data[i + 8]);
        }

        Vector2 GetAxisVector2(int i) const
        {
            return Vector2(data[i], data[i + 4]);
        }
    };

    /// @brief A 4x4 matrix used in general math.
    class CE_API Matrix4
    {
    public:
        Matrix4();
        ~Matrix4();

        float data[16];
        void From(Matrix4 *other);
        void From(Matrix4 other);
        void From(float *data);

        float operator[](int index)
        {
            return data[index];
        };

        Matrix4 operator*(const Matrix4 &other)
        {
            Matrix4 o;
            o.From(other);
            return Matrix4::Multiply(this, &o);
        };

        static Matrix4 Identity();
        static Matrix4 Empty();

        // WIP: Projections and transformations

        static Matrix4 Perspective(float fov, float aspect, float near, float far);
        static Matrix4 Ortho(float left, float right, float top, float bottom, float near, float far);
        static Matrix4 Translate(float x, float y, float z);
        static Matrix4 Translate(Vector3 *vec);

        static Matrix4 Multiply(Matrix4 *a, Matrix4 *b);
        static Matrix4 Invert(Matrix4 *a);

        static Matrix4 Multiply(Matrix4 a, Matrix4 b);
        static Matrix4 Invert(Matrix4 a);

        static Matrix4 RotationXYZ(Vector3 vec);
        static Matrix4 RotationXYZ(Vector3 *vec);
        static Matrix4 RotationXYZ(float rotationX, float rotationY, float rotationZ);

        static Matrix4 RotationZYX(Vector3 vec);
        static Matrix4 RotationZYX(Vector3 *vec);
        static Matrix4 RotationZYX(float rotationX, float rotationY, float rotationZ);

        static Matrix4 RotationX(float rotation);
        static Matrix4 RotationY(float rotation);
        static Matrix4 RotationZ(float rotation);

        static Vector3 Forward(Matrix4 mat);
        static Vector3 Forward(Matrix4 *mat);

        static Vector3 Right(Matrix4 mat);
        static Vector3 Right(Matrix4 *mat);

        static Matrix4 Scale(Vector3 *vec);
        static Matrix4 Scale(float x, float y, float z);
    };
}