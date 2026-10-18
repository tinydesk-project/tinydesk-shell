cmake_minimum_required(VERSION 3.16)
project(tdsh C)

option(TDSH_BUILD_POSIX "Build the POSIX host port" ON)
option(TDSH_BUILD_TESTS "Build portable regression tests" ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(tdsh_core STATIC
    src/core/tdsh_core.c
    src/core/tdsh_path.c
    src/core/tdsh_parser.c
    src/core/tdsh_script.c
    src/core/tdsh_builtin.c
    src/core/tdsh_terminal.c
    src/core/tdsh_board.c
)
target_include_directories(tdsh_core PUBLIC include)
target_compile_options(tdsh_core PRIVATE -Wall -Wextra -Wpedantic)

if(WIN32)
    # Windows (MinGW-w64, UCRT): the core expects newlib/glibc stdio; the
    # compat layer adds per-thread stdin/stdout, funopen() and mkdir(path,
    # mode). It is force-included everywhere except in its own source.
    set(TDSH_WIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ports/windows)
    set(TDSH_WIN_COMPAT -include ${TDSH_WIN_DIR}/tdsh_win_compat.h)
    add_library(tdsh_wincompat STATIC ${TDSH_WIN_DIR}/tdsh_win_compat.c)
    target_include_directories(tdsh_wincompat PUBLIC ${TDSH_WIN_DIR})
    target_compile_options(tdsh_core PRIVATE ${TDSH_WIN_COMPAT})
    target_link_libraries(tdsh_core PUBLIC tdsh_wincompat)

    add_library(tdsh_win STATIC
        ${TDSH_WIN_DIR}/tdsh_platform_win.c
        ${TDSH_WIN_DIR}/tdsh_win_commands.c
        ${TDSH_WIN_DIR}/tdsh_win_console.c
    )
    target_include_directories(tdsh_win PUBLIC include ${TDSH_WIN_DIR})
    target_compile_options(tdsh_win PRIVATE ${TDSH_WIN_COMPAT})
    # ifconfig and ping use the IP Helper API.
    target_link_libraries(tdsh_win PUBLIC tdsh_core iphlpapi ws2_32)

    add_executable(tdsh_host examples/windows/main.c)
    target_compile_options(tdsh_host PRIVATE ${TDSH_WIN_COMPAT})
    target_link_libraries(tdsh_host PRIVATE tdsh_win)

    if(TDSH_BUILD_TESTS)
        enable_testing()
        add_executable(tdsh_console_access_tests tests/test_console_access.c)
        target_include_directories(tdsh_console_access_tests PRIVATE include)
        add_test(NAME tdsh_console_access_tests COMMAND tdsh_console_access_tests)
        add_executable(tdsh_board_tests tests/test_board.c)
        target_compile_options(tdsh_board_tests PRIVATE ${TDSH_WIN_COMPAT})
        target_link_libraries(tdsh_board_tests PRIVATE tdsh_core)
        add_test(NAME tdsh_board_tests COMMAND tdsh_board_tests)
        add_executable(tdsh_mem_tests tests/test_mem.c)
        target_compile_options(tdsh_mem_tests PRIVATE ${TDSH_WIN_COMPAT} -Wall -Wextra -Wpedantic)
        target_link_libraries(tdsh_mem_tests PRIVATE tdsh_core)
        add_test(NAME tdsh_mem_tests COMMAND tdsh_mem_tests)
        add_executable(tdsh_script_oom_tests tests/test_script_oom.c)
        target_compile_options(tdsh_script_oom_tests PRIVATE ${TDSH_WIN_COMPAT} -Wall -Wextra -Wpedantic)
        target_link_libraries(tdsh_script_oom_tests PRIVATE tdsh_core)
        add_test(NAME tdsh_script_oom_tests COMMAND tdsh_script_oom_tests)
        add_executable(tdsh_nano_tests tests/test_nano.c ports/posix/tdsh_nano_posix.c)
        target_compile_options(tdsh_nano_tests PRIVATE ${TDSH_WIN_COMPAT} -Wall -Wextra -Wpedantic)
        target_link_libraries(tdsh_nano_tests PRIVATE tdsh_core)
        add_test(NAME tdsh_nano_tests COMMAND tdsh_nano_tests)
        add_executable(tdsh_terminal_wrap_tests tests/test_terminal_wrap.c)
        target_compile_options(tdsh_terminal_wrap_tests PRIVATE ${TDSH_WIN_COMPAT} -Wall -Wextra -Wpedantic)
        target_link_libraries(tdsh_terminal_wrap_tests PRIVATE tdsh_core)
        add_test(NAME tdsh_terminal_wrap_tests COMMAND tdsh_terminal_wrap_tests)
        # The program itself, fed from a pipe, with its files in the build folder.
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/smoke_input.txt
             "version
echo sum=$((6 * 7))
mkdir -p ~/t
echo hi > ~/t/a.txt
cat ~/t/a.txt
exit
")
        add_test(NAME tdsh_windows_smoke
                 COMMAND ${CMAKE_COMMAND} -DPROGRAM=$<TARGET_FILE:tdsh_host>
                         -DINPUT=${CMAKE_CURRENT_BINARY_DIR}/smoke_input.txt
                         -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/run_with_input.cmake)
        set_tests_properties(tdsh_windows_smoke PROPERTIES
            ENVIRONMENT "LOCALAPPDATA=${CMAKE_CURRENT_BINARY_DIR}/appdata"
            PASS_REGULAR_EXPRESSION "TinyDesk Shell [0-9.]+ [(]windows[)].*sum=42.*hi")
    endif()
    return()
endif()

if(TDSH_BUILD_POSIX)
    add_library(tdsh_posix STATIC
        ports/posix/tdsh_posix.c
        ports/posix/tdsh_posix_commands.c
        ports/posix/tdsh_nano_posix.c
    )
    target_include_directories(tdsh_posix PUBLIC include ports/posix)
    target_link_libraries(tdsh_posix PUBLIC tdsh_core pthread)
    target_compile_options(tdsh_posix PRIVATE -Wall -Wextra -Wpedantic)

    add_executable(tdsh_host examples/posix/main.c)
    target_link_libraries(tdsh_host PRIVATE tdsh_posix)
endif()

if(TDSH_BUILD_TESTS)
    enable_testing()
    add_executable(tdsh_console_access_tests tests/test_console_access.c)
    target_include_directories(tdsh_console_access_tests PRIVATE include)
    add_test(NAME tdsh_console_access_tests COMMAND tdsh_console_access_tests)
    add_executable(tdsh_core_tests tests/test_core.c)
    target_include_directories(tdsh_core_tests PRIVATE ports/posix)
    target_link_libraries(tdsh_core_tests PRIVATE tdsh_posix)
    add_test(NAME tdsh_core_tests COMMAND tdsh_core_tests)

    add_executable(tdsh_board_tests tests/test_board.c)
    target_link_libraries(tdsh_board_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_board_tests COMMAND tdsh_board_tests)

    add_executable(tdsh_mem_tests tests/test_mem.c)
    target_compile_options(tdsh_mem_tests PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(tdsh_mem_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_mem_tests COMMAND tdsh_mem_tests)
    add_executable(tdsh_script_oom_tests tests/test_script_oom.c)
    target_compile_options(tdsh_script_oom_tests PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(tdsh_script_oom_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_script_oom_tests COMMAND tdsh_script_oom_tests)

    add_executable(tdsh_nano_tests tests/test_nano.c ports/posix/tdsh_nano_posix.c)
    target_compile_options(tdsh_nano_tests PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(tdsh_nano_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_nano_tests COMMAND tdsh_nano_tests)

    add_executable(tdsh_memory_stress tests/test_memory_stress.c)
    target_include_directories(tdsh_memory_stress PRIVATE ports/posix)
    target_link_libraries(tdsh_memory_stress PRIVATE tdsh_posix)
    add_test(NAME tdsh_memory_stress COMMAND tdsh_memory_stress)

    add_executable(tdsh_posix_host_mapping_tests tests/test_posix_host_mapping.c)
    target_include_directories(tdsh_posix_host_mapping_tests PRIVATE ports/posix)
    target_link_libraries(tdsh_posix_host_mapping_tests PRIVATE tdsh_posix)
    add_test(NAME tdsh_posix_host_mapping_tests COMMAND tdsh_posix_host_mapping_tests)

    add_executable(tdsh_terminal_editor_tests tests/test_terminal_editor.c)
    target_include_directories(tdsh_terminal_editor_tests PRIVATE ports/posix)
    target_link_libraries(tdsh_terminal_editor_tests PRIVATE tdsh_posix)
    add_test(NAME tdsh_terminal_editor_tests COMMAND tdsh_terminal_editor_tests)

    add_executable(tdsh_terminal_wrap_tests tests/test_terminal_wrap.c)
    target_compile_options(tdsh_terminal_wrap_tests PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(tdsh_terminal_wrap_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_terminal_wrap_tests COMMAND tdsh_terminal_wrap_tests)

    add_executable(tdsh_full_uscript_tests tests/test_full_uscript.c)
    target_include_directories(tdsh_full_uscript_tests PRIVATE ports/posix)
    target_compile_definitions(tdsh_full_uscript_tests PRIVATE TDSH_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_libraries(tdsh_full_uscript_tests PRIVATE tdsh_posix)
    add_test(NAME tdsh_full_uscript_tests COMMAND tdsh_full_uscript_tests)
endif()
