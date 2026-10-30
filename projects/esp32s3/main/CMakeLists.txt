# The application is the same as the ESP32-C6 firmware's (../../../main).
set(TDSH_BOARD_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
include("${CMAKE_CURRENT_LIST_DIR}/../../../cmake/board_conf.cmake")
idf_component_register(SRCS "${CMAKE_CURRENT_LIST_DIR}/../../../main/main.c"
                       EMBED_TXTFILES "${TDSH_BOARD_BUILTIN}"
                       REQUIRES tdsh nvs_flash)
