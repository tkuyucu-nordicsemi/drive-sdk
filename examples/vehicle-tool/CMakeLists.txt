set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET (CMAKE_C_FLAGS      "")

include(FindGLIB2)
include(FindReadline)

include_directories(${drivekit_SOURCE_DIR}/include
                    ${bzle_SOURCE_DIR}/include
                    ${GLIB2_INCLUDE_DIRS}
                    ${READLINE_INCLUDE_DIR}
                    )


# Add sources
set(vehicleTool_SOURCES
                vehicle_tool.c
                vehicle_cmd.c
                display.c
)

add_executable(vehicle-tool ${vehicleTool_SOURCES})
target_link_libraries(vehicle-tool
                    ankidrive
                    bzle
                    ${GLIB2_LIBRARIES}
                    ${READLINE_LIBRARY}
)
install(TARGETS vehicle-tool 
    RUNTIME DESTINATION bin
)
