
set(GRAPHICS_SRC src/RenderDevice.cpp)

add_library(graphics ${GRAPHICS_SRC})
setup_common_target_flags(graphics)
target_link_libraries(graphics PUBLIC Vulkan::Vulkan vk-bootstrap)