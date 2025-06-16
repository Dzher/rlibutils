set(ATIDAQ_VERSION "1.0.6")
set(ATIDAQ_VERSION_MAJOR "1")
set(ATIDAQ_VERSION_MINOR "0")
set(ATIDAQ_VERSION_PATCH "6")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was atidaq-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/atidaq-export.cmake")

set(ATIDAQ_DEFINITIONS "")
set(ATIDAQ_INCLUDE_DIR ${PACKAGE_PREFIX_DIR}/include)

macro(select_library_location target basename)
	if(TARGET ${target})
		foreach(property IN ITEMS IMPORTED_LOCATION IMPORTED_IMPLIB)
			get_target_property(${basename}_${property}_DEBUG ${target} ${property}_DEBUG)
			get_target_property(${basename}_${property}_MINSIZEREL ${target} ${property}_MINSIZEREL)
			get_target_property(${basename}_${property}_RELEASE ${target} ${property}_RELEASE)
			get_target_property(${basename}_${property}_RELWITHDEBINFO ${target} ${property}_RELWITHDEBINFO)
			
			if(${basename}_${property}_DEBUG AND ${basename}_${property}_RELEASE)
				set(${basename}_LIBRARY debug ${${basename}_${property}_DEBUG} optimized ${${basename}_${property}_RELEASE})
			elseif(${basename}_${property}_DEBUG AND ${basename}_${property}_RELWITHDEBINFO)
				set(${basename}_LIBRARY debug ${${basename}_${property}_DEBUG} optimized ${${basename}_${property}_RELWITHDEBINFO})
			elseif(${basename}_${property}_DEBUG AND ${basename}_${property}_MINSIZEREL)
				set(${basename}_LIBRARY debug ${${basename}_${property}_DEBUG} optimized ${${basename}_${property}_MINSIZEREL})
			elseif(${basename}_${property}_RELEASE)
				set(${basename}_LIBRARY ${${basename}_${property}_RELEASE})
			elseif(${basename}_${property}_RELWITHDEBINFO)
				set(${basename}_LIBRARY ${${basename}_${property}_RELWITHDEBINFO})
			elseif(${basename}_${property}_MINSIZEREL)
				set(${basename}_LIBRARY ${${basename}_${property}_MINSIZEREL})
			elseif(${basename}_${property}_DEBUG)
				set(${basename}_LIBRARY ${${basename}_${property}_DEBUG})
			endif()
		endforeach()
	endif()
endmacro()

macro(select_executable_location target basename)
	if(TARGET ${target})
		get_target_property(${basename}_IMPORTED_LOCATION_DEBUG ${target} IMPORTED_LOCATION_DEBUG)
		get_target_property(${basename}_IMPORTED_LOCATION_MINSIZEREL ${target} IMPORTED_LOCATION_MINSIZEREL)
		get_target_property(${basename}_IMPORTED_LOCATION_RELEASE ${target} IMPORTED_LOCATION_RELEASE)
		get_target_property(${basename}_IMPORTED_LOCATION_RELWITHDEBINFO ${target} IMPORTED_LOCATION_RELWITHDEBINFO)
		
		if(${basename}_IMPORTED_LOCATION_RELEASE)
			set(${basename}_EXECUTABLE ${${basename}_IMPORTED_LOCATION_RELEASE})
		elseif(${basename}_IMPORTED_LOCATION_RELWITHDEBINFO)
			set(${basename}_EXECUTABLE ${${basename}_IMPORTED_LOCATION_RELWITHDEBINFO})
		elseif(${basename}_IMPORTED_LOCATION_MINSIZEREL)
			set(${basename}_EXECUTABLE ${${basename}_IMPORTED_LOCATION_MINSIZEREL})
		elseif(${basename}_IMPORTED_LOCATION_DEBUG)
			set(${basename}_EXECUTABLE ${${basename}_IMPORTED_LOCATION_DEBUG})
		endif()
	endif()
endmacro()

select_library_location(ATIDAQ::ATIDAQ ATIDAQ)
select_executable_location(ATIDAQ::calinfo ATIDAQ_CALINFO)
select_executable_location(ATIDAQ::ftconvert ATIDAQ_FTCONVERT)

set(ATIDAQ_INCLUDE_DIRS ${ATIDAQ_INCLUDE_DIR})
set(ATIDAQ_LIBRARIES ${ATIDAQ_LIBRARY})

if(NOT ATIDAQ_SHARED)
	if(UNIX)
		list(APPEND ATIDAQ_LIBRARIES m)
	endif()
endif()
