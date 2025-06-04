#include "utils.h"

#include <filesystem>
#include <rl/mdl/UrdfFactory.h>
#include <rl/mdl/XmlFactory.h>

using namespace roblib;

namespace {
rl::math::Transform transformPos2RlTransfromImpl1(const xyzWithQuaternion& in)
{
    return rl::math::Transform(
        Eigen::Translation3d(
            in.x(),
            in.y(),
            in.z())
        * Eigen::Quaterniond(
            in.q1(),
            in.q2(),
            in.q3(),
            in.q4())
            .normalized());
}

rl::math::Transform transformPos2RlTransfromImpl2(const xyzWithQuaternion& in)
{
    rl::math::Transform t;
    rl::math::Quaternion q(
        in.q1(),
        in.q2(),
        in.q3(),
        in.q4());
    q.normalize();
    t.linear() = q.toRotationMatrix();
    t.translation().x() = in.x();
    t.translation().y() = in.y();
    t.translation().z() = in.z();
    return t;
}
}

rl::mdl::Model* ModelUtils::getModelFromUrdf(const ::std::string& model_file_path)
{
    rl::mdl::UrdfFactory urdf_factory;
    return urdf_factory.create(model_file_path);
}

rl::mdl::Model* ModelUtils::getModelFromXml(const ::std::string& model_file_path)
{
    rl::mdl::XmlFactory xml_factory;
    return xml_factory.create(model_file_path);
}

bool ModelUtils::isUrdfFile(const std::string& file_path)
{
    std::filesystem::path path(file_path);
    return path.extension() == ".urdf";
}

bool ModelUtils::isXmlFile(const std::string& file_path)
{
    std::filesystem::path path(file_path);
    return path.extension() == ".xml";
}

rl::math::Transform ModelUtils::xyzQuat2RlTransfrom(const xyzWithQuaternion& in)
{
    // TODO: which method is better? It's a problem
    return transformPos2RlTransfromImpl2(in);
}

xyzWithQuaternion ModelUtils::rlTransform2XyzQuat(const rl::math::Transform& in)
{
    xyzWithQuaternion res;
    const auto& t = in.translation();
    res.position({ t.x(), t.y(), t.z() });

    // Eigen::Quaterniond q(in.linear());
    rl::math::Quaternion q(in.linear());
    res.rotation({ q.w(), q.x(), q.y(), q.z() });

    return res;
}

rl::math::Transform ModelUtils::xyzEuler2RlTransfrom(const xyzWithEuler& in)
{
    rl::math::Transform t;
    t = rl::math::AngleAxis(in.a(), rl::math::Vector3::UnitZ()) * rl::math::AngleAxis(in.b(), rl::math::Vector3::UnitY()) * rl::math::AngleAxis(in.c(), rl::math::Vector3::UnitX());
    t.translation().x() = in.x();
    t.translation().y() = in.y();
    t.translation().z() = in.z();
    return t;
}

xyzWithEuler ModelUtils::rlTransform2XyzEuler(const rl::math::Transform& in)
{
    xyzWithEuler res;
    const auto& t = in.translation();
    res.position({ t.x(), t.y(), t.z() });

    // TODO: some issues here
    // const rl::math::Rotation euler { in.rotation() };
    // res.rotation({ euler.x(), euler.y(), euler.z() });
    const rl::math::Rotation r { in.rotation() };
    res.euler.a = std::atan2(r(1, 0), r(0, 0));
    res.euler.b = std::atan2(-r(2, 0), std::sqrt(r(2, 1) * r(2, 1) + r(2, 2) * r(2, 2)));
    res.euler.c = std::atan2(r(2, 1), r(2, 2));

    return res;
}

Euler ModelUtils::quaternion2Euler(const Quaternion& quat)
{
    Euler res;
    rl::math::Quaternion q;
    q.w() = quat.q1;
    q.x() = quat.q2;
    q.y() = quat.q3;
    q.z() = quat.q4;

    rl::math::Vector3 euler = q.toRotationMatrix().eulerAngles(2, 1, 0);
    res.a = euler[0];
    res.b = euler[1];
    res.c = euler[2];

    return res;
}

Quaternion ModelUtils::euler2Quaternion(const Euler& euler)
{
    Quaternion res;
    rl::math::Quaternion q = rl::math::AngleAxis(euler.a, rl::math::Vector3::UnitZ()) * rl::math::AngleAxis(euler.b, rl::math::Vector3::UnitY()) * rl::math::AngleAxis(euler.c, rl::math::Vector3::UnitX());
    res.q1 = q.w();
    res.q2 = q.x();
    res.q3 = q.y();
    res.q4 = q.z();

    return res;
}