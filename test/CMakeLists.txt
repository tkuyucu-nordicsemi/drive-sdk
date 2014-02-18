set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${drivekit_SOURCE_DIR}/src
                    )

# Add sources
set(test_SOURCES greatest.h
                 anki_greatest.h
                 test_suite.c
                 test_ble_advertisement.c
                 test_vehicle_advertisement.c
                 test_protocol.c
)

add_executable(Test ${test_SOURCES})
target_link_libraries(Test
                    ankidrive
                    )
