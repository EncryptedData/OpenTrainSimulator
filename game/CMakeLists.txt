
set(GAME_SRC src/main.cpp
        src/SDLWindow.cpp)

add_executable(game ${GAME_SRC})
setup_common_target_flags(game)
target_link_libraries(game PRIVATE core SDL3::SDL3 glm::glm graphics)