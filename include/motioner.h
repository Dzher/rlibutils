#pragma once

#include "data.h"
#include "macro.h"
#include <optional>
#include <string>
#include <vector>

namespace roblib {

struct MotionerPrivate;

class RLIB_API Motioner {
public:
    explicit Motioner(const std::string& model_file_path);
    Motioner(const Motioner& other);
    ~Motioner();

    bool isValid() const;
    int getDof() const;
    int getOperationDof() const;
    xyzWithQuaternion getEndEffectorQuatPos() const;
    xyzWithEuler getEndEffectorEulerPos() const;
    std::vector<double> getJointDegree() const;
    // Forward Kinematics
    std::optional<xyzWithQuaternion> getEndEffectorPosByDegree(const std::vector<double>& joint_degrees) const;
    std::optional<xyzWithQuaternion> getEndEffectorPosByRadian(const std::vector<double>& joint_radians) const;
    // std::optional<xyzWithEuler> getEndEffectorPosByDegree(const std::vector<double>& joint_degrees) const;
    // std::optional<xyzWithEuler> getEndEffectorPosByRadian(const std::vector<double>& joint_radians) const;

    // Inverse Kinematics
    std::optional<std::vector<double>> getDegreesByXyzQuat(const xyzWithQuaternion& target, InverseMethod method = InverseMethod::Jacob) const;
    std::optional<std::vector<double>> getRadiansByXyzQuat(const xyzWithQuaternion& target, InverseMethod method = InverseMethod::Jacob) const;
    std::optional<std::vector<double>> getDegreesByXyzEuler(const xyzWithEuler& target, InverseMethod method = InverseMethod::Jacob) const;
    std::optional<std::vector<double>> getRadiansByXyzEuler(const xyzWithEuler& target, InverseMethod method = InverseMethod::Jacob) const;

private:
    MotionerPrivate* d_ = nullptr;
};
}