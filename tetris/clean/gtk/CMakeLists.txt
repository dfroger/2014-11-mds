find_package(GTK2 2.6 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})

add_library(${TETRIS_GTK_LIBRARY} SHARED
    rgb_color.c
)
add_executable(tetris-gtk tetris-gtk.c)
target_link_libraries(tetris-gtk 
    ${TETRIS_CORE_LIBRARY}
    ${TETRIS_GTK_LIBRARY}
    ${GTK2_LIBRARIES}
)

add_subdirectory(test)

