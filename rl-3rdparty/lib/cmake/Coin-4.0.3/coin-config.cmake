cmake_minimum_required(VERSION 2.8.12)

# Have a look at VTKConfig.cmake.in, especially regarding UseVTK.cmake
# https://github.com/Kitware/VTK/blob/master/CMake/VTKConfig.cmake.in
# https://github.com/Kitware/VTK/blob/master/CMake/UseVTK.cmake
# Usage example:
# https://github.com/LuaDist/cmake/blob/master/Modules/FindVTK.cmake
# Bastiaan Veelo 2016.03.15

set(COIN_VERSION 4.0.3)

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was coin-config.cmake.in                            ########

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

set(COIN_BUILD_MAC_FRAMEWORK OFF)
if(NOT COIN_BUILD_MAC_FRAMEWORK)

set_and_check(COINDIR "${PACKAGE_PREFIX_DIR}")
set_and_check(Coin_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include")
set_and_check(Coin_LIB_DIR "${PACKAGE_PREFIX_DIR}/lib")

# optional directory from documentation component
if (EXISTS "${PACKAGE_PREFIX_DIR}/share/doc/Coin/")
  set(Coin_DOC_DIR     "${PACKAGE_PREFIX_DIR}/share/doc/Coin")
endif()

set(COIN_NAME Coin)

set(COIN_BUILD_SHARED_LIBS ON)
if(WIN32)
	if (COIN_BUILD_SHARED_LIBS)
		SET(Coin_DEFINES -DCOIN_DLL)
	else()
		SET(Coin_DEFINES -DCOIN_NOT_DLL)
	endif()
endif()

set(Coin_CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)
set(Coin_BUILD_TYPE Release)
foreach(configuration IN LISTS Coin_CONFIGURATION_TYPES)
	if(configuration STREQUAL "Debug")
		set(Coin_LIBRARY_DEBUG ${COIN_NAME}4d)
	else()
		set(Coin_LIBRARY_RELEASE ${COIN_NAME}4)
	endif()
endforeach()

if(NOT Coin_CONFIGURATION_TYPES)
	if(Coin_BUILD_TYPE STREQUAL "Debug")
		set(Coin_LIBRARY_RELEASE ${COIN_NAME}4d)
	else()
		set(Coin_LIBRARY_RELEASE ${COIN_NAME}4)
	endif()
endif()

if(Coin_LIBRARY_RELEASE AND NOT Coin_LIBRARY_DEBUG)
	set(Coin_LIBRARY_DEBUG   ${Coin_LIBRARY_RELEASE})
	set(Coin_LIBRARY         ${Coin_LIBRARY_RELEASE})
	set(Coin_LIBRARIES       ${Coin_LIBRARY_RELEASE})
endif()

if(Coin_LIBRARY_DEBUG AND NOT Coin_LIBRARY_RELEASE)
	set(Coin_LIBRARY_RELEASE ${Coin_LIBRARY_DEBUG})
	set(Coin_LIBRARY         ${Coin_LIBRARY_DEBUG})
	set(Coin_LIBRARIES       ${Coin_LIBRARY_DEBUG})
endif()

if(Coin_LIBRARY_DEBUG AND Coin_LIBRARY_RELEASE)
	if(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
		# If the generator supports configuration types then set
		# optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
		SET(Coin_LIBRARY optimized ${Coin_LIBRARY_RELEASE} debug ${Coin_LIBRARY_DEBUG})
	else()
		# If there are no configuration types and CMAKE_BUILD_TYPE has no value
		# then just use the release libraries
		SET(Coin_LIBRARY ${Coin_LIBRARY_RELEASE})
	endif()
	set(Coin_LIBRARIES optimized ${Coin_LIBRARY_RELEASE} debug ${Coin_LIBRARY_DEBUG})
endif()

set(Coin_LIBRARY ${Coin_LIBRARY} CACHE FILEPATH "The Coin library")
mark_as_advanced(Coin_LIBRARY_RELEASE Coin_LIBRARY_DEBUG)

endif()
include(CMakeFindDependencyMacro)

if(NOT COIN_BUILD_SHARED_LIBS)
	set(_Boost_FOUND TRUE)
	if(_Boost_FOUND)
		find_dependency(Boost)
	endif()
	set(_OPENGL_FOUND TRUE)
	if(_OPENGL_FOUND)
		find_dependency(OpenGL)
	endif()
	set(_Threads_FOUND TRUE)
	if(_Threads_FOUND)
		find_dependency(Threads)
	endif()
	set(_EXPAT_FOUND )
	if(_EXPAT_FOUND)
		find_dependency(EXPAT)
	endif()
	set(_superglu_FOUND 1)
	if(_superglu_FOUND)
		find_dependency(superglu)
	endif()
	set(_ZLIB_FOUND )
	if(_ZLIB_FOUND)
		find_dependency(ZLIB)
	endif()
	set(_BZip2_FOUND )
	if(_BZip2_FOUND)
		find_dependency(BZip2)
	endif()
	set(_Freetype_FOUND )
	if(_Freetype_FOUND)
		find_dependency(Freetype)
	endif()
endif()

set(_simage_FOUND )
if(_simage_FOUND)
	find_dependency(simage)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/coin-export.cmake")

# export "coin-config --have-feature" equivalent info
set(Coin_HAVE_3DS_IMPORT_CAPABILITIES 1)
set(Coin_HAVE_VRML97 1)
set(Coin_HAVE_SOUND 1)
set(Coin_HAVE_SUPERGLU 1)
set(Coin_HAVE_THREADS 1)
set(Coin_HAVE_SAFETHREAD 0)

