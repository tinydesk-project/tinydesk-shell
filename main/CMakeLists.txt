set(TDSH_BOARD_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
include("${CMAKE_CURRENT_LIST_DIR}/../cmake/board_conf.cmake")
idf_component_register(SRCS "main.c" INCLUDE_DIRS "."
                       EMBED_TXTFILES "${TDSH_BOARD_BUILTIN}"
                       REQUIRES tdsh nvs_flash micropython)
