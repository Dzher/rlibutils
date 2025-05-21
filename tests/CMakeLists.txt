set(TARGET_NAME rl_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${TARGET_NAME} 
    main.cpp
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
    rl_utils_lib
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE "DEBUG")
endif()

# add_dependencies(${TARGET_NAME} robotflowedit)