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

set(RLIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)

set_target_properties(rlibutils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${RLIB_OUTPUT_DIR}/bin  # .dll 文件输出位置
    ARCHIVE_OUTPUT_DIRECTORY ${RLIB_OUTPUT_DIR}/lib  # .lib 文件输出位置
    LIBRARY_OUTPUT_DIRECTORY ${RLIB_OUTPUT_DIR}/lib  
)


# install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${RLIB_OUTPUT_DIR}/include)
# install(TARGETS rlibutils
#     RUNTIME DESTINATION ${RLIB_OUTPUT_DIR}/bin
#     ARCHIVE DESTINATION ${RLIB_OUTPUT_DIR}/lib
#     LIBRARY DESTINATION ${RLIB_OUTPUT_DIR}/lib
# )

file(COPY ${CMAKE_SOURCE_DIR}/include DESTINATION ${RLIB_OUTPUT_DIR}/)

set(RLIB_ZIP_FILE ${RLIB_OUTPUT_DIR}/rlib.zip)

add_custom_command(
    OUTPUT ${RLIB_ZIP_FILE}
    WORKING_DIRECTORY ${RLIB_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E tar "cf" ${RLIB_ZIP_FILE} --format=zip
    include bin lib
    DEPENDS rlibutils
    COMMENT "Creating rlib.zip Archive"
)

add_custom_target(package_rlib ALL DEPENDS ${RLIB_ZIP_FILE})