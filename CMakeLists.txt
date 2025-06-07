cmake_minimum_required(VERSION 3.15)
project(RL_LIB_UTILS VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build test tools" ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

add_definitions(-D_USE_MATH_DEFINES)

# 设置 RL 安装路径根目录
set(RL_BASE_DIR "I:/workspace/rl-install")

# 根据构建类型选择合适的前缀路径
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(RL_DIR "${RL_BASE_DIR}/debug")
else()
    set(RL_DIR "${RL_BASE_DIR}/release")
endif()

# 设置 CMake 查找路径
set(CMAKE_PREFIX_PATH "${RL_DIR}" ${CMAKE_PREFIX_PATH})
# set(CMAKE_PREFIX_PATH "I:/workspace/rl-3rdparty/bin" ${CMAKE_PREFIX_PATH})
# set(CMAKE_PREFIX_PATH "I:/workspace/rl-3rdparty/lib" ${CMAKE_PREFIX_PATH})
# set(CMAKE_PREFIX_PATH "I:/workspace/rl-3rdparty/include" ${CMAKE_PREFIX_PATH})


# find_package(RL COMPONENTS MDL KIN MATH REQUIRED)
find_package(rl REQUIRED)

include_directories(
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(source)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
