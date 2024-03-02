#include "Shader.h"
#include "Core/Logger.h"
#include "Platform/FileSystem.h"

#include <glad/glad.h>
#include <vector>

namespace Core
{
    static CeU32 LoadShader(const char *path, GLenum type)
    {
        // New source casted
        std::string source = FileSystem::ReadFileContent(path);
        const GLchar *newSrc = (const GLchar *)source.c_str();

        CeU32 shader = glCreateShader(type);
        glShaderSource(shader, 1, &newSrc, 0);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            CE_CORE_ERROR("Shader compilation failed.");
            CE_CORE_ERROR("(%s) %s", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog.data());

            glDeleteShader(shader);
            return (GLuint)0;
        }

        return shader;
    };

    Shader::Shader(const std::string &vertex, const std::string &fragment)
    {
        CeU32 vertexShader = LoadShader(vertex.c_str(), GL_VERTEX_SHADER);
        CeU32 fragmentShader = LoadShader(fragment.c_str(), GL_FRAGMENT_SHADER);

        // Compile program
        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        GLint isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
        valid = true;
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(id);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            CE_CORE_ERROR("ProgramError: %s", infoLog.data());

            valid = false;
        }

        // Delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    void Shader::Use()
    {
        glUseProgram(id);
    }

    void Shader::Int(int i, const char *name)
    {
        glUniform1i(GetUniLoc(name), i);
    }

    void Shader::Vec4(float x, float y, float z, float w, const char *name)
    {
        glUniform4f(GetUniLoc(name), x, y, z, w);
    }

    void Shader::Vec4(const Color &color, const char *name)
    {
        Vec4(color.R, color.G, color.B, color.A, name);
    }

    void Shader::Vec4(Color *color, const char *name)
    {
        Vec4(color->R, color->G, color->B, color->A, name);
    }

    void Shader::Vec4(const Vector4 &vec4, const char *name)
    {
        Vec4(vec4.x, vec4.y, vec4.z, vec4.w, name);
    }

    void Shader::Vec4(Vector4 *vec4, const char *name)
    {
        Vec4(vec4->x, vec4->y, vec4->z, vec4->w, name);
    }

    void Shader::Vec3(float x, float y, float z, const char *name)
    {
        glUniform3f(GetUniLoc(name), x, y, z);
    }

    void Shader::Vec3(Vector3 *vec3, const char *name)
    {
        Vec3(vec3->x, vec3->y, vec3->z, name);
    }

    void Shader::Vec3(const Vector3 &vec3, const char *name)
    {
        Vec3(vec3.x, vec3.y, vec3.z, name);
    }

    void Shader::Vec2(float x, float y, const char *name)
    {
        glUniform2f(GetUniLoc(name), x, y);
    }

    void Shader::Vec2(const Vector2 &vec2, const char *name)
    {
        Vec2(vec2.x, vec2.y, name);
    }

    void Shader::Vec2(Vector2 *vec2, const char *name)
    {
        Vec2(vec2->x, vec2->y, name);
    }

    void Shader::Mat4(Matrix4 *m, const char *name)
    {
        int it = GetUniLoc(name);
        glUniformMatrix4fv(GetUniLoc(name), 1, GL_FALSE, m->data);
    }

    void Shader::Mat4(float *data, const char *name)
    {
        int it = GetUniLoc(name);
        glUniformMatrix4fv(GetUniLoc(name), 1, GL_FALSE, data);
    }

    void Shader::Mat4(Matrix4 m, const char *name)
    {
        glUniformMatrix4fv(GetUniLoc(name), 1, false, m.data);
    }

    int Shader::GetUniLoc(const char *name)
    {
        Use();
        return glGetUniformLocation(id, name);
    }
}