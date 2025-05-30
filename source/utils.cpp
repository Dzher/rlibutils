#include "utils.h"

#include <filesystem>
#include <rl/mdl/UrdfFactory.h>
#include <rl/mdl/XmlFactory.h>

using namespace roblib;

namespace {
rl::math::Transform transformPos2RlTransfromImpl1(const TransformPos& in)
{
    return rl::math::Transform(
        Eigen::Translation3d(
            in.translation[0],
            in.translation[1],
            in.translation[2])
        * Eigen::Quaterniond(
            in.rotation[0],
            in.rotation[1],
            in.rotation[2],
            in.rotation[3])
            .normalized());
}

rl::math::Transform transformPos2RlTransfromImpl2(const TransformPos& in)
{
    rl::math::Transform t;
    rl::math::Quaternion q(in.rotation[0], in.rotation[1], in.rotation[2],
        in.rotation[3]);
    q.normalize();
    t.linear() = q.toRotationMatrix();
    t.translation().x() = in.translation[0];
    t.translation().y() = in.translation[1];
    t.translation().z() = in.translation[2];
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

rl::math::Transform ModelUtils::transformPos2RlTransfrom(const TransformPos& in)
{
    // TODO: which method is better? It's a problem
    return transformPos2RlTransfromImpl2(in);
}

TransformPos ModelUtils::rlTransform2TransfromPos(const rl::math::Transform& in)
{
    TransformPos res;
    const auto& t = in.translation();
    res.translation = { t.x(), t.y(), t.z() };

    Eigen::Quaterniond q(in.linear());
    res.rotation = { q.w(), q.x(), q.y(), q.z() };
    return res;
}