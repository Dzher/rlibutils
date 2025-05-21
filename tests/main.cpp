#pragma once

#include "../source/motioner.h"
#include <iomanip>
#include <iostream>

void test_default_pos(roblib::Motioner& motioner)
{
    auto endless_trans = motioner.getEndlessPosition();
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

void test_forward(roblib::Motioner& motioner, const std::vector<double>& pos)
{
    auto res = motioner.getPositonByDegree(pos);
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

int main()
{
    roblib::Motioner motioner("../../tests/xMateCR7.urdf");
    std::cout << "Dof: " << motioner.getDof() << std::endl;
    std::cout << std::fixed << std::setprecision(3);

    test_default_pos(motioner);

    // test forward operations
    // test_forward(motioner, { 0., 0., 0., 0., 0., 0. });
    test_forward(motioner, { 5., 0., 0., 0., 0., 0. });

    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
