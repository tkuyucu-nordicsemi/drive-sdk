set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET (CMAKE_C_FLAGS      "")

include_directories(${drivekit_SOURCE_DIR}/include
                    ${bzle_SOURCE_DIR}/include
                    )

# Add sources
set(vehiclescan_SOURCES
                vehicle-scan.c
)

add_executable(vehicle-scan ${vehiclescan_SOURCES})
target_link_libraries(vehicle-scan
                    ankidrive
                    bzle
)

install(TARGETS vehicle-scan 
    RUNTIME DESTINATION bin
)
