#include "motioner.h"
#include "utils.h"
#include <iostream>
#include <rl/math/Transform.h>
#include <rl/mdl/JacobianInverseKinematics.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Model.h>
#include <rl/mdl/NloptInverseKinematics.h>

using namespace roblib;

struct roblib::MotionerPrivate {
    rl::mdl::Model* model = nullptr;
};

Motioner::Motioner(const std::string& model_file_path)
    : d_(new MotionerPrivate)
{
    d_->model = ModelUtils::isUrdfFile(model_file_path) ? ModelUtils::getModelFromUrdf(model_file_path) : ModelUtils::getModelFromXml(model_file_path);
}

Motioner::~Motioner()
{
    delete d_->model;
    delete d_;
}

int Motioner::getDof()
{
    return d_->model->getDof();
}

TransformPos Motioner::getEndEffectorPos()
{
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);
    rl::math::Transform endless_pos = kin_model->getOperationalPosition(0);
    return ModelUtils::rlTransform2TransfromPos(endless_pos);
}

std::vector<double> Motioner::getJointDegree()
{
    std::vector<double> res;
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);

    for (int i = 0; i < kin_model->getPosition().size(); ++i) {
        res.push_back(kin_model->getPosition()[i]);
    }
    return res;
}

std::optional<TransformPos> Motioner::getEndEffectorPosByDegree(const std::vector<double>& joint_degrees)
{
    if (joint_degrees.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (auto& each_degree : joint_degrees) {
        position << each_degree * rl::math::RAD2DEG;
    }
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform endless_pos = kin_model->getOperationalPosition(0);

    TransformPos res;
    const auto& t = endless_pos.translation();
    res.translation = { t.x(), t.y(), t.z() };

    Eigen::Quaterniond q(endless_pos.linear());
    res.rotation = { q.w(), q.x(), q.y(), q.z() };
    return res;
}

std::optional<TransformPos> Motioner::getEndEffectorPosByRadian(const std::vector<double>& joint_radians)
{
    if (joint_radians.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (auto& each_degree : joint_radians) {
        position << each_degree;
    }
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform endless_pos = kin_model->getOperationalPosition(0);

    return ModelUtils::rlTransform2TransfromPos(endless_pos);
}

std::vector<double> Motioner::getDegreesByTransfromPos(const TransformPos& target)
{
    auto trans = ModelUtils::transformPos2RlTransfrom(target);
    auto kin_model = dynamic_cast<rl::mdl::Kinematic*>(d_->model);

    rl::mdl::JacobianInverseKinematics ik(kin_model);
    ik.goals.push_back({ trans, 0 });

    std::vector<double> res;

    if (ik.solve()) {
        std::cout << "q: " << kin_model->getPosition().transpose() << std::endl;

        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            res.push_back(kin_model->getPosition()[i]);
        }
    }
    return res;

    // kin_model->forwardPosition();
    // position = kin_model->getOperationalPosition(0).translation();
    // orientation = kin_model->getOperationalPosition(0).rotation().eulerAngles(2, 1, 0).reverse();
}

// std::vector<double> Motioner::getRadiansByTransfromPos(const TransformPos& target) { }