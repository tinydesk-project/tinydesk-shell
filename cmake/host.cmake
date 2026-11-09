cmake_minimum_required(VERSION 3.16)
project(tdsh C)

option(TDSH_BUILD_POSIX "Build the POSIX host port" ON)
option(TDSH_BUILD_TESTS "Build portable regression tests" ON)
set(TDSH_TEST_MBEDTLS_DIR "" CACHE PATH "Optional mbedTLS 3.x source for production account-store tests")
option(TDSH_WITH_PYTHON "Build the py command (MicroPython) into the host program" ON)
# ssl in py needs mbedTLS 3.x: this source tree, or ESP-IDF's copy when one
# is installed; without it py has no TLS (sockets work).
set(TDSH_MBEDTLS_DIR "" CACHE PATH "mbedTLS 3.x source tree for ssl in py (default: ESP-IDF's)")
if(TDSH_WITH_PYTHON AND NOT TDSH_MBEDTLS_DIR)
    foreach(cand "$ENV{IDF_PATH}/components/mbedtls/mbedtls"
                 "C:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls"
                 "$ENV{HOME}/esp/esp-idf/components/mbedtls/mbedtls")
        if(EXISTS "${cand}/include/mbedtls/ssl.h")
            set(TDSH_MBEDTLS_DIR "${cand}")
            break()
        endif()
    endforeach()
endif()
# Release builds set this, so a program without ssl is never published.
option(TDSH_REQUIRE_TLS "Fail when py would be built without ssl (no mbedTLS found)" OFF)
if(TDSH_MBEDTLS_DIR AND NOT EXISTS "${TDSH_MBEDTLS_DIR}/include/mbedtls/ssl.h")
    message(FATAL_ERROR "tdsh: TDSH_MBEDTLS_DIR=${TDSH_MBEDTLS_DIR} is not an mbedTLS 3.x source tree (no include/mbedtls/ssl.h)")
endif()
if(TDSH_REQUIRE_TLS AND TDSH_WITH_PYTHON AND NOT TDSH_MBEDTLS_DIR)
    message(FATAL_ERROR "tdsh: TDSH_REQUIRE_TLS is on but no mbedTLS was found; pass -DTDSH_MBEDTLS_DIR=<mbedTLS 3.x source>")
endif()
# py with TLS when mbedTLS was found.
macro(tdsh_python_tls)
    if(TDSH_MBEDTLS_DIR)
        message(STATUS "tdsh: ssl in py with mbedTLS from ${TDSH_MBEDTLS_DIR}")
        if(NOT TARGET mbedcrypto)
            set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)
            set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
            set(MBEDTLS_FATAL_WARNINGS OFF CACHE BOOL "" FORCE)
            set(GEN_FILES OFF CACHE BOOL "" FORCE)
            add_subdirectory(${TDSH_MBEDTLS_DIR} ${CMAKE_BINARY_DIR}/mbedtls EXCLUDE_FROM_ALL)
        endif()
        target_compile_definitions(tdsh_python PRIVATE TD_PY_MBEDTLS)
        target_link_libraries(tdsh_python PRIVATE mbedtls mbedx509 mbedcrypto)
        if(WIN32)
            target_link_libraries(tdsh_python PRIVATE bcrypt)
        endif()
    else()
        message(STATUS "tdsh: no mbedTLS found, py without ssl")
    endif()
endmacro()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(tdsh_core STATIC
    src/core/tdsh_core.c
    src/core/tdsh_path.c
    src/core/tdsh_parser.c
    src/core/tdsh_script.c
    src/core/tdsh_builtin.c
    src/core/tdsh_venv.c
    src/core/tdsh_terminal.c
    src/core/tdsh_board.c
)
target_include_directories(tdsh_core PUBLIC include)
target_compile_options(tdsh_core PRIVATE -Wall -Wextra -Wpedantic)
if(TDSH_BUILD_TESTS)
    enable_testing()
    add_executable(tdsh_permissions_tests tests/test_permissions.c)
    target_link_libraries(tdsh_permissions_tests PRIVATE tdsh_core)
    add_test(NAME tdsh_permissions_tests COMMAND tdsh_permissions_tests)
endif()

