set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET (CMAKE_C_FLAGS      "")

set(bluez_SOURCE_DIR $ENV{BLUEZ_ROOT})

add_library(bluez STATIC IMPORTED)
set_property(TARGET bluez PROPERTY IMPORTED_LOCATION ${bluez_SOURCE_DIR}/lib/.libs/libbluetooth-internal.a)

include_directories(${drivekit_SOURCE_DIR}/include
                    ${bluez_SOURCE_DIR}/lib 
                    )

# Add sources
set(vehiclescan_SOURCES
                vehicle-scan.c
)

add_executable(vehicle-scan ${vehiclescan_SOURCES})
target_link_libraries(vehicle-scan
                    ankidrive
                    bluez
                    )
