#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "solid3::solid3" for configuration "Release"
set_property(TARGET solid3::solid3 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(solid3::solid3 PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/solid3.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/solid3.dll"
  )

list(APPEND _cmake_import_check_targets solid3::solid3 )
list(APPEND _cmake_import_check_files_for_solid3::solid3 "${_IMPORT_PREFIX}/lib/solid3.lib" "${_IMPORT_PREFIX}/bin/solid3.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
