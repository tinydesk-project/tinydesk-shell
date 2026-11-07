# The micropython component of TinyDesk Shell's firmware: the interpreter
# (third_party/micropython), the shell's port (python/), and the generated
# headers and frozen modules of one configuration.
#
# The shell's own component (CMakeLists.txt next to this file) uses
# python/gen. An application with Python modules of its own makes a
# component named micropython in a component directory listed after the
# shell's (it then replaces this one) and calls:
#
#   include(${TDSH_SDK_ROOT}/ports/esp_idf/components/micropython/micropython_component.cmake)
#   tdsh_micropython_component(GEN_DIR dir EXTRA_SRCS files... EXTRA_INCLUDES dirs...
#                              EXTRA_REQUIRES components... [BOARD_NAME name]
#                              [HELP_EXTERNAL])
#
# HELP_EXTERNAL: the application defines td_py_help_text (see td_py.h).

set(TDSH_PY_COMPONENT_DIR "${CMAKE_CURRENT_LIST_DIR}")
get_filename_component(TDSH_PY_SDK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE)

# A macro, not a function: ESP-IDF's first pass over the components reads
# what idf_component_register sets in the component's own scope.
macro(tdsh_micropython_component)
    cmake_parse_arguments(P "HELP_EXTERNAL" "GEN_DIR;BOARD_NAME" "EXTRA_SRCS;EXTRA_INCLUDES;EXTRA_REQUIRES" ${ARGN})
    set(TDSH_MICROPYTHON_DIR "${TDSH_PY_SDK_ROOT}/third_party/micropython")
    set(py_dir "${TDSH_PY_SDK_ROOT}/python")
    if(NOT P_GEN_DIR)
        set(P_GEN_DIR "${py_dir}/gen")
    endif()
    include("${TDSH_MICROPYTHON_DIR}/sources.cmake")
    set(port_srcs
        "${py_dir}/td_py.c"
        "${py_dir}/td_py_machine.c"
        "${py_dir}/td_py_vfs.c"
        "${py_dir}/td_py_socket.c"
        "${py_dir}/td_py_tls_ca.c"
        "${py_dir}/hw/td_py_hw_esp.c"   # machine: the chip's drivers
        "${py_dir}/hw/td_py_hw_pins.c"
        ${P_EXTRA_SRCS}
    )
    set(frozen "${P_GEN_DIR}/frozen/frozen_content.c")
    idf_component_register(
        SRCS ${TDSH_MICROPYTHON_SRCS} ${frozen} ${port_srcs}
        # The generated headers first: genhdr/ of this configuration.
        INCLUDE_DIRS "${P_GEN_DIR}" "${TDSH_MICROPYTHON_DIR}" "${py_dir}" ${P_EXTRA_INCLUDES}
        PRIV_INCLUDE_DIRS "${TDSH_PY_COMPONENT_DIR}/include"   # poll.h for extmod/vfs_posix_file.c
        # mbedtls: hashlib; the drivers and esp_adc: machine
        REQUIRES tdsh esp_timer vfs mbedtls lwip esp_netif esp_driver_gpio esp_driver_ledc esp_driver_i2c
                 esp_driver_spi esp_driver_uart esp_driver_rmt esp_adc ${P_EXTRA_REQUIRES}
    )
    # Configure again when this file changes (CMake only tracks CMakeLists.txt).
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${TDSH_PY_COMPONENT_DIR}/micropython_component.cmake")
    target_compile_definitions(${COMPONENT_LIB} PUBLIC TD_WITH_PYTHON)
    if(P_BOARD_NAME)
        target_compile_definitions(${COMPONENT_LIB} PRIVATE "TD_PY_BOARD_NAME=\"${P_BOARD_NAME}\"")
    endif()
    if(P_HELP_EXTERNAL)
        target_compile_definitions(${COMPONENT_LIB} PRIVATE TD_PY_APP_HELP)   # the application's td_py_help_text
    endif()
    if(IDF_TARGET STREQUAL "esp32s3")
        target_compile_definitions(${COMPONENT_LIB} PUBLIC TD_PY_ESP32S3)   # the banner's chip name
    endif()
    set_source_files_properties(${TDSH_MICROPYTHON_SRCS} ${frozen} PROPERTIES COMPILE_OPTIONS "-w")   # third-party code
    # vfs_posix_file.c also defines sys.stdin/stdout/stderr on file
    # descriptors 0-2 (the UART console). Rename them, so sys_stdio_mphal.c's,
    # which go through the shell session, are the ones linked.
    set_source_files_properties("${TDSH_MICROPYTHON_DIR}/extmod/vfs_posix_file.c" PROPERTIES COMPILE_DEFINITIONS
        "mp_sys_stdin_obj=td_py_posix_stdin_unused;mp_sys_stdout_obj=td_py_posix_stdout_unused;mp_sys_stderr_obj=td_py_posix_stderr_unused")
    # -Wno-unused-parameter: MicroPython's headers have inline stubs.
    set_source_files_properties(${port_srcs} PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Wno-unused-parameter;-Werror")
endmacro()
