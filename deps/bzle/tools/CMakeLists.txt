# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(
                    ${bzle_SOURCE_DIR}/include
                    )


set(hciconfig_SOURCES
csr.h csr.c hciconfig.c textfile.c textfile.h
)

add_executable(hciconfig ${hciconfig_SOURCES})
target_link_libraries(hciconfig
                    bzle
                    )

install(TARGETS hciconfig 
    RUNTIME DESTINATION bin
)
