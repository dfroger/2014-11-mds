enable_testing()

include_directories(
    ${TETRIS_CORE_INCLUDE}
    ${TETRIS_GTK_INCLUDE}
)

add_executable(test_tetris_gtk test_tetris_gtk.c)
target_link_libraries(test_tetris_gtk 
    ${TETRIS_CORE_LIBRARY}
    ${TETRIS_GTK_LIBRARY}
    cunit
)

add_test(test_tetris_gtk ${EXECUTABLE_OUTPUT_PATH}/test_tetris_gtk)
