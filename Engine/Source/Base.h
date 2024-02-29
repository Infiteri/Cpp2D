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
#pragma CE_VERSION "0.0.2 - 29.02.2024"