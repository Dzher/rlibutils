#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SoQt::SoQt" for configuration "Debug"
set_property(TARGET SoQt::SoQt APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SoQt::SoQt PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/SoQt1d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/SoQt1d.dll"
  )

list(APPEND _cmake_import_check_targets SoQt::SoQt )
list(APPEND _cmake_import_check_files_for_SoQt::SoQt "${_IMPORT_PREFIX}/lib/SoQt1d.lib" "${_IMPORT_PREFIX}/bin/SoQt1d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
