# CMake package configuration file for simage
#
# Defines the target "simage::simage"
#
# Add the following lines to your CMakeLists.txt to depend on simage
#
#    find_package(simage REQUIRED)
#    target_link_libraries(my_target_name simage::simage)
#
# Additionally you may use one of the following variables (or their corresponding
# upper case version) that are also defined.
#
# simage_COMPILE_DEFINITIONS
# simage_DEFINITIONS
# simage_INCLUDE_DIRS
# simage_INCLUDE_DIR
# simage_LIBRARY
# simage_LIBRARIES
# simage_LIBRARY_DIRS
# simage_LIBRARY_DIR
#
# However, in most cases using the simage::simage target is sufficient,
# and you won't need these variables.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was simage-config.cmake.in                            ########

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

set(simage_BUILD_SHARED_LIBS ON)
if(NOT simage_BUILD_SHARED_LIBS)
  set(_simage_have_qt6 )
  set(_simage_have_qt5 )
  set(_simage_have_qt4 )
  if(_simage_have_qt6)
    find_dependency(Qt6Core)
    find_dependency(Qt6Gui)
  elseif(_simage_have_qt5)
    find_dependency(Qt5Core)
    find_dependency(Qt5Gui)
  elseif(_simage_have_qt4)
    find_dependency(Qt4 COMPONENTS QtCore QtGui)
  endif()
  set(_simage_quicktime_support OFF)
  if(_simage_quicktime_support)
    find_dependency(QuickTime)
  endif()
  set(_simage_have_giflib )
  if(_simage_have_giflib)
    find_dependency(GIF)
  endif()
  set(_simage_have_jasper )
  if(_simage_have_jasper)
    find_dependency(Jasper)
  endif()
  set(_simage_have_jpeglib )
  if(_simage_have_jpeglib)
    find_dependency(JPEG)
  endif()
  set(_simage_have_pnglib )
  if(_simage_have_pnglib)
    find_dependency(PNG)
  endif()
  set(_simage_have_tifflib )
  if(_simage_have_tifflib)
    find_dependency(TIFF)
  endif()
endif()

include("${CMAKE_CURRENT_LIST_DIR}/simage-export.cmake")

get_property(simage_COMPILE_DEFINITIONS TARGET simage::simage PROPERTY INTERFACE_COMPILE_DEFINITIONS)
foreach(_def ${simage_COMPILE_DEFINITIONS})
  list(APPEND simage_DEFINITIONS -D${_def})
endforeach()

get_property(simage_INCLUDE_DIRS TARGET simage::simage PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(simage_INCLUDE_DIR ${simage_INCLUDE_DIRS})
set(simage_LIBRARY simage::simage)
get_property(simage_LIBRARIES TARGET simage::simage PROPERTY INTERFACE_LINK_LIBRARIES)
set(simage_LIBRARIES simage::simage ${simage_LIBRARIES})
set(simage_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib")
set(simage_LIBRARY_DIR ${simage_LIBRARY_DIRS})

# For backwards compatibility define upper case versions of output variables
foreach(_var
  simage_COMPILE_DEFINITIONS
  simage_DEFINITIONS
  simage_INCLUDE_DIRS
  simage_INCLUDE_DIR
  simage_LIBRARY
  simage_LIBRARIES
  simage_LIBRARY_DIRS
  simage_LIBRARY_DIR
  )
  string(TOUPPER ${_var} _uppercase_var)
  set(${_uppercase_var} ${${_var}})
endforeach()
