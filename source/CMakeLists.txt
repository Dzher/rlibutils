set(LIB_SOURCES
    utils.cpp
    motioner.cpp
)


add_library(rlibutils
    SHARED
    ${LIB_SOURCES}
)

target_link_libraries(rlibutils ${RL_LIBRARIES})

if(WIN32)
    target_compile_definitions(rlibutils PRIVATE R_LIB_UTILS_EXPORTS)
    target_compile_definitions(rlibutils PUBLIC R_LIB_UTILS_IMPORTS)
endif()

set_target_properties(rlibutils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)