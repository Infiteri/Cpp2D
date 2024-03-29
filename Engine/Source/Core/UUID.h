#pragma once

#include "Base.h"

namespace Core
{
    class CE_API UUID
    {
    private:
        CeU64 id;

    public:
        UUID();
        UUID(CeU64 id);
        UUID(const UUID &) = default;
        ~UUID();

        operator CeU64() const { return id; };
        bool operator==(const UUID &o) { return Get() == o.Get(); };

        inline void Set(CeU64 newID) { id = newID; };

        inline CeU64 Get() const
        {
            return id;
        };
    };
}