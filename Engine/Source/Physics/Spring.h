#pragma once

#include "Base.h"
#include "PhysicsBody.h"

namespace Core
{
    class Spring
    {
    public:
        PhysicsBody *Point;
        PhysicsBody *Target;

        float SpringConstant;
        float RestLength;

        /// @brief Spring system (very unstable).
        /// Point - The Body at witch the spring is positioned
        /// Target - The Body to affect
        /// For more stable simulations use ultra low damping values for the Target Material
        Spring();
        ~Spring();

        void Update();
    };
}