#include "utils.h"

#include <filesystem>
#include <rl/mdl/UrdfFactory.h>
#include <rl/mdl/XmlFactory.h>

using namespace roblib;

namespace {
rl::math::Transform transformPos2RlTransfromImpl(const xyzWithQuaternion& in)
{
    return rl::math::Transform(
        Eigen::Translation3d(
            in.x(),
            in.y(),
            in.z())
        * rl::math::Quaternion(
            in.qw(),
            in.qx(),
            in.qy(),
            in.qz())
            .normalized());
}
}

std::shared_ptr<rl::mdl::Model> ModelUtils::getModelFromUrdf(const ::std::string& model_file_path)
{
    rl::mdl::UrdfFactory urdf_factory;
    return urdf_factory.create(model_file_path);
}

std::shared_ptr<rl::mdl::Model> ModelUtils::getModelFromXml(const ::std::string& model_file_path)
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
    return transformPos2RlTransfromImpl(in);
}

xyzWithQuaternion ModelUtils::rlTransform2XyzQuat(const rl::math::Transform& in)
{
    xyzWithQuaternion res;
    const auto& t = in.translation();
    res.position({ t.x(), t.y(), t.z() });

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

    Eigen::Matrix3d rotation = in.linear();
    Eigen::Vector3d euler = rotation.eulerAngles(0, 1, 2); // cba-012-XYZ-RPY 顺序
    res.euler.c = euler[0];
    res.euler.b = euler[1];
    res.euler.a = euler[2];
    return res;
}

Euler ModelUtils::quaternion2Euler(const Quaternion& quat)
{
    Euler res;
    rl::math::Quaternion q;
    q.w() = quat.qw;
    q.x() = quat.qx;
    q.y() = quat.qy;
    q.z() = quat.qz;

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
    res.qw = q.w();
    res.qx = q.x();
    res.qy = q.y();
    res.qz = q.z();

    return res;
}