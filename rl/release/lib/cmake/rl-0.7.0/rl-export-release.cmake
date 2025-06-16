#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "rl::kin" for configuration "Release"
set_property(TARGET rl::kin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rl::kin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/rlkins.lib"
  )

list(APPEND _cmake_import_check_targets rl::kin )
list(APPEND _cmake_import_check_files_for_rl::kin "${_IMPORT_PREFIX}/lib/rlkins.lib" )

# Import target "rl::mdl" for configuration "Release"
set_property(TARGET rl::mdl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rl::mdl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/rlmdls.lib"
  )

list(APPEND _cmake_import_check_targets rl::mdl )
list(APPEND _cmake_import_check_files_for_rl::mdl "${_IMPORT_PREFIX}/lib/rlmdls.lib" )

# Import target "rl::hal" for configuration "Release"
set_property(TARGET rl::hal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rl::hal PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/rlhals.lib"
  )

list(APPEND _cmake_import_check_targets rl::hal )
list(APPEND _cmake_import_check_files_for_rl::hal "${_IMPORT_PREFIX}/lib/rlhals.lib" )

# Import target "rl::sg" for configuration "Release"
set_property(TARGET rl::sg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rl::sg PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/rlsgs.lib"
  )

list(APPEND _cmake_import_check_targets rl::sg )
list(APPEND _cmake_import_check_files_for_rl::sg "${_IMPORT_PREFIX}/lib/rlsgs.lib" )

# Import target "rl::plan" for configuration "Release"
set_property(TARGET rl::plan APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(rl::plan PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/rlplans.lib"
  )

list(APPEND _cmake_import_check_targets rl::plan )
list(APPEND _cmake_import_check_files_for_rl::plan "${_IMPORT_PREFIX}/lib/rlplans.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
