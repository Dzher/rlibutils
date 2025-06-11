#pragma once

#include "../common.h"
#include "rl/math/Constants.h"
#include "utils.h"
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::fixed << std::setprecision(6);
    rl::math::Transform transform;
    transform.setIdentity();
    // 先平移操作
    transform.translate(Eigen::Vector3d(1.0, 2.0, 3.0));
    // 再旋转操作，绕Z轴旋转
    transform.rotate(Eigen::AngleAxisd(rl::math::constants::pi / 4, Eigen::Vector3d::UnitZ()));
    // from rl::math::transform to xyzWithQuat
    std::cout << "rlTransform2XyzQuat" << std::endl;
    auto xyz_with_quat = roblib::ModelUtils::rlTransform2XyzQuat(transform);
    std::cout << "x: " << xyz_with_quat.x() << std::endl;
    std::cout << "y: " << xyz_with_quat.y() << std::endl;
    std::cout << "z: " << xyz_with_quat.z() << std::endl;
    std::cout << "qw: " << xyz_with_quat.qw() << std::endl;
    std::cout << "qx: " << xyz_with_quat.qx() << std::endl;
    std::cout << "qy: " << xyz_with_quat.qy() << std::endl;
    std::cout << "qz: " << xyz_with_quat.qz() << std::endl;
    std::cout << "====================================" << std::endl;
    // from rl::math::transform to xyzWithEuler
    std::cout << "rlTransform2XyzEuler" << std::endl;
    auto xyz_with_euler = roblib::ModelUtils::rlTransform2XyzEuler(transform);
    std::cout << "x: " << xyz_with_euler.x() << std::endl;
    std::cout << "y: " << xyz_with_euler.y() << std::endl;
    std::cout << "z: " << xyz_with_euler.z() << std::endl;
    std::cout << "euler-X: " << xyz_with_euler.c() << std::endl;
    std::cout << "euler-Y: " << xyz_with_euler.b() << std::endl;
    std::cout << "euler-Z: " << xyz_with_euler.a() << std::endl;
    std::cout << "====================================" << std::endl;

    auto transform_from_xyzquat = roblib::ModelUtils::xyzQuat2RlTransfrom(xyz_with_quat);
    std::cout << "xyzQuat2RlTransfrom success" << std::endl;
    auto t1 = roblib::ModelUtils::rlTransform2XyzQuat(transform_from_xyzquat);
    std::cout << "x: " << t1.x() << std::endl;
    std::cout << "y: " << t1.y() << std::endl;
    std::cout << "z: " << t1.z() << std::endl;
    std::cout << "qw: " << t1.qw() << std::endl;
    std::cout << "qx: " << t1.qx() << std::endl;
    std::cout << "qy: " << t1.qy() << std::endl;
    std::cout << "qz: " << t1.qz() << std::endl;
    std::cout << "====================================" << std::endl;

    auto transform_from_xyzeuler = roblib::ModelUtils::xyzEuler2RlTransfrom(xyz_with_euler);
    std::cout << "xyzEuler2RlTransfrom success" << std::endl;
    auto t2 = roblib::ModelUtils::rlTransform2XyzEuler(transform_from_xyzeuler);
    std::cout << "x: " << t2.x() << std::endl;
    std::cout << "y: " << t2.y() << std::endl;
    std::cout << "z: " << t2.z() << std::endl;
    std::cout << "euler-X: " << t2.c() << std::endl;
    std::cout << "euler-Y: " << t2.b() << std::endl;
    std::cout << "euler-Z: " << t2.a() << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
