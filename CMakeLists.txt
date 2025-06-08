cmake_minimum_required(VERSION 3.15)
project(RL_LIB_UTILS VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build test tools" OFF)

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

set(CMAKE_PREFIX_PATH "${RL_DIR}" ${CMAKE_PREFIX_PATH})

find_package(rl REQUIRED)

# include_directories(
#     PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )

# add_subdirectory(source)

if(BUILD_TESTS)
  # add_subdirectory(tests)
endif()

add_library(rlibutils
    source/motioner.cpp
    source/utils.cpp
)

if(WIN32)
    target_compile_definitions(rlibutils PRIVATE R_LIB_UTILS_EXPORTS)
    target_compile_definitions(rlibutils PUBLIC R_LIB_UTILS_IMPORTS)
endif()

target_link_libraries(rlibutils ${RL_LIBRARIES})

target_include_directories(rlibutils
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

# 生成多配置目标（例如 Debug 和 Release）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 安装规则
install(TARGETS rlibutils
    EXPORT rlibutilsTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # exe/dll
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # 静态库
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # 共享库
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 导出 targets
install(EXPORT rlibutilsTargets
    FILE rlibutilsTargets.cmake
    NAMESPACE rlibutils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rlibutils
)

# 配置包文件
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/rlibutilsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/rlibutilsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rlibutils
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/rlibutilsConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rlibutils
)


set(CPACK_PACKAGE_NAME "rlibutils")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

include(CPack)
