set(TARGET_NAME test_forward)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${TARGET_NAME}
    main.cpp
)

target_include_directories(${TARGET_NAME}
    PRIVATE
    ../common.h
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
    rlibutils
)

add_custom_command(TARGET test_forward POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:rlibutils> 
        $<TARGET_FILE_DIR:test_forward>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE "DEBUG")
endif()
