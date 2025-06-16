set(RL_VERSION "0.7.0")
set(RL_VERSION_MAJOR "0")
set(RL_VERSION_MINOR "7")
set(RL_VERSION_PATCH "0")

set(RL_HAL_FOUND ON)
set(RL_KIN_FOUND ON)
set(RL_MATH_FOUND ON)
set(RL_MDL_FOUND ON)
set(RL_PLAN_FOUND ON)
set(RL_SG_FOUND ON)
set(RL_UTIL_FOUND ON)
set(RL_UTIL_RTAI_FOUND OFF)
set(RL_UTIL_XENOMAI_FOUND OFF)
set(RL_XML_FOUND ON)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was rl-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/rl-export.cmake")

check_required_components(RL)

set(RL_LIBRARIES "rl::std;rl::math;rl::util;rl::xml;rl::kin;rl::mdl;rl::hal;rl::sg;rl::plan")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include(CMakeFindDependencyMacro)

find_dependency(Boost)
find_dependency(Bullet)
find_dependency(Coin)
find_dependency(Eigen3)
find_dependency(LibXml2)
find_dependency(LibXslt)
find_dependency(NLopt)
find_dependency(ODE)
find_dependency(PQP)
find_dependency(fcl)
find_dependency(solid3)
