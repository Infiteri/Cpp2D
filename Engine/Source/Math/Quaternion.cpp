#include "Quaternion.h"

namespace Core
{
    Quaternion::Quaternion()
    {
        Set(1, 0, 0, 0);
    }

    Quaternion::Quaternion(float r, float i, float j, float k)
    {
        Set(r, i, j, k);
    }

    Quaternion::Quaternion(const Quaternion &other)
    {
        Set(other);
    }

    Quaternion::~Quaternion() {}

    void Quaternion::Set(float r, float i, float j, float k)
    {
        this->r = r;
        this->i = i;
        this->j = j;
        this->k = k;
    }
}