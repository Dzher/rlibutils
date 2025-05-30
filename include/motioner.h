#pragma once

#ifdef _WIN32
#ifdef R_LIB_UTILS_EXPORTS
#define RLIB_API __declspec(dllexport)
#else
#define RLIB_API __declspec(dllimport)
#endif
#else
#define RLIB_API
#endif

#include "data.h"
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

    int getDof() const;
    int getOperationDof() const;
    xyzWithQuaternion getEndEffectorQuatPos() const;
    xyzWithEuler getEndEffectorEulerPos() const;
    std::vector<double> getJointDegree() const;
    // Forward Kinematics
    std::optional<xyzWithQuaternion> getEndEffectorPosByDegree(const std::vector<double>& joint_degrees) const;
    std::optional<xyzWithQuaternion> getEndEffectorPosByRadian(const std::vector<double>& joint_radians) const;

    // Inverse Kinematics
    std::vector<double> getDegreesByTXyzQuat(const xyzWithQuaternion& target) const;
    std::vector<double> getRadiansByTXyzQuat(const xyzWithQuaternion& target) const;
    std::vector<double> getDegreesByXyzEuler(const xyzWithEuler& target) const;
    std::vector<double> getRadiansByXyzEuler(const xyzWithEuler& target) const;

private:
    MotionerPrivate* d_ = nullptr;
};
}