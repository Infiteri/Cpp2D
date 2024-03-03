#pragma once

#include "Base.h"
typedef struct GLFWwindow GLFWwindow;

namespace Core
{
    class Window
    {
    public:
        enum SizeMode
        {
            /// @brief Windowed, X, Y, Width and Height are taken into consideration.
            Normal,

            /// @brief Windowed, X, Y, Width and Height are not taken into consideration but still updated.
            Windowed,

            /// @brief No topbar.
            Fullscreen,
        };

        struct Configuration
        {
            int X;
            int Y;
            int Width;
            int Height;
            const char *Title;
            bool VSync = false;
            SizeMode Mode = Normal;
        };

    private:
        GLFWwindow *handle;
        Configuration state;

    public:
        Window(const Configuration &config);
        ~Window();

        void Update();

        /// @brief Represents weather or not the window is active.
        /// @return Boolean
        bool ShouldRun() const;

        inline GLFWwindow *GetHandle() { return handle; };

        /// @brief A configuration is treated like a state. Props like x, y, width, height, etc are correct and set frame by frame.
        /// @return A pointer to a Window::Configuration object.
        inline Configuration *GetState() { return &state; };

        inline int GetWidth() { return state.Width; };
        inline int GetHeight() { return state.Height; };
    };

}