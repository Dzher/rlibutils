#include "motioner.h"
#include "utils.h"
#include <rl/math/Constants.h>
#include <rl/math/Transform.h>
#include <rl/mdl/JacobianInverseKinematics.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Model.h>
#include <rl/mdl/NloptInverseKinematics.h>
using namespace roblib;

struct roblib::MotionerPrivate {
    std::shared_ptr<rl::mdl::Model> model = nullptr;
};

Motioner::Motioner(const std::string& model_file_path)
    : d_(new MotionerPrivate)
{
    d_->model = ModelUtils::isUrdfFile(model_file_path) ? ModelUtils::getModelFromUrdf(model_file_path) : ModelUtils::getModelFromXml(model_file_path);
}

Motioner::Motioner(const Motioner& other)
{
    d_ = new MotionerPrivate;
    d_->model = other.d_->model;
}

Motioner::~Motioner()
{
    delete d_;
}

bool Motioner::isValid() const
{
    return d_->model != nullptr;
}

int Motioner::getDof() const
{
    return d_->model->getDof();
}

int Motioner::getOperationDof() const
{
    return d_->model->getOperationalDof();
}

xyzWithQuaternion Motioner::getEndEffectorQuatPos() const
{
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);
    return ModelUtils::rlTransform2XyzQuat(end_effector_pos);
}

xyzWithEuler Motioner::getEndEffectorEulerPos() const
{
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);
    return ModelUtils::rlTransform2XyzEuler(end_effector_pos);
}

std::vector<double> Motioner::getJointDegree() const
{
    std::vector<double> res;
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    for (int i = 0; i < kin_model->getPosition().size(); ++i) {
        res.push_back(kin_model->getPosition()[i]);
    }
    return res;
}

std::optional<xyzWithQuaternion> Motioner::getEndEffectorQuatPosByDegree(const std::vector<double>& joint_degrees) const
{
    if (joint_degrees.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (int i = 0; i < position.size(); ++i) {
        position[i] = joint_degrees[i] * rl::math::constants::deg2rad;
    }
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);

    return ModelUtils::rlTransform2XyzQuat(end_effector_pos);
}

std::optional<xyzWithQuaternion> Motioner::getEndEffectorQuatPosByRadian(const std::vector<double>& joint_radians) const
{
    if (joint_radians.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (int i = 0; i < position.size(); ++i) {
        position[i] = joint_radians[i];
    }
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);

    return ModelUtils::rlTransform2XyzQuat(end_effector_pos);
}

std::optional<xyzWithEuler> Motioner::getEndEffectorEulerPosByDegree(const std::vector<double>& joint_degrees) const
{
    if (joint_degrees.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (int i = 0; i < position.size(); ++i) {
        position[i] = joint_degrees[i] * rl::math::constants::deg2rad;
    }
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);
    kin_model->getPosition();

    return ModelUtils::rlTransform2XyzEuler(end_effector_pos);
}

std::optional<xyzWithEuler> Motioner::getEndEffectorEulerPosByRadian(const std::vector<double>& joint_radians) const
{
    if (joint_radians.size() != getDof()) {
        return std::nullopt;
    }

    rl::math::Vector position { getDof() };
    for (int i = 0; i < position.size(); ++i) {
        position[i] = joint_radians[i];
    }
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    kin_model->setPosition(position);
    kin_model->forwardPosition();

    rl::math::Transform end_effector_pos = kin_model->getOperationalPosition(0);

    return ModelUtils::rlTransform2XyzEuler(end_effector_pos);
}

std::optional<std::vector<double>> Motioner::getDegreesByXyzQuat(const xyzWithQuaternion& target, InverseMethod method) const
{
    auto trans = ModelUtils::xyzQuat2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    std::unique_ptr<rl::mdl::InverseKinematics> ik;
    if (method == InverseMethod::Jacob) {
        ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    ik->addGoal({ trans, 0 });

    if (ik->solve()) {
        std::vector<double> res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            res.push_back(kin_model->getPosition()[i] * rl::math::constants::rad2deg);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<std::vector<double>> Motioner::getRadiansByXyzQuat(const xyzWithQuaternion& target, InverseMethod method) const
{
    auto trans = ModelUtils::xyzQuat2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    std::unique_ptr<rl::mdl::InverseKinematics> ik;
    if (method == InverseMethod::Jacob) {
        ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    ik->addGoal({ trans, 0 });

    if (ik->solve()) {
        std::vector<double> res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            res.push_back(kin_model->getPosition()[i]);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<std::vector<double>> Motioner::getDegreesByXyzEuler(const xyzWithEuler& target, InverseMethod method) const
{
    auto trans = ModelUtils::xyzEuler2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    std::unique_ptr<rl::mdl::InverseKinematics> ik;
    if (method == InverseMethod::Jacob) {
        ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    ik->addGoal({ trans, 0 });

    if (ik->solve()) {
        std::vector<double> res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            res.push_back(kin_model->getPosition()[i] * rl::math::constants::rad2deg);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<std::vector<double>> Motioner::getRadiansByXyzEuler(const xyzWithEuler& target, InverseMethod method) const
{
    auto trans = ModelUtils::xyzEuler2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    std::unique_ptr<rl::mdl::InverseKinematics> ik;
    if (method == InverseMethod::Jacob) {
        ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    ik->addGoal({ trans, 0 });

    if (ik->solve()) {
        std::vector<double> res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            res.push_back(kin_model->getPosition()[i]);
        }
        return res;
    }
    return std::nullopt;
}