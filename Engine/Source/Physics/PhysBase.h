#pragma once

#include "Core/Engine.h"

#define CE_GRAVITY_SCALE 1.0f

///@brief Scale down for more accurate and slow results
#define CE_DELTA_SCALE_DOWN 2.0f

#define CE_DELTA_PHYSICS Engine::GetDeltaTime() / CE_DELTA_SCALE_DOWN