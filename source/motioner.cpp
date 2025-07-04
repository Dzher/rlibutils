#include "motioner.h"
#include "utils.h"
#include <cmath>
#include <iostream>
#include <rl/math/Constants.h>
#include <rl/math/Transform.h>
#include <rl/mdl/JacobianInverseKinematics.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Model.h>
#include <rl/mdl/NloptInverseKinematics.h>

using namespace roblib;

struct roblib::MotionerPrivate {
    std::shared_ptr<rl::mdl::Model> model = nullptr;
    std::unique_ptr<rl::mdl::IterativeInverseKinematics> ik = nullptr;
    double max_radian = rl::math::constants::pi;
    double max_degree_delta = 10 * rl::math::constants::deg2rad;
};

Motioner::Motioner(const std::string& model_file_path, InverseMethod method)
    : d_(new MotionerPrivate)
{
    d_->model = ModelUtils::isUrdfFile(model_file_path) ? ModelUtils::getModelFromUrdf(model_file_path) : ModelUtils::getModelFromXml(model_file_path);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    if (method == InverseMethod::Jacob) {
        d_->ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        d_->ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    d_->ik->setDuration(std::chrono::milliseconds(250));
}

Motioner::Motioner(ModelType type, const std::string& model_dir, InverseMethod method)
    : d_(new MotionerPrivate)
{
    std::string full_path;

    switch (type) {
    case roblib::ModelType::KawasakiRs013: {
        full_path = model_dir + "/rs013.urdf";
        break;
    }
    case roblib::ModelType::KawasakiRs020: {
        full_path = model_dir + "/rs020.urdf";
        break;
    }
    case roblib::ModelType::KawasakiRs025: {
        full_path = model_dir + "/rs025.urdf";
        break;
    }
    case roblib::ModelType::RokaeCR7: {
        full_path = model_dir + "/xMateCR7.urdf";
        break;
    }
    case roblib::ModelType::RokaeCR12: {
        full_path = model_dir + "/xMateCR12.urdf";
        break;
    }
    }

    d_->model = ModelUtils::getModelFromUrdf(full_path);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    if (method == InverseMethod::Jacob) {
        d_->ik = std::make_unique<rl::mdl::JacobianInverseKinematics>(kin_model.get());
    } else {
        d_->ik = std::make_unique<rl::mdl::NloptInverseKinematics>(kin_model.get());
    }
    d_->ik->setDuration(std::chrono::milliseconds(100));
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

void Motioner::setDuration(long long ms)
{
    d_->ik->setDuration(std::chrono::milliseconds(ms));
}

void Motioner::setJointMaxDegree(double max_degree)
{
    d_->max_radian = max_degree * rl::math::constants::deg2rad;
}

void Motioner::setJointMaxDegreeDelta(double max_degree_delta)
{
    d_->max_degree_delta = max_degree_delta * rl::math::constants::deg2rad;
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

JointAngles Motioner::getJointRadians() const
{
    JointAngles res;
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    for (int i = 0; i < kin_model->getPosition().size(); ++i) {
        res.push_back(kin_model->getPosition()[i]);
    }
    return res;
}

JointAngles Motioner::getJointDegrees() const
{
    JointAngles res;
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);

    for (int i = 0; i < kin_model->getPosition().size(); ++i) {
        res.push_back(kin_model->getPosition()[i] * rl::math::constants::rad2deg);
    }
    return res;
}

std::optional<xyzWithQuaternion> Motioner::getEndEffectorQuatPosByDegree(const JointAngles& joint_degrees) const
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

std::optional<xyzWithQuaternion> Motioner::getEndEffectorQuatPosByRadian(const JointAngles& joint_radians) const
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

std::optional<xyzWithEuler> Motioner::getEndEffectorEulerPosByDegree(const JointAngles& joint_degrees) const
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

std::optional<xyzWithEuler> Motioner::getEndEffectorEulerPosByRadian(const JointAngles& joint_radians) const
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

std::optional<JointAngles> Motioner::getDegreesByXyzQuat(const xyzWithQuaternion& target) const
{
    auto trans = ModelUtils::xyzQuat2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Vector origin_joint_radians = kin_model->getPosition();

    d_->ik->clearGoals();
    d_->ik->addGoal({ trans, 0 });

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool solved = d_->ik->solve();
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
    std::cout << (solved ? "true" : "false") << " " << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() * 1000 << " ms" << std::endl;

    if (solved) {
        JointAngles res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            double joint_radian = kin_model->getPosition()[i];
            if (joint_radian > d_->max_radian) {
                std::cout << "Warning: larger than joint max radian" << std::endl;
                return std::nullopt;
            }
            if (std::abs(joint_radian - origin_joint_radians[i]) > d_->max_degree_delta) {
                std::cout << "Warning: larger than joint max change delta" << std::endl;
                return std::nullopt;
            }
            res.push_back(joint_radian * rl::math::constants::rad2deg);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<JointAngles> Motioner::getRadiansByXyzQuat(const xyzWithQuaternion& target) const
{
    auto trans = ModelUtils::xyzQuat2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Vector origin_joint_radians = kin_model->getPosition();

    d_->ik->clearGoals();
    d_->ik->addGoal({ trans, 0 });

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool solved = d_->ik->solve();
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
    std::cout << (solved ? "true" : "false") << " " << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() * 1000 << " ms" << std::endl;

    if (solved) {
        JointAngles res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            double joint_radian = kin_model->getPosition()[i];
            if (joint_radian > d_->max_radian) {
                std::cout << "Warning: larger than joint max radian" << std::endl;
                return std::nullopt;
            }
            if (std::abs(joint_radian - origin_joint_radians[i]) > d_->max_degree_delta) {
                std::cout << "Warning: larger than joint max change delta" << std::endl;
                return std::nullopt;
            }
            res.push_back(joint_radian);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<JointAngles> Motioner::getDegreesByXyzEuler(const xyzWithEuler& target) const
{
    auto trans = ModelUtils::xyzEuler2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Vector origin_joint_radians = kin_model->getPosition();

    d_->ik->clearGoals();
    d_->ik->addGoal({ trans, 0 });

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool solved = d_->ik->solve();
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
    std::cout << (solved ? "true" : "false") << " " << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() * 1000 << " ms" << std::endl;

    if (solved) {
        JointAngles res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            double joint_radian = kin_model->getPosition()[i];
            if (joint_radian > d_->max_radian) {
                std::cout << "Warning: larger than joint max radian" << std::endl;
                return std::nullopt;
            }
            if (std::abs(joint_radian - origin_joint_radians[i]) > d_->max_degree_delta) {
                std::cout << "Warning: larger than joint max change delta" << std::endl;
                return std::nullopt;
            }
            res.push_back(joint_radian * rl::math::constants::rad2deg);
        }
        return res;
    }
    return std::nullopt;
}

std::optional<JointAngles> Motioner::getRadiansByXyzEuler(const xyzWithEuler& target) const
{
    auto trans = ModelUtils::xyzEuler2RlTransfrom(target);
    auto kin_model = dynamic_pointer_cast<rl::mdl::Kinematic>(d_->model);
    rl::math::Vector origin_joint_radians = kin_model->getPosition();

    d_->ik->clearGoals();
    d_->ik->addGoal({ trans, 0 });

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool solved = d_->ik->solve();
    std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
    std::cout << (solved ? "true" : "false") << " " << std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count() * 1000 << " ms" << std::endl;

    if (solved) {
        JointAngles res;
        for (int i = 0; i < kin_model->getPosition().size(); ++i) {
            double joint_radian = kin_model->getPosition()[i];
            if (joint_radian > d_->max_radian) {
                std::cout << "Warning: larger than joint max radian" << std::endl;
                return std::nullopt;
            }
            if (std::abs(joint_radian - origin_joint_radians[i]) > d_->max_degree_delta) {
                std::cout << "Warning: larger than joint max change delta" << std::endl;
                return std::nullopt;
            }
            res.push_back(joint_radian);
        }
        return res;
    }
    return std::nullopt;
}

xyzWithEuler Motioner::getTcpXyzWithEuler(const xyzWithEuler& device_in_world, const xyzWithEuler& device_offset, DeviceMountType type)
{
    auto device_mount = getDeviceMountRotation(type);
    auto rl_device_mount = ModelUtils::xyzEuler2RlTransfrom(device_mount);
    auto rl_device_in_world = rl_device_mount * ModelUtils::xyzEuler2RlTransfrom(device_in_world);
    auto rl_device_offset = ModelUtils::xyzEuler2RlTransfrom(device_offset);
    rl::math::Transform tcp_in_world = rl_device_in_world * rl_device_offset.inverse();
    return ModelUtils::rlTransform2XyzEuler(tcp_in_world);
}

xyzWithEuler Motioner::getDeviceXyzWithEuler(const xyzWithEuler& tcp_in_world, const xyzWithEuler& device_offset, DeviceMountType type)
{
    auto rl_tcp_in_world = ModelUtils::xyzEuler2RlTransfrom(tcp_in_world);
    auto rl_device_offset = ModelUtils::xyzEuler2RlTransfrom(device_offset);
    auto device_mount = getDeviceMountRotation(type);
    auto rl_device_mount = ModelUtils::xyzEuler2RlTransfrom(device_mount);
    rl::math::Transform device_in_world = rl_device_mount.inverse() * rl_tcp_in_world * rl_device_offset;
    return ModelUtils::rlTransform2XyzEuler(device_in_world);
}

xyzWithEuler Motioner::getDeviceMountRotation(DeviceMountType mount_type)
{
    rl::math::Transform rotate;
    rotate.setIdentity();
    switch (mount_type) {
    case roblib::DeviceMountType::Top: {
        rotate.rotate(rl::math::AngleAxis(rl::math::constants::pi, Eigen::Vector3d::UnitX())); // X +180°
        break;
    }
    case roblib::DeviceMountType::Left: {
        rotate.rotate(rl::math::AngleAxis(-90 * rl::math::constants::deg2rad, Eigen::Vector3d::UnitZ())); // Z -90°
        break;
    }
    case roblib::DeviceMountType::Right: {
        rotate.rotate(rl::math::AngleAxis(90 * rl::math::constants::deg2rad, Eigen::Vector3d::UnitZ())); // Z +90°
        break;
    }
    case roblib::DeviceMountType::Back: {
        rotate.rotate(rl::math::AngleAxis(rl::math::constants::pi, Eigen::Vector3d::UnitY())); // Y +180°
        break;
    }
    case roblib::DeviceMountType::Self:
        // "Self" is identity
        break;
    }

    return ModelUtils::rlTransform2XyzEuler(rotate);
}