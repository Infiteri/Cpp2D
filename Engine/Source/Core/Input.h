#pragma once

#include "Base.h"
#include "Math/Vectors.h"

namespace Core
{
    /// @brief Keys
    enum class Keys
    {
        // Printable keys
        Space = 32,
        Apostrophe = 39, // '
        Comma = 44,      // ,
        Minus = 45,      // -
        Period = 46,     // .
        Slash = 47,      // /
        Key0 = 48,
        Key1 = 49,
        Key2 = 50,
        Key3 = 51,
        Key4 = 52,
        Key5 = 53,
        Key6 = 54,
        Key7 = 55,
        Key8 = 56,
        Key9 = 57,
        Semicolon = 59, // ;
        Equal = 61,     // =
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftBracket = 91,  // [
        Backslash = 92,    //
        RightBracket = 93, // ]
        GraveAccent = 96,  // `

        // Function keys
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        // Keypad
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        // Modifiers
        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,

        // Miscellaneous
        Menu = 348
    };

    enum class Buttons
    {
        Left = 0,
        Right = 1,
        Middle = 2
    };

    enum MouseMode
    {
        Visible,
        Hidden,
        Locked
    };

    class CE_API Input
    {
    public:
        Input(){};
        ~Input(){};

        static void Init();
        static void Shutdown();

        /// @brief Will return weather or not the passed in key is pressed.
        /// @param key The key.
        /// @return Boolean
        static bool GetKey(Keys key);

        /// @brief Will return weather or not the passed in button is pressed.
        /// @param button The button.
        /// @return Boolean
        static bool GetButton(Buttons button);

        /// @brief Will set the mouse mode.
        /// @param mode The mouse mode to set.
        static void SetMouseMode(MouseMode mode);

        /// @brief Will return the current mouse position in the window.
        /// @return Vector2 class.
        static Vector2 GetMousePosition();

        /// @brief Will return the current mouse delta (current position - last position) in the window.
        /// @return Vector2 class.
        static Vector2 GetMouseDelta();

        /// @brief Will set the cursor position on screen. Keep in mind it is relative to the window.
        /// @param vector A vector to represent its new position on screen.
        static void SetMousePosition(const Vector2 &vector);

        /// @brief Will return if the current key is just pressed now.
        /// @param key The key to check for.
        /// @return True if pressed, otherwise false.
        static bool GetKeyJustNow(Keys key);

        /// @brief Will return the mouse wheel delta.
        /// @return Floating point number.
        static float GetMouseWheelDelta();

        static void InternalUpdate();
    };

    void InputUpdateKey(Keys key, bool pressed);
    void InputUpdateButton(Buttons button, bool pressed);
    void InputUpdateMouse(int x, int y);
    void InputUpdateScroll(int x, int y);

}