# The public API against api/tdsh.api (tools/check_api.py; see STABILITY.md).
if(TDSH_BUILD_TESTS)
    find_package(Python3 COMPONENTS Interpreter)
    if(Python3_FOUND)
        enable_testing()
        set(TDSH_PUBLIC_HEADERS
            include/tdsh.h include/tdsh_board.h include/tdsh_console_access.h
            include/tdsh_permissions.h include/tdsh_platform.h include/tdsh_terminal.h
            ports/esp_idf/components/tdsh/include/tdsh_espidf.h
            ports/posix/tdsh_posix.h ports/windows/tdsh_platform_win.h
            python/td_py.h python/td_py_tdsh.h)
        add_test(NAME tdsh_api_stable
                 COMMAND ${Python3_EXECUTABLE} tools/check_api.py api/tdsh.api ${TDSH_PUBLIC_HEADERS}
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        # The board.conf keys the code reads against api/board_keys.txt.
        add_test(NAME tdsh_board_keys
                 COMMAND ${Python3_EXECUTABLE} tools/check_board_keys.py api/board_keys.txt src ports main python
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
endif()

if(TDSH_BUILD_TESTS AND TDSH_TEST_MBEDTLS_DIR AND NOT MSVC)
    if(NOT TARGET mbedcrypto)
        set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)
        set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
        set(MBEDTLS_FATAL_WARNINGS OFF CACHE BOOL "" FORCE)
        set(GEN_FILES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${TDSH_TEST_MBEDTLS_DIR} ${CMAKE_BINARY_DIR}/mbedtls EXCLUDE_FROM_ALL)
    endif()
    add_executable(tdsh_users_storage_tests tests/test_users_storage.c)
    target_include_directories(tdsh_users_storage_tests PRIVATE tests/users_stubs)
    target_link_libraries(tdsh_users_storage_tests PRIVATE tdsh_core mbedcrypto)
    if(WIN32)
        target_link_libraries(tdsh_users_storage_tests PRIVATE bcrypt)
    endif()
    target_compile_options(tdsh_users_storage_tests PRIVATE -Wall -Wextra -Werror)
    add_test(NAME tdsh_users_storage_tests COMMAND tdsh_users_storage_tests)
endif()

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
    if(TDSH_WITH_PYTHON)
        include(${CMAKE_CURRENT_SOURCE_DIR}/python/tdsh_python.cmake)
        tdsh_add_python(NAME tdsh_python LINK tdsh_core COMPAT_FLAG ${TDSH_WIN_COMPAT})
        tdsh_python_tls()
        target_link_libraries(tdsh_host PRIVATE tdsh_python)
        # py's modules against python/py_contract.json (STABILITY.md).
        if(TDSH_BUILD_TESTS AND Python3_FOUND AND TDSH_MBEDTLS_DIR)   # the contract has ssl
            add_test(NAME tdsh_py_contract
                     COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_py_contract.py
                             $<TARGET_FILE:tdsh_host>)
        endif()
        set(TDSH_SMOKE_PY "py -c \"print('py', 6 * 7)\"\n")
        set(TDSH_SMOKE_PY_EXPECT ".*py 42")
    endif()

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
${TDSH_SMOKE_PY}exit
")
        add_test(NAME tdsh_windows_smoke
                 COMMAND ${CMAKE_COMMAND} -DPROGRAM=$<TARGET_FILE:tdsh_host>
                         -DINPUT=${CMAKE_CURRENT_BINARY_DIR}/smoke_input.txt
                         -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/run_with_input.cmake)
        set_tests_properties(tdsh_windows_smoke PROPERTIES
            ENVIRONMENT "LOCALAPPDATA=${CMAKE_CURRENT_BINARY_DIR}/appdata"
            PASS_REGULAR_EXPRESSION "TinyDesk Shell [0-9.]+ [(]windows[)].*sum=42.*hi${TDSH_SMOKE_PY_EXPECT}")
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
    if(TDSH_WITH_PYTHON)
        include(${CMAKE_CURRENT_SOURCE_DIR}/python/tdsh_python.cmake)
        tdsh_add_python(NAME tdsh_python LINK tdsh_core)
        tdsh_python_tls()
        target_link_libraries(tdsh_host PRIVATE tdsh_python)
        # py's modules against python/py_contract.json (STABILITY.md).
        if(TDSH_BUILD_TESTS AND Python3_FOUND AND TDSH_MBEDTLS_DIR)   # the contract has ssl
            add_test(NAME tdsh_py_contract
                     COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_py_contract.py
                             $<TARGET_FILE:tdsh_host>)
        endif()
    endif()
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
