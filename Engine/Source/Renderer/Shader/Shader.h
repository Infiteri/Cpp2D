#pragma once

#include "Base.h"
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

        inline CeU32 GetID() { return id; };
        inline bool IsValid() { return valid; };
    };
}