#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ATIDAQ::ATIDAQ" for configuration "Debug"
set_property(TARGET ATIDAQ::ATIDAQ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ATIDAQ::ATIDAQ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/atidaqsd.lib"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::ATIDAQ )
list(APPEND _cmake_import_check_files_for_ATIDAQ::ATIDAQ "${_IMPORT_PREFIX}/lib/atidaqsd.lib" )

# Import target "ATIDAQ::calinfo" for configuration "Debug"
set_property(TARGET ATIDAQ::calinfo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ATIDAQ::calinfo PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/calinfo.exe"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::calinfo )
list(APPEND _cmake_import_check_files_for_ATIDAQ::calinfo "${_IMPORT_PREFIX}/bin/calinfo.exe" )

# Import target "ATIDAQ::ftconvert" for configuration "Debug"
set_property(TARGET ATIDAQ::ftconvert APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ATIDAQ::ftconvert PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/ftconvert.exe"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::ftconvert )
list(APPEND _cmake_import_check_files_for_ATIDAQ::ftconvert "${_IMPORT_PREFIX}/bin/ftconvert.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
