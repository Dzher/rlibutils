#include "motioner.h"
#include <iostream>
#include <sstream>

inline void test_forward(const roblib::Motioner& motioner, const std::vector<double>& pos, bool mute = false)
{
    auto res = motioner.getEndEffectorPosByDegree(pos);
    if (res.has_value()) {
        if (mute) {
            return;
        }
        auto endless_trans = res.value();
        std::cout << "Position: " << std::endl;
        for (auto each : endless_trans.position()) {
            std::cout << each << " ";
        }
        std::cout << std::endl;

        std::cout << "Rotation: " << std::endl;
        for (auto each : endless_trans.rotation()) {
            std::cout << each << " ";
        }
        std::cout << std::endl
                  << std::endl;
        return;
    }
    std::cout << "error_occur" << std::endl;
}

inline void test_inverse(const roblib::Motioner& motioner, const roblib::xyzWithQuaternion& transpos)
{
    auto res = motioner.getDegreesByXyzQuat(transpos);
    if (!res.has_value()) {
        std::cout << "Inverse Operation has NO Answer!";
        return;
    }
    std::cout << "inv" << std::endl;
    for (auto each : res.value()) {
        std::cout << each << " ";
    }
    std::cout << std::endl
              << std::endl;
}

inline std::vector<double> readJoints(int dof)
{
    std::vector<double> degrees;
    std::string input;

    std::cout << "Please input " << dof << " Joint Degrees(split by space), or input non-number character exit:" << std::endl;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    double degree;
    while (iss >> degree) {
        degrees.push_back(degree);
    }

    return degrees;
}

inline std::vector<double> readPositions()
{
    std::vector<double> positions;
    std::string input;

    std::cout << "Please input " << 3 << " End Effector Position(split by space), or input non-number character exit:" << std::endl;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    double degree;
    while (iss >> degree) {
        positions.push_back(degree);
    }

    return positions;
}

inline std::vector<double> readQuaternions()
{
    std::vector<double> quaternions;
    std::string input;

    std::cout << "Please input " << 4 << " End Effector Quaternions(split by space), or input non-number character exit:" << std::endl;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    double degree;
    while (iss >> degree) {
        quaternions.push_back(degree);
    }

    return quaternions;
}

inline roblib::Motioner loadModel()
{
    std::string model_path;
    std::cout << "Please input model path..." << std::endl;
    std::getline(std::cin, model_path);
    if (model_path.empty()) {
        model_path = "../xMateCR7.urdf";
    }
    roblib::Motioner motioner(model_path);
    return motioner;
}