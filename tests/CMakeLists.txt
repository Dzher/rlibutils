set(TARGET_NAME rl_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${TARGET_NAME} 
    main.cpp
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
    rlibutils
)

add_custom_command(TARGET rl_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:rlibutils> 
        $<TARGET_FILE_DIR:rl_test>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE "DEBUG")
endif()
