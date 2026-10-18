# Official ESP-IDF port for the portable TinyDesk Shell.
# The portable core remains in the repository root and contains no ESP-IDF headers.
get_filename_component(TDSH_SDK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE)

idf_component_register(
    SRCS
        "${TDSH_SDK_ROOT}/src/core/tdsh_core.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_path.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_parser.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_script.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_builtin.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_terminal.c"
        "${TDSH_SDK_ROOT}/src/core/tdsh_board.c"
        "src/tdsh_console_espidf.c"
        "src/tdsh_platform_espidf.c"
        "src/tdsh_fs_espidf.c"
        "src/tdsh_commands_espidf.c"
        "src/tdsh_users.c"
        "src/tdsh_wifi.c"
        "src/tdsh_ethernet.c"
        "src/tdsh_network.c"
        "src/tdsh_netmount.c"
        "src/tdsh_sdcard.c"
        "src/tdsh_time.c"
        "src/tdsh_ping.c"
        "src/tdsh_ftp.c"
        "src/tdsh_editor.c"
        "src/tdsh_nano.c"
        "src/tdsh_hwtest.c"
        "src/tdsh_ssh.c"
        "src/tdsh_md5_rom.c"
    INCLUDE_DIRS
        "${TDSH_SDK_ROOT}/include"
        "include"
        "src"
    REQUIRES
        esp_driver_gpio
        esp_driver_spi
        esp_driver_uart
        esp_driver_sdspi
        esp_driver_usb_serial_jtag
        esp_eth
        vfs
        fatfs
        sdmmc
        esp_system
        esp_hw_support
        esp_psram
        heap
        esp_timer
        freertos
        esp_wifi
        esp_netif
        esp_event
        nvs_flash
        lwip
        mbedtls
        joltwallet__littlefs
        espressif__w6100
        sahlberg__libsmb2
        wolfssh_local
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE WOLFSSH_SFTP)
# Classic ESP32: libsmb2 comes after this component on the link line, so pull
# in the MD5 shim (src/tdsh_md5_rom.c) explicitly.
if(IDF_TARGET STREQUAL "esp32")
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-u MD5Init" "-u MD5Update" "-u MD5Final")
endif()
# Legacy compact editor/nano source is intentionally retained from the validated
# C6 firmware. Do not promote this formatting diagnostic to an error.
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=misleading-indentation)
