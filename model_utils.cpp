#include "model_utils.h"
#include <rl/mdl/UrdfFactory.h>
#include <rl/mdl/XmlFactory.h>

using namespace robutils;

rl::mdl::Model* getModelFromUrdf(const ::std::string& model_file_path)
{
    rl::mdl::UrdfFactory urdf_factory;
    return urdf_factory.create(model_file_path);
}

rl::mdl::Model* getModelFromXml(const ::std::string& model_file_path)
{
    rl::mdl::XmlFactory xml_factory;
    return xml_factory.create(model_file_path);
}
