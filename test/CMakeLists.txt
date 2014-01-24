set(CMAKE_INCLUDE_CURRENT_DIR ON)

#add_library(gtest STATIC IMPORTED)
#set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${drivekit_SOURCE_DIR}/test/gtest/lib/libgtest.a)

#add_library(gtest SHARED IMPORTED)
#if(APPLE)
#set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${drivekit_SOURCE_DIR}/test/gtest/lib/libgtest.dylib)
#set_property(TARGET gtest PROPERTY RPATH ${drivekit_SOURCE_DIR}/test/gtest/lib)
#endif(APPLE)

include_directories(${drivekit_SOURCE_DIR}/src
                    )

# Add sources
set(test_SOURCES greatest.h
                test_suite.c
                test_ble_advertisement.c
                test_vehicle_advertisement.c
                test_protocol.c
)

add_executable(Test ${test_SOURCES})
target_link_libraries(Test
                    ankidrive
                    )
