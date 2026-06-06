cmake_minimum_required(VERSION 3.15)

project(OpenTrainSimulator)

include(cmake/SetupCommonTargetFlags.cmake)

add_subdirectory(core)
add_subdirectory(game)