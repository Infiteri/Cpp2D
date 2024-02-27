#include "FileSystem.h"
#include "Core/Logger.h"

namespace Core
{
    std::string FileSystem::ReadFileContent(const std::string &filename)
    {
        // Read files
        std::string result;
        std::ifstream in(filename, std::ios::in | std::ios::binary);

        if (in)
        {

            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            CE_CORE_ERROR("Unable to read file content:  %s", filename.c_str());
            result = "";
        }

        return result;
    }
}