#pragma once

#include "Base.h"
#include "Core/Engine.h"
#include "PhysicsEngine.h"

#define CE_FPS_CALCULATION PhysicsEngine::GetValueSet()->FPS // Keep it small, directly impacts the engine

#define CE_FPS_DIVISION_FACTOR 60

#define CE_DELTA_TIME (Core::Engine::GetDeltaTime())

#define CE_PHYSICS_DELTA_TIME (Core::Engine::GetDeltaTime() / (CE_FPS_CALCULATION / CE_FPS_DIVISION_FACTOR))