#pragma once

//? Type definition
typedef unsigned char CeU8;
typedef unsigned short CeU16;
typedef unsigned int CeU32;
typedef unsigned long long CeU64;

// ? Platform definition
#define CE_PLATFORM_WIN32 0

#ifdef __WIN32
#undef CE_PLATFORM_WIN32
#define CE_PLATFORM_WIN32 1
#endif

//? Export definition
#if CE_PLATFORM_WIN32 == 1
#ifdef CE_BUILD_DLL
#define CE_API __declspec(dllexport)
#else
#define CE_API __declspec(dllimport)
#endif
#endif

/// @brief MAJOR.MINOR.ULTRA_MINOR - DD.MM.YYYY
#pragma CE_VERSION "0.1.1 - 26.03.2024"

#define CE_ACTOR_SCRIPT_DEFINE(className) \
    extern "C" __declspec(dllexport) Core::ActorScript *className##Create() { return new className(); }
