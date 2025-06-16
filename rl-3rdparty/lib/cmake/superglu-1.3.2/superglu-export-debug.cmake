#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "superglu::GLU" for configuration "Debug"
set_property(TARGET superglu::GLU APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(superglu::GLU PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/GLUsd.lib"
  )

list(APPEND _cmake_import_check_targets superglu::GLU )
list(APPEND _cmake_import_check_files_for_superglu::GLU "${_IMPORT_PREFIX}/lib/GLUsd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
