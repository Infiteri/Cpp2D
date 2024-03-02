#pragma once

#include "Base.h"
#include "Renderer/Color.h"
#include "Math/Matrix4.h"
#include "Math/Vectors.h"
#include <string>

namespace Core
{
    class CE_API Shader
    {
    private:
        CeU32 id;
        bool valid = false;

        int GetUniLoc(const char *name);

    public:
        Shader(const std::string &vertexShader, const std::string &fragmentShader);
        ~Shader();

        void Use();

        /// @brief Will upload an integer to the passed in uniform.
        /// @param i The integer to upload.
        /// @param name Uniform name.
        void Int(int i, const char *name);

        void Vec4(const Color &color, const char *name);
        void Vec4(Color *color, const char *name);
        void Vec4(float x, float y, float z, float w, const char *name);
        void Vec4(const Vector4 &vec4, const char *name);
        void Vec4(Vector4 *vec4, const char *name);

        void Vec3(float x, float y, float z, const char *name);
        void Vec3(const Vector3 &vec3, const char *name);
        void Vec3(Vector3 *vec3, const char *name);

        void Vec2(float x, float y, const char *name);
        void Vec2(const Vector2 &vec2, const char *name);
        void Vec2(Vector2 *vec2, const char *name);

        void Mat4(Matrix4 *m, const char *name);
        void Mat4(Matrix4 m, const char *name);
        void Mat4(float *data, const char *name);

        inline CeU32 GetID() { return id; };
        inline bool IsValid() { return valid; };
    };
}