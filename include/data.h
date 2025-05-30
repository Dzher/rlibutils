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

struct RLIB_API Pos {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

struct RLIB_API Quaternion {
    double q1 = 1.0;
    double q2 = 0.0;
    double q3 = 0.0;
    double q4 = 0.0;
};

struct RLIB_API Euler {
    double c = 1.0; // roll
    double b = 0.0; // pitch
    double a = 0.0; // yaw
};

struct RLIB_API xyzWithQuaternion {
    xyzWithQuaternion()
    {
        pos.x = 0.0;
        pos.y = 0.0;
        pos.z = 0.0;
        quat.q1 = 1.0;
        quat.q2 = 0.0;
        quat.q3 = 0.0;
        quat.q4 = 0.0;
    }

    xyzWithQuaternion(const std::array<double, 3>& pos,
        const std::array<double, 4>& quat)
    {
        positon(pos);
        rotation(quat);
    }

    xyzWithQuaternion identity()
    {
        return { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0, 0.0 } };
    }

    Pos pos;
    void positon(std::array<double, 3> xyz)
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
    void rotation(const std::array<double, 4>& q4)
    {
        quat.q1 = q4[0];
        quat.q2 = q4[1];
        quat.q3 = q4[2];
        quat.q4 = q4[3];
    }
    std::array<double, 4> rotation()
    {
        return { quat.q1, quat.q2, quat.q3, quat.q4 };
    };
    double q1() const { return quat.q1; }
    double q2() const { return quat.q2; }
    double q3() const { return quat.q3; }
    double q4() const { return quat.q4; }
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