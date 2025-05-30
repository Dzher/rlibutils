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

#include <array>

namespace roblib {
struct RLIB_API TransformPos {
    TransformPos()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        q1 = 1.0;
        q2 = 0.0;
        q3 = 0.0;
        q4 = 0.0;
    }

    TransformPos(const std::array<double, 3>& pos,
        const std::array<double, 4>& quat)
        : translation(pos)
        , rotation(quat)
    {
    }

    TransformPos identity()
    {
        return { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0, 0.0 } };
    }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    std::array<double, 3> translation = { x, y, z };

    double q1 = 1.0;
    double q2 = 0.0;
    double q3 = 0.0;
    double q4 = 0.0;
    std::array<double, 4> rotation = { q1, q2, q3, q4 };
};
}