# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FindGLIB2)

include_directories(
    ${bzle_SOURCE_DIR}/include    
    ${GLIB2_INCLUDE_DIRS}
)

set(bzle_SOURCES
att.c bluetooth.c btio.c gatt.c gattrib.c hci.c log.h log.c sdp.c utils.c uuid.c
)

add_library(bzle ${bzle_SOURCES})
target_link_libraries(bzle
                    ${GLIB2_LIBRARIES}
                    )
