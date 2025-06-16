# CMake package configuration file for superglu
#
# Defines the target "superglu::GLU"
#
# Add the following lines to your CMakeLists.txt to depend on superglu
#
#    find_package(superglu REQUIRED)
#    target_link_libraries(my_target_name superglu::GLU)
#
# Additionally you may one of the following variables (or their corresponding
# upper case version) that are also defined.
#
# superglu_COMPILE_DEFINITIONS
# superglu_DEFINITIONS
# superglu_INCLUDE_DIRS
# superglu_INCLUDE_DIR
# superglu_LIBRARY
# superglu_LIBRARIES
# superglu_LIBRARY_DIRS
# superglu_LIBRARY_DIR
#
# However, in most cases using the superglu::GLU target is sufficient,
# and you won't need these variables.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was superglu-config.cmake.in                            ########

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

include(CMakeFindDependencyMacro)

find_dependency(OpenGL REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/superglu-export.cmake")

get_property(superglu_COMPILE_DEFINITIONS TARGET superglu::GLU PROPERTY INTERFACE_COMPILE_DEFINITIONS)
foreach(_def ${superglu_COMPILE_DEFINITIONS})
  list(APPEND superglu_DEFINITIONS -D${_def})
endforeach()

set(superglu_VERSION 1.3.2)

get_property(superglu_INCLUDE_DIRS TARGET superglu::GLU PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(superglu_INCLUDE_DIR ${superglu_INCLUDE_DIRS})
set(superglu_LIBRARY superglu::GLU)
get_property(superglu_LIBRARIES TARGET superglu::GLU PROPERTY INTERFACE_LINK_LIBRARIES)
set(superglu_LIBRARIES superglu::GLU ${superglu_LIBRARIES})

set_and_check(superglu_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib")
set(superglu_LIBRARY_DIR ${superglu_LIBRARY_DIRS})

# For backwards compatibility define upper case versions of output variables
foreach(_var
  superglu_COMPILE_DEFINITIONS
  superglu_DEFINITIONS
  superglu_INCLUDE_DIRS
  superglu_INCLUDE_DIR
  superglu_LIBRARY
  superglu_LIBRARIES
  superglu_LIBRARY_DIRS
  superglu_LIBRARY_DIR
  superglu_VERSION
  )
  string(TOUPPER ${_var} _uppercase_var)
  set(${_uppercase_var} ${${_var}})
endforeach()
