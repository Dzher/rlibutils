# CMake package configuration file for SoQt
#
# Defines the target "SoQt::SoQt"
#
# Add the following lines to your CMakeLists.txt to depend on SoQt
#
#    find_package(SoQt REQUIRED)
#    target_link_libraries(my_target_name SoQt::SoQt)
#
# Additionally you may one of the following variables (or their corresponding
# upper case version) that are also defined.
#
# SoQt_COMPILE_DEFINITIONS
# SoQt_DEFINITIONS
# SoQt_INCLUDE_DIRS
# SoQt_INCLUDE_DIR
# SoQt_LIBRARY
# SoQt_LIBRARIES
# SoQt_LIBRARY_DIRS
# SoQt_LIBRARY_DIR
#
# However, in most cases using the SoQt::SoQt target is sufficient,
# and you won't need these variables.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was soqt-config.cmake.in                            ########

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

find_dependency(Coin)

set(SoQt_HAVE_QT6 1)
set(SoQt_HAVE_QT5 )
set(SoQt_HAVE_QT4 )

if(SoQt_HAVE_QT6)
  find_dependency(Qt6Core)
  find_dependency(Qt6Gui)
  find_dependency(Qt6OpenGL)
  find_dependency(Qt6Widgets)
elseif(SoQt_HAVE_QT5)
  find_dependency(Qt5Core)
  find_dependency(Qt5Gui)
  find_dependency(Qt5OpenGL)
  find_dependency(Qt5Widgets)
elseif(SoQt_HAVE_QT4)
  find_dependency(Qt4)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/soqt-export.cmake")

get_property(SoQt_COMPILE_DEFINITIONS TARGET SoQt::SoQt PROPERTY INTERFACE_COMPILE_DEFINITIONS)
foreach(_def ${SoQt_COMPILE_DEFINITIONS})
  list(APPEND SoQt_DEFINITIONS -D${_def})
endforeach()

set(SoQt_VERSION 1.6.3)

get_property(SoQt_INCLUDE_DIRS TARGET SoQt::SoQt PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(SoQt_INCLUDE_DIR ${SoQt_INCLUDE_DIRS})

set(SoQt_LIBRARY SoQt::SoQt)
get_property(SoQt_LIBRARIES TARGET SoQt::SoQt PROPERTY INTERFACE_LINK_LIBRARIES)
set(SoQt_LIBRARIES SoQt::SoQt ${SoQt_LIBRARIES})

set_and_check(SoQt_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib")
set(SoQt_LIBRARY_DIR ${SoQt_LIBRARY_DIRS})

# For backwards compatibility define upper case versions of output variables
foreach(_var
  SoQt_COMPILE_DEFINITIONS
  SoQt_DEFINITIONS
  SoQt_INCLUDE_DIRS
  SoQt_INCLUDE_DIR
  SoQt_LIBRARY
  SoQt_LIBRARIES
  SoQt_LIBRARY_DIRS
  SoQt_LIBRARY_DIR
  SoQt_VERSION
  )
  string(TOUPPER ${_var} _uppercase_var)
  set(${_uppercase_var} ${${_var}})
endforeach()
