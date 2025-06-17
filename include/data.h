#pragma once

#include "macro.h"
#include <array>
#include <vector>

namespace roblib {
enum class InverseMethod {
    Jacob,
    Nolpt
};

enum class ModelType {
    RokaeCR7,
    RokaeCR12,
    KawasakiRs013,
    KawasakiRs020,
    KawasakiRs025
};

enum class DeviceMountType {
    Self,
    Left,
    Right,
    Top,
    Back
};

using JointAngles = std::vector<double>;

struct RLIB_API Pos {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

struct RLIB_API Quaternion {
    double qw = 1.0;
    double qx = 0.0;
    double qy = 0.0;
    double qz = 0.0;
};

struct RLIB_API Euler {
    // cba-012-XYZ-RPY
    double c = 1.0; // roll-X-c-0
    double b = 0.0; // pitch-Y-b-1
    double a = 0.0; // yaw-Z-a-2
};

struct RLIB_API xyzWithQuaternion {
    xyzWithQuaternion()
    {
        pos.x = 0.0;
        pos.y = 0.0;
        pos.z = 0.0;
        quat.qw = 1.0;
        quat.qx = 0.0;
        quat.qy = 0.0;
        quat.qz = 0.0;
    }

    xyzWithQuaternion(const std::array<double, 3>& pos,
        const std::array<double, 4>& quat)
    {
        position(pos);
        rotation(quat);
    }

    xyzWithQuaternion identity()
    {
        return { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0, 0.0 } };
    }

    Pos pos;
    void position(std::array<double, 3> xyz)
    {
        pos.x = xyz[0];
        pos.y = xyz[1];
        pos.z = xyz[2];
    }
    std::array<double, 3> position()
    {
        return { pos.x, pos.y, pos.z };
    };
    double x() const { return pos.x; }
    double y() const { return pos.y; }
    double z() const { return pos.z; }

    Quaternion quat;
    void rotation(const std::array<double, 4>& wxyz)
    {
        quat.qw = wxyz[0];
        quat.qx = wxyz[1];
        quat.qy = wxyz[2];
        quat.qz = wxyz[3];
    }
    std::array<double, 4> rotation()
    {
        return { quat.qw, quat.qx, quat.qy, quat.qz };
    };
    double qw() const { return quat.qw; }
    double qx() const { return quat.qx; }
    double qy() const { return quat.qy; }
    double qz() const { return quat.qz; }
};

struct RLIB_API xyzWithEuler {
    xyzWithEuler()
    {
        pos.x = 0.0;
        pos.y = 0.0;
        pos.z = 0.0;
        euler.c = 0.0;
        euler.b = 0.0;
        euler.a = 0.0;
    }

    xyzWithEuler(const std::array<double, 3>& pos,
        const std::array<double, 3>& euler)

    {
        position(pos);
        rotation(euler);
    }

    Pos pos;
    void position(std::array<double, 3> xyz)
    {
        pos.x = xyz[0];
        pos.y = xyz[1];
        pos.z = xyz[2];
    }
    std::array<double, 3> position()
    {
        return { pos.x, pos.y, pos.z };
    };
    double x() const { return pos.x; }
    double y() const { return pos.y; }
    double z() const { return pos.z; }

    Euler euler;
    void rotation(const std::array<double, 3>& cba)
    {
        euler.c = cba[0];
        euler.b = cba[1];
        euler.a = cba[2];
    }
    std::array<double, 3> rotation()
    {
        return { euler.c, euler.b, euler.a };
    };
    double c() const { return euler.c; }
    double b() const { return euler.b; }
    double a() const { return euler.a; }
};
}