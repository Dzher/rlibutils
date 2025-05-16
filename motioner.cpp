#include "motioner.h"
#include "model_utils.h"
#include <iostream>
#include <rl/math/Transform.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Model.h>

using namespace roblib;

struct roblib::MotionerPrivate {
    rl::mdl::Model* model = nullptr;
};

Motioner::Motioner(const std::string& model_file_path)
    : d_(new MotionerPrivate)
{
    d_->model = ModelUtils::isUrdfFile(model_file_path) ? ModelUtils::getModelFromUrdf(model_file_path) : ModelUtils::getModelFromXml(model_file_path);
}

int Motioner::getDof()
{
    return d_->model->getDof();
}

void Motioner::getPositonByDegree(const std::vector<double>& joint_degrees)
{
    if (joint_degrees.size() != getDof()) {
        return;
    }

    rl::math::Vector position;
    for (auto& each_degree : joint_degrees) {
        position << each_degree * rl::math::RAD2DEG;
    }
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform endless_pos = kin_model->getOperationalPosition(0);
    std::cout << endless_pos.translation().transpose() << std::endl;
}

void Motioner::getPositonByRadian(const std::vector<double>& joint_radians)
{
    if (joint_radians.size() != getDof()) {
        return;
    }

    rl::math::Vector position;
    for (auto& each_degree : joint_radians) {
        position << each_degree;
    }
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform endless_pos = kin_model->getOperationalPosition(0);
    std::cout << endless_pos.translation().transpose() << std::endl;
}