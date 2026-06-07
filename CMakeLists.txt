cmake_minimum_required(VERSION 3.15)

project(OpenTrainSimulator)

include(cmake/CPM.cmake)
include(cmake/SetupCommonTargetFlags.cmake)

CPMAddPackage("gh:libsdl-org/SDL#release-3.4.10")
CPMAddPackage("gh:g-truc/glm#1.0.3")
CPMAddPackage("gh:charles-lunarg/vk-bootstrap#v1.4.352")

find_package(Vulkan REQUIRED)
get_target_property(VULKAN_LIB_LOCATION Vulkan::Vulkan IMPORTED_LOCATION)
message(STATUS "Found Vulkan Library: ${VULKAN_LIB_LOCATION}")

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(game)