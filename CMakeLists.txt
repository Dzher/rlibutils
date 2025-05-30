cmake_minimum_required(VERSION 3.31.6)
project(RL_LIB_UTILS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build test tools" ON)

add_definitions(-D_USE_MATH_DEFINES)
find_package(RL COMPONENTS MDL KIN MATH REQUIRED)

include_directories(
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(source)

# if(BUILD_TESTS)
#   add_subdirectory(tests)
# endif()
