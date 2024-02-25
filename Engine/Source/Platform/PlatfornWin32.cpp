#include "Platform.h"

#if CE_PLATFORM_WIN32 == 1

#include <Windows.h>

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
}

#endif