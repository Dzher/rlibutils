# RoboticLibUtils
Using Robotics Library implement some utils funcs.

## Attention
You can change this lib's install direction by modify the `CMakePresets.json` file's configuration: the `CMAKE_INSTALL_PREFIX` field's value.
## Install Method
### Install Release
`cd build-rel`

`cmake --install . --config Release`

### Install Debug
`cd build-dbg`

`cmake --install . --config Debug`

## Package Method
`cd build-rel` or `cd build-dbg`

`cpack --config CPackConfig.cmake`

## How To Use
`find_package(rlutilslib CONFIG REQUIRED)`

`target_link_libraries(your_target PRIVATE rlutilslib::rlutilslib)`
