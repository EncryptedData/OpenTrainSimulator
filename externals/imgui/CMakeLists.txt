
set(IMGUI_SRC src/imgui.cpp
        src/imgui_draw.cpp
        src/imgui_impl_sdl3.cpp
        src/imgui_impl_vulkan.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp)

add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)