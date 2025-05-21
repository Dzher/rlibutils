#pragma once

#include "../source/motioner.h"
#include <iomanip>
#include <iostream>

void test_get_current_endpos(roblib::Motioner& motioner)
{
    auto endless_trans = motioner.getEndEffectorPos();
    std::cout << "translation: " << std::endl;
    for (auto each : endless_trans.translation) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;

    std::cout << "rotation: " << std::endl;
    for (auto each : endless_trans.rotation) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;
}

void test_get_current_joint_degree(roblib::Motioner& motioner)
{
    auto joint_degrees = motioner.getJointDegree();
    std::cout << "model joint degrees: " << std::endl;
    for (auto each : joint_degrees) {
        std::cout << each << ", ";
    }
    std::cout << std::endl;
}

void test_forward(roblib::Motioner& motioner, const std::vector<double>& pos)
{
    auto res = motioner.getEndEffectorPosByDegree(pos);
    if (res.has_value()) {
        auto endless_trans = res.value();
        std::cout << "translation: " << std::endl;
        for (auto each : endless_trans.translation) {
            std::cout << each << ", ";
        }
        std::cout << std::endl;

        std::cout << "rotation: " << std::endl;
        for (auto each : endless_trans.rotation) {
            std::cout << each << ", ";
        }
        std::cout << std::endl;
        return;
    }
    std::cout << "error_occur" << std::endl;
}

void test_inverse(roblib::Motioner& motioner, const roblib::TransformPos& transpos)
{
    motioner.getDegreesByTransfromPos(transpos);
}

int main()
{
    roblib::Motioner motioner("../../tests/xMateCR7.urdf");
    std::cout << "Dof: " << motioner.getDof() << std::endl;
    std::cout << std::fixed << std::setprecision(3);

    // test get model infos
    test_get_current_endpos(motioner);
    test_get_current_joint_degree(motioner);

    // test forward operations
    test_forward(motioner, { 0., 0., 0., 0., 0., 0. });
    test_forward(motioner, { 5., 0., 0., 0., 0., 0. });

    // test inverse operations
    test_inverse(motioner, roblib::TransformPos().identity());

    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
