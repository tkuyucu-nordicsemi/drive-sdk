cmake_minimum_required(VERSION 2.8)

project(drivekit)

set(CMAKE_MODULE_PATH ${drivekit_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

OPTION( BUILD_EXAMPLES                "Build example apps"                OFF )

SET (CMAKE_C_FLAGS                "-Wall -std=c99")
include(MacroOutOfSourceBuild)

macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")
 
add_subdirectory(src)
add_subdirectory(test)
if (BUILD_EXAMPLES)
    add_subdirectory(deps/bzle)
    add_subdirectory(examples)
endif ()

enable_testing()

add_test(NAME TestSuite COMMAND Test)

