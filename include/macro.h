#pragma once

/*====================================================================*/
// when use shared library
// #ifdef _WIN32
//     #ifdef R_LIB_SHARED_EXPORT
//         #define RLIB_API __declspec(dllexport)
//     #else
//         #define RLIB_API __declspec(dllimport)
//     #endif
// #else
//     #define RLIB_API
// #endif
/*====================================================================*/

/*====================================================================*/
// when use static library
#define RLIB_API
/*====================================================================*/
