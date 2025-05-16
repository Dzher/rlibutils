#pragma once

#include <rl/mdl/Model.h>
#include <string>

namespace roblib {
class ModelUtils {
public:
    static bool isUrdfFile(const std::string& file_path);
    static bool isXmlFile(const std::string& file_path);

    // load model form file
    static rl::mdl::Model* getModelFromUrdf(const ::std::string& model_file_path);
    static rl::mdl::Model* getModelFromXml(const ::std::string& model_file_path);
};
}
