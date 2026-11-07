# MicroPython for TinyDesk Shell's PC builds (POSIX, Windows): the
# interpreter (third_party/micropython), the shell's port (python/*.c) and
# the generated headers and frozen modules of one configuration.
#
#   include(${TDSH_ROOT}/python/tdsh_python.cmake)
#   tdsh_add_python(NAME tdsh_python
#       [GEN_DIR dir]          # genhdr/ and frozen/ (default: python/gen)
#       [EXTRA_SRCS files...]  # an application's own modules
#       [LINK libs...]         # what they and the port link with (tdsh, ...)
#       [COMPAT_FLAG flags]    # Windows: the shell's compat include for td_py.c
#       [BOARD_NAME name]      # the product in the banner (default TinyDesk Shell)
#       [HELP_EXTERNAL])       # the application defines td_py_help_text (help())
#
# An application with modules of its own generates its GEN_DIR with
# tools/micropython (EXT_C, MANIFEST, OUT): the tables there list its
# modules, so the shell's python/gen is not used then. The ESP-IDF builds
# use ports/esp_idf/components/micropython.

set(TDSH_PY_DIR ${CMAKE_CURRENT_LIST_DIR})
set(TDSH_MICROPYTHON_DIR ${CMAKE_CURRENT_LIST_DIR}/../third_party/micropython)
get_filename_component(TDSH_MICROPYTHON_DIR ${TDSH_MICROPYTHON_DIR} ABSOLUTE)

function(tdsh_add_python)
    cmake_parse_arguments(P "HELP_EXTERNAL" "NAME;GEN_DIR;BOARD_NAME" "EXTRA_SRCS;LINK;COMPAT_FLAG" ${ARGN})
    if(NOT P_GEN_DIR)
        set(P_GEN_DIR ${TDSH_PY_DIR}/gen)
    endif()
    include(${TDSH_MICROPYTHON_DIR}/sources.cmake)
    set(port_srcs
        ${TDSH_PY_DIR}/td_py.c
        ${TDSH_PY_DIR}/td_py_machine.c
        ${TDSH_PY_DIR}/td_py_vfs.c
        ${TDSH_PY_DIR}/td_py_socket.c
        ${TDSH_PY_DIR}/td_py_tdsh.c
        ${TDSH_PY_DIR}/td_py_tls_ca.c
        ${TDSH_PY_DIR}/hw/td_py_hw_host.c   # machine: no hardware on a PC
    )
    set(frozen ${P_GEN_DIR}/frozen/frozen_content.c)
    add_library(${P_NAME} STATIC ${TDSH_MICROPYTHON_SRCS} ${frozen} ${port_srcs} ${P_EXTRA_SRCS})
    # The generated headers first: genhdr/ of this configuration.
    target_include_directories(${P_NAME} PUBLIC ${P_GEN_DIR} ${TDSH_MICROPYTHON_DIR} ${TDSH_PY_DIR})
    target_link_libraries(${P_NAME} PUBLIC ${P_LINK})
    if(WIN32)
        target_link_libraries(${P_NAME} PUBLIC ws2_32 crypt32)   # socket; ssl's root certificates
    else()
        target_link_libraries(${P_NAME} PUBLIC m)   # floats: libm is separate on Linux
    endif()
    target_compile_definitions(${P_NAME} PUBLIC TD_WITH_PYTHON)
    if(P_BOARD_NAME)
        target_compile_definitions(${P_NAME} PRIVATE "TD_PY_BOARD_NAME=\"${P_BOARD_NAME}\"")
    endif()
    if(P_HELP_EXTERNAL)
        target_compile_definitions(${P_NAME} PRIVATE TD_PY_APP_HELP)   # the application's td_py_help_text
    endif()
    set_target_properties(${P_NAME} PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
    set_source_files_properties(${TDSH_MICROPYTHON_SRCS} ${frozen} PROPERTIES COMPILE_OPTIONS -w)   # third-party code
    # vfs_posix_file.c also defines sys.stdin/stdout/stderr on file
    # descriptors 0-2 (the process's console, the UART on a board). Rename
    # them, so sys_stdio_mphal.c's, which go through the shell session, are
    # the ones linked.
    set_source_files_properties(${TDSH_MICROPYTHON_DIR}/extmod/vfs_posix_file.c PROPERTIES COMPILE_DEFINITIONS
        "mp_sys_stdin_obj=td_py_posix_stdin_unused;mp_sys_stdout_obj=td_py_posix_stdout_unused;mp_sys_stderr_obj=td_py_posix_stderr_unused")
    # -Wno-unused-parameter: MicroPython's headers have inline stubs.
    set(warnings -Wall -Wextra -Wno-unused-parameter -Werror)
    set_source_files_properties(${port_srcs} ${P_EXTRA_SRCS} PROPERTIES COMPILE_OPTIONS "${warnings}")
    if(WIN32 AND P_COMPAT_FLAG)
        # td_py.c reads and writes the shell thread's stdin/stdout.
        set_source_files_properties(${TDSH_PY_DIR}/td_py.c PROPERTIES COMPILE_OPTIONS "${warnings};${P_COMPAT_FLAG}")
    endif()
endfunction()
