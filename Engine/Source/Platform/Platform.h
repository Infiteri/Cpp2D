#pragma once

#include "Base.h"
#include "Core/Logger.h"
#include <string>
#include <unordered_map>

namespace Core
{
    struct DynamicLibraryFunction
    {
        std::string Name;
        void *PFN;
    };

    struct DynamicLibrary
    {
        /// @brief Name with no extension.
        std::string Name;
        /// @brief Full name, along side extension. (e.g. NAME.dll on Win32).
        std::string FileName;

        /// @brief Represents if the library is valid or not.
        bool Valid = false;

        /// @brief Internal block of memory.
        void *Internal;

        std::unordered_map<std::string, DynamicLibraryFunction *> Functions;
    };

    class CE_API Platform
    {
    public:
        enum ConsoleColors
        {
            White,
            Gray,
            Red,
            Yellow,
            Blue,
            Green,
        };

        Platform(){};
        ~Platform(){};

        // --------------- LOG ----------------------------
        static void SetConsoleColor(ConsoleColors color);
        static void Log(const char *message);
        // ------------------------------------------------

        // --------------- FILE DIALOGS ------------------
        static std::string OpenFileDialog(const char *filter);
        static std::string SaveFileDialog(const char *filter);
        // ------------------------------------------------

        // --------------- DYNAMIC LIBRARY ---------------

        /// @brief Will populate a library.
        /// @param _name The name with no extension.
        /// @param out The library to populate.
        /// @return BOolean that represents if the library's creation was successful.
        static bool CreateLibrary(const std::string &_name, DynamicLibrary *out);
        static bool LibraryLoadFunction(DynamicLibrary *library, const std::string &functionName);
        static void DestroyLibrary(DynamicLibrary *library);
        template <typename T>
        static T LibraryGetFunction(DynamicLibrary *library, const std::string &funcName)
        {
            if (!library || !library->Valid)
            {
                CE_CORE_ERROR("Platform::LibraryGetFunction: Library not valid when searching for function.");
                return NULL;
            }

            if (!library->Functions[funcName])
            {
                if (!LibraryLoadFunction(library, funcName))
                {
                    CE_CORE_ERROR("Platform::LibraryGetFunction:Unable to load function for library when trying to get it.");
                    return NULL;
                }
            }

            return (T)library->Functions[funcName]->PFN;
        };
        // ------------------------------------------------

        // --------------- MEMORY ------------------------
        static void *MemSet(void *data, int s, int size);
        // --------------- FILE DIALOGS ------------------
    };

}
