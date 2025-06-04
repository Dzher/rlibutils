#pragma once

#include "../common.h"
#include "motioner.h"
#include <iomanip>
#include <iostream>

int main()
{
    roblib::Motioner motioner("../xMateCR7.urdf");
    std::cout << std::fixed << std::setprecision(6);

    // test forward operations
    test_forward(motioner, { 5., 5., 0., 0., 0., 0. });

    // save end position after forward
    auto end_position = motioner.getEndEffectorQuatPos();

    // reset the robotic end positon
    test_forward(motioner, { 0., 0., 0., 0., 0., 0. });

    // test inverse operations
    test_inverse(motioner, end_position);

    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
