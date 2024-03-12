#pragma once

#include "Base.h"
#include <string>

namespace Core
{
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

        // --------------- MEMORY ------------------------
        static void *MemSet(void *data, int s, int size);
        // --------------- FILE DIALOGS ------------------
    };
}
