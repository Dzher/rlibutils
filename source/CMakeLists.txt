set(LIB_SOURCES
    utils.h
    utils.cpp
    motioner.h
    motioner.cpp
)

add_library(rl_utils_lib ${LIB_SOURCES})
target_link_libraries(rl_utils_lib ${RL_LIBRARIES})