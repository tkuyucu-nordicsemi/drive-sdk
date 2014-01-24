set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET (CMAKE_C_FLAGS      "")


set(bluez_SOURCE_DIR $ENV{BLUEZ_ROOT})

add_library(bluez STATIC IMPORTED)
set_property(TARGET bluez PROPERTY IMPORTED_LOCATION ${bluez_SOURCE_DIR}/lib/.libs/libbluetooth-internal.a)

include(FindGLIB2)
include(FindReadline)

include_directories(${drivekit_SOURCE_DIR}/include
                    ${bluez_SOURCE_DIR}/lib 
                    ${GLIB2_INCLUDE_DIRS}
                    ${READLINE_INCLUDE_DIR}
                    )


# Add sources
set(vehicleTool_SOURCES
                att.c
                gatt.c
                gattrib.c
                vehicle_tool.c
                vehicle_cmd.c
                utils.c
                log.c
                btio/btio.c
                client/display.c
)

add_executable(vehicle-tool ${vehicleTool_SOURCES})
target_link_libraries(vehicle-tool
                    ankidrive
                    bluez
                    ${GLIB2_LIBRARIES}
                    ${READLINE_LIBRARY}
                    )
