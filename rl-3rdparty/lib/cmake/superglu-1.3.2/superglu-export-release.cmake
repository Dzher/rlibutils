#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "superglu::GLU" for configuration "Release"
set_property(TARGET superglu::GLU APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(superglu::GLU PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/GLUs.lib"
  )

list(APPEND _cmake_import_check_targets superglu::GLU )
list(APPEND _cmake_import_check_files_for_superglu::GLU "${_IMPORT_PREFIX}/lib/GLUs.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
