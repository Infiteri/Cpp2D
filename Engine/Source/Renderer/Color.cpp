#include "Color.h"

namespace Core
{
    Color::Color()
    {
        Set(255, 255, 255, 255);
    }

    Color::Color(float r, float g, float b, float a)
    {
        Set(r, g, b, a);
    }

    Color::Color(const Color &other)
    {
        Set(other);
    }

    Color::~Color()
    {
    }

    void Color::Set(float r, float g, float b, float a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    void Color::Set(const Color &color)
    {
        Set(color.R, color.G, color.B, color.A);
    }

    void Color::Set(float *data, float mul)
    {
        Set(data[0] * mul, data[1] * mul, data[2] * mul, data[3] * mul);
    }

    void Color::Set(Color *color)
    {
        Set(color->R, color->G, color->B, color->A);
    }

    Color Color::Normalized()
    {
        return {R / 255, G / 255, B / 255, A / 255};
    }
}