#pragma once

#include "Base.h"

#include <string>
#include <fstream>

namespace Core
{
    class CE_API FileSystem
    {
    public:
        FileSystem(){};
        ~FileSystem(){};

        static std::string ReadFileContent(const std::string &filename);
    };

}