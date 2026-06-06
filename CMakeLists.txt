cmake_minimum_required(VERSION 3.15)

project(OpenTrainSimulator)

include(cmake/CPM.cmake)
include(cmake/SetupCommonTargetFlags.cmake)

CPMAddPackage("gh:libsdl-org/SDL#release-3.4.10")
CPMAddPackage("gh:g-truc/glm#1.0.3")
find_package(Vulkan)

add_subdirectory(core)
add_subdirectory(game)