#include "Platform.h"

#if CE_PLATFORM_WIN32 == 1

#include "Core/Engine.h"
#include "Core/Logger.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <commdlg.h>
#include <shlwapi.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Core
{
    void *Platform::MemSet(void *data, int s, int size)
    {
        return memset(data, s, size);
    }

    void Platform::SetConsoleColor(ConsoleColors color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD colorAttribute = FOREGROUND_INTENSITY; // Default to high-intensity (bright) text

        switch (color)
        {
        case White:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case Gray:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case Red:
            colorAttribute |= FOREGROUND_RED;
            break;

        case Blue:
            colorAttribute |= FOREGROUND_BLUE;
            break;

        case Green:
            colorAttribute |= FOREGROUND_GREEN;
            break;

        case Yellow:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN;
            break;

        default:
            // Default to white if an unsupported color is specified
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        }

        SetConsoleTextAttribute(hConsole, colorAttribute);
    }

    void Platform::Log(const char *message)
    {
        OutputDebugStringA(message);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD bytesWritten;
        WriteConsoleA(hConsole, message, strlen(message), &bytesWritten, NULL);
    }

    std::string Platform::OpenFileDialog(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;

        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }

    std::string Platform::SaveFileDialog(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        // Sets the default extension by extracting it from the filter
        ofn.lpstrDefExt = strchr(filter, '\0') + 1;

        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }

    bool Platform::CreateLibrary(const std::string &_name, DynamicLibrary *out)
    {
        if (_name.empty())
        {
            out->Valid = false;
            CE_CORE_ERROR("Platform::CreateLibrary: Unable to create a library with no name.");
            return false;
        }

        HMODULE mod = LoadLibrary((_name + ".dll").c_str());
        if (mod == NULL)
        {
            out->Valid = false;
            CE_CORE_ERROR("Platform::CreateLibrary: Unable to create a library with name '%s'.", _name.c_str());
            return false;
        }

        out->Valid = true;
        out->Name = _name;
        out->FileName = _name + ".dll";
        out->Internal = mod;

        return true;
    }

    bool Platform::LibraryLoadFunction(DynamicLibrary *library, const std::string &functionName)
    {
        if (!library || !library->Valid || library->Functions[functionName] != nullptr)
        {
            CE_CORE_ERROR("Platform::LibraryLoadFunction: Invalid library.");
            return false;
        }

        FARPROC f_addr = GetProcAddress((HMODULE)library->Internal, functionName.c_str());
        if (!f_addr)
        {
            CE_CORE_ERROR("Platform::LibraryLoadFunction: Invalid function under name '%s'.", functionName.c_str());
            return false;
        }

        DynamicLibraryFunction *f = new DynamicLibraryFunction;
        f->PFN = (void *)f_addr;
        f->Name = functionName;
        library->Functions[functionName] = f;

        return true;
    }

    void Platform::DestroyLibrary(DynamicLibrary *library)
    {
        if (!library || !library->Valid || library->Name.empty())
            return;

        for (auto it = library->Functions.begin(); it != library->Functions.end(); it++)
            delete it->second;

        library->Functions.clear();

        FreeLibrary((HMODULE)library->Internal);

        // Clear
        library->Name = "";
        library->FileName = "";
        library->Internal = NULL;
        library->Valid = false;
    }
}

#endif