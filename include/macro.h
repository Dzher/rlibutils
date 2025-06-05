#pragma once

#ifdef _WIN32
#ifdef R_LIB_UTILS_EXPORTS
#define RLIB_API __declspec(dllexport)
#else
#define RLIB_API __declspec(dllimport)
#endif
#else
#define RLIB_API
#endif