cmake_minimum_required(VERSION 2.8)

project(drivekit)

set(CMAKE_MODULE_PATH ${drivekit_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# Set the default install path to be './build/dist'
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) 
    set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/dist CACHE PATH "drive-sdk install prefix" FORCE) 
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) 

OPTION( BUILD_EXAMPLES                "Build example apps"                OFF )

SET (CMAKE_C_FLAGS                "-Wall -std=c99")
include(MacroOutOfSourceBuild)
include(TargetDistclean)

macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")
 
add_subdirectory(src)
add_subdirectory(test)

install(DIRECTORY include/ankidrive DESTINATION include)

if (BUILD_EXAMPLES)
    add_subdirectory(deps/bzle)
    add_subdirectory(examples)
endif ()

# CTest is flaky - Create a target to run our test suite directly
add_custom_target(test COMMAND ${PROJECT_BINARY_DIR}/test/Test)
