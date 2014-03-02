cmake_minimum_required(VERSION 2.8)

project(bzle)

set(CMAKE_MODULE_PATH ${bzle_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

SET (CMAKE_C_FLAGS                "-Wall")
include(MacroOutOfSourceBuild)

macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")
 
add_subdirectory(src)
add_subdirectory(tools)
