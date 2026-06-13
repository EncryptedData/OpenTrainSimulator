
set(CORE_SRC src/GameState.cpp
    src/io/PhyscialFileStream.cpp)

add_library(core ${CORE_SRC})
setup_common_target_flags(core)
target_link_libraries(core PUBLIC glm)