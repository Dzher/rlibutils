#pragma once

#include <string>
#include <vector>

namespace roblib {

struct MotionerPrivate;

class Motioner {
public:
    explicit Motioner(const std::string& model_file_path);
    int getDof();
    void getPositonByDegree(const std::vector<double>& joint_degrees);
    void getPositonByRadian(const std::vector<double>& joint_radians);

private:
    MotionerPrivate* d_ = nullptr;
};
}