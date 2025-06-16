#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LibXslt::LibXslt" for configuration "Debug"
set_property(TARGET LibXslt::LibXslt APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LibXslt::LibXslt PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libxsltd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libxsltd.dll"
  )

list(APPEND _cmake_import_check_targets LibXslt::LibXslt )
list(APPEND _cmake_import_check_files_for_LibXslt::LibXslt "${_IMPORT_PREFIX}/lib/libxsltd.lib" "${_IMPORT_PREFIX}/bin/libxsltd.dll" )

# Import target "LibXslt::LibExslt" for configuration "Debug"
set_property(TARGET LibXslt::LibExslt APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LibXslt::LibExslt PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libexsltd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libexsltd.dll"
  )

list(APPEND _cmake_import_check_targets LibXslt::LibExslt )
list(APPEND _cmake_import_check_files_for_LibXslt::LibExslt "${_IMPORT_PREFIX}/lib/libexsltd.lib" "${_IMPORT_PREFIX}/bin/libexsltd.dll" )

# Import target "LibXslt::xsltproc" for configuration "Debug"
set_property(TARGET LibXslt::xsltproc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LibXslt::xsltproc PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/xsltproc.exe"
  )

list(APPEND _cmake_import_check_targets LibXslt::xsltproc )
list(APPEND _cmake_import_check_files_for_LibXslt::xsltproc "${_IMPORT_PREFIX}/bin/xsltproc.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
