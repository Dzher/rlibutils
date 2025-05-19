#pragma once

#include <array>

namespace roblib {
struct TransformPos {
    std::array<double, 3> translation = { 0.0, 0.0, 0.0 };
    std::array<double, 4> rotation = { 1.0, 0.0, 0.0, 0.0 };

    TransformPos() = default;
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
};
}