#pragma once

#include "../common.h"
#include "motioner.h"
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    std::string model_path;
    std::cout << "Please input model path..." << std::endl;
    std::getline(std::cin, model_path);
    if (model_path.empty()) {
        model_path = "../xMateCR7.urdf";
    }
    roblib::Motioner motioner(model_path);
    if (!motioner.isValid()) {
        std::cerr << "Model path invalid, process exit!" << std::endl;
        return 1;
    }

    std::vector<double> degrees;

    while (true) {
        std::vector<double> joints = readJoints(motioner.getDof());

        if (joints.empty() || joints.size() != motioner.getDof()) {
            std::cout << "Process Exit!" << std::endl;
            break;
        }

        test_forward(motioner, joints);
        test_forward(motioner, { 0., 0., 0., 0., 0., 0. }, true);
    }

    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);
}
