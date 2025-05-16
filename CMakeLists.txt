cmake_minimum_required(VERSION 3.31.6)
project(rl_utils_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-D_USE_MATH_DEFINES)
find_package(RL COMPONENTS MDL KIN MATH REQUIRED)

set(LIB_SOURCES
    model_utils.h
    model_utils.cpp
    motioner.h
    motioner.cpp
    roboticslib_utils.h
)

add_library(rl_utils_lib ${LIB_SOURCES})
target_link_libraries(rl_utils_lib ${RL_LIBRARIES})
