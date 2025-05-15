#pragma once

#include <rl/mdl/Model.h>
#include <string>

namespace robutils {
// load model form file
static rl::mdl::Model* getModelFromUrdf(const ::std::string& model_file_path);
static rl::mdl::Model* getModelFromXml(const ::std::string& model_file_path);
}
