#pragma once

#include "data.h"
#include <optional>
#include <string>
#include <vector>

namespace roblib {

struct MotionerPrivate;

class Motioner {
public:
    explicit Motioner(const std::string& model_file_path);

    int getDof();
    TransformPos getEndlessPosition();
    // Forward Kinematics
    std::optional<TransformPos> getPositonByDegree(const std::vector<double>& joint_degrees);
    std::optional<TransformPos> getPositonByRadian(const std::vector<double>& joint_radians);

    // Inverse Kinematics
    std::vector<double> getDegreesByTransfromPos(const TransformPos& target);
    // std::vector<double> getRadiansByTransfromPos(const TransformPos& target);

private:
    MotionerPrivate* d_ = nullptr;
};
}