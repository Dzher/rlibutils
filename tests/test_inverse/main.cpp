#pragma once

#include "../common.h"
#include "motioner.h"
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    auto motioner = loadModel();
    if (!motioner.isValid()) {
        std::cerr << "Model path invalid, process exit!" << std::endl;
        return 1;
    }

    std::vector<double> degrees;

    while (true) {
        std::vector<double> positions = readPositions();
        if (positions.empty() || positions.size() != 3) {
            std::cout << "Process Exit!" << std::endl;
            break;
        }

        std::vector<double> quaternions = readQuaternions();
        if (quaternions.empty() || quaternions.size() != 4) {
            std::cout << "Process Exit!" << std::endl;
            break;
        }

        roblib::xyzWithQuaternion new_pos;
        new_pos.pos.x = positions[0];
        new_pos.pos.y = positions[1];
        new_pos.pos.z = positions[2];
        new_pos.quat.q1 = quaternions[0];
        new_pos.quat.q2 = quaternions[1];
        new_pos.quat.q3 = quaternions[2];
        new_pos.quat.q4 = quaternions[3];

        test_inverse(motioner, new_pos);
    }

    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
