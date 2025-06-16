#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SoQt::SoQt" for configuration "Release"
set_property(TARGET SoQt::SoQt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SoQt::SoQt PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/SoQt1.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/SoQt1.dll"
  )

list(APPEND _cmake_import_check_targets SoQt::SoQt )
list(APPEND _cmake_import_check_files_for_SoQt::SoQt "${_IMPORT_PREFIX}/lib/SoQt1.lib" "${_IMPORT_PREFIX}/bin/SoQt1.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
