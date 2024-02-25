#pragma once

#include "Base.h"

namespace Core
{
    class Platform
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

        static void SetConsoleColor(ConsoleColors color);
        static void Log(const char *message);

        static void *MemSet(void *data, int s, int size);
    };
}
