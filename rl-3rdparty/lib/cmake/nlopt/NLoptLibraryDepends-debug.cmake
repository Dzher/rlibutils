#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "NLopt::nlopt" for configuration "Debug"
set_property(TARGET NLopt::nlopt APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(NLopt::nlopt PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/nloptd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/nloptd.dll"
  )

list(APPEND _cmake_import_check_targets NLopt::nlopt )
list(APPEND _cmake_import_check_files_for_NLopt::nlopt "${_IMPORT_PREFIX}/lib/nloptd.lib" "${_IMPORT_PREFIX}/bin/nloptd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
