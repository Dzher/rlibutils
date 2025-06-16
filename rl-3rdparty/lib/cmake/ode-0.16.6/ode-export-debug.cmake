#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ODE::ODE" for configuration "Debug"
set_property(TARGET ODE::ODE APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ODE::ODE PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ode_doubled.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/ode_doubled.dll"
  )

list(APPEND _cmake_import_check_targets ODE::ODE )
list(APPEND _cmake_import_check_files_for_ODE::ODE "${_IMPORT_PREFIX}/lib/ode_doubled.lib" "${_IMPORT_PREFIX}/bin/ode_doubled.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
