#pragma once

#include "data.h"
#include "macro.h"
#include <optional>
#include <string>

namespace roblib {

struct MotionerPrivate;

class RLIB_API Motioner {
public:
    explicit Motioner(const std::string& model_file_path, InverseMethod method = InverseMethod::Jacob);
    explicit Motioner(ModelType type, const std::string& model_dir, InverseMethod method = InverseMethod::Jacob);
    Motioner(const Motioner& other);
    ~Motioner();

    bool isValid() const;
    void setDuration(long long ms);
    void setJointMaxDegree(double max_degree);
    void setJointMaxDegreeDelta(double max_degree_delta);

    int getDof() const;
    int getOperationDof() const;

    xyzWithQuaternion getEndEffectorQuatPos() const;
    xyzWithEuler getEndEffectorEulerPos() const;

    JointAngles getJointDegrees() const;
    JointAngles getJointRadians() const;

    // Forward Kinematics
    std::optional<xyzWithQuaternion> getEndEffectorQuatPosByDegree(const JointAngles& joint_degrees) const;
    std::optional<xyzWithQuaternion> getEndEffectorQuatPosByRadian(const JointAngles& joint_radians) const;
    std::optional<xyzWithEuler> getEndEffectorEulerPosByDegree(const JointAngles& joint_degrees) const;
    std::optional<xyzWithEuler> getEndEffectorEulerPosByRadian(const JointAngles& joint_radians) const;

    // Inverse Kinematics
    std::optional<JointAngles> getDegreesByXyzQuat(const xyzWithQuaternion& target) const;
    std::optional<JointAngles> getRadiansByXyzQuat(const xyzWithQuaternion& target) const;
    std::optional<JointAngles> getDegreesByXyzEuler(const xyzWithEuler& target) const;
    std::optional<JointAngles> getRadiansByXyzEuler(const xyzWithEuler& target) const;

    static xyzWithEuler getTcpXyzWithEuler(const xyzWithEuler& device_in_world, const xyzWithEuler& device_offset, DeviceMountType type);
    static xyzWithEuler getDeviceXyzWithEuler(const xyzWithEuler& tcp_in_world, const xyzWithEuler& device_offset, DeviceMountType type);
    static xyzWithEuler getDeviceMountRotation(DeviceMountType mount_type);

private:
    MotionerPrivate* d_ = nullptr;
};
}