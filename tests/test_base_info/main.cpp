#pragma once

#include "motioner.h"
#include <iomanip>
#include <iostream>

void test_get_current_endpos(const roblib::Motioner& motioner)
{
    auto endless_trans = motioner.getEndEffectorQuatPos();
    std::cout << "position: " << std::endl;
    for (auto each : endless_trans.position()) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;

    std::cout << "rotation: " << std::endl;
    for (auto each : endless_trans.rotation()) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;
}

void test_get_current_joint_degree(const roblib::Motioner& motioner)
{
    auto joint_degrees = motioner.getJointDegree();
    std::cout << "model joint degrees: " << std::endl;
    for (auto each : joint_degrees) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    roblib::Motioner motioner("../xMateCR7.urdf");
    std::cout << "Dof: " << motioner.getDof() << std::endl;
    std::cout << "Operation Dof: " << motioner.getOperationDof() << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    // test get model infos
    std::cout << "current end effector" << std::endl;
    test_get_current_endpos(motioner);
    test_get_current_joint_degree(motioner);
}
