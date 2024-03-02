#pragma once

#include "Base.h"

namespace Core
{
    /// @brief Represents a color using RGBA values in the range of 0 to 255.
    class Color
    {
    public:
        /// Red component of the color, in the range 0 to 255.
        float R;

        /// Green component of the color, in the range 0 to 255.
        float G;

        /// Blue component of the color, in the range 0 to 255.
        float B;

        /// Alpha (transparency) component of the color, in the range 0 to 255.
        float A;

        /// @brief Default constructor, initializes the color to white (255, 255, 255, 255).
        Color();

        /// @brief Constructor that sets the color using RGBA values.
        /// @param r The red component in the range 0 to 255.
        /// @param g The green component in the range 0 to 255.
        /// @param b The blue component in the range 0 to 255.
        /// @param a The alpha (transparency) component in the range 0 to 255.
        Color(float r, float g, float b, float a);

        /// @brief Copy constructor.
        /// @param other The color to copy.
        Color(const Color &other);

        /// @brief Destructor.
        ~Color();

        /// @brief Set the color using RGBA values.
        /// @param r The red component in the range 0 to 255.
        /// @param g The green component in the range 0 to 255.
        /// @param b The blue component in the range 0 to 255.
        /// @param a The alpha (transparency) component in the range 0 to 255.
        void Set(float r, float g, float b, float a);

        /// @brief Set the color using another Color object.
        /// @param color Another Color object whose values will be copied.
        void Set(const Color &color);

        /// @brief Set the color using an array of RGBA values.
        /// @param data An array containing RGBA values.
        /// @param mul An optional multiplier for the values (default is 1).
        void Set(float *data, float mul = 1);

        /// @brief Set the color using another Color object.
        /// @param color Pointer to another Color object whose values will be copied.
        void Set(Color *color);

        /// @brief Will return a new Color object with the RGBA components between 0.0 to 1.0.
        /// @return A new Color object.
        Color Normalized();
    };
}
