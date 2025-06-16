#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ATIDAQ::ATIDAQ" for configuration "Release"
set_property(TARGET ATIDAQ::ATIDAQ APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ATIDAQ::ATIDAQ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/atidaqs.lib"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::ATIDAQ )
list(APPEND _cmake_import_check_files_for_ATIDAQ::ATIDAQ "${_IMPORT_PREFIX}/lib/atidaqs.lib" )

# Import target "ATIDAQ::calinfo" for configuration "Release"
set_property(TARGET ATIDAQ::calinfo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ATIDAQ::calinfo PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/calinfo.exe"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::calinfo )
list(APPEND _cmake_import_check_files_for_ATIDAQ::calinfo "${_IMPORT_PREFIX}/bin/calinfo.exe" )

# Import target "ATIDAQ::ftconvert" for configuration "Release"
set_property(TARGET ATIDAQ::ftconvert APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ATIDAQ::ftconvert PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ftconvert.exe"
  )

list(APPEND _cmake_import_check_targets ATIDAQ::ftconvert )
list(APPEND _cmake_import_check_files_for_ATIDAQ::ftconvert "${_IMPORT_PREFIX}/bin/ftconvert.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
