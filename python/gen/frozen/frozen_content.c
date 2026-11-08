//
// Content for MICROPY_MODULE_FROZEN_STR
//
#include <stdint.h>
#define MP_FROZEN_STR_NAMES \

const uint32_t mp_frozen_str_sizes[] = { 0 };
const char mp_frozen_str_content[] = {
"\0"
};

//
// Content for MICROPY_MODULE_FROZEN_MPY
//
#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"
#include "py/nativeglue.h"

#if MICROPY_LONGINT_IMPL != 2
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MPZ_DIG_SIZE != 16
#error "incompatible MPZ_DIG_SIZE"
#endif

#if MICROPY_PY_BUILTINS_FLOAT
typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;
#endif

#if MICROPY_PY_BUILTINS_COMPLEX
typedef struct _mp_obj_complex_t {
    mp_obj_base_t base;
    mp_float_t real;
    mp_float_t imag;
} mp_obj_complex_t;
#endif

enum {
    MP_QSTR__0x0d__0x0a_ = MP_QSTRnumber_of,
    MP_QSTR__space__space__percent__hyphen_24s_space__percent__hyphen_8s_space__percent_d_space_files,
    MP_QSTR__space__space_nothing_space_installed,
    MP_QSTR__bang_BB,
    MP_QSTR__bang_BBH,
    MP_QSTR__bang_BBQ,
    MP_QSTR__bang_H,
    MP_QSTR__bang_I,
    MP_QSTR__bang_Q,
    MP_QSTR__hash_,
    MP_QSTR__percent_s_space__paren_open__percent_s_paren_close__colon_,
    MP_QSTR__percent_s_colon__space__percent_s,
    MP_QSTR__amp_,
    MP_QSTR__hyphen__hyphen_help,
    MP_QSTR__hyphen_h,
    MP_QSTR__hyphen_r,
    MP_QSTR__hyphen_r_space_takes_space_one_space_file,
    MP_QSTR__dot_,
    MP_QSTR__dot_json,
    MP_QSTR__dot_mpy,
    MP_QSTR__dot_py,
    MP_QSTR__slash__dot_upip_dot_json,
    MP_QSTR__slash__slash_,
    MP_QSTR__slash_rom,
    MP_QSTR__slash_venv_dot_json,
    MP_QSTR_0_0x0d__0x0a__0x0d__0x0a_,
    MP_QSTR_0_dot_0_dot_8,
    MP_QSTR_13,
    MP_QSTR__colon_,
    MP_QSTR__lt_ClientResponse_space__percent_d_space__percent_s_gt_,
    MP_QSTR__question_,
    MP_QSTR__at_sign_,
    MP_QSTR_Authorization,
    MP_QSTR_BINARY,
    MP_QSTR_Basic_space__brace_open__brace_close_,
    MP_QSTR_BodyStream,
    MP_QSTR_CLOSE,
    MP_QSTR_CONT,
    MP_QSTR_ChunkedClientResponse,
    MP_QSTR_ClientResponse,
    MP_QSTR_ClientSession,
    MP_QSTR_ClientWebSocketResponse,
    MP_QSTR_Connection,
    MP_QSTR_Content_hyphen_Length,
    MP_QSTR_Content_hyphen_Type,
    MP_QSTR_Copying_colon_,
    MP_QSTR_DEBUG,
    MP_QSTR_DELAY,
    MP_QSTR_DELETE,
    MP_QSTR_DeflateIO,
    MP_QSTR_Done,
    MP_QSTR_Downloading_space__brace_open__brace_close__space_to_space__brace_open__brace_close_,
    MP_QSTR_ERROR,
    MP_QSTR_Error,
    MP_QSTR_Event,
    MP_QSTR_Exists_colon_,
    MP_QSTR_File_space_not_space_found_colon__space__brace_open__brace_close__space__brace_open__brace_close_,
    MP_QSTR_GET,
    MP_QSTR_GZIP,
    MP_QSTR_HEAD,
    MP_QSTR_HTTP_slash_1_dot_0,
    MP_QSTR_HTTP_slash_1_dot_1,
    MP_QSTR_Host,
    MP_QSTR_HttpVersion10,
    MP_QSTR_HttpVersion11,
    MP_QSTR_IOQueue,
    MP_QSTR_Installing_space__brace_open__brace_close__space_to_space__brace_open__brace_close_,
    MP_QSTR_Lock,
    MP_QSTR_Lock_space_not_space_acquired,
    MP_QSTR_Loop,
    MP_QSTR_MQTTClient,
    MP_QSTR_MQTTException,
    MP_QSTR_NeoPixel,
    MP_QSTR_OPTIONS,
    MP_QSTR_OP_BINARY,
    MP_QSTR_OP_CLOSE,
    MP_QSTR_OP_CONT,
    MP_QSTR_OP_PING,
    MP_QSTR_OP_PONG,
    MP_QSTR_OP_TEXT,
    MP_QSTR_ORDER,
    MP_QSTR_Origin,
    MP_QSTR_PATCH,
    MP_QSTR_PING,
    MP_QSTR_PONG,
    MP_QSTR_POST,
    MP_QSTR_PUT,
    MP_QSTR_Package_space_not_space_found_colon_,
    MP_QSTR_Removed_space__percent_s_space__paren_open__percent_d_space_files_paren_close_,
    MP_QSTR_Response,
    MP_QSTR_Scheme_space__brace_open__brace_close__space_is_space_invalid,
    MP_QSTR_Sec_hyphen_WebSocket_hyphen_Key,
    MP_QSTR_Sec_hyphen_WebSocket_hyphen_Version,
    MP_QSTR_Server,
    MP_QSTR_SingletonGenerator,
    MP_QSTR_Stream,
    MP_QSTR_StreamReader,
    MP_QSTR_StreamWriter,
    MP_QSTR_TEXT,
    MP_QSTR_ThreadSafeFlag,
    MP_QSTR_TimeoutError,
    MP_QSTR_Transfer_hyphen_Encoding,
    MP_QSTR_URI,
    MP_QSTR_URL_RE,
    MP_QSTR_USAGE,
    MP_QSTR_Unsupported_space_protocol_colon__space_,
    MP_QSTR_Upgrade,
    MP_QSTR_User_hyphen_Agent,
    MP_QSTR_VIRTUAL_ENV,
    MP_QSTR_WSMsgType,
    MP_QSTR_WebSocket,
    MP_QSTR_WebSocketClient,
    MP_QSTR_WebSocketConnectionClosedException,
    MP_QSTR_WebSocketException,
    MP_QSTR_WebSocketMessage,
    MP_QSTR_ZLIB,
    MP_QSTR__HOSTS,
    MP_QSTR__Remove,
    MP_QSTR__RequestContextManager,
    MP_QSTR__WSRequestContextManager,
    MP_QSTR___version__,
    MP_QSTR__attrs,
    MP_QSTR__base_headers,
    MP_QSTR__base_url,
    MP_QSTR__cached,
    MP_QSTR__check_exists,
    MP_QSTR__chunk,
    MP_QSTR__context,
    MP_QSTR__decode,
    MP_QSTR__dequeue,
    MP_QSTR__download_file,
    MP_QSTR__encode_len,
    MP_QSTR__encode_websocket_frame,
    MP_QSTR__enqueue,
    MP_QSTR__ensure_path_exists,
    MP_QSTR__exc_context,
    MP_QSTR__exc_handler,
    MP_QSTR__exists,
    MP_QSTR__files,
    MP_QSTR__get_header,
    MP_QSTR__http_version,
    MP_QSTR__install_json,
    MP_QSTR__install_package,
    MP_QSTR__io_queue,
    MP_QSTR__isdir,
    MP_QSTR__json,
    MP_QSTR__load,
    MP_QSTR__names,
    MP_QSTR__parse_frame_header,
    MP_QSTR__process_websocket_frame,
    MP_QSTR__promote_to_task,
    MP_QSTR__rand,
    MP_QSTR__read_exact,
    MP_QSTR__read_frame,
    MP_QSTR__reader,
    MP_QSTR__recv_len,
    MP_QSTR__remaining,
    MP_QSTR__request,
    MP_QSTR__requirements,
    MP_QSTR__rewrite_url,
    MP_QSTR__run,
    MP_QSTR__save,
    MP_QSTR__send_str,
    MP_QSTR__send_subunsub,
    MP_QSTR__serve,
    MP_QSTR__sock,
    MP_QSTR__split_url,
    MP_QSTR__stop_task,
    MP_QSTR__stopper,
    MP_QSTR__ws_connect,
    MP_QSTR_ack_n,
    MP_QSTR_ack_op,
    MP_QSTR_aclose,
    MP_QSTR_acquire,
    MP_QSTR_aiohttp_slash___init___dot_py,
    MP_QSTR_aiohttp_slash_aiohttp_ws_dot_py,
    MP_QSTR_aiohttp_ws,
    MP_QSTR_application_slash_json,
    MP_QSTR_application_slash_octet_hyphen_stream,
    MP_QSTR_asyncio,
    MP_QSTR_asyncio_slash___init___dot_py,
    MP_QSTR_asyncio_slash_core_dot_py,
    MP_QSTR_asyncio_slash_event_dot_py,
    MP_QSTR_asyncio_slash_funcs_dot_py,
    MP_QSTR_asyncio_slash_lock_dot_py,
    MP_QSTR_asyncio_slash_stream_dot_py,
    MP_QSTR_attempts,
    MP_QSTR_attr,
    MP_QSTR_auth,
    MP_QSTR_aw,
    MP_QSTR_awrite,
    MP_QSTR_awritestr,
    MP_QSTR_backlog,
    MP_QSTR_base_url,
    MP_QSTR_bpp,
    MP_QSTR_branch,
    MP_QSTR_buf,
    MP_QSTR_cadata,
    MP_QSTR_cafile,
    MP_QSTR_call_exception_handler,
    MP_QSTR_can_squot_t_space_gather,
    MP_QSTR_cb,
    MP_QSTR_cert,
    MP_QSTR_cert_reqs,
    MP_QSTR_certfile,
    MP_QSTR_check_msg,
    MP_QSTR_chunk_size,
    MP_QSTR_chunked,
    MP_QSTR_clean_session,
    MP_QSTR_client,
    MP_QSTR_closed,
    MP_QSTR_closed_space_by_space_the_space_server,
    MP_QSTR_cls,
    MP_QSTR_codeberg_colon_,
    MP_QSTR_compat,
    MP_QSTR_connection_space_closed,
    MP_QSTR_content,
    MP_QSTR_content_hyphen_encoding,
    MP_QSTR_content_hyphen_length,
    MP_QSTR_context,
    MP_QSTR_core,
    MP_QSTR_coro_equals_,
    MP_QSTR_coroutine_space_expected,
    MP_QSTR_create_connection,
    MP_QSTR_create_task,
    MP_QSTR_current_task,
    MP_QSTR_default_exception_handler,
    MP_QSTR_deflate,
    MP_QSTR_delay,
    MP_QSTR_delete,
    MP_QSTR_deps,
    MP_QSTR_dest,
    MP_QSTR_disconnect,
    MP_QSTR_do_handshake,
    MP_QSTR_drain,
    MP_QSTR_dt,
    MP_QSTR_environment_space_,
    MP_QSTR_er,
    MP_QSTR_event,
    MP_QSTR_exc,
    MP_QSTR_exc_tb,
    MP_QSTR_exc_type,
    MP_QSTR_exc_val,
    MP_QSTR_exception,
    MP_QSTR_f,
    MP_QSTR_files,
    MP_QSTR_fill,
    MP_QSTR_flags,
    MP_QSTR_freeze,
    MP_QSTR_funcs,
    MP_QSTR_future,
    MP_QSTR_future_colon_,
    MP_QSTR_gather,
    MP_QSTR_get_event_loop,
    MP_QSTR_get_exception_handler,
    MP_QSTR_get_extra_info,
    MP_QSTR_github_colon_,
    MP_QSTR_gitlab_colon_,
    MP_QSTR_gzip,
    MP_QSTR_gzip_comma_deflate,
    MP_QSTR_handshake,
    MP_QSTR_handshake_space_failed_colon__space_,
    MP_QSTR_handshake_request,
    MP_QSTR_hashes,
    MP_QSTR_head,
    MP_QSTR_header,
    MP_QSTR_headers,
    MP_QSTR_host,
    MP_QSTR_hostname,
    MP_QSTR_http,
    MP_QSTR_http_colon_,
    MP_QSTR_http_colon__slash__slash_,
    MP_QSTR_https,
    MP_QSTR_https_colon_,
    MP_QSTR_https_colon__slash__slash_,
    MP_QSTR_i,
    MP_QSTR_idx,
    MP_QSTR_in_reconnect,
    MP_QSTR_install,
    MP_QSTR_is_handshake,
    MP_QSTR_is_set,
    MP_QSTR_keepalive,
    MP_QSTR_keyfile,
    MP_QSTR_keyname,
    MP_QSTR_latest,
    MP_QSTR_listing,
    MP_QSTR_lock,
    MP_QSTR_locked,
    MP_QSTR_loop,
    MP_QSTR_lw_msg,
    MP_QSTR_lw_qos,
    MP_QSTR_lw_retain,
    MP_QSTR_lw_topic,
    MP_QSTR_main_task,
    MP_QSTR_message,
    MP_QSTR_method,
    MP_QSTR_mip,
    MP_QSTR_mip_slash___init___dot_py,
    MP_QSTR_mpy,
    MP_QSTR_mqtt_space_reconnect_colon__space__percent_r,
    MP_QSTR_mqtt_colon__space__percent_r,
    MP_QSTR_msg,
    MP_QSTR_n,
    MP_QSTR_neopixel_dot_py,
    MP_QSTR_new_event_loop,
    MP_QSTR_no_space_environment_space_active,
    MP_QSTR_no_space_running_space_event_space_loop,
    MP_QSTR_opcode,
    MP_QSTR_open_connection,
    MP_QSTR_options,
    MP_QSTR_out,
    MP_QSTR_out_buf,
    MP_QSTR_p,
    MP_QSTR_package,
    MP_QSTR_package_dot_json,
    MP_QSTR_package_json_url,
    MP_QSTR_packages,
    MP_QSTR_params,
    MP_QSTR_parse_headers,
    MP_QSTR_password,
    MP_QSTR_patch,
    MP_QSTR_payload,
    MP_QSTR_peername,
    MP_QSTR_pid,
    MP_QSTR_pin,
    MP_QSTR_ping,
    MP_QSTR_pkt,
    MP_QSTR_place,
    MP_QSTR_poller,
    MP_QSTR_port,
    MP_QSTR_post,
    MP_QSTR_protocol,
    MP_QSTR_pswd,
    MP_QSTR_publish,
    MP_QSTR_put,
    MP_QSTR_py,
    MP_QSTR_qos,
    MP_QSTR_queue_read,
    MP_QSTR_queue_write,
    MP_QSTR_raw,
    MP_QSTR_reader,
    MP_QSTR_readexactly,
    MP_QSTR_reason,
    MP_QSTR_receive,
    MP_QSTR_receive_bytes,
    MP_QSTR_receive_json,
    MP_QSTR_receive_str,
    MP_QSTR_reconnect,
    MP_QSTR_record,
    MP_QSTR_recv_frame,
    MP_QSTR_rel,
    MP_QSTR_remaining,
    MP_QSTR_req,
    MP_QSTR_reqco,
    MP_QSTR_request,
    MP_QSTR_request_co,
    MP_QSTR_request_raw,
    MP_QSTR_requesting,
    MP_QSTR_requests,
    MP_QSTR_requests_slash___init___dot_py,
    MP_QSTR_retain,
    MP_QSTR_return_exceptions,
    MP_QSTR_root,
    MP_QSTR_run,
    MP_QSTR_run_forever,
    MP_QSTR_run_until_complete,
    MP_QSTR_runq_len,
    MP_QSTR_s,
    MP_QSTR_send_binary,
    MP_QSTR_send_bytes,
    MP_QSTR_send_frame,
    MP_QSTR_send_json,
    MP_QSTR_send_str,
    MP_QSTR_server,
    MP_QSTR_set_callback,
    MP_QSTR_set_exception_handler,
    MP_QSTR_set_last_will,
    MP_QSTR_sgen,
    MP_QSTR_short_hash,
    MP_QSTR_simple,
    MP_QSTR_sock,
    MP_QSTR_src,
    MP_QSTR_ssl,
    MP_QSTR_ssl_dot_py,
    MP_QSTR_ssl_params,
    MP_QSTR_start_server,
    MP_QSTR_status_code,
    MP_QSTR_stream,
    MP_QSTR_stream_awrite,
    MP_QSTR_subscribe,
    MP_QSTR_sz,
    MP_QSTR_t,
    MP_QSTR_task,
    MP_QSTR_tb,
    MP_QSTR_text,
    MP_QSTR_ticks,
    MP_QSTR_timing,
    MP_QSTR_top,
    MP_QSTR_topic,
    MP_QSTR_typ,
    MP_QSTR_umqtt_slash_robust_dot_py,
    MP_QSTR_umqtt_slash_simple_dot_py,
    MP_QSTR_uninstall,
    MP_QSTR_unsubscribe,
    MP_QSTR_upip_dot_py,
    MP_QSTR_upip_colon_,
    MP_QSTR_uri,
    MP_QSTR_url,
    MP_QSTR_urlparse,
    MP_QSTR_urls,
    MP_QSTR_v,
    MP_QSTR_val,
    MP_QSTR_verify,
    MP_QSTR_w,
    MP_QSTR_wait_closed,
    MP_QSTR_wait_for,
    MP_QSTR_wait_for_ms,
    MP_QSTR_wait_io_event,
    MP_QSTR_wait_msg,
    MP_QSTR_waiter,
    MP_QSTR_waiting,
    MP_QSTR_waitq_len,
    MP_QSTR_walk,
    MP_QSTR_wb,
    MP_QSTR_websocket,
    MP_QSTR_websocket_dot_py,
    MP_QSTR_writer,
    MP_QSTR_ws,
    MP_QSTR_ws_colon__slash__slash_,
    MP_QSTR_ws_connect,
    MP_QSTR_wsclient,
    MP_QSTR_wss,
    MP_QSTR_wss_colon__slash__slash_,
    MP_QSTR__brace_open__brace_close__slash_file_slash__brace_open__brace_close__slash__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__slash_package_slash__brace_open__brace_close__slash__brace_open__brace_close__slash__brace_open__brace_close__dot_json,
    MP_QSTR__brace_open__brace_close__slash__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__colon__space__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__colon__slash__slash__brace_open__brace_close__colon__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__colon__slash__slash__brace_open__brace_close__colon__brace_open__brace_close__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__colon__brace_open__brace_close_,
    MP_QSTR__brace_open__brace_close__equals__brace_open__brace_close_,
};

const qstr_hash_t mp_qstr_frozen_const_hashes[] = {
    27298,
    60367,
    36248,
    12100,
    6028,
    6037,
    26188,
    26189,
    26197,
    46470,
    9342,
    50207,
    46467,
    28212,
    26336,
    26362,
    16592,
    46475,
    16755,
    7567,
    14722,
    35182,
    26341,
    63706,
    34935,
    1365,
    25885,
    26663,
    46495,
    42218,
    46490,
    46565,
    40382,
    21194,
    57753,
    55177,
    34899,
    55667,
    28005,
    12671,
    40706,
    51658,
    42451,
    45021,
    47385,
    31962,
    27956,
    33968,
    11292,
    11960,
    51237,
    17354,
    6557,
    4573,
    35561,
    1983,
    11802,
    48915,
    59137,
    32237,
    17469,
    17468,
    64005,
    5830,
    5831,
    26002,
    40031,
    59534,
    43943,
    59673,
    2816,
    62926,
    33641,
    59349,
    22698,
    61747,
    34515,
    49269,
    42995,
    32184,
    26955,
    32273,
    55275,
    4629,
    6803,
    6461,
    3220,
    20518,
    49156,
    5830,
    3261,
    24914,
    42975,
    2976,
    12601,
    55353,
    39580,
    35638,
    53336,
    9558,
    19302,
    53440,
    59307,
    58150,
    2336,
    38204,
    6069,
    59840,
    52038,
    53696,
    37264,
    31529,
    30403,
    45639,
    30011,
    7864,
    55625,
    37244,
    49959,
    54915,
    38975,
    24346,
    13948,
    16027,
    6226,
    7715,
    49025,
    7717,
    48470,
    49770,
    53815,
    33604,
    27284,
    26816,
    9133,
    13092,
    52355,
    45562,
    58831,
    30892,
    32199,
    55644,
    7934,
    43474,
    38303,
    33026,
    11932,
    34958,
    53389,
    64761,
    24914,
    18531,
    11772,
    5546,
    51135,
    35040,
    3974,
    1451,
    9142,
    37796,
    58803,
    53083,
    14476,
    53570,
    55469,
    45870,
    22972,
    5648,
    12837,
    59743,
    46973,
    42636,
    24658,
    54045,
    43848,
    61910,
    29313,
    48680,
    36904,
    44357,
    63415,
    61558,
    25345,
    46624,
    16486,
    35185,
    26331,
    48310,
    47277,
    28211,
    49657,
    2796,
    43370,
    25380,
    18887,
    22033,
    18804,
    26615,
    19745,
    19688,
    4535,
    28388,
    45349,
    15087,
    53475,
    39173,
    62500,
    3583,
    35073,
    10908,
    19959,
    42992,
    19545,
    44416,
    23137,
    21825,
    55724,
    62722,
    53597,
    55546,
    56254,
    21001,
    50473,
    36040,
    21139,
    8734,
    45889,
    14974,
    19536,
    59292,
    60551,
    60707,
    34213,
    32646,
    18805,
    28053,
    8400,
    28082,
    27081,
    9435,
    24306,
    52220,
    13695,
    60370,
    46531,
    52560,
    13514,
    36858,
    50862,
    27400,
    14592,
    22842,
    2184,
    19971,
    60604,
    16583,
    22202,
    31274,
    57153,
    13366,
    55058,
    33899,
    31612,
    34369,
    24045,
    39066,
    43945,
    13605,
    38338,
    39837,
    3847,
    59623,
    3918,
    63796,
    4820,
    46540,
    21584,
    26196,
    56068,
    48247,
    58562,
    1385,
    62580,
    13461,
    27646,
    6183,
    9134,
    47631,
    9273,
    17400,
    21612,
    34404,
    58496,
    31740,
    48238,
    22682,
    17073,
    29955,
    17857,
    17533,
    63572,
    18044,
    46539,
    49582,
    3209,
    3101,
    49107,
    61975,
    25560,
    25589,
    24363,
    30085,
    46549,
    51135,
    23177,
    21804,
    49132,
    57977,
    44963,
    28570,
    40587,
    1355,
    8320,
    29688,
    29682,
    62037,
    29610,
    42494,
    42221,
    55388,
    55357,
    62771,
    34485,
    27228,
    28788,
    28684,
    30696,
    52601,
    8726,
    35809,
    20288,
    23753,
    59329,
    46414,
    50824,
    39465,
    36740,
    4460,
    29480,
    64709,
    35710,
    43417,
    35683,
    60367,
    45172,
    8455,
    41615,
    56532,
    48775,
    26741,
    11104,
    47572,
    739,
    35180,
    25036,
    37871,
    52773,
    46550,
    41545,
    51391,
    4763,
    14782,
    22707,
    10432,
    43409,
    5288,
    6291,
    32154,
    17434,
    19467,
    40913,
    36103,
    36329,
    48942,
    30954,
    63679,
    62819,
    54361,
    59482,
    2061,
    28908,
    46545,
    40488,
    28563,
    44952,
    2115,
    9013,
    25390,
    55556,
    24824,
    33545,
    40458,
    64735,
    41174,
    41630,
    28547,
    25483,
    25486,
    19963,
    54589,
    46547,
    31486,
    722,
    46546,
    29411,
    40746,
    25035,
    6948,
    43752,
    60665,
    31214,
    21895,
    22260,
    28784,
    36240,
    6327,
    48106,
    28769,
    39579,
    3552,
    13816,
    31986,
    296,
    38218,
    18473,
    60938,
    51359,
    58115,
    42597,
    14943,
    18072,
};

const qstr_len_t mp_qstr_frozen_const_lengths[] = {
    2,
    21,
    19,
    3,
    4,
    4,
    2,
    2,
    2,
    1,
    8,
    6,
    1,
    6,
    2,
    2,
    17,
    1,
    5,
    4,
    3,
    11,
    2,
    4,
    10,
    5,
    5,
    2,
    1,
    22,
    1,
    1,
    13,
    6,
    8,
    10,
    5,
    4,
    21,
    14,
    13,
    23,
    10,
    14,
    12,
    8,
    5,
    5,
    6,
    9,
    4,
    20,
    5,
    5,
    5,
    7,
    21,
    3,
    4,
    4,
    8,
    8,
    4,
    13,
    13,
    7,
    19,
    4,
    17,
    4,
    10,
    13,
    8,
    7,
    9,
    8,
    7,
    7,
    7,
    7,
    5,
    6,
    5,
    4,
    4,
    4,
    3,
    18,
    21,
    8,
    20,
    17,
    21,
    6,
    18,
    6,
    12,
    12,
    4,
    14,
    12,
    17,
    3,
    6,
    5,
    22,
    7,
    10,
    11,
    9,
    9,
    15,
    34,
    18,
    16,
    4,
    6,
    7,
    22,
    24,
    11,
    6,
    13,
    9,
    7,
    13,
    6,
    8,
    7,
    8,
    14,
    11,
    23,
    8,
    19,
    12,
    12,
    7,
    6,
    11,
    13,
    13,
    16,
    9,
    6,
    5,
    5,
    6,
    19,
    24,
    16,
    5,
    11,
    11,
    7,
    9,
    10,
    8,
    13,
    12,
    4,
    5,
    9,
    14,
    6,
    5,
    10,
    10,
    8,
    11,
    5,
    6,
    6,
    7,
    19,
    21,
    10,
    16,
    24,
    7,
    19,
    15,
    16,
    16,
    15,
    17,
    8,
    4,
    4,
    2,
    6,
    9,
    7,
    8,
    3,
    6,
    3,
    6,
    6,
    22,
    12,
    2,
    4,
    9,
    8,
    9,
    10,
    7,
    13,
    6,
    6,
    20,
    3,
    9,
    6,
    17,
    7,
    16,
    14,
    7,
    4,
    5,
    18,
    17,
    11,
    12,
    25,
    7,
    5,
    6,
    4,
    4,
    10,
    12,
    5,
    2,
    12,
    2,
    5,
    3,
    6,
    8,
    7,
    9,
    1,
    5,
    4,
    5,
    6,
    5,
    6,
    7,
    6,
    14,
    21,
    14,
    7,
    7,
    4,
    12,
    9,
    18,
    17,
    6,
    4,
    6,
    7,
    4,
    8,
    4,
    5,
    7,
    5,
    6,
    8,
    1,
    3,
    12,
    7,
    12,
    6,
    9,
    7,
    7,
    6,
    7,
    4,
    6,
    4,
    6,
    6,
    9,
    8,
    9,
    7,
    6,
    3,
    15,
    3,
    18,
    8,
    3,
    1,
    11,
    14,
    21,
    21,
    6,
    15,
    7,
    3,
    7,
    1,
    7,
    12,
    16,
    8,
    6,
    13,
    8,
    5,
    7,
    8,
    3,
    3,
    4,
    3,
    5,
    6,
    4,
    4,
    8,
    4,
    7,
    3,
    2,
    3,
    10,
    11,
    3,
    6,
    11,
    6,
    7,
    13,
    12,
    11,
    9,
    6,
    10,
    3,
    9,
    3,
    5,
    7,
    10,
    11,
    10,
    8,
    20,
    6,
    17,
    4,
    3,
    11,
    18,
    8,
    1,
    11,
    10,
    10,
    9,
    8,
    6,
    12,
    21,
    13,
    4,
    10,
    6,
    4,
    3,
    3,
    6,
    10,
    12,
    11,
    6,
    13,
    9,
    2,
    1,
    4,
    2,
    4,
    5,
    6,
    3,
    5,
    3,
    15,
    15,
    9,
    11,
    7,
    5,
    3,
    3,
    8,
    4,
    1,
    3,
    6,
    1,
    11,
    8,
    11,
    13,
    8,
    6,
    7,
    9,
    4,
    2,
    9,
    12,
    6,
    2,
    5,
    10,
    8,
    3,
    6,
    13,
    24,
    5,
    6,
    10,
    12,
    5,
    5,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    &mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    true, // is_sorted
    10, // allocated entries
    441, // used entries
    (qstr_hash_t *)mp_qstr_frozen_const_hashes,
    (qstr_len_t *)mp_qstr_frozen_const_lengths,
    {
        "\x0d\x0a",
        "  %-24s %-8s %d files",
        "  nothing installed",
        "!BB",
        "!BBH",
        "!BBQ",
        "!H",
        "!I",
        "!Q",
        "#",
        "%s (%s):",
        "%s: %s",
        "&",
        "--help",
        "-h",
        "-r",
        "-r takes one file",
        ".",
        ".json",
        ".mpy",
        ".py",
        "/.upip.json",
        "//",
        "/rom",
        "/venv.json",
        "\x30\x0d\x0a\x0d\x0a",
        "0.0.8",
        "13",
        ":",
        "<ClientResponse %d %s>",
        "?",
        "@",
        "Authorization",
        "BINARY",
        "Basic {}",
        "BodyStream",
        "CLOSE",
        "CONT",
        "ChunkedClientResponse",
        "ClientResponse",
        "ClientSession",
        "ClientWebSocketResponse",
        "Connection",
        "Content-Length",
        "Content-Type",
        "Copying:",
        "DEBUG",
        "DELAY",
        "DELETE",
        "DeflateIO",
        "Done",
        "Downloading {} to {}",
        "ERROR",
        "Error",
        "Event",
        "Exists:",
        "File not found: {} {}",
        "GET",
        "GZIP",
        "HEAD",
        "HTTP/1.0",
        "HTTP/1.1",
        "Host",
        "HttpVersion10",
        "HttpVersion11",
        "IOQueue",
        "Installing {} to {}",
        "Lock",
        "Lock not acquired",
        "Loop",
        "MQTTClient",
        "MQTTException",
        "NeoPixel",
        "OPTIONS",
        "OP_BINARY",
        "OP_CLOSE",
        "OP_CONT",
        "OP_PING",
        "OP_PONG",
        "OP_TEXT",
        "ORDER",
        "Origin",
        "PATCH",
        "PING",
        "PONG",
        "POST",
        "PUT",
        "Package not found:",
        "Removed %s (%d files)",
        "Response",
        "Scheme {} is invalid",
        "Sec-WebSocket-Key",
        "Sec-WebSocket-Version",
        "Server",
        "SingletonGenerator",
        "Stream",
        "StreamReader",
        "StreamWriter",
        "TEXT",
        "ThreadSafeFlag",
        "TimeoutError",
        "Transfer-Encoding",
        "URI",
        "URL_RE",
        "USAGE",
        "Unsupported protocol: ",
        "Upgrade",
        "User-Agent",
        "VIRTUAL_ENV",
        "WSMsgType",
        "WebSocket",
        "WebSocketClient",
        "WebSocketConnectionClosedException",
        "WebSocketException",
        "WebSocketMessage",
        "ZLIB",
        "_HOSTS",
        "_Remove",
        "_RequestContextManager",
        "_WSRequestContextManager",
        "__version__",
        "_attrs",
        "_base_headers",
        "_base_url",
        "_cached",
        "_check_exists",
        "_chunk",
        "_context",
        "_decode",
        "_dequeue",
        "_download_file",
        "_encode_len",
        "_encode_websocket_frame",
        "_enqueue",
        "_ensure_path_exists",
        "_exc_context",
        "_exc_handler",
        "_exists",
        "_files",
        "_get_header",
        "_http_version",
        "_install_json",
        "_install_package",
        "_io_queue",
        "_isdir",
        "_json",
        "_load",
        "_names",
        "_parse_frame_header",
        "_process_websocket_frame",
        "_promote_to_task",
        "_rand",
        "_read_exact",
        "_read_frame",
        "_reader",
        "_recv_len",
        "_remaining",
        "_request",
        "_requirements",
        "_rewrite_url",
        "_run",
        "_save",
        "_send_str",
        "_send_subunsub",
        "_serve",
        "_sock",
        "_split_url",
        "_stop_task",
        "_stopper",
        "_ws_connect",
        "ack_n",
        "ack_op",
        "aclose",
        "acquire",
        "aiohttp/__init__.py",
        "aiohttp/aiohttp_ws.py",
        "aiohttp_ws",
        "application/json",
        "application/octet-stream",
        "asyncio",
        "asyncio/__init__.py",
        "asyncio/core.py",
        "asyncio/event.py",
        "asyncio/funcs.py",
        "asyncio/lock.py",
        "asyncio/stream.py",
        "attempts",
        "attr",
        "auth",
        "aw",
        "awrite",
        "awritestr",
        "backlog",
        "base_url",
        "bpp",
        "branch",
        "buf",
        "cadata",
        "cafile",
        "call_exception_handler",
        "can't gather",
        "cb",
        "cert",
        "cert_reqs",
        "certfile",
        "check_msg",
        "chunk_size",
        "chunked",
        "clean_session",
        "client",
        "closed",
        "closed by the server",
        "cls",
        "codeberg:",
        "compat",
        "connection closed",
        "content",
        "content-encoding",
        "content-length",
        "context",
        "core",
        "coro=",
        "coroutine expected",
        "create_connection",
        "create_task",
        "current_task",
        "default_exception_handler",
        "deflate",
        "delay",
        "delete",
        "deps",
        "dest",
        "disconnect",
        "do_handshake",
        "drain",
        "dt",
        "environment ",
        "er",
        "event",
        "exc",
        "exc_tb",
        "exc_type",
        "exc_val",
        "exception",
        "f",
        "files",
        "fill",
        "flags",
        "freeze",
        "funcs",
        "future",
        "future:",
        "gather",
        "get_event_loop",
        "get_exception_handler",
        "get_extra_info",
        "github:",
        "gitlab:",
        "gzip",
        "gzip,deflate",
        "handshake",
        "handshake failed: ",
        "handshake_request",
        "hashes",
        "head",
        "header",
        "headers",
        "host",
        "hostname",
        "http",
        "http:",
        "http://",
        "https",
        "https:",
        "https://",
        "i",
        "idx",
        "in_reconnect",
        "install",
        "is_handshake",
        "is_set",
        "keepalive",
        "keyfile",
        "keyname",
        "latest",
        "listing",
        "lock",
        "locked",
        "loop",
        "lw_msg",
        "lw_qos",
        "lw_retain",
        "lw_topic",
        "main_task",
        "message",
        "method",
        "mip",
        "mip/__init__.py",
        "mpy",
        "mqtt reconnect: %r",
        "mqtt: %r",
        "msg",
        "n",
        "neopixel.py",
        "new_event_loop",
        "no environment active",
        "no running event loop",
        "opcode",
        "open_connection",
        "options",
        "out",
        "out_buf",
        "p",
        "package",
        "package.json",
        "package_json_url",
        "packages",
        "params",
        "parse_headers",
        "password",
        "patch",
        "payload",
        "peername",
        "pid",
        "pin",
        "ping",
        "pkt",
        "place",
        "poller",
        "port",
        "post",
        "protocol",
        "pswd",
        "publish",
        "put",
        "py",
        "qos",
        "queue_read",
        "queue_write",
        "raw",
        "reader",
        "readexactly",
        "reason",
        "receive",
        "receive_bytes",
        "receive_json",
        "receive_str",
        "reconnect",
        "record",
        "recv_frame",
        "rel",
        "remaining",
        "req",
        "reqco",
        "request",
        "request_co",
        "request_raw",
        "requesting",
        "requests",
        "requests/__init__.py",
        "retain",
        "return_exceptions",
        "root",
        "run",
        "run_forever",
        "run_until_complete",
        "runq_len",
        "s",
        "send_binary",
        "send_bytes",
        "send_frame",
        "send_json",
        "send_str",
        "server",
        "set_callback",
        "set_exception_handler",
        "set_last_will",
        "sgen",
        "short_hash",
        "simple",
        "sock",
        "src",
        "ssl",
        "ssl.py",
        "ssl_params",
        "start_server",
        "status_code",
        "stream",
        "stream_awrite",
        "subscribe",
        "sz",
        "t",
        "task",
        "tb",
        "text",
        "ticks",
        "timing",
        "top",
        "topic",
        "typ",
        "umqtt/robust.py",
        "umqtt/simple.py",
        "uninstall",
        "unsubscribe",
        "upip.py",
        "upip:",
        "uri",
        "url",
        "urlparse",
        "urls",
        "v",
        "val",
        "verify",
        "w",
        "wait_closed",
        "wait_for",
        "wait_for_ms",
        "wait_io_event",
        "wait_msg",
        "waiter",
        "waiting",
        "waitq_len",
        "walk",
        "wb",
        "websocket",
        "websocket.py",
        "writer",
        "ws",
        "ws://",
        "ws_connect",
        "wsclient",
        "wss",
        "wss://",
        "{}/file/{}/{}",
        "{}/package/{}/{}/{}.json",
        "{}/{}",
        "{}: {}",
        "{}://{}:{}",
        "{}://{}:{}{}",
        "{}:{}",
        "{}={}",
    },
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio___init__
// - original source file: build/frozen_mpy/asyncio/__init__.mpy
// - frozen file name: asyncio/__init__.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/__init__.py, scope asyncio___init____lt_module_gt_
static const byte fun_data_asyncio___init____lt_module_gt_[75] = {
    0x10,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x02, // LOAD_CONST_STRING '*'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME 'core'
    0x69, // IMPORT_STAR
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x16,0x0e, // STORE_NAME '__version__'
    0x2c,0x0a, // BUILD_MAP 10
    0x10,0x04, // LOAD_CONST_STRING 'funcs'
    0x10,0x05, // LOAD_CONST_STRING 'wait_for'
    0x62, // STORE_MAP
    0x10,0x04, // LOAD_CONST_STRING 'funcs'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x62, // STORE_MAP
    0x10,0x04, // LOAD_CONST_STRING 'funcs'
    0x10,0x06, // LOAD_CONST_STRING 'gather'
    0x62, // STORE_MAP
    0x10,0x07, // LOAD_CONST_STRING 'event'
    0x10,0x08, // LOAD_CONST_STRING 'Event'
    0x62, // STORE_MAP
    0x10,0x07, // LOAD_CONST_STRING 'event'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x62, // STORE_MAP
    0x10,0x09, // LOAD_CONST_STRING 'lock'
    0x10,0x0a, // LOAD_CONST_STRING 'Lock'
    0x62, // STORE_MAP
    0x10,0x0b, // LOAD_CONST_STRING 'stream'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x62, // STORE_MAP
    0x10,0x0b, // LOAD_CONST_STRING 'stream'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x62, // STORE_MAP
    0x10,0x0b, // LOAD_CONST_STRING 'stream'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x62, // STORE_MAP
    0x10,0x0b, // LOAD_CONST_STRING 'stream'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x62, // STORE_MAP
    0x16,0x0f, // STORE_NAME '_attrs'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x0c, // STORE_NAME '__getattr__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio___init____lt_module_gt_
// frozen bytecode for file asyncio/__init__.py, scope asyncio___init_____getattr__
static const byte fun_data_asyncio___init_____getattr__[51] = {
    0x49,0x04, // prelude
    0x0c,0x10, // names: __getattr__, attr
     // code info
    0x12,0x0f, // LOAD_GLOBAL '_attrs'
    0x14,0x0d, // LOAD_METHOD 'get'
    0xb0, // LOAD_FAST 0
    0x51, // LOAD_CONST_NONE
    0x36,0x02, // CALL_METHOD 2
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x11, // LOAD_GLOBAL 'AttributeError'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x12, // LOAD_GLOBAL 'getattr'
    0x12,0x13, // LOAD_GLOBAL '__import__'
    0xb1, // LOAD_FAST 1
    0x12,0x14, // LOAD_GLOBAL 'globals'
    0x34,0x00, // CALL_FUNCTION 0
    0x51, // LOAD_CONST_NONE
    0x52, // LOAD_CONST_TRUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0x34,0x05, // CALL_FUNCTION 5
    0xb0, // LOAD_FAST 0
    0x34,0x02, // CALL_FUNCTION 2
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x12,0x14, // LOAD_GLOBAL 'globals'
    0x34,0x00, // CALL_FUNCTION 0
    0xb0, // LOAD_FAST 0
    0x56, // STORE_SUBSCR
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio___init_____getattr__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio___init_____getattr__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 51,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_asyncio___init_____getattr__ + 4,
        .line_info_top = fun_data_asyncio___init_____getattr__ + 4,
        .opcodes = fun_data_asyncio___init_____getattr__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio___init_____getattr__ fun_data_asyncio___init_____getattr__[0]
#endif

static const mp_raw_code_t *const children_asyncio___init____lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio___init_____getattr__,
};

static const mp_raw_code_truncated_t proto_fun_asyncio___init____lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio___init____lt_module_gt_,
    .children = (void *)&children_asyncio___init____lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 75,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio___init____lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio___init____lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio___init____lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio___init__[21] = {
    MP_QSTR_asyncio_slash___init___dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR__star_,
    MP_QSTR_core,
    MP_QSTR_funcs,
    MP_QSTR_wait_for,
    MP_QSTR_gather,
    MP_QSTR_event,
    MP_QSTR_Event,
    MP_QSTR_lock,
    MP_QSTR_Lock,
    MP_QSTR_stream,
    MP_QSTR___getattr__,
    MP_QSTR_get,
    MP_QSTR___version__,
    MP_QSTR__attrs,
    MP_QSTR_attr,
    MP_QSTR_AttributeError,
    MP_QSTR_getattr,
    MP_QSTR___import__,
    MP_QSTR_globals,
};

// constants
static const mp_rom_obj_tuple_t const_obj_asyncio___init___0 = {{&mp_type_tuple}, 3, {
    MP_ROM_INT(3),
    MP_ROM_INT(0),
    MP_ROM_INT(0),
}};

// constant table
static const mp_rom_obj_t const_obj_table_data_asyncio___init__[7] = {
    MP_ROM_PTR(&const_obj_asyncio___init___0),
    MP_ROM_QSTR(MP_QSTR_wait_for_ms),
    MP_ROM_QSTR(MP_QSTR_ThreadSafeFlag),
    MP_ROM_QSTR(MP_QSTR_open_connection),
    MP_ROM_QSTR(MP_QSTR_start_server),
    MP_ROM_QSTR(MP_QSTR_StreamReader),
    MP_ROM_QSTR(MP_QSTR_StreamWriter),
};

static const mp_frozen_module_t frozen_module_asyncio___init__ = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio___init__,
        .obj_table = (mp_obj_t *)&const_obj_table_data_asyncio___init__,
    },
    .proto_fun = &proto_fun_asyncio___init____lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio_core
// - original source file: build/frozen_mpy/asyncio/core.mpy
// - frozen file name: asyncio/core.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/core.py, scope asyncio_core__lt_module_gt_
static const byte fun_data_asyncio_core__lt_module_gt_[218] = {
    0x2c,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x02, // LOAD_CONST_STRING 'ticks_ms'
    0x10,0x03, // LOAD_CONST_STRING 'ticks_diff'
    0x10,0x04, // LOAD_CONST_STRING 'ticks_add'
    0x2a,0x03, // BUILD_TUPLE 3
    0x1b,0x05, // IMPORT_NAME 'time'
    0x1c,0x02, // IMPORT_FROM 'ticks_ms'
    0x16,0x49, // STORE_NAME 'ticks'
    0x1c,0x03, // IMPORT_FROM 'ticks_diff'
    0x16,0x03, // STORE_NAME 'ticks_diff'
    0x1c,0x04, // IMPORT_FROM 'ticks_add'
    0x16,0x04, // STORE_NAME 'ticks_add'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x06, // IMPORT_NAME 'sys'
    0x16,0x06, // STORE_NAME 'sys'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x07, // IMPORT_NAME 'select'
    0x16,0x07, // STORE_NAME 'select'
    0x48,0x14, // SETUP_EXCEPT 20
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x08, // LOAD_CONST_STRING 'TaskQueue'
    0x10,0x09, // LOAD_CONST_STRING 'Task'
    0x2a,0x02, // BUILD_TUPLE 2
    0x1b,0x0a, // IMPORT_NAME '_asyncio'
    0x1c,0x08, // IMPORT_FROM 'TaskQueue'
    0x16,0x08, // STORE_NAME 'TaskQueue'
    0x1c,0x09, // IMPORT_FROM 'Task'
    0x16,0x09, // STORE_NAME 'Task'
    0x59, // POP_TOP
    0x4a,0x16, // POP_EXCEPT_JUMP 22
    0x59, // POP_TOP
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x08, // LOAD_CONST_STRING 'TaskQueue'
    0x10,0x09, // LOAD_CONST_STRING 'Task'
    0x2a,0x02, // BUILD_TUPLE 2
    0x1b,0x0b, // IMPORT_NAME 'task'
    0x1c,0x08, // IMPORT_FROM 'TaskQueue'
    0x16,0x08, // STORE_NAME 'TaskQueue'
    0x1c,0x09, // IMPORT_FROM 'Task'
    0x16,0x09, // STORE_NAME 'Task'
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x0c, // LOAD_CONST_STRING 'CancelledError'
    0x11,0x4a, // LOAD_NAME 'BaseException'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x0c, // STORE_NAME 'CancelledError'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x0d, // LOAD_CONST_STRING 'TimeoutError'
    0x11,0x4b, // LOAD_NAME 'Exception'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x0d, // STORE_NAME 'TimeoutError'
    0x2c,0x03, // BUILD_MAP 3
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x10,0x0e, // LOAD_CONST_STRING 'message'
    0x62, // STORE_MAP
    0x51, // LOAD_CONST_NONE
    0x10,0x0f, // LOAD_CONST_STRING 'exception'
    0x62, // STORE_MAP
    0x51, // LOAD_CONST_NONE
    0x10,0x10, // LOAD_CONST_STRING 'future'
    0x62, // STORE_MAP
    0x16,0x4c, // STORE_NAME '_exc_context'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x11, // LOAD_CONST_STRING 'SingletonGenerator'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x11, // STORE_NAME 'SingletonGenerator'
    0x11,0x11, // LOAD_NAME 'SingletonGenerator'
    0x34,0x00, // CALL_FUNCTION 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x14, // STORE_NAME 'sleep_ms'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x16, // STORE_NAME 'sleep'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x05, // MAKE_FUNCTION 5
    0x10,0x12, // LOAD_CONST_STRING 'IOQueue'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x12, // STORE_NAME 'IOQueue'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x17, // STORE_NAME '_promote_to_task'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x18, // STORE_NAME 'create_task'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x08, // MAKE_FUNCTION_DEFARGS 8
    0x16,0x1b, // STORE_NAME 'run_until_complete'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x26, // STORE_NAME 'run'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x27, // STORE_NAME '_stopper'
    0x51, // LOAD_CONST_NONE
    0x17,0x4d, // STORE_GLOBAL 'cur_task'
    0x51, // LOAD_CONST_NONE
    0x17,0x4e, // STORE_GLOBAL '_stop_task'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x0b, // MAKE_FUNCTION 11
    0x10,0x13, // LOAD_CONST_STRING 'Loop'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x13, // STORE_NAME 'Loop'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x0c, // MAKE_FUNCTION_DEFARGS 12
    0x16,0x28, // STORE_NAME 'get_event_loop'
    0x32,0x0d, // MAKE_FUNCTION 13
    0x16,0x29, // STORE_NAME 'current_task'
    0x32,0x0e, // MAKE_FUNCTION 14
    0x16,0x2a, // STORE_NAME 'new_event_loop'
    0x11,0x2a, // LOAD_NAME 'new_event_loop'
    0x34,0x00, // CALL_FUNCTION 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_CancelledError
static const byte fun_data_asyncio_core_CancelledError[13] = {
    0x00,0x02, // prelude
    0x0c, // names: CancelledError
     // code info
    0x11,0x4f, // LOAD_NAME '__name__'
    0x16,0x50, // STORE_NAME '__module__'
    0x10,0x0c, // LOAD_CONST_STRING 'CancelledError'
    0x16,0x51, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_CancelledError = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_CancelledError,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_asyncio_core_CancelledError + 3,
        .line_info_top = fun_data_asyncio_core_CancelledError + 3,
        .opcodes = fun_data_asyncio_core_CancelledError + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_CancelledError fun_data_asyncio_core_CancelledError[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_TimeoutError
static const byte fun_data_asyncio_core_TimeoutError[13] = {
    0x00,0x02, // prelude
    0x0d, // names: TimeoutError
     // code info
    0x11,0x4f, // LOAD_NAME '__name__'
    0x16,0x50, // STORE_NAME '__module__'
    0x10,0x0d, // LOAD_CONST_STRING 'TimeoutError'
    0x16,0x51, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_TimeoutError = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_TimeoutError,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_asyncio_core_TimeoutError + 3,
        .line_info_top = fun_data_asyncio_core_TimeoutError + 3,
        .opcodes = fun_data_asyncio_core_TimeoutError + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_TimeoutError fun_data_asyncio_core_TimeoutError[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_SingletonGenerator
static const byte fun_data_asyncio_core_SingletonGenerator[25] = {
    0x00,0x02, // prelude
    0x11, // names: SingletonGenerator
     // code info
    0x11,0x4f, // LOAD_NAME '__name__'
    0x16,0x50, // STORE_NAME '__module__'
    0x10,0x11, // LOAD_CONST_STRING 'SingletonGenerator'
    0x16,0x51, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x2b, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2d, // STORE_NAME '__iter__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2e, // STORE_NAME '__next__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_core_SingletonGenerator
// frozen bytecode for file asyncio/core.py, scope asyncio_core_SingletonGenerator___init__
static const byte fun_data_asyncio_core_SingletonGenerator___init__[17] = {
    0x11,0x04, // prelude
    0x2b,0x63, // names: __init__, self
     // code info
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x15, // STORE_ATTR 'state'
    0x12,0x5d, // LOAD_GLOBAL 'StopIteration'
    0x34,0x00, // CALL_FUNCTION 0
    0xb0, // LOAD_FAST 0
    0x18,0x2c, // STORE_ATTR 'exc'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_SingletonGenerator___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_SingletonGenerator___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 43,
        .line_info = fun_data_asyncio_core_SingletonGenerator___init__ + 4,
        .line_info_top = fun_data_asyncio_core_SingletonGenerator___init__ + 4,
        .opcodes = fun_data_asyncio_core_SingletonGenerator___init__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_SingletonGenerator___init__ fun_data_asyncio_core_SingletonGenerator___init__[0]
#endif

// child of asyncio_core_SingletonGenerator
// frozen bytecode for file asyncio/core.py, scope asyncio_core_SingletonGenerator___iter__
static const byte fun_data_asyncio_core_SingletonGenerator___iter__[6] = {
    0x09,0x04, // prelude
    0x2d,0x63, // names: __iter__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_SingletonGenerator___iter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_SingletonGenerator___iter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_asyncio_core_SingletonGenerator___iter__ + 4,
        .line_info_top = fun_data_asyncio_core_SingletonGenerator___iter__ + 4,
        .opcodes = fun_data_asyncio_core_SingletonGenerator___iter__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_SingletonGenerator___iter__ fun_data_asyncio_core_SingletonGenerator___iter__[0]
#endif

// child of asyncio_core_SingletonGenerator
// frozen bytecode for file asyncio/core.py, scope asyncio_core_SingletonGenerator___next__
static const byte fun_data_asyncio_core_SingletonGenerator___next__[42] = {
    0x21,0x04, // prelude
    0x2e,0x63, // names: __next__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'state'
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x15, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'exc'
    0x18,0x2f, // STORE_ATTR '__traceback__'
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'exc'
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_SingletonGenerator___next__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_SingletonGenerator___next__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 42,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_asyncio_core_SingletonGenerator___next__ + 4,
        .line_info_top = fun_data_asyncio_core_SingletonGenerator___next__ + 4,
        .opcodes = fun_data_asyncio_core_SingletonGenerator___next__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_SingletonGenerator___next__ fun_data_asyncio_core_SingletonGenerator___next__[0]
#endif

static const mp_raw_code_t *const children_asyncio_core_SingletonGenerator[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_core_SingletonGenerator___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_SingletonGenerator___iter__,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_SingletonGenerator___next__,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_core_SingletonGenerator = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_SingletonGenerator,
    .children = (void *)&children_asyncio_core_SingletonGenerator,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 17,
        .line_info = fun_data_asyncio_core_SingletonGenerator + 3,
        .line_info_top = fun_data_asyncio_core_SingletonGenerator + 3,
        .opcodes = fun_data_asyncio_core_SingletonGenerator + 3,
    },
    #endif
    #endif
};

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_sleep_ms
static const byte fun_data_asyncio_core_sleep_ms[25] = {
    0xb2,0x01,0x06, // prelude
    0x14,0x52,0x53, // names: sleep_ms, t, sgen
     // code info
    0x12,0x04, // LOAD_GLOBAL 'ticks_add'
    0x12,0x49, // LOAD_GLOBAL 'ticks'
    0x34,0x00, // CALL_FUNCTION 0
    0x12,0x54, // LOAD_GLOBAL 'max'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x34,0x02, // CALL_FUNCTION 2
    0x34,0x02, // CALL_FUNCTION 2
    0xb1, // LOAD_FAST 1
    0x18,0x15, // STORE_ATTR 'state'
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_sleep_ms = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_sleep_ms,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 20,
        .line_info = fun_data_asyncio_core_sleep_ms + 6,
        .line_info_top = fun_data_asyncio_core_sleep_ms + 6,
        .opcodes = fun_data_asyncio_core_sleep_ms + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_sleep_ms fun_data_asyncio_core_sleep_ms[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_sleep
static const byte fun_data_asyncio_core_sleep[18] = {
    0x21,0x04, // prelude
    0x16,0x52, // names: sleep, t
     // code info
    0x12,0x14, // LOAD_GLOBAL 'sleep_ms'
    0x12,0x55, // LOAD_GLOBAL 'int'
    0xb0, // LOAD_FAST 0
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_sleep = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_sleep,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 22,
        .line_info = fun_data_asyncio_core_sleep + 4,
        .line_info_top = fun_data_asyncio_core_sleep + 4,
        .opcodes = fun_data_asyncio_core_sleep + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_sleep fun_data_asyncio_core_sleep[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue
static const byte fun_data_asyncio_core_IOQueue[41] = {
    0x00,0x02, // prelude
    0x12, // names: IOQueue
     // code info
    0x11,0x4f, // LOAD_NAME '__name__'
    0x16,0x50, // STORE_NAME '__module__'
    0x10,0x12, // LOAD_CONST_STRING 'IOQueue'
    0x16,0x51, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x2b, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x32, // STORE_NAME '_enqueue'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x37, // STORE_NAME '_dequeue'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x39, // STORE_NAME 'queue_read'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x3a, // STORE_NAME 'queue_write'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x3b, // STORE_NAME 'remove'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x1f, // STORE_NAME 'wait_io_event'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue___init__
static const byte fun_data_asyncio_core_IOQueue___init__[20] = {
    0x11,0x04, // prelude
    0x2b,0x63, // names: __init__, self
     // code info
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x14,0x30, // LOAD_METHOD 'poll'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x31, // STORE_ATTR 'poller'
    0x2c,0x00, // BUILD_MAP 0
    0xb0, // LOAD_FAST 0
    0x18,0x1e, // STORE_ATTR 'map'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 43,
        .line_info = fun_data_asyncio_core_IOQueue___init__ + 4,
        .line_info_top = fun_data_asyncio_core_IOQueue___init__ + 4,
        .opcodes = fun_data_asyncio_core_IOQueue___init__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue___init__ fun_data_asyncio_core_IOQueue___init__[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue__enqueue
static const byte fun_data_asyncio_core_IOQueue__enqueue[105] = {
    0x4b,0x08, // prelude
    0x32,0x63,0x64,0x65, // names: _enqueue, self, s, idx
     // code info
    0x12,0x66, // LOAD_GLOBAL 'id'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x6f, // POP_JUMP_IF_FALSE 47
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xb1, // LOAD_FAST 1
    0x2b,0x03, // BUILD_LIST 3
    0xc3, // STORE_FAST 3
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0x56, // STORE_SUBSCR
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0x12,0x66, // LOAD_GLOBAL 'id'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x33, // LOAD_METHOD 'register'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x34, // LOAD_ATTR 'POLLIN'
    0x42,0x44, // JUMP 4
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x35, // LOAD_ATTR 'POLLOUT'
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x42,0x61, // JUMP 33
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0x12,0x66, // LOAD_GLOBAL 'id'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x55, // LOAD_SUBSCR
    0xc4, // STORE_FAST 4
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0xb4, // LOAD_FAST 4
    0xb2, // LOAD_FAST 2
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x36, // LOAD_METHOD 'modify'
    0xb1, // LOAD_FAST 1
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x34, // LOAD_ATTR 'POLLIN'
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x35, // LOAD_ATTR 'POLLOUT'
    0xed, // BINARY_OP 22 __or__
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0x18,0x21, // STORE_ATTR 'data'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue__enqueue = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue__enqueue,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 105,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 50,
        .line_info = fun_data_asyncio_core_IOQueue__enqueue + 6,
        .line_info_top = fun_data_asyncio_core_IOQueue__enqueue + 6,
        .opcodes = fun_data_asyncio_core_IOQueue__enqueue + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue__enqueue fun_data_asyncio_core_IOQueue__enqueue[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue__dequeue
static const byte fun_data_asyncio_core_IOQueue__dequeue[27] = {
    0x22,0x06, // prelude
    0x37,0x63,0x64, // names: _dequeue, self, s
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0x12,0x66, // LOAD_GLOBAL 'id'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x53, // LOAD_NULL
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x38, // LOAD_METHOD 'unregister'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue__dequeue = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue__dequeue,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 27,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 55,
        .line_info = fun_data_asyncio_core_IOQueue__dequeue + 5,
        .line_info_top = fun_data_asyncio_core_IOQueue__dequeue + 5,
        .opcodes = fun_data_asyncio_core_IOQueue__dequeue + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue__dequeue fun_data_asyncio_core_IOQueue__dequeue[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue_queue_read
static const byte fun_data_asyncio_core_IOQueue_queue_read[15] = {
    0x2a,0x06, // prelude
    0x39,0x63,0x64, // names: queue_read, self, s
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x32, // LOAD_METHOD '_enqueue'
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue_queue_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue_queue_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 57,
        .line_info = fun_data_asyncio_core_IOQueue_queue_read + 5,
        .line_info_top = fun_data_asyncio_core_IOQueue_queue_read + 5,
        .opcodes = fun_data_asyncio_core_IOQueue_queue_read + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue_queue_read fun_data_asyncio_core_IOQueue_queue_read[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue_queue_write
static const byte fun_data_asyncio_core_IOQueue_queue_write[15] = {
    0x2a,0x06, // prelude
    0x3a,0x63,0x64, // names: queue_write, self, s
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x32, // LOAD_METHOD '_enqueue'
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue_queue_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue_queue_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_asyncio_core_IOQueue_queue_write + 5,
        .line_info_top = fun_data_asyncio_core_IOQueue_queue_write + 5,
        .opcodes = fun_data_asyncio_core_IOQueue_queue_write + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue_queue_write fun_data_asyncio_core_IOQueue_queue_write[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue_remove
static const byte fun_data_asyncio_core_IOQueue_remove[65] = {
    0x6a,0x06, // prelude
    0x3b,0x63,0x0b, // names: remove, self, task
     // code info
    0x51, // LOAD_CONST_NONE
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0x5f, // GET_ITER_STACK
    0x4b,0x1f, // FOR_ITER 31
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0xb3, // LOAD_FAST 3
    0x55, // LOAD_SUBSCR
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xc6, // STORE_FAST 6
    0xb4, // LOAD_FAST 4
    0xb1, // LOAD_FAST 1
    0xde, // BINARY_OP 7 <is>
    0x43,0x45, // POP_JUMP_IF_TRUE 5
    0xb5, // LOAD_FAST 5
    0xb1, // LOAD_FAST 1
    0xde, // BINARY_OP 7 <is>
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb6, // LOAD_FAST 6
    0xc2, // STORE_FAST 2
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x1f, // JUMP -33
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb0, // LOAD_FAST 0
    0x14,0x37, // LOAD_METHOD '_dequeue'
    0xb6, // LOAD_FAST 6
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x42, // JUMP 2
    0x42,0x06, // JUMP -58
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue_remove = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue_remove,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 65,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 59,
        .line_info = fun_data_asyncio_core_IOQueue_remove + 5,
        .line_info_top = fun_data_asyncio_core_IOQueue_remove + 5,
        .opcodes = fun_data_asyncio_core_IOQueue_remove + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue_remove fun_data_asyncio_core_IOQueue_remove[0]
#endif

// child of asyncio_core_IOQueue
// frozen bytecode for file asyncio/core.py, scope asyncio_core_IOQueue_wait_io_event
static const byte fun_data_asyncio_core_IOQueue_wait_io_event[156] = {
    0x62,0x06, // prelude
    0x1f,0x63,0x67, // names: wait_io_event, self, dt
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x3c, // LOAD_METHOD 'ipoll'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x5f, // GET_ITER_STACK
    0x4b,0x89,0x01, // FOR_ITER 137
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'map'
    0x12,0x66, // LOAD_GLOBAL 'id'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x55, // LOAD_SUBSCR
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x35, // LOAD_ATTR 'POLLOUT'
    0xd2, // UNARY_OP 2 __invert__
    0xef, // BINARY_OP 24 __and__
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x56, // STORE_SUBSCR
    0xb3, // LOAD_FAST 3
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x34, // LOAD_ATTR 'POLLIN'
    0xd2, // UNARY_OP 2 __invert__
    0xef, // BINARY_OP 24 __and__
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x56, // STORE_SUBSCR
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb0, // LOAD_FAST 0
    0x14,0x37, // LOAD_METHOD '_dequeue'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x63, // JUMP 35
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x36, // LOAD_METHOD 'modify'
    0xb2, // LOAD_FAST 2
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x35, // LOAD_ATTR 'POLLOUT'
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x42,0x4d, // JUMP 13
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'poller'
    0x14,0x36, // LOAD_METHOD 'modify'
    0xb2, // LOAD_FAST 2
    0x12,0x07, // LOAD_GLOBAL 'select'
    0x13,0x34, // LOAD_ATTR 'POLLIN'
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x42,0xf4,0x7e, // JUMP -140
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue_wait_io_event = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue_wait_io_event,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 156,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 31,
        .line_info = fun_data_asyncio_core_IOQueue_wait_io_event + 5,
        .line_info_top = fun_data_asyncio_core_IOQueue_wait_io_event + 5,
        .opcodes = fun_data_asyncio_core_IOQueue_wait_io_event + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_IOQueue_wait_io_event fun_data_asyncio_core_IOQueue_wait_io_event[0]
#endif

static const mp_raw_code_t *const children_asyncio_core_IOQueue[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue__enqueue,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue__dequeue,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue_queue_read,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue_queue_write,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue_remove,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue_wait_io_event,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_core_IOQueue = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_IOQueue,
    .children = (void *)&children_asyncio_core_IOQueue,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 41,
    .n_children = 7,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_asyncio_core_IOQueue + 3,
        .line_info_top = fun_data_asyncio_core_IOQueue + 3,
        .opcodes = fun_data_asyncio_core_IOQueue + 3,
    },
    #endif
    #endif
};

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core__promote_to_task
static const byte fun_data_asyncio_core__promote_to_task[21] = {
    0x19,0x04, // prelude
    0x17,0x56, // names: _promote_to_task, aw
     // code info
    0x12,0x57, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x09, // LOAD_GLOBAL 'Task'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
    0x12,0x18, // LOAD_GLOBAL 'create_task'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core__promote_to_task = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core__promote_to_task,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 21,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 23,
        .line_info = fun_data_asyncio_core__promote_to_task + 4,
        .line_info_top = fun_data_asyncio_core__promote_to_task + 4,
        .opcodes = fun_data_asyncio_core__promote_to_task + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core__promote_to_task fun_data_asyncio_core__promote_to_task[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_create_task
static const byte fun_data_asyncio_core_create_task[40] = {
    0x21,0x04, // prelude
    0x18,0x22, // names: create_task, coro
     // code info
    0x12,0x58, // LOAD_GLOBAL 'hasattr'
    0xb0, // LOAD_FAST 0
    0x10,0x19, // LOAD_CONST_STRING 'send'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x59, // LOAD_GLOBAL 'TypeError'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x09, // LOAD_GLOBAL 'Task'
    0xb0, // LOAD_FAST 0
    0x12,0x5a, // LOAD_GLOBAL 'globals'
    0x34,0x00, // CALL_FUNCTION 0
    0x34,0x02, // CALL_FUNCTION 2
    0xc1, // STORE_FAST 1
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_create_task = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_create_task,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_asyncio_core_create_task + 4,
        .line_info_top = fun_data_asyncio_core_create_task + 4,
        .opcodes = fun_data_asyncio_core_create_task + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_create_task fun_data_asyncio_core_create_task[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_run_until_complete
static const byte fun_data_asyncio_core_run_until_complete[346] = {
    0xf1,0x03,0x04, // prelude
    0x1b,0x5c, // names: run_until_complete, main_task
     // code info
    0x12,0x0c, // LOAD_GLOBAL 'CancelledError'
    0x12,0x4b, // LOAD_GLOBAL 'Exception'
    0x2a,0x02, // BUILD_TUPLE 2
    0xc1, // STORE_FAST 1
    0x12,0x0c, // LOAD_GLOBAL 'CancelledError'
    0x12,0x5d, // LOAD_GLOBAL 'StopIteration'
    0x2a,0x02, // BUILD_TUPLE 2
    0xc2, // STORE_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc3, // STORE_FAST 3
    0x42,0x7e, // JUMP 62
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xc3, // STORE_FAST 3
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1c, // LOAD_METHOD 'peek'
    0x36,0x00, // CALL_METHOD 0
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x54, // LOAD_GLOBAL 'max'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x12,0x03, // LOAD_GLOBAL 'ticks_diff'
    0xb4, // LOAD_FAST 4
    0x13,0x1d, // LOAD_ATTR 'ph_key'
    0x12,0x49, // LOAD_GLOBAL 'ticks'
    0x34,0x00, // CALL_FUNCTION 0
    0x34,0x02, // CALL_FUNCTION 2
    0x34,0x02, // CALL_FUNCTION 2
    0xc3, // STORE_FAST 3
    0x42,0x57, // JUMP 23
    0x12,0x5e, // LOAD_GLOBAL '_io_queue'
    0x13,0x1e, // LOAD_ATTR 'map'
    0x43,0x51, // POP_JUMP_IF_TRUE 17
    0x51, // LOAD_CONST_NONE
    0x17,0x4d, // STORE_GLOBAL 'cur_task'
    0xb0, // LOAD_FAST 0
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'state'
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x83, // LOAD_CONST_SMALL_INT 3
    0xc3, // STORE_FAST 3
    0x42,0x40, // JUMP 0
    0x12,0x5e, // LOAD_GLOBAL '_io_queue'
    0x14,0x1f, // LOAD_METHOD 'wait_io_event'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x43,0xbc,0x7f, // POP_JUMP_IF_TRUE -68
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x20, // LOAD_METHOD 'pop'
    0x36,0x00, // CALL_METHOD 0
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x17,0x4d, // STORE_GLOBAL 'cur_task'
    0x48,0x22, // SETUP_EXCEPT 34
    0xb4, // LOAD_FAST 4
    0x13,0x21, // LOAD_ATTR 'data'
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0xb4, // LOAD_FAST 4
    0x13,0x22, // LOAD_ATTR 'coro'
    0x14,0x19, // LOAD_METHOD 'send'
    0x51, // LOAD_CONST_NONE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x4d, // JUMP 13
    0x51, // LOAD_CONST_NONE
    0xb4, // LOAD_FAST 4
    0x18,0x21, // STORE_ATTR 'data'
    0xb4, // LOAD_FAST 4
    0x13,0x22, // LOAD_ATTR 'coro'
    0x14,0x23, // LOAD_METHOD 'throw'
    0xb5, // LOAD_FAST 5
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0xcc,0x01, // POP_EXCEPT_JUMP 204
    0x57, // DUP_TOP
    0xb1, // LOAD_FAST 1
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0xc5,0x81, // POP_JUMP_IF_FALSE 197
    0xc6, // STORE_FAST 6
    0x49,0xba,0x01, // SETUP_FINALLY 186
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0xde, // BINARY_OP 7 <is>
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x44,0x5d, // POP_JUMP_IF_FALSE 29
    0x51, // LOAD_CONST_NONE
    0x17,0x4d, // STORE_GLOBAL 'cur_task'
    0x12,0x57, // LOAD_GLOBAL 'isinstance'
    0xb6, // LOAD_FAST 6
    0x12,0x5d, // LOAD_GLOBAL 'StopIteration'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0x50, // LOAD_CONST_FALSE
    0xb4, // LOAD_FAST 4
    0x18,0x15, // STORE_ATTR 'state'
    0xb6, // LOAD_FAST 6
    0x65, // RAISE_OBJ
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x50, // LOAD_CONST_FALSE
    0xb4, // LOAD_FAST 4
    0x18,0x15, // STORE_ATTR 'state'
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x44,0xe4,0x80, // POP_JUMP_IF_FALSE 100
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb7, // LOAD_FAST 7
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x50, // LOAD_CONST_FALSE
    0x42,0x41, // JUMP 1
    0x51, // LOAD_CONST_NONE
    0xb4, // LOAD_FAST 4
    0x18,0x15, // STORE_ATTR 'state'
    0x42,0x78, // JUMP 56
    0x12,0x5f, // LOAD_GLOBAL 'callable'
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0xb4, // LOAD_FAST 4
    0x14,0x15, // LOAD_METHOD 'state'
    0xb4, // LOAD_FAST 4
    0xb6, // LOAD_FAST 6
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0xb4, // LOAD_FAST 4
    0x18,0x15, // STORE_ATTR 'state'
    0x52, // LOAD_CONST_TRUE
    0xc7, // STORE_FAST 7
    0x42,0x5f, // JUMP 31
    0x42,0x50, // JUMP 16
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x14,0x20, // LOAD_METHOD 'pop'
    0x36,0x00, // CALL_METHOD 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0xc7, // STORE_FAST 7
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x14,0x1c, // LOAD_METHOD 'peek'
    0x36,0x00, // CALL_METHOD 0
    0x43,0x27, // POP_JUMP_IF_TRUE -25
    0x50, // LOAD_CONST_FALSE
    0xb4, // LOAD_FAST 4
    0x18,0x15, // STORE_ATTR 'state'
    0xb7, // LOAD_FAST 7
    0x43,0x50, // POP_JUMP_IF_TRUE 16
    0x12,0x57, // LOAD_GLOBAL 'isinstance'
    0xb6, // LOAD_FAST 6
    0xb2, // LOAD_FAST 2
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0xb4, // LOAD_FAST 4
    0x18,0x21, // STORE_ATTR 'data'
    0x42,0x62, // JUMP 34
    0xb4, // LOAD_FAST 4
    0x13,0x15, // LOAD_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x5b, // POP_JUMP_IF_FALSE 27
    0xb5, // LOAD_FAST 5
    0xb4, // LOAD_FAST 4
    0x18,0x21, // STORE_ATTR 'data'
    0xb5, // LOAD_FAST 5
    0x12,0x4c, // LOAD_GLOBAL '_exc_context'
    0x10,0x0f, // LOAD_CONST_STRING 'exception'
    0x56, // STORE_SUBSCR
    0xb4, // LOAD_FAST 4
    0x12,0x4c, // LOAD_GLOBAL '_exc_context'
    0x10,0x10, // LOAD_CONST_STRING 'future'
    0x56, // STORE_SUBSCR
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x14,0x24, // LOAD_METHOD 'call_exception_handler'
    0x12,0x4c, // LOAD_GLOBAL '_exc_context'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x40, // JUMP 0
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0xb6, // LOAD_FAST 6
    0x13,0x25, // LOAD_ATTR 'value'
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc6, // STORE_FAST 6
    0x28,0x06, // DELETE_FAST 6
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x42,0xbb,0x7d, // JUMP -325
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_run_until_complete = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_run_until_complete,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 346,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 27,
        .line_info = fun_data_asyncio_core_run_until_complete + 5,
        .line_info_top = fun_data_asyncio_core_run_until_complete + 5,
        .opcodes = fun_data_asyncio_core_run_until_complete + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_run_until_complete fun_data_asyncio_core_run_until_complete[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_run
static const byte fun_data_asyncio_core_run[14] = {
    0x19,0x04, // prelude
    0x26,0x22, // names: run, coro
     // code info
    0x12,0x1b, // LOAD_GLOBAL 'run_until_complete'
    0x12,0x18, // LOAD_GLOBAL 'create_task'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_run = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_run,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 38,
        .line_info = fun_data_asyncio_core_run + 4,
        .line_info_top = fun_data_asyncio_core_run + 4,
        .opcodes = fun_data_asyncio_core_run + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_run fun_data_asyncio_core_run[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core__stopper
static const byte fun_data_asyncio_core__stopper[6] = {
    0x80,0x40,0x02, // prelude
    0x27, // names: _stopper
     // code info
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core__stopper = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_core__stopper,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data_asyncio_core__stopper + 4,
        .line_info_top = fun_data_asyncio_core__stopper + 4,
        .opcodes = fun_data_asyncio_core__stopper + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core__stopper fun_data_asyncio_core__stopper[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop
static const byte fun_data_asyncio_core_Loop[52] = {
    0x00,0x02, // prelude
    0x13, // names: Loop
     // code info
    0x11,0x4f, // LOAD_NAME '__name__'
    0x16,0x50, // STORE_NAME '__module__'
    0x10,0x13, // LOAD_CONST_STRING 'Loop'
    0x16,0x51, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x16,0x41, // STORE_NAME '_exc_handler'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x18, // STORE_NAME 'create_task'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x3d, // STORE_NAME 'run_forever'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x1b, // STORE_NAME 'run_until_complete'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x3e, // STORE_NAME 'stop'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x3f, // STORE_NAME 'close'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x40, // STORE_NAME 'set_exception_handler'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x42, // STORE_NAME 'get_exception_handler'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x43, // STORE_NAME 'default_exception_handler'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x24, // STORE_NAME 'call_exception_handler'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_create_task
static const byte fun_data_asyncio_core_Loop_create_task[10] = {
    0x11,0x04, // prelude
    0x18,0x22, // names: create_task, coro
     // code info
    0x12,0x18, // LOAD_GLOBAL 'create_task'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_create_task = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_create_task,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_asyncio_core_Loop_create_task + 4,
        .line_info_top = fun_data_asyncio_core_Loop_create_task + 4,
        .opcodes = fun_data_asyncio_core_Loop_create_task + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_create_task fun_data_asyncio_core_Loop_create_task[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_run_forever
static const byte fun_data_asyncio_core_Loop_run_forever[26] = {
    0x10,0x02, // prelude
    0x3d, // names: run_forever
     // code info
    0x12,0x09, // LOAD_GLOBAL 'Task'
    0x12,0x27, // LOAD_GLOBAL '_stopper'
    0x34,0x00, // CALL_FUNCTION 0
    0x12,0x5a, // LOAD_GLOBAL 'globals'
    0x34,0x00, // CALL_FUNCTION 0
    0x34,0x02, // CALL_FUNCTION 2
    0x17,0x4e, // STORE_GLOBAL '_stop_task'
    0x12,0x1b, // LOAD_GLOBAL 'run_until_complete'
    0x12,0x4e, // LOAD_GLOBAL '_stop_task'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_run_forever = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_run_forever,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 61,
        .line_info = fun_data_asyncio_core_Loop_run_forever + 3,
        .line_info_top = fun_data_asyncio_core_Loop_run_forever + 3,
        .opcodes = fun_data_asyncio_core_Loop_run_forever + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_run_forever fun_data_asyncio_core_Loop_run_forever[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_run_until_complete
static const byte fun_data_asyncio_core_Loop_run_until_complete[14] = {
    0x19,0x04, // prelude
    0x1b,0x56, // names: run_until_complete, aw
     // code info
    0x12,0x1b, // LOAD_GLOBAL 'run_until_complete'
    0x12,0x17, // LOAD_GLOBAL '_promote_to_task'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_run_until_complete = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_run_until_complete,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 27,
        .line_info = fun_data_asyncio_core_Loop_run_until_complete + 4,
        .line_info_top = fun_data_asyncio_core_Loop_run_until_complete + 4,
        .opcodes = fun_data_asyncio_core_Loop_run_until_complete + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_run_until_complete fun_data_asyncio_core_Loop_run_until_complete[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_stop
static const byte fun_data_asyncio_core_Loop_stop[24] = {
    0x10,0x02, // prelude
    0x3e, // names: stop
     // code info
    0x12,0x4e, // LOAD_GLOBAL '_stop_task'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x5b, // LOAD_GLOBAL '_task_queue'
    0x14,0x1a, // LOAD_METHOD 'push'
    0x12,0x4e, // LOAD_GLOBAL '_stop_task'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x17,0x4e, // STORE_GLOBAL '_stop_task'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_stop = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_stop,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 24,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 62,
        .line_info = fun_data_asyncio_core_Loop_stop + 3,
        .line_info_top = fun_data_asyncio_core_Loop_stop + 3,
        .opcodes = fun_data_asyncio_core_Loop_stop + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_stop fun_data_asyncio_core_Loop_stop[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_close
static const byte fun_data_asyncio_core_Loop_close[5] = {
    0x00,0x02, // prelude
    0x3f, // names: close
     // code info
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 5,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 63,
        .line_info = fun_data_asyncio_core_Loop_close + 3,
        .line_info_top = fun_data_asyncio_core_Loop_close + 3,
        .opcodes = fun_data_asyncio_core_Loop_close + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_close fun_data_asyncio_core_Loop_close[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_set_exception_handler
static const byte fun_data_asyncio_core_Loop_set_exception_handler[11] = {
    0x11,0x04, // prelude
    0x40,0x68, // names: set_exception_handler, handler
     // code info
    0xb0, // LOAD_FAST 0
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x18,0x41, // STORE_ATTR '_exc_handler'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_set_exception_handler = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_set_exception_handler,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 11,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_asyncio_core_Loop_set_exception_handler + 4,
        .line_info_top = fun_data_asyncio_core_Loop_set_exception_handler + 4,
        .opcodes = fun_data_asyncio_core_Loop_set_exception_handler + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_set_exception_handler fun_data_asyncio_core_Loop_set_exception_handler[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_get_exception_handler
static const byte fun_data_asyncio_core_Loop_get_exception_handler[8] = {
    0x00,0x02, // prelude
    0x42, // names: get_exception_handler
     // code info
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x13,0x41, // LOAD_ATTR '_exc_handler'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_get_exception_handler = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_get_exception_handler,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 8,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 66,
        .line_info = fun_data_asyncio_core_Loop_get_exception_handler + 3,
        .line_info_top = fun_data_asyncio_core_Loop_get_exception_handler + 3,
        .opcodes = fun_data_asyncio_core_Loop_get_exception_handler + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_get_exception_handler fun_data_asyncio_core_Loop_get_exception_handler[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_default_exception_handler
static const byte fun_data_asyncio_core_Loop_default_exception_handler[64] = {
    0x42,0x06, // prelude
    0x43,0x69,0x6a, // names: default_exception_handler, loop, context
     // code info
    0x12,0x6b, // LOAD_GLOBAL 'print'
    0xb1, // LOAD_FAST 1
    0x10,0x0e, // LOAD_CONST_STRING 'message'
    0x55, // LOAD_SUBSCR
    0x10,0x44, // LOAD_CONST_STRING 'file'
    0x12,0x06, // LOAD_GLOBAL 'sys'
    0x13,0x45, // LOAD_ATTR 'stderr'
    0x34,0x82,0x01, // CALL_FUNCTION 257
    0x59, // POP_TOP
    0x12,0x6b, // LOAD_GLOBAL 'print'
    0x10,0x46, // LOAD_CONST_STRING 'future:'
    0xb1, // LOAD_FAST 1
    0x10,0x10, // LOAD_CONST_STRING 'future'
    0x55, // LOAD_SUBSCR
    0x10,0x47, // LOAD_CONST_STRING 'coro='
    0xb1, // LOAD_FAST 1
    0x10,0x10, // LOAD_CONST_STRING 'future'
    0x55, // LOAD_SUBSCR
    0x13,0x22, // LOAD_ATTR 'coro'
    0x10,0x44, // LOAD_CONST_STRING 'file'
    0x12,0x06, // LOAD_GLOBAL 'sys'
    0x13,0x45, // LOAD_ATTR 'stderr'
    0x34,0x82,0x04, // CALL_FUNCTION 260
    0x59, // POP_TOP
    0x12,0x06, // LOAD_GLOBAL 'sys'
    0x14,0x48, // LOAD_METHOD 'print_exception'
    0xb1, // LOAD_FAST 1
    0x10,0x0f, // LOAD_CONST_STRING 'exception'
    0x55, // LOAD_SUBSCR
    0x12,0x06, // LOAD_GLOBAL 'sys'
    0x13,0x45, // LOAD_ATTR 'stderr'
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_default_exception_handler = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_default_exception_handler,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 64,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 67,
        .line_info = fun_data_asyncio_core_Loop_default_exception_handler + 5,
        .line_info_top = fun_data_asyncio_core_Loop_default_exception_handler + 5,
        .opcodes = fun_data_asyncio_core_Loop_default_exception_handler + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_default_exception_handler fun_data_asyncio_core_Loop_default_exception_handler[0]
#endif

// child of asyncio_core_Loop
// frozen bytecode for file asyncio/core.py, scope asyncio_core_Loop_call_exception_handler
static const byte fun_data_asyncio_core_Loop_call_exception_handler[22] = {
    0x19,0x04, // prelude
    0x24,0x6a, // names: call_exception_handler, context
     // code info
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x13,0x41, // LOAD_ATTR '_exc_handler'
    0x45,0x04, // JUMP_IF_TRUE_OR_POP 4
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x13,0x43, // LOAD_ATTR 'default_exception_handler'
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0xb0, // LOAD_FAST 0
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop_call_exception_handler = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop_call_exception_handler,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 36,
        .line_info = fun_data_asyncio_core_Loop_call_exception_handler + 4,
        .line_info_top = fun_data_asyncio_core_Loop_call_exception_handler + 4,
        .opcodes = fun_data_asyncio_core_Loop_call_exception_handler + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_Loop_call_exception_handler fun_data_asyncio_core_Loop_call_exception_handler[0]
#endif

static const mp_raw_code_t *const children_asyncio_core_Loop[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_create_task,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_run_forever,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_run_until_complete,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_stop,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_close,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_set_exception_handler,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_get_exception_handler,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_default_exception_handler,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop_call_exception_handler,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_core_Loop = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_Loop,
    .children = (void *)&children_asyncio_core_Loop,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 52,
    .n_children = 9,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_asyncio_core_Loop + 3,
        .line_info_top = fun_data_asyncio_core_Loop + 3,
        .opcodes = fun_data_asyncio_core_Loop + 3,
    },
    #endif
    #endif
};

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_get_event_loop
static const byte fun_data_asyncio_core_get_event_loop[10] = {
    0x92,0x80,0x01,0x06, // prelude
    0x28,0x60,0x61, // names: get_event_loop, runq_len, waitq_len
     // code info
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_get_event_loop = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_get_event_loop,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 40,
        .line_info = fun_data_asyncio_core_get_event_loop + 7,
        .line_info_top = fun_data_asyncio_core_get_event_loop + 7,
        .opcodes = fun_data_asyncio_core_get_event_loop + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_get_event_loop fun_data_asyncio_core_get_event_loop[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_current_task
static const byte fun_data_asyncio_core_current_task[19] = {
    0x08,0x02, // prelude
    0x29, // names: current_task
     // code info
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x62, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x4d, // LOAD_GLOBAL 'cur_task'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_current_task = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_current_task,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_asyncio_core_current_task + 3,
        .line_info_top = fun_data_asyncio_core_current_task + 3,
        .opcodes = fun_data_asyncio_core_current_task + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_current_task fun_data_asyncio_core_current_task[0]
#endif

// child of asyncio_core__lt_module_gt_
// frozen bytecode for file asyncio/core.py, scope asyncio_core_new_event_loop
static const byte fun_data_asyncio_core_new_event_loop[18] = {
    0x00,0x02, // prelude
    0x2a, // names: new_event_loop
     // code info
    0x12,0x08, // LOAD_GLOBAL 'TaskQueue'
    0x34,0x00, // CALL_FUNCTION 0
    0x17,0x5b, // STORE_GLOBAL '_task_queue'
    0x12,0x12, // LOAD_GLOBAL 'IOQueue'
    0x34,0x00, // CALL_FUNCTION 0
    0x17,0x5e, // STORE_GLOBAL '_io_queue'
    0x12,0x13, // LOAD_GLOBAL 'Loop'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_core_new_event_loop = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core_new_event_loop,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 42,
        .line_info = fun_data_asyncio_core_new_event_loop + 3,
        .line_info_top = fun_data_asyncio_core_new_event_loop + 3,
        .opcodes = fun_data_asyncio_core_new_event_loop + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_core_new_event_loop fun_data_asyncio_core_new_event_loop[0]
#endif

static const mp_raw_code_t *const children_asyncio_core__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_core_CancelledError,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_TimeoutError,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_SingletonGenerator,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_sleep_ms,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_sleep,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_IOQueue,
    (const mp_raw_code_t *)&proto_fun_asyncio_core__promote_to_task,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_create_task,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_run_until_complete,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_run,
    (const mp_raw_code_t *)&proto_fun_asyncio_core__stopper,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_Loop,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_get_event_loop,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_current_task,
    (const mp_raw_code_t *)&proto_fun_asyncio_core_new_event_loop,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_core__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_core__lt_module_gt_,
    .children = (void *)&children_asyncio_core__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 218,
    .n_children = 15,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio_core__lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio_core__lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio_core__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio_core[108] = {
    MP_QSTR_asyncio_slash_core_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_ticks_ms,
    MP_QSTR_ticks_diff,
    MP_QSTR_ticks_add,
    MP_QSTR_time,
    MP_QSTR_sys,
    MP_QSTR_select,
    MP_QSTR_TaskQueue,
    MP_QSTR_Task,
    MP_QSTR__asyncio,
    MP_QSTR_task,
    MP_QSTR_CancelledError,
    MP_QSTR_TimeoutError,
    MP_QSTR_message,
    MP_QSTR_exception,
    MP_QSTR_future,
    MP_QSTR_SingletonGenerator,
    MP_QSTR_IOQueue,
    MP_QSTR_Loop,
    MP_QSTR_sleep_ms,
    MP_QSTR_state,
    MP_QSTR_sleep,
    MP_QSTR__promote_to_task,
    MP_QSTR_create_task,
    MP_QSTR_send,
    MP_QSTR_push,
    MP_QSTR_run_until_complete,
    MP_QSTR_peek,
    MP_QSTR_ph_key,
    MP_QSTR_map,
    MP_QSTR_wait_io_event,
    MP_QSTR_pop,
    MP_QSTR_data,
    MP_QSTR_coro,
    MP_QSTR_throw,
    MP_QSTR_call_exception_handler,
    MP_QSTR_value,
    MP_QSTR_run,
    MP_QSTR__stopper,
    MP_QSTR_get_event_loop,
    MP_QSTR_current_task,
    MP_QSTR_new_event_loop,
    MP_QSTR___init__,
    MP_QSTR_exc,
    MP_QSTR___iter__,
    MP_QSTR___next__,
    MP_QSTR___traceback__,
    MP_QSTR_poll,
    MP_QSTR_poller,
    MP_QSTR__enqueue,
    MP_QSTR_register,
    MP_QSTR_POLLIN,
    MP_QSTR_POLLOUT,
    MP_QSTR_modify,
    MP_QSTR__dequeue,
    MP_QSTR_unregister,
    MP_QSTR_queue_read,
    MP_QSTR_queue_write,
    MP_QSTR_remove,
    MP_QSTR_ipoll,
    MP_QSTR_run_forever,
    MP_QSTR_stop,
    MP_QSTR_close,
    MP_QSTR_set_exception_handler,
    MP_QSTR__exc_handler,
    MP_QSTR_get_exception_handler,
    MP_QSTR_default_exception_handler,
    MP_QSTR_file,
    MP_QSTR_stderr,
    MP_QSTR_future_colon_,
    MP_QSTR_coro_equals_,
    MP_QSTR_print_exception,
    MP_QSTR_ticks,
    MP_QSTR_BaseException,
    MP_QSTR_Exception,
    MP_QSTR__exc_context,
    MP_QSTR_cur_task,
    MP_QSTR__stop_task,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_t,
    MP_QSTR_sgen,
    MP_QSTR_max,
    MP_QSTR_int,
    MP_QSTR_aw,
    MP_QSTR_isinstance,
    MP_QSTR_hasattr,
    MP_QSTR_TypeError,
    MP_QSTR_globals,
    MP_QSTR__task_queue,
    MP_QSTR_main_task,
    MP_QSTR_StopIteration,
    MP_QSTR__io_queue,
    MP_QSTR_callable,
    MP_QSTR_runq_len,
    MP_QSTR_waitq_len,
    MP_QSTR_RuntimeError,
    MP_QSTR_self,
    MP_QSTR_s,
    MP_QSTR_idx,
    MP_QSTR_id,
    MP_QSTR_dt,
    MP_QSTR_handler,
    MP_QSTR_loop,
    MP_QSTR_context,
    MP_QSTR_print,
};

// constants
static const mp_obj_str_t const_obj_asyncio_core_0 = {{&mp_type_str}, 64973, 31, (const byte*)"\x54\x61\x73\x6b\x20\x65\x78\x63\x65\x70\x74\x69\x6f\x6e\x20\x77\x61\x73\x6e\x27\x74\x20\x72\x65\x74\x72\x69\x65\x76\x65\x64"};

// constant table
static const mp_rom_obj_t const_obj_table_data_asyncio_core[3] = {
    MP_ROM_PTR(&const_obj_asyncio_core_0),
    MP_ROM_QSTR(MP_QSTR_coroutine_space_expected),
    MP_ROM_QSTR(MP_QSTR_no_space_running_space_event_space_loop),
};

static const mp_frozen_module_t frozen_module_asyncio_core = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio_core,
        .obj_table = (mp_obj_t *)&const_obj_table_data_asyncio_core,
    },
    .proto_fun = &proto_fun_asyncio_core__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio_event
// - original source file: build/frozen_mpy/asyncio/event.mpy
// - frozen file name: asyncio/event.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/event.py, scope asyncio_event__lt_module_gt_
static const byte fun_data_asyncio_event__lt_module_gt_[59] = {
    0x2c,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x02, // LOAD_CONST_STRING 'core'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME ''
    0x1c,0x02, // IMPORT_FROM 'core'
    0x16,0x02, // STORE_NAME 'core'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x04, // LOAD_CONST_STRING 'Event'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x04, // STORE_NAME 'Event'
    0x48,0x15, // SETUP_EXCEPT 21
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x05, // IMPORT_NAME 'io'
    0x16,0x05, // STORE_NAME 'io'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x06, // LOAD_CONST_STRING 'ThreadSafeFlag'
    0x11,0x05, // LOAD_NAME 'io'
    0x13,0x07, // LOAD_ATTR 'IOBase'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x06, // STORE_NAME 'ThreadSafeFlag'
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x11,0x19, // LOAD_NAME 'ImportError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_event__lt_module_gt_
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event
static const byte fun_data_asyncio_event_Event[33] = {
    0x00,0x02, // prelude
    0x04, // names: Event
     // code info
    0x11,0x1a, // LOAD_NAME '__name__'
    0x16,0x1b, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'Event'
    0x16,0x1c, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x08, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0c, // STORE_NAME 'is_set'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0d, // STORE_NAME 'set'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x12, // STORE_NAME 'clear'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x13, // STORE_NAME 'wait'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_event_Event
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event___init__
static const byte fun_data_asyncio_event_Event___init__[19] = {
    0x11,0x04, // prelude
    0x08,0x1d, // names: __init__, self
     // code info
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x0a, // LOAD_METHOD 'TaskQueue'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x0b, // STORE_ATTR 'waiting'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_Event___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_asyncio_event_Event___init__ + 4,
        .line_info_top = fun_data_asyncio_event_Event___init__ + 4,
        .opcodes = fun_data_asyncio_event_Event___init__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_Event___init__ fun_data_asyncio_event_Event___init__[0]
#endif

// child of asyncio_event_Event
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event_is_set
static const byte fun_data_asyncio_event_Event_is_set[8] = {
    0x09,0x04, // prelude
    0x0c,0x1d, // names: is_set, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'state'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event_is_set = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_Event_is_set,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 8,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_asyncio_event_Event_is_set + 4,
        .line_info_top = fun_data_asyncio_event_Event_is_set + 4,
        .opcodes = fun_data_asyncio_event_Event_is_set + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_Event_is_set fun_data_asyncio_event_Event_is_set[0]
#endif

// child of asyncio_event_Event
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event_set
static const byte fun_data_asyncio_event_Event_set[37] = {
    0x21,0x04, // prelude
    0x0d,0x1d, // names: set, self
     // code info
    0x42,0x50, // JUMP 16
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0e, // LOAD_ATTR '_task_queue'
    0x14,0x0f, // LOAD_METHOD 'push'
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'waiting'
    0x14,0x10, // LOAD_METHOD 'pop'
    0x36,0x00, // CALL_METHOD 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'waiting'
    0x14,0x11, // LOAD_METHOD 'peek'
    0x36,0x00, // CALL_METHOD 0
    0x43,0x27, // POP_JUMP_IF_TRUE -25
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event_set = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_Event_set,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_asyncio_event_Event_set + 4,
        .line_info_top = fun_data_asyncio_event_Event_set + 4,
        .opcodes = fun_data_asyncio_event_Event_set + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_Event_set fun_data_asyncio_event_Event_set[0]
#endif

// child of asyncio_event_Event
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event_clear
static const byte fun_data_asyncio_event_Event_clear[10] = {
    0x11,0x04, // prelude
    0x12,0x1d, // names: clear, self
     // code info
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event_clear = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_Event_clear,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_asyncio_event_Event_clear + 4,
        .line_info_top = fun_data_asyncio_event_Event_clear + 4,
        .opcodes = fun_data_asyncio_event_Event_clear + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_Event_clear fun_data_asyncio_event_Event_clear[0]
#endif

// child of asyncio_event_Event
// frozen bytecode for file asyncio/event.py, scope asyncio_event_Event_wait
static const byte fun_data_asyncio_event_Event_wait[36] = {
    0x99,0x40,0x04, // prelude
    0x13,0x1d, // names: wait, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'state'
    0x43,0x58, // POP_JUMP_IF_TRUE 24
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'waiting'
    0x14,0x0f, // LOAD_METHOD 'push'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x14, // LOAD_ATTR 'cur_task'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'waiting'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x14, // LOAD_ATTR 'cur_task'
    0x18,0x15, // STORE_ATTR 'data'
    0x51, // LOAD_CONST_NONE
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event_wait = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_event_Event_wait,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_asyncio_event_Event_wait + 5,
        .line_info_top = fun_data_asyncio_event_Event_wait + 5,
        .opcodes = fun_data_asyncio_event_Event_wait + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_Event_wait fun_data_asyncio_event_Event_wait[0]
#endif

static const mp_raw_code_t *const children_asyncio_event_Event[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event_is_set,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event_set,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event_clear,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event_wait,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_event_Event = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_Event,
    .children = (void *)&children_asyncio_event_Event,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 33,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data_asyncio_event_Event + 3,
        .line_info_top = fun_data_asyncio_event_Event + 3,
        .opcodes = fun_data_asyncio_event_Event + 3,
    },
    #endif
    #endif
};

// child of asyncio_event__lt_module_gt_
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag
static const byte fun_data_asyncio_event_ThreadSafeFlag[33] = {
    0x00,0x02, // prelude
    0x06, // names: ThreadSafeFlag
     // code info
    0x11,0x1a, // LOAD_NAME '__name__'
    0x16,0x1b, // STORE_NAME '__module__'
    0x10,0x06, // LOAD_CONST_STRING 'ThreadSafeFlag'
    0x16,0x1c, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x08, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x16, // STORE_NAME 'ioctl'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0d, // STORE_NAME 'set'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x12, // STORE_NAME 'clear'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x13, // STORE_NAME 'wait'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_event_ThreadSafeFlag
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag___init__
static const byte fun_data_asyncio_event_ThreadSafeFlag___init__[10] = {
    0x11,0x04, // prelude
    0x08,0x1d, // names: __init__, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag___init__ + 4,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag___init__ + 4,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag___init__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_ThreadSafeFlag___init__ fun_data_asyncio_event_ThreadSafeFlag___init__[0]
#endif

// child of asyncio_event_ThreadSafeFlag
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag_ioctl
static const byte fun_data_asyncio_event_ThreadSafeFlag_ioctl[19] = {
    0x23,0x08, // prelude
    0x16,0x1d,0x1e,0x1f, // names: ioctl, self, req, flags
     // code info
    0xb1, // LOAD_FAST 1
    0x83, // LOAD_CONST_SMALL_INT 3
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'state'
    0xb2, // LOAD_FAST 2
    0xf4, // BINARY_OP 29 __mul__
    0x63, // RETURN_VALUE
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag_ioctl = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag_ioctl,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 22,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag_ioctl + 6,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag_ioctl + 6,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag_ioctl + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_ThreadSafeFlag_ioctl fun_data_asyncio_event_ThreadSafeFlag_ioctl[0]
#endif

// child of asyncio_event_ThreadSafeFlag
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag_set
static const byte fun_data_asyncio_event_ThreadSafeFlag_set[10] = {
    0x11,0x04, // prelude
    0x0d,0x1d, // names: set, self
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag_set = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag_set,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag_set + 4,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag_set + 4,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag_set + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_ThreadSafeFlag_set fun_data_asyncio_event_ThreadSafeFlag_set[0]
#endif

// child of asyncio_event_ThreadSafeFlag
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag_clear
static const byte fun_data_asyncio_event_ThreadSafeFlag_clear[10] = {
    0x11,0x04, // prelude
    0x12,0x1d, // names: clear, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag_clear = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag_clear,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag_clear + 4,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag_clear + 4,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag_clear + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_ThreadSafeFlag_clear fun_data_asyncio_event_ThreadSafeFlag_clear[0]
#endif

// child of asyncio_event_ThreadSafeFlag
// frozen bytecode for file asyncio/event.py, scope asyncio_event_ThreadSafeFlag_wait
static const byte fun_data_asyncio_event_ThreadSafeFlag_wait[27] = {
    0x99,0x40,0x04, // prelude
    0x13,0x1d, // names: wait, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'state'
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x17, // LOAD_ATTR '_io_queue'
    0x14,0x18, // LOAD_METHOD 'queue_read'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag_wait = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag_wait,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 27,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag_wait + 5,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag_wait + 5,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag_wait + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_event_ThreadSafeFlag_wait fun_data_asyncio_event_ThreadSafeFlag_wait[0]
#endif

static const mp_raw_code_t *const children_asyncio_event_ThreadSafeFlag[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag_ioctl,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag_set,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag_clear,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag_wait,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_event_ThreadSafeFlag = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event_ThreadSafeFlag,
    .children = (void *)&children_asyncio_event_ThreadSafeFlag,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 33,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_asyncio_event_ThreadSafeFlag + 3,
        .line_info_top = fun_data_asyncio_event_ThreadSafeFlag + 3,
        .opcodes = fun_data_asyncio_event_ThreadSafeFlag + 3,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_asyncio_event__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_event_Event,
    (const mp_raw_code_t *)&proto_fun_asyncio_event_ThreadSafeFlag,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_event__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_event__lt_module_gt_,
    .children = (void *)&children_asyncio_event__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 59,
    .n_children = 2,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio_event__lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio_event__lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio_event__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio_event[32] = {
    MP_QSTR_asyncio_slash_event_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_core,
    MP_QSTR_,
    MP_QSTR_Event,
    MP_QSTR_io,
    MP_QSTR_ThreadSafeFlag,
    MP_QSTR_IOBase,
    MP_QSTR___init__,
    MP_QSTR_state,
    MP_QSTR_TaskQueue,
    MP_QSTR_waiting,
    MP_QSTR_is_set,
    MP_QSTR_set,
    MP_QSTR__task_queue,
    MP_QSTR_push,
    MP_QSTR_pop,
    MP_QSTR_peek,
    MP_QSTR_clear,
    MP_QSTR_wait,
    MP_QSTR_cur_task,
    MP_QSTR_data,
    MP_QSTR_ioctl,
    MP_QSTR__io_queue,
    MP_QSTR_queue_read,
    MP_QSTR_ImportError,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_req,
    MP_QSTR_flags,
};

static const mp_frozen_module_t frozen_module_asyncio_event = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio_event,
        .obj_table = NULL,
    },
    .proto_fun = &proto_fun_asyncio_event__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio_funcs
// - original source file: build/frozen_mpy/asyncio/funcs.mpy
// - frozen file name: asyncio/funcs.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs__lt_module_gt_
static const byte fun_data_asyncio_funcs__lt_module_gt_[56] = {
    0x18,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x02, // LOAD_CONST_STRING 'core'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME ''
    0x1c,0x02, // IMPORT_FROM 'core'
    0x16,0x02, // STORE_NAME 'core'
    0x59, // POP_TOP
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x07, // STORE_NAME '_run'
    0x11,0x02, // LOAD_NAME 'core'
    0x13,0x04, // LOAD_ATTR 'sleep'
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x0b, // STORE_NAME 'wait_for'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x12, // STORE_NAME 'wait_for_ms'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x03, // MAKE_FUNCTION 3
    0x10,0x05, // LOAD_CONST_STRING '_Remove'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x05, // STORE_NAME '_Remove'
    0x53, // LOAD_NULL
    0x2c,0x00, // BUILD_MAP 0
    0x50, // LOAD_CONST_FALSE
    0x10,0x06, // LOAD_CONST_STRING 'return_exceptions'
    0x62, // STORE_MAP
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x14, // STORE_NAME 'gather'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_funcs__lt_module_gt_
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs__run
static const byte fun_data_asyncio_funcs__run[66] = {
    0xd2,0x42,0x06, // prelude
    0x07,0x1b,0x1c, // names: _run, waiter, aw
     // code info
    0x48,0x09, // SETUP_EXCEPT 9
    0xb1, // LOAD_FAST 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc2, // STORE_FAST 2
    0x52, // LOAD_CONST_TRUE
    0xc3, // STORE_FAST 3
    0x4a,0x16, // POP_EXCEPT_JUMP 22
    0x57, // DUP_TOP
    0x12,0x1d, // LOAD_GLOBAL 'BaseException'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xc4, // STORE_FAST 4
    0x49,0x05, // SETUP_FINALLY 5
    0x51, // LOAD_CONST_NONE
    0xc2, // STORE_FAST 2
    0xb4, // LOAD_FAST 4
    0xc3, // STORE_FAST 3
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x28,0x04, // DELETE_FAST 4
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'data'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xb0, // LOAD_FAST 0
    0x14,0x09, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x0a, // LOAD_METHOD 'CancelledError'
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0xb0, // LOAD_FAST 0
    0x18,0x08, // STORE_ATTR 'data'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs__run = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_funcs__run,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 66,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 7,
        .line_info = fun_data_asyncio_funcs__run + 6,
        .line_info_top = fun_data_asyncio_funcs__run + 6,
        .opcodes = fun_data_asyncio_funcs__run + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs__run fun_data_asyncio_funcs__run[0]
#endif

// child of asyncio_funcs__lt_module_gt_
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs_wait_for
static const byte fun_data_asyncio_funcs_wait_for[119] = {
    0xdb,0x43,0x08, // prelude
    0x0b,0x1c,0x1e,0x04, // names: wait_for, aw, timeout, sleep
     // code info
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x0c, // LOAD_METHOD '_promote_to_task'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc0, // STORE_FAST 0
    0xb1, // LOAD_FAST 1
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb0, // LOAD_FAST 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x0d, // LOAD_METHOD 'create_task'
    0x12,0x07, // LOAD_GLOBAL '_run'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0e, // LOAD_ATTR 'cur_task'
    0xb0, // LOAD_FAST 0
    0x34,0x02, // CALL_FUNCTION 2
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0x48,0x0a, // SETUP_EXCEPT 10
    0xb2, // LOAD_FAST 2
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x4a,0x32, // POP_EXCEPT_JUMP 50
    0x57, // DUP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0a, // LOAD_ATTR 'CancelledError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x69, // POP_JUMP_IF_FALSE 41
    0xc4, // STORE_FAST 4
    0x49,0x1f, // SETUP_FINALLY 31
    0xb4, // LOAD_FAST 4
    0x13,0x0f, // LOAD_ATTR 'value'
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb3, // LOAD_FAST 3
    0x14,0x09, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x65, // RAISE_OBJ
    0xb5, // LOAD_FAST 5
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb4, // LOAD_FAST 4
    0x13,0x10, // LOAD_ATTR 'args'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
    0xb5, // LOAD_FAST 5
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x28,0x04, // DELETE_FAST 4
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb3, // LOAD_FAST 3
    0x14,0x09, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x11, // LOAD_ATTR 'TimeoutError'
    0x65, // RAISE_OBJ
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs_wait_for = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_funcs_wait_for,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 119,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 11,
        .line_info = fun_data_asyncio_funcs_wait_for + 7,
        .line_info_top = fun_data_asyncio_funcs_wait_for + 7,
        .opcodes = fun_data_asyncio_funcs_wait_for + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs_wait_for fun_data_asyncio_funcs_wait_for[0]
#endif

// child of asyncio_funcs__lt_module_gt_
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs_wait_for_ms
static const byte fun_data_asyncio_funcs_wait_for_ms[16] = {
    0x2a,0x06, // prelude
    0x12,0x1c,0x1e, // names: wait_for_ms, aw, timeout
     // code info
    0x12,0x0b, // LOAD_GLOBAL 'wait_for'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x13, // LOAD_ATTR 'sleep_ms'
    0x34,0x03, // CALL_FUNCTION 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs_wait_for_ms = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs_wait_for_ms,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_asyncio_funcs_wait_for_ms + 5,
        .line_info_top = fun_data_asyncio_funcs_wait_for_ms + 5,
        .opcodes = fun_data_asyncio_funcs_wait_for_ms + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs_wait_for_ms fun_data_asyncio_funcs_wait_for_ms[0]
#endif

// child of asyncio_funcs__lt_module_gt_
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs__Remove
static const byte fun_data_asyncio_funcs__Remove[21] = {
    0x08,0x02, // prelude
    0x05, // names: _Remove
     // code info
    0x11,0x1f, // LOAD_NAME '__name__'
    0x16,0x20, // STORE_NAME '__module__'
    0x10,0x05, // LOAD_CONST_STRING '_Remove'
    0x16,0x21, // STORE_NAME '__qualname__'
    0x11,0x22, // LOAD_NAME 'staticmethod'
    0x32,0x00, // MAKE_FUNCTION 0
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x16, // STORE_NAME 'remove'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_funcs__Remove
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs__Remove_remove
static const byte fun_data_asyncio_funcs__Remove_remove[6] = {
    0x09,0x04, // prelude
    0x16,0x28, // names: remove, t
     // code info
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs__Remove_remove = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs__Remove_remove,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 22,
        .line_info = fun_data_asyncio_funcs__Remove_remove + 4,
        .line_info_top = fun_data_asyncio_funcs__Remove_remove + 4,
        .opcodes = fun_data_asyncio_funcs__Remove_remove + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs__Remove_remove fun_data_asyncio_funcs__Remove_remove[0]
#endif

static const mp_raw_code_t *const children_asyncio_funcs__Remove[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs__Remove_remove,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_funcs__Remove = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs__Remove,
    .children = (void *)&children_asyncio_funcs__Remove,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 21,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_asyncio_funcs__Remove + 3,
        .line_info_top = fun_data_asyncio_funcs__Remove + 3,
        .opcodes = fun_data_asyncio_funcs__Remove + 3,
    },
    #endif
    #endif
};

// child of asyncio_funcs__lt_module_gt_
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs_gather
static const byte fun_data_asyncio_funcs_gather[281] = {
    0xf0,0xca,0x80,0xc0,0x40,0x85,0x01, // prelude
    0x14,0x06, // names: gather, return_exceptions
    0x00,0x07,0x08, // code info
    0xb0, // LOAD_FAST 0
    0xb7, // LOAD_FAST 7
    0xb8, // LOAD_FAST 8
    0x20,0x00,0x03, // MAKE_CLOSURE 0
    0xc2, // STORE_FAST 2
    0x32,0x01, // MAKE_FUNCTION 1
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x27,0x07, // STORE_DEREF 7
    0x12,0x23, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0xc4,0x80, // JUMP 68
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x15, // LOAD_ATTR 'state'
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x18,0x15, // STORE_ATTR 'state'
    0x25,0x07, // LOAD_DEREF 7
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x27,0x07, // STORE_DEREF 7
    0x42,0x69, // JUMP 41
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x15, // LOAD_ATTR 'state'
    0x43,0x5b, // POP_JUMP_IF_TRUE 27
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x08, // LOAD_ATTR 'data'
    0x12,0x25, // LOAD_GLOBAL 'StopIteration'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x4c, // POP_JUMP_IF_TRUE 12
    0x25,0x00, // LOAD_DEREF 0
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0x12,0x23, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xd1, // UNARY_OP 1 __neg__
    0x27,0x07, // STORE_DEREF 7
    0x42,0x47, // JUMP 7
    0x12,0x26, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0xb6,0x7f, // POP_JUMP_IF_TRUE -74
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0e, // LOAD_ATTR 'cur_task'
    0x27,0x08, // STORE_DEREF 8
    0x50, // LOAD_CONST_FALSE
    0xc5, // STORE_FAST 5
    0x25,0x07, // LOAD_DEREF 7
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x66, // POP_JUMP_IF_FALSE 38
    0x12,0x05, // LOAD_GLOBAL '_Remove'
    0x25,0x08, // LOAD_DEREF 8
    0x18,0x08, // STORE_ATTR 'data'
    0x48,0x05, // SETUP_EXCEPT 5
    0x51, // LOAD_CONST_NONE
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x4a,0x19, // POP_EXCEPT_JUMP 25
    0x57, // DUP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0a, // LOAD_ATTR 'CancelledError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0xc6, // STORE_FAST 6
    0x49,0x06, // SETUP_FINALLY 6
    0x52, // LOAD_CONST_TRUE
    0xc5, // STORE_FAST 5
    0xb6, // LOAD_FAST 6
    0x27,0x07, // STORE_DEREF 7
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc6, // STORE_FAST 6
    0x28,0x06, // DELETE_FAST 6
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x12,0x23, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0xda,0x80, // JUMP 90
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x15, // LOAD_ATTR 'state'
    0xb2, // LOAD_FAST 2
    0xde, // BINARY_OP 7 <is>
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x52, // LOAD_CONST_TRUE
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x18,0x15, // STORE_ATTR 'state'
    0xb5, // LOAD_FAST 5
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x14,0x09, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x42,0x7a, // JUMP 58
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x08, // LOAD_ATTR 'data'
    0x12,0x25, // LOAD_GLOBAL 'StopIteration'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x08, // LOAD_ATTR 'data'
    0x13,0x0f, // LOAD_ATTR 'value'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x56, // STORE_SUBSCR
    0x42,0x61, // JUMP 33
    0x25,0x00, // LOAD_DEREF 0
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x08, // LOAD_ATTR 'data'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x56, // STORE_SUBSCR
    0x42,0x53, // JUMP 19
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0x25,0x07, // LOAD_DEREF 7
    0x12,0x27, // LOAD_GLOBAL 'int'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0x13,0x08, // LOAD_ATTR 'data'
    0x27,0x07, // STORE_DEREF 7
    0x42,0x40, // JUMP 0
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0xa0,0x7f, // POP_JUMP_IF_TRUE -96
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x25,0x07, // LOAD_DEREF 7
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x25,0x07, // LOAD_DEREF 7
    0x65, // RAISE_OBJ
    0xb3, // LOAD_FAST 3
    0x63, // RETURN_VALUE
};
// child of asyncio_funcs_gather
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs_gather_done
static const byte fun_data_asyncio_funcs_gather_done[64] = {
    0xb9,0x04,0x0c, // prelude
    0x17,0x29,0x29,0x29,0x28,0x2a, // names: done, *, *, *, t, er
     // code info
    0x25,0x02, // LOAD_DEREF 2
    0x13,0x08, // LOAD_ATTR 'data'
    0x12,0x05, // LOAD_GLOBAL '_Remove'
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x25,0x00, // LOAD_DEREF 0
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0xb4, // LOAD_FAST 4
    0x12,0x25, // LOAD_GLOBAL 'StopIteration'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x45, // POP_JUMP_IF_TRUE 5
    0xb4, // LOAD_FAST 4
    0x27,0x01, // STORE_DEREF 1
    0x42,0x4c, // JUMP 12
    0x25,0x01, // LOAD_DEREF 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe6, // BINARY_OP 15 __isub__
    0x27,0x01, // STORE_DEREF 1
    0x25,0x01, // LOAD_DEREF 1
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_task_queue'
    0x14,0x19, // LOAD_METHOD 'push'
    0x25,0x02, // LOAD_DEREF 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs_gather_done = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs_gather_done,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 64,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 23,
        .line_info = fun_data_asyncio_funcs_gather_done + 9,
        .line_info_top = fun_data_asyncio_funcs_gather_done + 9,
        .opcodes = fun_data_asyncio_funcs_gather_done + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs_gather_done fun_data_asyncio_funcs_gather_done[0]
#endif

// child of asyncio_funcs_gather
// frozen bytecode for file asyncio/funcs.py, scope asyncio_funcs_gather__lt_listcomp_gt_
static const byte fun_data_asyncio_funcs_gather__lt_listcomp_gt_[23] = {
    0x49,0x04, // prelude
    0x1a,0x29, // names: <listcomp>, *
     // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x0c, // FOR_ITER 12
    0xc1, // STORE_FAST 1
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x0c, // LOAD_METHOD '_promote_to_task'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x2f,0x14, // STORE_COMP 20
    0x42,0x32, // JUMP -14
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_funcs_gather__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs_gather__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 23,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 26,
        .line_info = fun_data_asyncio_funcs_gather__lt_listcomp_gt_ + 4,
        .line_info_top = fun_data_asyncio_funcs_gather__lt_listcomp_gt_ + 4,
        .opcodes = fun_data_asyncio_funcs_gather__lt_listcomp_gt_ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_funcs_gather__lt_listcomp_gt_ fun_data_asyncio_funcs_gather__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_asyncio_funcs_gather[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs_gather_done,
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs_gather__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_funcs_gather = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_funcs_gather,
    .children = (void *)&children_asyncio_funcs_gather,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 281,
    .n_children = 2,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 2,
        .scope_flags = 13,
        .n_pos_args = 0,
        .n_kwonly_args = 1,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 20,
        .line_info = fun_data_asyncio_funcs_gather + 9,
        .line_info_top = fun_data_asyncio_funcs_gather + 9,
        .opcodes = fun_data_asyncio_funcs_gather + 12,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_asyncio_funcs__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs__run,
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs_wait_for,
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs_wait_for_ms,
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs__Remove,
    (const mp_raw_code_t *)&proto_fun_asyncio_funcs_gather,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_funcs__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_funcs__lt_module_gt_,
    .children = (void *)&children_asyncio_funcs__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 56,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio_funcs__lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio_funcs__lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio_funcs__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio_funcs[43] = {
    MP_QSTR_asyncio_slash_funcs_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_core,
    MP_QSTR_,
    MP_QSTR_sleep,
    MP_QSTR__Remove,
    MP_QSTR_return_exceptions,
    MP_QSTR__run,
    MP_QSTR_data,
    MP_QSTR_cancel,
    MP_QSTR_CancelledError,
    MP_QSTR_wait_for,
    MP_QSTR__promote_to_task,
    MP_QSTR_create_task,
    MP_QSTR_cur_task,
    MP_QSTR_value,
    MP_QSTR_args,
    MP_QSTR_TimeoutError,
    MP_QSTR_wait_for_ms,
    MP_QSTR_sleep_ms,
    MP_QSTR_gather,
    MP_QSTR_state,
    MP_QSTR_remove,
    MP_QSTR_done,
    MP_QSTR__task_queue,
    MP_QSTR_push,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR_waiter,
    MP_QSTR_aw,
    MP_QSTR_BaseException,
    MP_QSTR_timeout,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_staticmethod,
    MP_QSTR_len,
    MP_QSTR_isinstance,
    MP_QSTR_StopIteration,
    MP_QSTR_RuntimeError,
    MP_QSTR_int,
    MP_QSTR_t,
    MP_QSTR__star_,
    MP_QSTR_er,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data_asyncio_funcs[1] = {
    MP_ROM_QSTR(MP_QSTR_can_squot_t_space_gather),
};

static const mp_frozen_module_t frozen_module_asyncio_funcs = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio_funcs,
        .obj_table = (mp_obj_t *)&const_obj_table_data_asyncio_funcs,
    },
    .proto_fun = &proto_fun_asyncio_funcs__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio_lock
// - original source file: build/frozen_mpy/asyncio/lock.mpy
// - frozen file name: asyncio/lock.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/lock.py, scope asyncio_lock__lt_module_gt_
static const byte fun_data_asyncio_lock__lt_module_gt_[26] = {
    0x10,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x02, // LOAD_CONST_STRING 'core'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME ''
    0x1c,0x02, // IMPORT_FROM 'core'
    0x16,0x02, // STORE_NAME 'core'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x04, // LOAD_CONST_STRING 'Lock'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x04, // STORE_NAME 'Lock'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_lock__lt_module_gt_
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock
static const byte fun_data_asyncio_lock_Lock[37] = {
    0x00,0x02, // prelude
    0x04, // names: Lock
     // code info
    0x11,0x15, // LOAD_NAME '__name__'
    0x16,0x16, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'Lock'
    0x16,0x17, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x05, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x09, // STORE_NAME 'locked'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0a, // STORE_NAME 'release'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0f, // STORE_NAME 'acquire'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x13, // STORE_NAME '__aenter__'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x14, // STORE_NAME '__aexit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock___init__
static const byte fun_data_asyncio_lock_Lock___init__[19] = {
    0x11,0x04, // prelude
    0x05,0x18, // names: __init__, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'state'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x07, // LOAD_METHOD 'TaskQueue'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x08, // STORE_ATTR 'waiting'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_lock_Lock___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_asyncio_lock_Lock___init__ + 4,
        .line_info_top = fun_data_asyncio_lock_Lock___init__ + 4,
        .opcodes = fun_data_asyncio_lock_Lock___init__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock___init__ fun_data_asyncio_lock_Lock___init__[0]
#endif

// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock_locked
static const byte fun_data_asyncio_lock_Lock_locked[10] = {
    0x11,0x04, // prelude
    0x09,0x18, // names: locked, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'state'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xd9, // BINARY_OP 2 __eq__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock_locked = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_lock_Lock_locked,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_asyncio_lock_Lock_locked + 4,
        .line_info_top = fun_data_asyncio_lock_Lock_locked + 4,
        .opcodes = fun_data_asyncio_lock_Lock_locked + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock_locked fun_data_asyncio_lock_Lock_locked[0]
#endif

// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock_release
static const byte fun_data_asyncio_lock_Lock_release[57] = {
    0x19,0x04, // prelude
    0x0a,0x18, // names: release, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'state'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x19, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'waiting'
    0x14,0x0b, // LOAD_METHOD 'peek'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'waiting'
    0x14,0x0c, // LOAD_METHOD 'pop'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'state'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x0d, // LOAD_ATTR '_task_queue'
    0x14,0x0e, // LOAD_METHOD 'push'
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'state'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x44, // JUMP 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'state'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock_release = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_lock_Lock_release,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 57,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_asyncio_lock_Lock_release + 4,
        .line_info_top = fun_data_asyncio_lock_Lock_release + 4,
        .opcodes = fun_data_asyncio_lock_Lock_release + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock_release fun_data_asyncio_lock_Lock_release[0]
#endif

// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock_acquire
static const byte fun_data_asyncio_lock_Lock_acquire[88] = {
    0xb9,0x42,0x04, // prelude
    0x0f,0x18, // names: acquire, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'state'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x44,0xc5,0x80, // POP_JUMP_IF_FALSE 69
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'waiting'
    0x14,0x0e, // LOAD_METHOD 'push'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x10, // LOAD_ATTR 'cur_task'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'waiting'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x10, // LOAD_ATTR 'cur_task'
    0x18,0x11, // STORE_ATTR 'data'
    0x48,0x05, // SETUP_EXCEPT 5
    0x51, // LOAD_CONST_NONE
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x4a,0x29, // POP_EXCEPT_JUMP 41
    0x57, // DUP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x12, // LOAD_ATTR 'CancelledError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x60, // POP_JUMP_IF_FALSE 32
    0xc1, // STORE_FAST 1
    0x49,0x16, // SETUP_FINALLY 22
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'state'
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x10, // LOAD_ATTR 'cur_task'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'state'
    0xb0, // LOAD_FAST 0
    0x14,0x0a, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0xc1, // STORE_FAST 1
    0x28,0x01, // DELETE_FAST 1
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'state'
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock_acquire = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_lock_Lock_acquire,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 88,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_asyncio_lock_Lock_acquire + 5,
        .line_info_top = fun_data_asyncio_lock_Lock_acquire + 5,
        .opcodes = fun_data_asyncio_lock_Lock_acquire + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock_acquire fun_data_asyncio_lock_Lock_acquire[0]
#endif

// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock___aenter__
static const byte fun_data_asyncio_lock_Lock___aenter__[14] = {
    0x91,0x40,0x04, // prelude
    0x13,0x18, // names: __aenter__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0f, // LOAD_METHOD 'acquire'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock___aenter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_lock_Lock___aenter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_asyncio_lock_Lock___aenter__ + 5,
        .line_info_top = fun_data_asyncio_lock_Lock___aenter__ + 5,
        .opcodes = fun_data_asyncio_lock_Lock___aenter__ + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock___aenter__ fun_data_asyncio_lock_Lock___aenter__[0]
#endif

// child of asyncio_lock_Lock
// frozen bytecode for file asyncio/lock.py, scope asyncio_lock_Lock___aexit__
static const byte fun_data_asyncio_lock_Lock___aexit__[14] = {
    0xa8,0x44,0x0a, // prelude
    0x14,0x18,0x1a,0x1b,0x1c, // names: __aexit__, self, exc_type, exc, tb
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0a, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock___aexit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_lock_Lock___aexit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 20,
        .line_info = fun_data_asyncio_lock_Lock___aexit__ + 8,
        .line_info_top = fun_data_asyncio_lock_Lock___aexit__ + 8,
        .opcodes = fun_data_asyncio_lock_Lock___aexit__ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_lock_Lock___aexit__ fun_data_asyncio_lock_Lock___aexit__[0]
#endif

static const mp_raw_code_t *const children_asyncio_lock_Lock[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock_locked,
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock_release,
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock_acquire,
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock___aenter__,
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock___aexit__,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_lock_Lock = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_lock_Lock,
    .children = (void *)&children_asyncio_lock_Lock,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data_asyncio_lock_Lock + 3,
        .line_info_top = fun_data_asyncio_lock_Lock + 3,
        .opcodes = fun_data_asyncio_lock_Lock + 3,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_asyncio_lock__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_lock_Lock,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_lock__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_lock__lt_module_gt_,
    .children = (void *)&children_asyncio_lock__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio_lock__lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio_lock__lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio_lock__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio_lock[29] = {
    MP_QSTR_asyncio_slash_lock_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_core,
    MP_QSTR_,
    MP_QSTR_Lock,
    MP_QSTR___init__,
    MP_QSTR_state,
    MP_QSTR_TaskQueue,
    MP_QSTR_waiting,
    MP_QSTR_locked,
    MP_QSTR_release,
    MP_QSTR_peek,
    MP_QSTR_pop,
    MP_QSTR__task_queue,
    MP_QSTR_push,
    MP_QSTR_acquire,
    MP_QSTR_cur_task,
    MP_QSTR_data,
    MP_QSTR_CancelledError,
    MP_QSTR___aenter__,
    MP_QSTR___aexit__,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_RuntimeError,
    MP_QSTR_exc_type,
    MP_QSTR_exc,
    MP_QSTR_tb,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data_asyncio_lock[1] = {
    MP_ROM_QSTR(MP_QSTR_Lock_space_not_space_acquired),
};

static const mp_frozen_module_t frozen_module_asyncio_lock = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio_lock,
        .obj_table = (mp_obj_t *)&const_obj_table_data_asyncio_lock,
    },
    .proto_fun = &proto_fun_asyncio_lock__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module asyncio_stream
// - original source file: build/frozen_mpy/asyncio/stream.mpy
// - frozen file name: asyncio/stream.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file asyncio/stream.py, scope asyncio_stream__lt_module_gt_
static const byte fun_data_asyncio_stream__lt_module_gt_[90] = {
    0x10,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x02, // LOAD_CONST_STRING 'core'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME ''
    0x1c,0x02, // IMPORT_FROM 'core'
    0x16,0x02, // STORE_NAME 'core'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x04, // LOAD_CONST_STRING 'Stream'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x04, // STORE_NAME 'Stream'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x16,0x3c, // STORE_NAME 'StreamReader'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x16,0x3d, // STORE_NAME 'StreamWriter'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x0a, // STORE_NAME 'open_connection'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x05, // LOAD_CONST_STRING 'Server'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x05, // STORE_NAME 'Server'
    0x85, // LOAD_CONST_SMALL_INT 5
    0x51, // LOAD_CONST_NONE
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x1a, // STORE_NAME 'start_server'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x26, // STORE_NAME 'stream_awrite'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x13,0x06, // LOAD_ATTR 'wait_closed'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x18,0x07, // STORE_ATTR 'aclose'
    0x11,0x26, // LOAD_NAME 'stream_awrite'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x18,0x08, // STORE_ATTR 'awrite'
    0x11,0x26, // LOAD_NAME 'stream_awrite'
    0x11,0x04, // LOAD_NAME 'Stream'
    0x18,0x09, // STORE_ATTR 'awritestr'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_stream__lt_module_gt_
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream
static const byte fun_data_asyncio_stream_Stream[62] = {
    0x08,0x02, // prelude
    0x04, // names: Stream
     // code info
    0x11,0x3e, // LOAD_NAME '__name__'
    0x16,0x3f, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'Stream'
    0x16,0x40, // STORE_NAME '__qualname__'
    0x2c,0x00, // BUILD_MAP 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x29, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2d, // STORE_NAME 'get_extra_info'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2e, // STORE_NAME 'close'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x06, // STORE_NAME 'wait_closed'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x2f, // STORE_NAME 'read'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x31, // STORE_NAME 'readinto'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x32, // STORE_NAME 'readexactly'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x33, // STORE_NAME 'readline'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x27, // STORE_NAME 'write'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x28, // STORE_NAME 'drain'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream___init__
static const byte fun_data_asyncio_stream_Stream___init__[22] = {
    0xa3,0x01,0x08, // prelude
    0x29,0x46,0x2a,0x2b, // names: __init__, self, s, e
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 's'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'e'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xb0, // LOAD_FAST 0
    0x18,0x2c, // STORE_ATTR 'out_buf'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Stream___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_asyncio_stream_Stream___init__ + 7,
        .line_info_top = fun_data_asyncio_stream_Stream___init__ + 7,
        .opcodes = fun_data_asyncio_stream_Stream___init__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream___init__ fun_data_asyncio_stream_Stream___init__[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_get_extra_info
static const byte fun_data_asyncio_stream_Stream_get_extra_info[11] = {
    0x1a,0x06, // prelude
    0x2d,0x46,0x4c, // names: get_extra_info, self, v
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'e'
    0xb1, // LOAD_FAST 1
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_get_extra_info = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Stream_get_extra_info,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 11,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_asyncio_stream_Stream_get_extra_info + 5,
        .line_info_top = fun_data_asyncio_stream_Stream_get_extra_info + 5,
        .opcodes = fun_data_asyncio_stream_Stream_get_extra_info + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_get_extra_info fun_data_asyncio_stream_Stream_get_extra_info[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_close
static const byte fun_data_asyncio_stream_Stream_close[6] = {
    0x09,0x04, // prelude
    0x2e,0x46, // names: close, self
     // code info
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Stream_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_asyncio_stream_Stream_close + 4,
        .line_info_top = fun_data_asyncio_stream_Stream_close + 4,
        .opcodes = fun_data_asyncio_stream_Stream_close + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_close fun_data_asyncio_stream_Stream_close[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_wait_closed
static const byte fun_data_asyncio_stream_Stream_wait_closed[15] = {
    0x91,0x40,0x04, // prelude
    0x06,0x46, // names: wait_closed, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x2e, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_wait_closed = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_wait_closed,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_asyncio_stream_Stream_wait_closed + 5,
        .line_info_top = fun_data_asyncio_stream_Stream_wait_closed + 5,
        .opcodes = fun_data_asyncio_stream_Stream_wait_closed + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_wait_closed fun_data_asyncio_stream_Stream_wait_closed[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_read
static const byte fun_data_asyncio_stream_Stream_read[61] = {
    0xb2,0x41,0x06, // prelude
    0x2f,0x46,0x4d, // names: read, self, n
     // code info
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xc2, // STORE_FAST 2
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x30, // LOAD_METHOD 'queue_read'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x2f, // LOAD_METHOD 'read'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdb, // BINARY_OP 4 __ge__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb3, // LOAD_FAST 3
    0x63, // RETURN_VALUE
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x42,0x0e, // JUMP -50
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 61,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 47,
        .line_info = fun_data_asyncio_stream_Stream_read + 6,
        .line_info_top = fun_data_asyncio_stream_Stream_read + 6,
        .opcodes = fun_data_asyncio_stream_Stream_read + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_read fun_data_asyncio_stream_Stream_read[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_readinto
static const byte fun_data_asyncio_stream_Stream_readinto[28] = {
    0xa2,0x40,0x06, // prelude
    0x31,0x46,0x47, // names: readinto, self, buf
     // code info
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x30, // LOAD_METHOD 'queue_read'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x31, // LOAD_METHOD 'readinto'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_readinto = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_readinto,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 49,
        .line_info = fun_data_asyncio_stream_Stream_readinto + 6,
        .line_info_top = fun_data_asyncio_stream_Stream_readinto + 6,
        .opcodes = fun_data_asyncio_stream_Stream_readinto + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_readinto fun_data_asyncio_stream_Stream_readinto[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_readexactly
static const byte fun_data_asyncio_stream_Stream_readexactly[66] = {
    0xb2,0x40,0x06, // prelude
    0x32,0x46,0x4d, // names: readexactly, self, n
     // code info
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xc2, // STORE_FAST 2
    0x42,0x72, // JUMP 50
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x30, // LOAD_METHOD 'queue_read'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x2f, // LOAD_METHOD 'read'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x4e, // LOAD_GLOBAL 'EOFError'
    0x65, // RAISE_OBJ
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xe6, // BINARY_OP 15 __isub__
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x43,0x0b, // POP_JUMP_IF_TRUE -53
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_readexactly = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_readexactly,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 66,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 50,
        .line_info = fun_data_asyncio_stream_Stream_readexactly + 6,
        .line_info_top = fun_data_asyncio_stream_Stream_readexactly + 6,
        .opcodes = fun_data_asyncio_stream_Stream_readexactly + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_readexactly fun_data_asyncio_stream_Stream_readexactly[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_readline
static const byte fun_data_asyncio_stream_Stream_readline[56] = {
    0xa9,0x40,0x04, // prelude
    0x33,0x46, // names: readline, self
     // code info
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xc1, // STORE_FAST 1
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x30, // LOAD_METHOD 'queue_read'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x33, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x50, // JUMP 16
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xe5, // BINARY_OP 14 __iadd__
    0xc1, // STORE_FAST 1
    0xb2, // LOAD_FAST 2
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0xb1, // LOAD_FAST 1
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x8a, // LOAD_CONST_SMALL_INT 10
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
    0x42,0x12, // JUMP -46
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_readline = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_readline,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 56,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 51,
        .line_info = fun_data_asyncio_stream_Stream_readline + 5,
        .line_info_top = fun_data_asyncio_stream_Stream_readline + 5,
        .opcodes = fun_data_asyncio_stream_Stream_readline + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_readline fun_data_asyncio_stream_Stream_readline[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_write
static const byte fun_data_asyncio_stream_Stream_write[54] = {
    0x2a,0x06, // prelude
    0x27,0x46,0x47, // names: write, self, buf
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'out_buf'
    0x43,0x61, // POP_JUMP_IF_TRUE 33
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x27, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x2c, // LOAD_ATTR 'out_buf'
    0xb1, // LOAD_FAST 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x2c, // STORE_ATTR 'out_buf'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Stream_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 54,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data_asyncio_stream_Stream_write + 5,
        .line_info_top = fun_data_asyncio_stream_Stream_write + 5,
        .opcodes = fun_data_asyncio_stream_Stream_write + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_write fun_data_asyncio_stream_Stream_write[0]
#endif

// child of asyncio_stream_Stream
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Stream_drain
static const byte fun_data_asyncio_stream_Stream_drain[86] = {
    0xc1,0x40,0x04, // prelude
    0x28,0x46, // names: drain, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'out_buf'
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x23, // LOAD_METHOD 'sleep_ms'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
    0x12,0x4a, // LOAD_GLOBAL 'memoryview'
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'out_buf'
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0x42,0x65, // JUMP 37
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x19, // LOAD_METHOD 'queue_write'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 's'
    0x14,0x27, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x12, // POP_JUMP_IF_TRUE -46
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xb0, // LOAD_FAST 0
    0x18,0x2c, // STORE_ATTR 'out_buf'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream_drain = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Stream_drain,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 86,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 40,
        .line_info = fun_data_asyncio_stream_Stream_drain + 5,
        .line_info_top = fun_data_asyncio_stream_Stream_drain + 5,
        .opcodes = fun_data_asyncio_stream_Stream_drain + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Stream_drain fun_data_asyncio_stream_Stream_drain[0]
#endif

static const mp_raw_code_t *const children_asyncio_stream_Stream[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream___init__,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_get_extra_info,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_close,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_wait_closed,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_read,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_readinto,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_readexactly,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_readline,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_write,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream_drain,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Stream = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Stream,
    .children = (void *)&children_asyncio_stream_Stream,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 62,
    .n_children = 10,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data_asyncio_stream_Stream + 3,
        .line_info_top = fun_data_asyncio_stream_Stream + 3,
        .opcodes = fun_data_asyncio_stream_Stream + 3,
    },
    #endif
    #endif
};

// child of asyncio_stream__lt_module_gt_
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_open_connection
static const byte fun_data_asyncio_stream_open_connection[171] = {
    0x88,0xd6,0x01,0x0a, // prelude
    0x0a,0x41,0x42,0x12,0x16, // names: open_connection, host, port, ssl, server_hostname
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x0b, // LOAD_CONST_STRING 'EINPROGRESS'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x0c, // IMPORT_NAME 'errno'
    0x1c,0x0b, // IMPORT_FROM 'EINPROGRESS'
    0xc4, // STORE_FAST 4
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x0d, // IMPORT_NAME 'socket'
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x0e, // LOAD_METHOD 'getaddrinfo'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb5, // LOAD_FAST 5
    0x13,0x0f, // LOAD_ATTR 'SOCK_STREAM'
    0x36,0x04, // CALL_METHOD 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc6, // STORE_FAST 6
    0xb5, // LOAD_FAST 5
    0x14,0x0d, // LOAD_METHOD 'socket'
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xb6, // LOAD_FAST 6
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x36,0x03, // CALL_METHOD 3
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x14,0x10, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x48,0x0b, // SETUP_EXCEPT 11
    0xb7, // LOAD_FAST 7
    0x14,0x11, // LOAD_METHOD 'connect'
    0xb6, // LOAD_FAST 6
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x1b, // POP_EXCEPT_JUMP 27
    0x57, // DUP_TOP
    0x12,0x43, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xc8, // STORE_FAST 8
    0x49,0x0a, // SETUP_FINALLY 10
    0xb8, // LOAD_FAST 8
    0x13,0x0c, // LOAD_ATTR 'errno'
    0xb4, // LOAD_FAST 4
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb8, // LOAD_FAST 8
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc8, // STORE_FAST 8
    0x28,0x08, // DELETE_FAST 8
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb2, // LOAD_FAST 2
    0x44,0x6d, // POP_JUMP_IF_FALSE 45
    0xb2, // LOAD_FAST 2
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x12, // IMPORT_NAME 'ssl'
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x14,0x13, // LOAD_METHOD 'SSLContext'
    0xb9, // LOAD_FAST 9
    0x13,0x14, // LOAD_ATTR 'PROTOCOL_TLS_CLIENT'
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0xb3, // LOAD_FAST 3
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0xb0, // LOAD_FAST 0
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0x14,0x15, // LOAD_METHOD 'wrap_socket'
    0xb7, // LOAD_FAST 7
    0x10,0x16, // LOAD_CONST_STRING 'server_hostname'
    0xb3, // LOAD_FAST 3
    0x10,0x17, // LOAD_CONST_STRING 'do_handshake_on_connect'
    0x50, // LOAD_CONST_FALSE
    0x36,0x84,0x01, // CALL_METHOD 513
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x14,0x10, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x04, // LOAD_GLOBAL 'Stream'
    0xb7, // LOAD_FAST 7
    0x34,0x01, // CALL_FUNCTION 1
    0xca, // STORE_FAST 10
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x19, // LOAD_METHOD 'queue_write'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0xba, // LOAD_FAST 10
    0xba, // LOAD_FAST 10
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_open_connection = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_open_connection,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 171,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 18,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_asyncio_stream_open_connection + 9,
        .line_info_top = fun_data_asyncio_stream_open_connection + 9,
        .opcodes = fun_data_asyncio_stream_open_connection + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_open_connection fun_data_asyncio_stream_open_connection[0]
#endif

// child of asyncio_stream__lt_module_gt_
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server
static const byte fun_data_asyncio_stream_Server[33] = {
    0x00,0x02, // prelude
    0x05, // names: Server
     // code info
    0x11,0x3e, // LOAD_NAME '__name__'
    0x16,0x3f, // STORE_NAME '__module__'
    0x10,0x05, // LOAD_CONST_STRING 'Server'
    0x16,0x40, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x34, // STORE_NAME '__aenter__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x35, // STORE_NAME '__aexit__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2e, // STORE_NAME 'close'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x06, // STORE_NAME 'wait_closed'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x21, // STORE_NAME '_serve'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of asyncio_stream_Server
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server___aenter__
static const byte fun_data_asyncio_stream_Server___aenter__[7] = {
    0x89,0x40,0x04, // prelude
    0x34,0x46, // names: __aenter__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server___aenter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Server___aenter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 7,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_asyncio_stream_Server___aenter__ + 5,
        .line_info_top = fun_data_asyncio_stream_Server___aenter__ + 5,
        .opcodes = fun_data_asyncio_stream_Server___aenter__ + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Server___aenter__ fun_data_asyncio_stream_Server___aenter__[0]
#endif

// child of asyncio_stream_Server
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server___aexit__
static const byte fun_data_asyncio_stream_Server___aexit__[25] = {
    0xa8,0x44,0x0a, // prelude
    0x35,0x46,0x4f,0x50,0x51, // names: __aexit__, self, exc_type, exc, tb
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x06, // LOAD_METHOD 'wait_closed'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server___aexit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Server___aexit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 53,
        .line_info = fun_data_asyncio_stream_Server___aexit__ + 8,
        .line_info_top = fun_data_asyncio_stream_Server___aexit__ + 8,
        .opcodes = fun_data_asyncio_stream_Server___aexit__ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Server___aexit__ fun_data_asyncio_stream_Server___aexit__[0]
#endif

// child of asyncio_stream_Server
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server_close
static const byte fun_data_asyncio_stream_Server_close[18] = {
    0x11,0x04, // prelude
    0x2e,0x46, // names: close, self
     // code info
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x36, // STORE_ATTR 'state'
    0xb0, // LOAD_FAST 0
    0x13,0x22, // LOAD_ATTR 'task'
    0x14,0x25, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Server_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_asyncio_stream_Server_close + 4,
        .line_info_top = fun_data_asyncio_stream_Server_close + 4,
        .opcodes = fun_data_asyncio_stream_Server_close + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Server_close fun_data_asyncio_stream_Server_close[0]
#endif

// child of asyncio_stream_Server
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server_wait_closed
static const byte fun_data_asyncio_stream_Server_wait_closed[14] = {
    0x91,0x40,0x04, // prelude
    0x06,0x46, // names: wait_closed, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x22, // LOAD_ATTR 'task'
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server_wait_closed = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Server_wait_closed,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_asyncio_stream_Server_wait_closed + 5,
        .line_info_top = fun_data_asyncio_stream_Server_wait_closed + 5,
        .opcodes = fun_data_asyncio_stream_Server_wait_closed + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Server_wait_closed fun_data_asyncio_stream_Server_wait_closed[0]
#endif

// child of asyncio_stream_Server
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_Server__serve
static const byte fun_data_asyncio_stream_Server__serve[174] = {
    0xf8,0x46,0x0a, // prelude
    0x21,0x46,0x2a,0x44,0x12, // names: _serve, self, s, cb, ssl
     // code info
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x36, // STORE_ATTR 'state'
    0x48,0x0d, // SETUP_EXCEPT 13
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x18, // LOAD_ATTR '_io_queue'
    0x14,0x30, // LOAD_METHOD 'queue_read'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x4a,0x23, // POP_EXCEPT_JUMP 35
    0x57, // DUP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x24, // LOAD_ATTR 'CancelledError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0xc4, // STORE_FAST 4
    0x49,0x10, // SETUP_FINALLY 16
    0xb1, // LOAD_FAST 1
    0x14,0x2e, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x36, // LOAD_ATTR 'state'
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb4, // LOAD_FAST 4
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x28,0x04, // DELETE_FAST 4
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x48,0x0b, // SETUP_EXCEPT 11
    0xb1, // LOAD_FAST 1
    0x14,0x37, // LOAD_METHOD 'accept'
    0x36,0x00, // CALL_METHOD 0
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc5, // STORE_FAST 5
    0xc6, // STORE_FAST 6
    0x4a,0x06, // POP_EXCEPT_JUMP 6
    0x59, // POP_TOP
    0x40,0xda,0x80,0x01, // UNWIND_JUMP 90
    0x5d, // END_FINALLY
    0xb3, // LOAD_FAST 3
    0x44,0x76, // POP_JUMP_IF_FALSE 54
    0x48,0x10, // SETUP_EXCEPT 16
    0xb3, // LOAD_FAST 3
    0x14,0x15, // LOAD_METHOD 'wrap_socket'
    0xb5, // LOAD_FAST 5
    0x10,0x38, // LOAD_CONST_STRING 'server_side'
    0x52, // LOAD_CONST_TRUE
    0x10,0x17, // LOAD_CONST_STRING 'do_handshake_on_connect'
    0x50, // LOAD_CONST_FALSE
    0x36,0x84,0x01, // CALL_METHOD 513
    0xc5, // STORE_FAST 5
    0x4a,0x24, // POP_EXCEPT_JUMP 36
    0x57, // DUP_TOP
    0x12,0x43, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x5d, // POP_JUMP_IF_FALSE 29
    0xc7, // STORE_FAST 7
    0x49,0x13, // SETUP_FINALLY 19
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x39, // LOAD_ATTR 'sys'
    0x14,0x3a, // LOAD_METHOD 'print_exception'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x14,0x2e, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x40,0x68,0x02, // UNWIND_JUMP 40
    0x51, // LOAD_CONST_NONE
    0xc7, // STORE_FAST 7
    0x28,0x07, // DELETE_FAST 7
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb5, // LOAD_FAST 5
    0x14,0x10, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x04, // LOAD_GLOBAL 'Stream'
    0xb5, // LOAD_FAST 5
    0x2c,0x01, // BUILD_MAP 1
    0xb6, // LOAD_FAST 6
    0x10,0x3b, // LOAD_CONST_STRING 'peername'
    0x62, // STORE_MAP
    0x34,0x02, // CALL_FUNCTION 2
    0xc8, // STORE_FAST 8
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x20, // LOAD_METHOD 'create_task'
    0xb2, // LOAD_FAST 2
    0xb8, // LOAD_FAST 8
    0xb8, // LOAD_FAST 8
    0x34,0x02, // CALL_FUNCTION 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0xe0,0x7e, // JUMP -160
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server__serve = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_Server__serve,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 174,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 33,
        .line_info = fun_data_asyncio_stream_Server__serve + 8,
        .line_info_top = fun_data_asyncio_stream_Server__serve + 8,
        .opcodes = fun_data_asyncio_stream_Server__serve + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_Server__serve fun_data_asyncio_stream_Server__serve[0]
#endif

static const mp_raw_code_t *const children_asyncio_stream_Server[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server___aenter__,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server___aexit__,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server_close,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server_wait_closed,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server__serve,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_stream_Server = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream_Server,
    .children = (void *)&children_asyncio_stream_Server,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 33,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_asyncio_stream_Server + 3,
        .line_info_top = fun_data_asyncio_stream_Server + 3,
        .opcodes = fun_data_asyncio_stream_Server + 3,
    },
    #endif
    #endif
};

// child of asyncio_stream__lt_module_gt_
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_start_server
static const byte fun_data_asyncio_stream_start_server[138] = {
    0x81,0xd6,0x01,0x0c, // prelude
    0x1a,0x44,0x41,0x42,0x45,0x12, // names: start_server, cb, host, port, backlog, ssl
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x0d, // IMPORT_NAME 'socket'
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x0e, // LOAD_METHOD 'getaddrinfo'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc6, // STORE_FAST 6
    0xb5, // LOAD_FAST 5
    0x14,0x0d, // LOAD_METHOD 'socket'
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x14,0x10, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb7, // LOAD_FAST 7
    0x14,0x1b, // LOAD_METHOD 'setsockopt'
    0xb5, // LOAD_FAST 5
    0x13,0x1c, // LOAD_ATTR 'SOL_SOCKET'
    0xb5, // LOAD_FAST 5
    0x13,0x1d, // LOAD_ATTR 'SO_REUSEADDR'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x03, // CALL_METHOD 3
    0x59, // POP_TOP
    0xb7, // LOAD_FAST 7
    0x14,0x1e, // LOAD_METHOD 'bind'
    0xb6, // LOAD_FAST 6
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb7, // LOAD_FAST 7
    0x14,0x1f, // LOAD_METHOD 'listen'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x05, // LOAD_GLOBAL 'Server'
    0x34,0x00, // CALL_FUNCTION 0
    0xc8, // STORE_FAST 8
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x20, // LOAD_METHOD 'create_task'
    0xb8, // LOAD_FAST 8
    0x14,0x21, // LOAD_METHOD '_serve'
    0xb7, // LOAD_FAST 7
    0xb0, // LOAD_FAST 0
    0xb4, // LOAD_FAST 4
    0x36,0x03, // CALL_METHOD 3
    0x36,0x01, // CALL_METHOD 1
    0xb8, // LOAD_FAST 8
    0x18,0x22, // STORE_ATTR 'task'
    0x48,0x0d, // SETUP_EXCEPT 13
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x14,0x23, // LOAD_METHOD 'sleep_ms'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x4a,0x1d, // POP_EXCEPT_JUMP 29
    0x57, // DUP_TOP
    0x12,0x02, // LOAD_GLOBAL 'core'
    0x13,0x24, // LOAD_ATTR 'CancelledError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xc9, // STORE_FAST 9
    0x49,0x0a, // SETUP_FINALLY 10
    0xb8, // LOAD_FAST 8
    0x13,0x22, // LOAD_ATTR 'task'
    0x14,0x25, // LOAD_METHOD 'cancel'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb9, // LOAD_FAST 9
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0xc9, // STORE_FAST 9
    0x28,0x09, // DELETE_FAST 9
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb8, // LOAD_FAST 8
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_start_server = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_start_server,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 138,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 2,
        .scope_flags = 1,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 26,
        .line_info = fun_data_asyncio_stream_start_server + 10,
        .line_info_top = fun_data_asyncio_stream_start_server + 10,
        .opcodes = fun_data_asyncio_stream_start_server + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_start_server fun_data_asyncio_stream_start_server[0]
#endif

// child of asyncio_stream__lt_module_gt_
// frozen bytecode for file asyncio/stream.py, scope asyncio_stream_stream_awrite
static const byte fun_data_asyncio_stream_stream_awrite[63] = {
    0xb8,0xc4,0x01,0x0a, // prelude
    0x26,0x46,0x47,0x48,0x49, // names: stream_awrite, self, buf, off, sz
     // code info
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x43,0x45, // POP_JUMP_IF_TRUE 5
    0xb3, // LOAD_FAST 3
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x12,0x4a, // LOAD_GLOBAL 'memoryview'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0xb3, // LOAD_FAST 3
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x4b, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xf2, // BINARY_OP 27 __add__
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x14,0x27, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x28, // LOAD_METHOD 'drain'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_asyncio_stream_stream_awrite = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_asyncio_stream_stream_awrite,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 63,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 38,
        .line_info = fun_data_asyncio_stream_stream_awrite + 9,
        .line_info_top = fun_data_asyncio_stream_stream_awrite + 9,
        .opcodes = fun_data_asyncio_stream_stream_awrite + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_asyncio_stream_stream_awrite fun_data_asyncio_stream_stream_awrite[0]
#endif

static const mp_raw_code_t *const children_asyncio_stream__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Stream,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_open_connection,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_Server,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_start_server,
    (const mp_raw_code_t *)&proto_fun_asyncio_stream_stream_awrite,
};

static const mp_raw_code_truncated_t proto_fun_asyncio_stream__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_asyncio_stream__lt_module_gt_,
    .children = (void *)&children_asyncio_stream__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 90,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_asyncio_stream__lt_module_gt_ + 3,
        .line_info_top = fun_data_asyncio_stream__lt_module_gt_ + 3,
        .opcodes = fun_data_asyncio_stream__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_asyncio_stream[82] = {
    MP_QSTR_asyncio_slash_stream_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_core,
    MP_QSTR_,
    MP_QSTR_Stream,
    MP_QSTR_Server,
    MP_QSTR_wait_closed,
    MP_QSTR_aclose,
    MP_QSTR_awrite,
    MP_QSTR_awritestr,
    MP_QSTR_open_connection,
    MP_QSTR_EINPROGRESS,
    MP_QSTR_errno,
    MP_QSTR_socket,
    MP_QSTR_getaddrinfo,
    MP_QSTR_SOCK_STREAM,
    MP_QSTR_setblocking,
    MP_QSTR_connect,
    MP_QSTR_ssl,
    MP_QSTR_SSLContext,
    MP_QSTR_PROTOCOL_TLS_CLIENT,
    MP_QSTR_wrap_socket,
    MP_QSTR_server_hostname,
    MP_QSTR_do_handshake_on_connect,
    MP_QSTR__io_queue,
    MP_QSTR_queue_write,
    MP_QSTR_start_server,
    MP_QSTR_setsockopt,
    MP_QSTR_SOL_SOCKET,
    MP_QSTR_SO_REUSEADDR,
    MP_QSTR_bind,
    MP_QSTR_listen,
    MP_QSTR_create_task,
    MP_QSTR__serve,
    MP_QSTR_task,
    MP_QSTR_sleep_ms,
    MP_QSTR_CancelledError,
    MP_QSTR_cancel,
    MP_QSTR_stream_awrite,
    MP_QSTR_write,
    MP_QSTR_drain,
    MP_QSTR___init__,
    MP_QSTR_s,
    MP_QSTR_e,
    MP_QSTR_out_buf,
    MP_QSTR_get_extra_info,
    MP_QSTR_close,
    MP_QSTR_read,
    MP_QSTR_queue_read,
    MP_QSTR_readinto,
    MP_QSTR_readexactly,
    MP_QSTR_readline,
    MP_QSTR___aenter__,
    MP_QSTR___aexit__,
    MP_QSTR_state,
    MP_QSTR_accept,
    MP_QSTR_server_side,
    MP_QSTR_sys,
    MP_QSTR_print_exception,
    MP_QSTR_peername,
    MP_QSTR_StreamReader,
    MP_QSTR_StreamWriter,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_host,
    MP_QSTR_port,
    MP_QSTR_OSError,
    MP_QSTR_cb,
    MP_QSTR_backlog,
    MP_QSTR_self,
    MP_QSTR_buf,
    MP_QSTR_off,
    MP_QSTR_sz,
    MP_QSTR_memoryview,
    MP_QSTR_len,
    MP_QSTR_v,
    MP_QSTR_n,
    MP_QSTR_EOFError,
    MP_QSTR_exc_type,
    MP_QSTR_exc,
    MP_QSTR_tb,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data_asyncio_stream[1] = {
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
};

static const mp_frozen_module_t frozen_module_asyncio_stream = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_asyncio_stream,
        .obj_table = (mp_obj_t *)&const_obj_table_data_asyncio_stream,
    },
    .proto_fun = &proto_fun_asyncio_stream__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module neopixel
// - original source file: build/frozen_mpy/neopixel.mpy
// - frozen file name: neopixel.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file neopixel.py, scope neopixel__lt_module_gt_
static const byte fun_data_neopixel__lt_module_gt_[26] = {
    0x10,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x02, // LOAD_CONST_STRING 'bitstream'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME 'machine'
    0x1c,0x02, // IMPORT_FROM 'bitstream'
    0x16,0x02, // STORE_NAME 'bitstream'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x04, // LOAD_CONST_STRING 'NeoPixel'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x04, // STORE_NAME 'NeoPixel'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of neopixel__lt_module_gt_
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel
static const byte fun_data_neopixel_NeoPixel[46] = {
    0x08,0x02, // prelude
    0x04, // names: NeoPixel
     // code info
    0x11,0x14, // LOAD_NAME '__name__'
    0x16,0x15, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'NeoPixel'
    0x16,0x16, // STORE_NAME '__qualname__'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x16,0x0f, // STORE_NAME 'ORDER'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x05, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0d, // STORE_NAME '__len__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0e, // STORE_NAME '__setitem__'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x10, // STORE_NAME '__getitem__'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x11, // STORE_NAME 'fill'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x12, // STORE_NAME 'write'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel___init__
static const byte fun_data_neopixel_NeoPixel___init__[72] = {
    0xb9,0x84,0x01,0x0c, // prelude
    0x05,0x17,0x06,0x07,0x08,0x0c, // names: __init__, self, pin, n, bpp, timing
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR 'pin'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x07, // STORE_ATTR 'n'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x08, // STORE_ATTR 'bpp'
    0x12,0x18, // LOAD_GLOBAL 'bytearray'
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR 'buf'
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'pin'
    0x14,0x0a, // LOAD_METHOD 'init'
    0xb1, // LOAD_FAST 1
    0x13,0x0b, // LOAD_ATTR 'OUT'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x19, // LOAD_GLOBAL 'isinstance'
    0xb4, // LOAD_FAST 4
    0x12,0x1a, // LOAD_GLOBAL 'int'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0xb4, // LOAD_FAST 4
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x42,0x42, // JUMP 2
    0x23,0x02, // LOAD_CONST_OBJ 2
    0xb0, // LOAD_FAST 0
    0x18,0x0c, // STORE_ATTR 'timing'
    0x42,0x44, // JUMP 4
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0c, // STORE_ATTR 'timing'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 72,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_neopixel_NeoPixel___init__ + 10,
        .line_info_top = fun_data_neopixel_NeoPixel___init__ + 10,
        .opcodes = fun_data_neopixel_NeoPixel___init__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel___init__ fun_data_neopixel_NeoPixel___init__[0]
#endif

// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel___len__
static const byte fun_data_neopixel_NeoPixel___len__[8] = {
    0x09,0x04, // prelude
    0x0d,0x17, // names: __len__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x07, // LOAD_ATTR 'n'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel___len__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel___len__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 8,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_neopixel_NeoPixel___len__ + 4,
        .line_info_top = fun_data_neopixel_NeoPixel___len__ + 4,
        .opcodes = fun_data_neopixel_NeoPixel___len__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel___len__ fun_data_neopixel_NeoPixel___len__[0]
#endif

// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel___setitem__
static const byte fun_data_neopixel_NeoPixel___setitem__[45] = {
    0x5b,0x08, // prelude
    0x0e,0x17,0x1b,0x1c, // names: __setitem__, self, i, v
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0xf4, // BINARY_OP 29 __mul__
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x52, // JUMP 18
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'buf'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR 'ORDER'
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x56, // STORE_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x29, // POP_JUMP_IF_TRUE -23
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel___setitem__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel___setitem__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 45,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_neopixel_NeoPixel___setitem__ + 6,
        .line_info_top = fun_data_neopixel_NeoPixel___setitem__ + 6,
        .opcodes = fun_data_neopixel_NeoPixel___setitem__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel___setitem__ fun_data_neopixel_NeoPixel___setitem__[0]
#endif

// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel___getitem__
static const byte fun_data_neopixel_NeoPixel___getitem__[37] = {
    0x32,0x86,0x01, // prelude
    0x10,0x17,0x1b, // names: __getitem__, self, i
    0x00,0x02, // code info
    0xb1, // LOAD_FAST 1
    0x25,0x00, // LOAD_DEREF 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0xf4, // BINARY_OP 29 __mul__
    0x27,0x02, // STORE_DEREF 2
    0x12,0x1d, // LOAD_GLOBAL 'tuple'
    0xb0, // LOAD_FAST 0
    0xb2, // LOAD_FAST 2
    0x20,0x00,0x02, // MAKE_CLOSURE 0
    0x12,0x1e, // LOAD_GLOBAL 'range'
    0x25,0x00, // LOAD_DEREF 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
// child of neopixel_NeoPixel___getitem__
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel___getitem____lt_genexpr_gt_
static const byte fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_[34] = {
    0xdb,0x40,0x08, // prelude
    0x13,0x20,0x20,0x20, // names: <genexpr>, *, *, *
     // code info
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x13, // FOR_ITER 19
    0xc3, // STORE_FAST 3
    0x25,0x00, // LOAD_DEREF 0
    0x13,0x09, // LOAD_ATTR 'buf'
    0x25,0x01, // LOAD_DEREF 1
    0x25,0x00, // LOAD_DEREF 0
    0x13,0x0f, // LOAD_ATTR 'ORDER'
    0xb3, // LOAD_FAST 3
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x55, // LOAD_SUBSCR
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2b, // JUMP -21
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel___getitem____lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_ + 7,
        .line_info_top = fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_ + 7,
        .opcodes = fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel___getitem____lt_genexpr_gt_ fun_data_neopixel_NeoPixel___getitem____lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_neopixel_NeoPixel___getitem__[] = {
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel___getitem____lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel___getitem__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel___getitem__,
    .children = (void *)&children_neopixel_NeoPixel___getitem__,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 16,
        .line_info = fun_data_neopixel_NeoPixel___getitem__ + 6,
        .line_info_top = fun_data_neopixel_NeoPixel___getitem__ + 6,
        .opcodes = fun_data_neopixel_NeoPixel___getitem__ + 8,
    },
    #endif
    #endif
};

// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel_fill
static const byte fun_data_neopixel_NeoPixel_fill[61] = {
    0x7a,0x06, // prelude
    0x11,0x17,0x1c, // names: fill, self, v
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'buf'
    0xc2, // STORE_FAST 2
    0x12,0x1f, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x5f, // JUMP 31
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xb1, // LOAD_FAST 1
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xc5, // STORE_FAST 5
    0x12,0x1e, // LOAD_GLOBAL 'range'
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR 'ORDER'
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'bpp'
    0x34,0x03, // CALL_FUNCTION 3
    0x5f, // GET_ITER_STACK
    0x4b,0x07, // FOR_ITER 7
    0xc6, // STORE_FAST 6
    0xb5, // LOAD_FAST 5
    0xb2, // LOAD_FAST 2
    0xb6, // LOAD_FAST 6
    0x56, // STORE_SUBSCR
    0x42,0x37, // JUMP -9
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x1c, // POP_JUMP_IF_TRUE -36
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel_fill = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel_fill,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 61,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 17,
        .line_info = fun_data_neopixel_NeoPixel_fill + 5,
        .line_info_top = fun_data_neopixel_NeoPixel_fill + 5,
        .opcodes = fun_data_neopixel_NeoPixel_fill + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel_fill fun_data_neopixel_NeoPixel_fill[0]
#endif

// child of neopixel_NeoPixel
// frozen bytecode for file neopixel.py, scope neopixel_NeoPixel_write
static const byte fun_data_neopixel_NeoPixel_write[21] = {
    0x29,0x04, // prelude
    0x12,0x17, // names: write, self
     // code info
    0x12,0x02, // LOAD_GLOBAL 'bitstream'
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR 'pin'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x13,0x0c, // LOAD_ATTR 'timing'
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR 'buf'
    0x34,0x04, // CALL_FUNCTION 4
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 21,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_neopixel_NeoPixel_write + 4,
        .line_info_top = fun_data_neopixel_NeoPixel_write + 4,
        .opcodes = fun_data_neopixel_NeoPixel_write + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_neopixel_NeoPixel_write fun_data_neopixel_NeoPixel_write[0]
#endif

static const mp_raw_code_t *const children_neopixel_NeoPixel[] = {
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel___init__,
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel___len__,
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel___setitem__,
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel___getitem__,
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel_fill,
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel_write,
};

static const mp_raw_code_truncated_t proto_fun_neopixel_NeoPixel = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel_NeoPixel,
    .children = (void *)&children_neopixel_NeoPixel,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data_neopixel_NeoPixel + 3,
        .line_info_top = fun_data_neopixel_NeoPixel + 3,
        .opcodes = fun_data_neopixel_NeoPixel + 3,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_neopixel__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_neopixel_NeoPixel,
};

static const mp_raw_code_truncated_t proto_fun_neopixel__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_neopixel__lt_module_gt_,
    .children = (void *)&children_neopixel__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_neopixel__lt_module_gt_ + 3,
        .line_info_top = fun_data_neopixel__lt_module_gt_ + 3,
        .opcodes = fun_data_neopixel__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_neopixel[33] = {
    MP_QSTR_neopixel_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_bitstream,
    MP_QSTR_machine,
    MP_QSTR_NeoPixel,
    MP_QSTR___init__,
    MP_QSTR_pin,
    MP_QSTR_n,
    MP_QSTR_bpp,
    MP_QSTR_buf,
    MP_QSTR_init,
    MP_QSTR_OUT,
    MP_QSTR_timing,
    MP_QSTR___len__,
    MP_QSTR___setitem__,
    MP_QSTR_ORDER,
    MP_QSTR___getitem__,
    MP_QSTR_fill,
    MP_QSTR_write,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_bytearray,
    MP_QSTR_isinstance,
    MP_QSTR_int,
    MP_QSTR_i,
    MP_QSTR_v,
    MP_QSTR_tuple,
    MP_QSTR_range,
    MP_QSTR_len,
    MP_QSTR__star_,
};

// constants
static const mp_rom_obj_tuple_t const_obj_neopixel_0 = {{&mp_type_tuple}, 4, {
    MP_ROM_INT(1),
    MP_ROM_INT(0),
    MP_ROM_INT(2),
    MP_ROM_INT(3),
}};
static const mp_rom_obj_tuple_t const_obj_neopixel_1 = {{&mp_type_tuple}, 4, {
    MP_ROM_INT(400),
    MP_ROM_INT(850),
    MP_ROM_INT(800),
    MP_ROM_INT(450),
}};
static const mp_rom_obj_tuple_t const_obj_neopixel_2 = {{&mp_type_tuple}, 4, {
    MP_ROM_INT(800),
    MP_ROM_INT(1700),
    MP_ROM_INT(1600),
    MP_ROM_INT(900),
}};

// constant table
static const mp_rom_obj_t const_obj_table_data_neopixel[3] = {
    MP_ROM_PTR(&const_obj_neopixel_0),
    MP_ROM_PTR(&const_obj_neopixel_1),
    MP_ROM_PTR(&const_obj_neopixel_2),
};

static const mp_frozen_module_t frozen_module_neopixel = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_neopixel,
        .obj_table = (mp_obj_t *)&const_obj_table_data_neopixel,
    },
    .proto_fun = &proto_fun_neopixel__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module requests___init__
// - original source file: build/frozen_mpy/requests/__init__.mpy
// - frozen file name: requests/__init__.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file requests/__init__.py, scope requests___init____lt_module_gt_
static const byte fun_data_requests___init____lt_module_gt_[68] = {
    0x38,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'socket'
    0x16,0x02, // STORE_NAME 'socket'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x03, // LOAD_CONST_STRING 'BodyStream'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x03, // STORE_NAME 'BodyStream'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x04, // LOAD_CONST_STRING 'Response'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x04, // STORE_NAME 'Response'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x52, // LOAD_CONST_TRUE
    0x52, // LOAD_CONST_TRUE
    0x2a,0x08, // BUILD_TUPLE 8
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x05, // STORE_NAME 'request'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x36, // STORE_NAME 'head'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x29, // STORE_NAME 'get'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x38, // STORE_NAME 'post'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x3a, // STORE_NAME 'put'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x3c, // STORE_NAME 'patch'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x3e, // STORE_NAME 'delete'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___BodyStream
static const byte fun_data_requests___init___BodyStream[33] = {
    0x08,0x02, // prelude
    0x03, // names: BodyStream
     // code info
    0x11,0x4e, // LOAD_NAME '__name__'
    0x16,0x4f, // STORE_NAME '__module__'
    0x10,0x03, // LOAD_CONST_STRING 'BodyStream'
    0x16,0x50, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x40, // STORE_NAME '__init__'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x44, // STORE_NAME 'read'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x45, // STORE_NAME 'readinto'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x28, // STORE_NAME 'close'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of requests___init___BodyStream
// frozen bytecode for file requests/__init__.py, scope requests___init___BodyStream___init__
static const byte fun_data_requests___init___BodyStream___init__[22] = {
    0x23,0x08, // prelude
    0x40,0x63,0x64,0x65, // names: __init__, self, sock, remaining
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x41, // STORE_ATTR '_sock'
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd7, // BINARY_OP 0 __lt__
    0xb0, // LOAD_FAST 0
    0x18,0x42, // STORE_ATTR '_chunk'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x43, // STORE_ATTR '_remaining'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___BodyStream___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___BodyStream___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_requests___init___BodyStream___init__ + 6,
        .line_info_top = fun_data_requests___init___BodyStream___init__ + 6,
        .opcodes = fun_data_requests___init___BodyStream___init__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___BodyStream___init__ fun_data_requests___init___BodyStream___init__[0]
#endif

// child of requests___init___BodyStream
// frozen bytecode for file requests/__init__.py, scope requests___init___BodyStream_read
static const byte fun_data_requests___init___BodyStream_read[75] = {
    0xc2,0x01,0x06, // prelude
    0x44,0x63,0x66, // names: read, self, n
     // code info
    0x12,0x67, // LOAD_GLOBAL 'bytearray'
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdb, // BINARY_OP 4 __ge__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb1, // LOAD_FAST 1
    0x42,0x43, // JUMP 3
    0x22,0x82,0x00, // LOAD_CONST_SMALL_INT 256
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdb, // BINARY_OP 4 __ge__
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb0, // LOAD_FAST 0
    0x14,0x45, // LOAD_METHOD 'readinto'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xb3, // LOAD_FAST 3
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
    0x23,0x11, // LOAD_CONST_OBJ 17
    0x63, // RETURN_VALUE
    0x23,0x11, // LOAD_CONST_OBJ 17
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x45, // LOAD_METHOD 'readinto'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0xb4, // LOAD_FAST 4
    0x63, // RETURN_VALUE
    0xb4, // LOAD_FAST 4
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xb3, // LOAD_FAST 3
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0x42,0x29, // JUMP -23
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___BodyStream_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___BodyStream_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 75,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 68,
        .line_info = fun_data_requests___init___BodyStream_read + 6,
        .line_info_top = fun_data_requests___init___BodyStream_read + 6,
        .opcodes = fun_data_requests___init___BodyStream_read + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___BodyStream_read fun_data_requests___init___BodyStream_read[0]
#endif

// child of requests___init___BodyStream
// frozen bytecode for file requests/__init__.py, scope requests___init___BodyStream_readinto
static const byte fun_data_requests___init___BodyStream_readinto[146] = {
    0x42,0x06, // prelude
    0x45,0x63,0x68, // names: readinto, self, buf
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x41, // LOAD_ATTR '_sock'
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xda, // BINARY_OP 3 __le__
    0x44,0x78, // POP_JUMP_IF_FALSE 56
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x12,0x5d, // LOAD_GLOBAL 'int'
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x14,0x0e, // LOAD_METHOD 'split'
    0x23,0x12, // LOAD_CONST_OBJ 18
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x90, // LOAD_CONST_SMALL_INT 16
    0x34,0x02, // CALL_FUNCTION 2
    0xb0, // LOAD_FAST 0
    0x18,0x43, // STORE_ATTR '_remaining'
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb3, // LOAD_FAST 3
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x42,0x2d, // JUMP -19
    0x12,0x60, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x12,0x69, // LOAD_GLOBAL 'memoryview'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc1, // STORE_FAST 1
    0xb2, // LOAD_FAST 2
    0x14,0x45, // LOAD_METHOD 'readinto'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x5c, // LOAD_GLOBAL 'ValueError'
    0x23,0x13, // LOAD_CONST_OBJ 19
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x43, // LOAD_ATTR '_remaining'
    0xb4, // LOAD_FAST 4
    0xe6, // BINARY_OP 15 __isub__
    0x5a, // ROT_TWO
    0x18,0x43, // STORE_ATTR '_remaining'
    0xb0, // LOAD_FAST 0
    0x13,0x43, // LOAD_ATTR '_remaining'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb0, // LOAD_FAST 0
    0x13,0x42, // LOAD_ATTR '_chunk'
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xb0, // LOAD_FAST 0
    0x18,0x43, // STORE_ATTR '_remaining'
    0xb4, // LOAD_FAST 4
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___BodyStream_readinto = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___BodyStream_readinto,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 146,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 69,
        .line_info = fun_data_requests___init___BodyStream_readinto + 5,
        .line_info_top = fun_data_requests___init___BodyStream_readinto + 5,
        .opcodes = fun_data_requests___init___BodyStream_readinto + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___BodyStream_readinto fun_data_requests___init___BodyStream_readinto[0]
#endif

// child of requests___init___BodyStream
// frozen bytecode for file requests/__init__.py, scope requests___init___BodyStream_close
static const byte fun_data_requests___init___BodyStream_close[14] = {
    0x11,0x04, // prelude
    0x28,0x63, // names: close, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x41, // LOAD_ATTR '_sock'
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___BodyStream_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___BodyStream_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 40,
        .line_info = fun_data_requests___init___BodyStream_close + 4,
        .line_info_top = fun_data_requests___init___BodyStream_close + 4,
        .opcodes = fun_data_requests___init___BodyStream_close + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___BodyStream_close fun_data_requests___init___BodyStream_close[0]
#endif

static const mp_raw_code_t *const children_requests___init___BodyStream[] = {
    (const mp_raw_code_t *)&proto_fun_requests___init___BodyStream___init__,
    (const mp_raw_code_t *)&proto_fun_requests___init___BodyStream_read,
    (const mp_raw_code_t *)&proto_fun_requests___init___BodyStream_readinto,
    (const mp_raw_code_t *)&proto_fun_requests___init___BodyStream_close,
};

static const mp_raw_code_truncated_t proto_fun_requests___init___BodyStream = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___BodyStream,
    .children = (void *)&children_requests___init___BodyStream,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 33,
    .n_children = 4,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 3,
        .line_info = fun_data_requests___init___BodyStream + 3,
        .line_info_top = fun_data_requests___init___BodyStream + 3,
        .opcodes = fun_data_requests___init___BodyStream + 3,
    },
    #endif
    #endif
};

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___Response
static const byte fun_data_requests___init___Response[49] = {
    0x08,0x02, // prelude
    0x04, // names: Response
     // code info
    0x11,0x4e, // LOAD_NAME '__name__'
    0x16,0x4f, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'Response'
    0x16,0x50, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x40, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x28, // STORE_NAME 'close'
    0x11,0x51, // LOAD_NAME 'property'
    0x32,0x02, // MAKE_FUNCTION 2
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x49, // STORE_NAME 'content'
    0x11,0x51, // LOAD_NAME 'property'
    0x32,0x03, // MAKE_FUNCTION 3
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x4a, // STORE_NAME 'text'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x24, // STORE_NAME 'json'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x4c, // STORE_NAME '__enter__'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x4d, // STORE_NAME '__exit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response___init__
static const byte fun_data_requests___init___Response___init__[20] = {
    0x1a,0x06, // prelude
    0x40,0x63,0x6a, // names: __init__, self, f
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x46, // STORE_ATTR 'raw'
    0x10,0x26, // LOAD_CONST_STRING 'utf-8'
    0xb0, // LOAD_FAST 0
    0x18,0x47, // STORE_ATTR 'encoding'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x48, // STORE_ATTR '_cached'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_requests___init___Response___init__ + 5,
        .line_info_top = fun_data_requests___init___Response___init__ + 5,
        .opcodes = fun_data_requests___init___Response___init__ + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response___init__ fun_data_requests___init___Response___init__[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response_close
static const byte fun_data_requests___init___Response_close[27] = {
    0x11,0x04, // prelude
    0x28,0x63, // names: close, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x46, // LOAD_ATTR 'raw'
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb0, // LOAD_FAST 0
    0x13,0x46, // LOAD_ATTR 'raw'
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x46, // STORE_ATTR 'raw'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x48, // STORE_ATTR '_cached'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 27,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 40,
        .line_info = fun_data_requests___init___Response_close + 4,
        .line_info_top = fun_data_requests___init___Response_close + 4,
        .opcodes = fun_data_requests___init___Response_close + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response_close fun_data_requests___init___Response_close[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response_content
static const byte fun_data_requests___init___Response_content[41] = {
    0x2d,0x04, // prelude
    0x49,0x63, // names: content, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x48, // LOAD_ATTR '_cached'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x49,0x0b, // SETUP_FINALLY 11
    0xb0, // LOAD_FAST 0
    0x13,0x46, // LOAD_ATTR 'raw'
    0x14,0x44, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x48, // STORE_ATTR '_cached'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x13,0x46, // LOAD_ATTR 'raw'
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x46, // STORE_ATTR 'raw'
    0x5d, // END_FINALLY
    0xb0, // LOAD_FAST 0
    0x13,0x48, // LOAD_ATTR '_cached'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response_content = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response_content,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 41,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 73,
        .line_info = fun_data_requests___init___Response_content + 4,
        .line_info_top = fun_data_requests___init___Response_content + 4,
        .opcodes = fun_data_requests___init___Response_content + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response_content fun_data_requests___init___Response_content[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response_text
static const byte fun_data_requests___init___Response_text[15] = {
    0x19,0x04, // prelude
    0x4a,0x63, // names: text, self
     // code info
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0xb0, // LOAD_FAST 0
    0x13,0x49, // LOAD_ATTR 'content'
    0xb0, // LOAD_FAST 0
    0x13,0x47, // LOAD_ATTR 'encoding'
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response_text = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response_text,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 74,
        .line_info = fun_data_requests___init___Response_text + 4,
        .line_info_top = fun_data_requests___init___Response_text + 4,
        .opcodes = fun_data_requests___init___Response_text + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response_text fun_data_requests___init___Response_text[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response_json
static const byte fun_data_requests___init___Response_json[18] = {
    0x21,0x04, // prelude
    0x24,0x63, // names: json, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x24, // IMPORT_NAME 'json'
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x4b, // LOAD_METHOD 'loads'
    0xb0, // LOAD_FAST 0
    0x13,0x49, // LOAD_ATTR 'content'
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response_json,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 36,
        .line_info = fun_data_requests___init___Response_json + 4,
        .line_info_top = fun_data_requests___init___Response_json + 4,
        .opcodes = fun_data_requests___init___Response_json + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response_json fun_data_requests___init___Response_json[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response___enter__
static const byte fun_data_requests___init___Response___enter__[6] = {
    0x09,0x04, // prelude
    0x4c,0x63, // names: __enter__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response___enter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response___enter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 76,
        .line_info = fun_data_requests___init___Response___enter__ + 4,
        .line_info_top = fun_data_requests___init___Response___enter__ + 4,
        .opcodes = fun_data_requests___init___Response___enter__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response___enter__ fun_data_requests___init___Response___enter__[0]
#endif

// child of requests___init___Response
// frozen bytecode for file requests/__init__.py, scope requests___init___Response___exit__
static const byte fun_data_requests___init___Response___exit__[16] = {
    0xa8,0x04,0x0a, // prelude
    0x4d,0x63,0x6b,0x6c,0x6d, // names: __exit__, self, exc_type, exc_val, exc_tb
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___Response___exit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response___exit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 77,
        .line_info = fun_data_requests___init___Response___exit__ + 8,
        .line_info_top = fun_data_requests___init___Response___exit__ + 8,
        .opcodes = fun_data_requests___init___Response___exit__ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___Response___exit__ fun_data_requests___init___Response___exit__[0]
#endif

static const mp_raw_code_t *const children_requests___init___Response[] = {
    (const mp_raw_code_t *)&proto_fun_requests___init___Response___init__,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response_close,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response_content,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response_text,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response_json,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response___enter__,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response___exit__,
};

static const mp_raw_code_truncated_t proto_fun_requests___init___Response = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___Response,
    .children = (void *)&children_requests___init___Response,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 49,
    .n_children = 7,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data_requests___init___Response + 3,
        .line_info_top = fun_data_requests___init___Response + 3,
        .opcodes = fun_data_requests___init___Response + 3,
    },
    #endif
    #endif
};

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___request
static const byte fun_data_requests___init___request[1216] = {
    0xf6,0xa0,0x84,0x80,0x01,0x16, // prelude
    0x05,0x52,0x53,0x54,0x24,0x35,0x55,0x56,0x57,0x58,0x59, // names: request, method, url, data, json, headers, stream, auth, timeout, parse_headers, verify
     // code info
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x2c,0x00, // BUILD_MAP 0
    0xc4, // STORE_FAST 4
    0x42,0x46, // JUMP 6
    0xb4, // LOAD_FAST 4
    0x14,0x06, // LOAD_METHOD 'copy'
    0x36,0x00, // CALL_METHOD 0
    0xc4, // STORE_FAST 4
    0x51, // LOAD_CONST_NONE
    0xca, // STORE_FAST 10
    0xb2, // LOAD_FAST 2
    0x46,0x13, // JUMP_IF_FALSE_OR_POP 19
    0x12,0x5a, // LOAD_GLOBAL 'getattr'
    0xb2, // LOAD_FAST 2
    0x10,0x07, // LOAD_CONST_STRING '__next__'
    0x51, // LOAD_CONST_NONE
    0x34,0x03, // CALL_FUNCTION 3
    0x46,0x09, // JUMP_IF_FALSE_OR_POP 9
    0x12,0x5a, // LOAD_GLOBAL 'getattr'
    0xb2, // LOAD_FAST 2
    0x10,0x08, // LOAD_CONST_STRING '__len__'
    0x51, // LOAD_CONST_NONE
    0x34,0x03, // CALL_FUNCTION 3
    0xd3, // UNARY_OP 3 <not>
    0xcb, // STORE_FAST 11
    0xb6, // LOAD_FAST 6
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x70, // POP_JUMP_IF_FALSE 48
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x09, // IMPORT_NAME 'binascii'
    0xcc, // STORE_FAST 12
    0xb6, // LOAD_FAST 6
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xcd, // STORE_FAST 13
    0xce, // STORE_FAST 14
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x14,0x0a, // LOAD_METHOD 'format'
    0xbd, // LOAD_FAST 13
    0xbe, // LOAD_FAST 14
    0x36,0x02, // CALL_METHOD 2
    0xcf, // STORE_FAST 15
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0xbc, // LOAD_FAST 12
    0x14,0x0b, // LOAD_METHOD 'b2a_base64'
    0xbf, // LOAD_FAST 15
    0x36,0x01, // CALL_METHOD 1
    0x51, // LOAD_CONST_NONE
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x10,0x0c, // LOAD_CONST_STRING 'ascii'
    0x34,0x02, // CALL_FUNCTION 2
    0xcf, // STORE_FAST 15
    0x10,0x0d, // LOAD_CONST_STRING 'Basic {}'
    0x14,0x0a, // LOAD_METHOD 'format'
    0xbf, // LOAD_FAST 15
    0x36,0x01, // CALL_METHOD 1
    0xb4, // LOAD_FAST 4
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x56, // STORE_SUBSCR
    0x48,0x14, // SETUP_EXCEPT 20
    0xb1, // LOAD_FAST 1
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x0f, // LOAD_CONST_STRING '/'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x36,0x02, // CALL_METHOD 2
    0x30,0x04, // UNPACK_SEQUENCE 4
    0x26,0x10, // STORE_FAST_N 16
    0x26,0x11, // STORE_FAST_N 17
    0x26,0x12, // STORE_FAST_N 18
    0x26,0x13, // STORE_FAST_N 19
    0x4a,0x1e, // POP_EXCEPT_JUMP 30
    0x57, // DUP_TOP
    0x12,0x5c, // LOAD_GLOBAL 'ValueError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x0f, // LOAD_CONST_STRING '/'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0x30,0x03, // UNPACK_SEQUENCE 3
    0x26,0x10, // STORE_FAST_N 16
    0x26,0x11, // STORE_FAST_N 17
    0x26,0x12, // STORE_FAST_N 18
    0x10,0x10, // LOAD_CONST_STRING ''
    0x26,0x13, // STORE_FAST_N 19
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x24,0x10, // LOAD_FAST_N 16
    0x10,0x11, // LOAD_CONST_STRING 'http:'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x22,0x80,0x50, // LOAD_CONST_SMALL_INT 80
    0x26,0x14, // STORE_FAST_N 20
    0x42,0x5e, // JUMP 30
    0x24,0x10, // LOAD_FAST_N 16
    0x10,0x12, // LOAD_CONST_STRING 'https:'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x13, // IMPORT_NAME 'tls'
    0x26,0x15, // STORE_FAST_N 21
    0x22,0x83,0x3b, // LOAD_CONST_SMALL_INT 443
    0x26,0x14, // STORE_FAST_N 20
    0x42,0x4a, // JUMP 10
    0x12,0x5c, // LOAD_GLOBAL 'ValueError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x24,0x10, // LOAD_FAST_N 16
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x10,0x14, // LOAD_CONST_STRING '?'
    0x24,0x12, // LOAD_FAST_N 18
    0xdd, // BINARY_OP 6 <in>
    0x44,0x59, // POP_JUMP_IF_FALSE 25
    0x24,0x12, // LOAD_FAST_N 18
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x14, // LOAD_CONST_STRING '?'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0x26,0x12, // STORE_FAST_N 18
    0x26,0x16, // STORE_FAST_N 22
    0x10,0x14, // LOAD_CONST_STRING '?'
    0x24,0x16, // LOAD_FAST_N 22
    0xf2, // BINARY_OP 27 __add__
    0x24,0x13, // LOAD_FAST_N 19
    0xf2, // BINARY_OP 27 __add__
    0x26,0x13, // STORE_FAST_N 19
    0x10,0x15, // LOAD_CONST_STRING '#'
    0x24,0x12, // LOAD_FAST_N 18
    0xdd, // BINARY_OP 6 <in>
    0x44,0x59, // POP_JUMP_IF_FALSE 25
    0x24,0x12, // LOAD_FAST_N 18
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x15, // LOAD_CONST_STRING '#'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0x26,0x12, // STORE_FAST_N 18
    0x26,0x16, // STORE_FAST_N 22
    0x10,0x15, // LOAD_CONST_STRING '#'
    0x24,0x16, // LOAD_FAST_N 22
    0xf2, // BINARY_OP 27 __add__
    0x24,0x13, // LOAD_FAST_N 19
    0xf2, // BINARY_OP 27 __add__
    0x26,0x13, // STORE_FAST_N 19
    0x10,0x16, // LOAD_CONST_STRING ':'
    0x24,0x12, // LOAD_FAST_N 18
    0xdd, // BINARY_OP 6 <in>
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0x24,0x12, // LOAD_FAST_N 18
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x16, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0x26,0x12, // STORE_FAST_N 18
    0x26,0x14, // STORE_FAST_N 20
    0x12,0x5d, // LOAD_GLOBAL 'int'
    0x24,0x14, // LOAD_FAST_N 20
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x14, // STORE_FAST_N 20
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x14,0x17, // LOAD_METHOD 'getaddrinfo'
    0x24,0x12, // LOAD_FAST_N 18
    0x24,0x14, // LOAD_FAST_N 20
    0x80, // LOAD_CONST_SMALL_INT 0
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x13,0x18, // LOAD_ATTR 'SOCK_STREAM'
    0x36,0x04, // CALL_METHOD 4
    0x26,0x17, // STORE_FAST_N 23
    0x24,0x17, // LOAD_FAST_N 23
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x26,0x17, // STORE_FAST_N 23
    0x51, // LOAD_CONST_NONE
    0x26,0x18, // STORE_FAST_N 24
    0xb8, // LOAD_FAST 8
    0x50, // LOAD_CONST_FALSE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x2c,0x00, // BUILD_MAP 0
    0x26,0x18, // STORE_FAST_N 24
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x14,0x02, // LOAD_METHOD 'socket'
    0x24,0x17, // LOAD_FAST_N 23
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x13,0x18, // LOAD_ATTR 'SOCK_STREAM'
    0x24,0x17, // LOAD_FAST_N 23
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x36,0x03, // CALL_METHOD 3
    0x26,0x19, // STORE_FAST_N 25
    0xb7, // LOAD_FAST 7
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x19, // LOAD_METHOD 'settimeout'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x48,0xac,0x05, // SETUP_EXCEPT 684
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x1a, // LOAD_METHOD 'connect'
    0x24,0x17, // LOAD_FAST_N 23
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x10, // LOAD_FAST_N 16
    0x10,0x12, // LOAD_CONST_STRING 'https:'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x66, // POP_JUMP_IF_FALSE 38
    0x24,0x15, // LOAD_FAST_N 21
    0x14,0x1b, // LOAD_METHOD 'SSLContext'
    0x24,0x15, // LOAD_FAST_N 21
    0x13,0x1c, // LOAD_ATTR 'PROTOCOL_TLS_CLIENT'
    0x36,0x01, // CALL_METHOD 1
    0x26,0x1a, // STORE_FAST_N 26
    0xb9, // LOAD_FAST 9
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0x24,0x15, // LOAD_FAST_N 21
    0x13,0x1d, // LOAD_ATTR 'CERT_NONE'
    0x24,0x1a, // LOAD_FAST_N 26
    0x18,0x1e, // STORE_ATTR 'verify_mode'
    0x24,0x1a, // LOAD_FAST_N 26
    0x14,0x1f, // LOAD_METHOD 'wrap_socket'
    0x24,0x19, // LOAD_FAST_N 25
    0x10,0x20, // LOAD_CONST_STRING 'server_hostname'
    0x24,0x12, // LOAD_FAST_N 18
    0x36,0x82,0x01, // CALL_METHOD 257
    0x26,0x19, // STORE_FAST_N 25
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0xb0, // LOAD_FAST 0
    0x24,0x13, // LOAD_FAST_N 19
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x10,0x22, // LOAD_CONST_STRING 'Host'
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x24,0x12, // LOAD_FAST_N 18
    0xb4, // LOAD_FAST 4
    0x10,0x22, // LOAD_CONST_STRING 'Host'
    0x56, // STORE_SUBSCR
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x5f, // POP_JUMP_IF_FALSE 31
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x23, // LOAD_CONST_STRING 'dumps'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x24, // IMPORT_NAME 'json'
    0x1c,0x23, // IMPORT_FROM 'dumps'
    0x26,0x1b, // STORE_FAST_N 27
    0x59, // POP_TOP
    0x24,0x1b, // LOAD_FAST_N 27
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x23,0x05, // LOAD_CONST_OBJ 5
    0xb4, // LOAD_FAST 4
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x56, // STORE_SUBSCR
    0xb2, // LOAD_FAST 2
    0x44,0x7e, // POP_JUMP_IF_FALSE 62
    0xbb, // LOAD_FAST 11
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x23,0x07, // LOAD_CONST_OBJ 7
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x10,0x25, // LOAD_CONST_STRING 'chunked'
    0xb4, // LOAD_FAST 4
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x56, // STORE_SUBSCR
    0x42,0x65, // JUMP 37
    0x12,0x5e, // LOAD_GLOBAL 'isinstance'
    0xb2, // LOAD_FAST 2
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x5f, // LOAD_GLOBAL 'bytes'
    0xb2, // LOAD_FAST 2
    0x10,0x26, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0xc2, // STORE_FAST 2
    0x23,0x07, // LOAD_CONST_OBJ 7
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0x12,0x60, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb4, // LOAD_FAST 4
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x56, // STORE_SUBSCR
    0x10,0x27, // LOAD_CONST_STRING 'Connection'
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x10,0x28, // LOAD_CONST_STRING 'close'
    0xb4, // LOAD_FAST 4
    0x10,0x27, // LOAD_CONST_STRING 'Connection'
    0x56, // STORE_SUBSCR
    0xb4, // LOAD_FAST 4
    0x5f, // GET_ITER_STACK
    0x4b,0x2a, // FOR_ITER 42
    0x26,0x1c, // STORE_FAST_N 28
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x24,0x1c, // LOAD_FAST_N 28
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0xb4, // LOAD_FAST 4
    0x24,0x1c, // LOAD_FAST_N 28
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x14, // JUMP -44
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x44,0xe1,0x80, // POP_JUMP_IF_FALSE 97
    0xbb, // LOAD_FAST 11
    0x44,0xd5,0x80, // POP_JUMP_IF_FALSE 85
    0xb4, // LOAD_FAST 4
    0x14,0x29, // LOAD_METHOD 'get'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x51, // LOAD_CONST_NONE
    0x36,0x02, // CALL_METHOD 2
    0x10,0x25, // LOAD_CONST_STRING 'chunked'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x75, // POP_JUMP_IF_FALSE 53
    0xb2, // LOAD_FAST 2
    0x5f, // GET_ITER_STACK
    0x4b,0x26, // FOR_ITER 38
    0x26,0x1d, // STORE_FAST_N 29
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0x12,0x60, // LOAD_GLOBAL 'len'
    0x24,0x1d, // LOAD_FAST_N 29
    0x34,0x01, // CALL_FUNCTION 1
    0xf8, // BINARY_OP 33 __mod__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x24,0x1d, // LOAD_FAST_N 29
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x18, // JUMP -40
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x10,0x2a, // LOAD_CONST_STRING '0\r\n\r\n'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x51, // JUMP 17
    0xb2, // LOAD_FAST 2
    0x5f, // GET_ITER_STACK
    0x4b,0x0d, // FOR_ITER 13
    0x26,0x1d, // STORE_FAST_N 29
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0x24,0x1d, // LOAD_FAST_N 29
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x31, // JUMP -15
    0x42,0x48, // JUMP 8
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x21, // LOAD_METHOD 'write'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x2b, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x26,0x1e, // STORE_FAST_N 30
    0x24,0x1e, // LOAD_FAST_N 30
    0x14,0x0e, // LOAD_METHOD 'split'
    0x51, // LOAD_CONST_NONE
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0x26,0x1e, // STORE_FAST_N 30
    0x12,0x60, // LOAD_GLOBAL 'len'
    0x24,0x1e, // LOAD_FAST_N 30
    0x34,0x01, // CALL_FUNCTION 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x5c, // LOAD_GLOBAL 'ValueError'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x24,0x1e, // LOAD_FAST_N 30
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x5d, // LOAD_GLOBAL 'int'
    0x24,0x1e, // LOAD_FAST_N 30
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x1f, // STORE_FAST_N 31
    0x10,0x10, // LOAD_CONST_STRING ''
    0x26,0x20, // STORE_FAST_N 32
    0x12,0x60, // LOAD_GLOBAL 'len'
    0x24,0x1e, // LOAD_FAST_N 30
    0x34,0x01, // CALL_FUNCTION 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x24,0x1e, // LOAD_FAST_N 30
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x14,0x2c, // LOAD_METHOD 'rstrip'
    0x36,0x00, // CALL_METHOD 0
    0x26,0x20, // STORE_FAST_N 32
    0x51, // LOAD_CONST_NONE
    0x26,0x21, // STORE_FAST_N 33
    0x50, // LOAD_CONST_FALSE
    0x26,0x22, // STORE_FAST_N 34
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x2b, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x26,0x1e, // STORE_FAST_N 30
    0x24,0x1e, // LOAD_FAST_N 30
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x24,0x1e, // LOAD_FAST_N 30
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x42,0xe3,0x81, // JUMP 227
    0x24,0x1e, // LOAD_FAST_N 30
    0x14,0x2d, // LOAD_METHOD 'lower'
    0x36,0x00, // CALL_METHOD 0
    0x26,0x23, // STORE_FAST_N 35
    0x24,0x23, // LOAD_FAST_N 35
    0x14,0x2e, // LOAD_METHOD 'startswith'
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0x36,0x01, // CALL_METHOD 1
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x24,0x1e, // LOAD_FAST_N 30
    0xdd, // BINARY_OP 6 <in>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x52, // LOAD_CONST_TRUE
    0x26,0x22, // STORE_FAST_N 34
    0x42,0xf0,0x80, // JUMP 112
    0x24,0x23, // LOAD_FAST_N 35
    0x14,0x2e, // LOAD_METHOD 'startswith'
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0x36,0x01, // CALL_METHOD 1
    0x44,0xe5,0x80, // POP_JUMP_IF_FALSE 101
    0x22,0x81,0x48, // LOAD_CONST_SMALL_INT 200
    0x24,0x1f, // LOAD_FAST_N 31
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x06, // JUMP_IF_FALSE_OR_POP 6
    0x22,0x82,0x2b, // LOAD_CONST_SMALL_INT 299
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x43,0xd0,0x80, // POP_JUMP_IF_TRUE 80
    0x24,0x1f, // LOAD_FAST_N 31
    0x22,0x82,0x2d, // LOAD_CONST_SMALL_INT 301
    0x22,0x82,0x2e, // LOAD_CONST_SMALL_INT 302
    0x22,0x82,0x2f, // LOAD_CONST_SMALL_INT 303
    0x22,0x82,0x33, // LOAD_CONST_SMALL_INT 307
    0x22,0x82,0x34, // LOAD_CONST_SMALL_INT 308
    0x2b,0x05, // BUILD_LIST 5
    0xdd, // BINARY_OP 6 <in>
    0x44,0x6e, // POP_JUMP_IF_FALSE 46
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0x24,0x1e, // LOAD_FAST_N 30
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x10,0x26, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0xca, // STORE_FAST 10
    0xba, // LOAD_FAST 10
    0x14,0x2e, // LOAD_METHOD 'startswith'
    0x10,0x0f, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x55, // POP_JUMP_IF_FALSE 21
    0x24,0x10, // LOAD_FAST_N 16
    0x10,0x2f, // LOAD_CONST_STRING '//'
    0xf2, // BINARY_OP 27 __add__
    0x24,0x12, // LOAD_FAST_N 18
    0xf2, // BINARY_OP 27 __add__
    0x10,0x16, // LOAD_CONST_STRING ':'
    0xf2, // BINARY_OP 27 __add__
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0x24,0x14, // LOAD_FAST_N 20
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xba, // LOAD_FAST 10
    0xf2, // BINARY_OP 27 __add__
    0xca, // STORE_FAST 10
    0x42,0x4a, // JUMP 10
    0x12,0x61, // LOAD_GLOBAL 'NotImplementedError'
    0x23,0x0f, // LOAD_CONST_OBJ 15
    0x24,0x1f, // LOAD_FAST_N 31
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x40, // JUMP 0
    0xb8, // LOAD_FAST 8
    0x50, // LOAD_CONST_FALSE
    0xde, // BINARY_OP 7 <is>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x42,0xc9,0x80, // JUMP 73
    0xb8, // LOAD_FAST 8
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x7c, // POP_JUMP_IF_FALSE 60
    0x12,0x5b, // LOAD_GLOBAL 'str'
    0x24,0x1e, // LOAD_FAST_N 30
    0x10,0x26, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0x26,0x1e, // STORE_FAST_N 30
    0x24,0x1e, // LOAD_FAST_N 30
    0x14,0x0e, // LOAD_METHOD 'split'
    0x10,0x16, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0x26,0x1c, // STORE_FAST_N 28
    0x26,0x24, // STORE_FAST_N 36
    0x24,0x24, // LOAD_FAST_N 36
    0x14,0x30, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0x26,0x24, // STORE_FAST_N 36
    0x24,0x24, // LOAD_FAST_N 36
    0x24,0x18, // LOAD_FAST_N 24
    0x24,0x1c, // LOAD_FAST_N 28
    0x56, // STORE_SUBSCR
    0x24,0x23, // LOAD_FAST_N 35
    0x14,0x2e, // LOAD_METHOD 'startswith'
    0x23,0x10, // LOAD_CONST_OBJ 16
    0x36,0x01, // CALL_METHOD 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x5d, // LOAD_GLOBAL 'int'
    0x24,0x24, // LOAD_FAST_N 36
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x21, // STORE_FAST_N 33
    0x42,0x48, // JUMP 8
    0xb8, // LOAD_FAST 8
    0x24,0x1e, // LOAD_FAST_N 30
    0x24,0x18, // LOAD_FAST_N 24
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x42,0x87,0x7e, // JUMP -249
    0x4a,0x10, // POP_EXCEPT_JUMP 16
    0x57, // DUP_TOP
    0x12,0x62, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x59, // POP_TOP
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x64, // RAISE_LAST
    0x5d, // END_FINALLY
    0xba, // LOAD_FAST 10
    0x44,0x7a, // POP_JUMP_IF_FALSE 58
    0x24,0x19, // LOAD_FAST_N 25
    0x14,0x28, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x14,0x31, // LOAD_METHOD 'pop'
    0x10,0x22, // LOAD_CONST_STRING 'Host'
    0x51, // LOAD_CONST_NONE
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x24,0x1f, // LOAD_FAST_N 31
    0x22,0x82,0x2d, // LOAD_CONST_SMALL_INT 301
    0x22,0x82,0x2e, // LOAD_CONST_SMALL_INT 302
    0x22,0x82,0x2f, // LOAD_CONST_SMALL_INT 303
    0x2b,0x03, // BUILD_LIST 3
    0xdd, // BINARY_OP 6 <in>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x32, // LOAD_CONST_STRING 'GET'
    0xba, // LOAD_FAST 10
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x34,0x06, // CALL_FUNCTION 6
    0x63, // RETURN_VALUE
    0x12,0x05, // LOAD_GLOBAL 'request'
    0xb0, // LOAD_FAST 0
    0xba, // LOAD_FAST 10
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x34,0x06, // CALL_FUNCTION 6
    0x63, // RETURN_VALUE
    0x42,0xce,0x80, // JUMP 78
    0x24,0x22, // LOAD_FAST_N 34
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0x12,0x04, // LOAD_GLOBAL 'Response'
    0x12,0x03, // LOAD_GLOBAL 'BodyStream'
    0x24,0x19, // LOAD_FAST_N 25
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x34,0x02, // CALL_FUNCTION 2
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x25, // STORE_FAST_N 37
    0x42,0x5f, // JUMP 31
    0x24,0x21, // LOAD_FAST_N 33
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0x12,0x04, // LOAD_GLOBAL 'Response'
    0x12,0x03, // LOAD_GLOBAL 'BodyStream'
    0x24,0x19, // LOAD_FAST_N 25
    0x24,0x21, // LOAD_FAST_N 33
    0x34,0x02, // CALL_FUNCTION 2
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x25, // STORE_FAST_N 37
    0x42,0x48, // JUMP 8
    0x12,0x04, // LOAD_GLOBAL 'Response'
    0x24,0x19, // LOAD_FAST_N 25
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x25, // STORE_FAST_N 37
    0x24,0x1f, // LOAD_FAST_N 31
    0x24,0x25, // LOAD_FAST_N 37
    0x18,0x33, // STORE_ATTR 'status_code'
    0x24,0x20, // LOAD_FAST_N 32
    0x24,0x25, // LOAD_FAST_N 37
    0x18,0x34, // STORE_ATTR 'reason'
    0x24,0x18, // LOAD_FAST_N 24
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x24,0x18, // LOAD_FAST_N 24
    0x24,0x25, // LOAD_FAST_N 37
    0x18,0x35, // STORE_ATTR 'headers'
    0x24,0x25, // LOAD_FAST_N 37
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___request = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___request,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 1216,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 47,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 10,
        .n_kwonly_args = 0,
        .n_def_pos_args = 8,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_requests___init___request + 17,
        .line_info_top = fun_data_requests___init___request + 17,
        .opcodes = fun_data_requests___init___request + 17,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___request fun_data_requests___init___request[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___head
static const byte fun_data_requests___init___head[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x36,0x53, // names: head, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x37, // LOAD_CONST_STRING 'HEAD'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___head = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___head,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 54,
        .line_info = fun_data_requests___init___head + 6,
        .line_info_top = fun_data_requests___init___head + 6,
        .opcodes = fun_data_requests___init___head + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___head fun_data_requests___init___head[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___get
static const byte fun_data_requests___init___get[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x29,0x53, // names: get, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x32, // LOAD_CONST_STRING 'GET'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___get = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___get,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_requests___init___get + 6,
        .line_info_top = fun_data_requests___init___get + 6,
        .opcodes = fun_data_requests___init___get + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___get fun_data_requests___init___get[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___post
static const byte fun_data_requests___init___post[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x38,0x53, // names: post, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x39, // LOAD_CONST_STRING 'POST'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___post = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___post,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 56,
        .line_info = fun_data_requests___init___post + 6,
        .line_info_top = fun_data_requests___init___post + 6,
        .opcodes = fun_data_requests___init___post + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___post fun_data_requests___init___post[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___put
static const byte fun_data_requests___init___put[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x3a,0x53, // names: put, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x3b, // LOAD_CONST_STRING 'PUT'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___put = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___put,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_requests___init___put + 6,
        .line_info_top = fun_data_requests___init___put + 6,
        .opcodes = fun_data_requests___init___put + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___put fun_data_requests___init___put[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___patch
static const byte fun_data_requests___init___patch[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x3c,0x53, // names: patch, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x3d, // LOAD_CONST_STRING 'PATCH'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___patch = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___patch,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 60,
        .line_info = fun_data_requests___init___patch + 6,
        .line_info_top = fun_data_requests___init___patch + 6,
        .opcodes = fun_data_requests___init___patch + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___patch fun_data_requests___init___patch[0]
#endif

// child of requests___init____lt_module_gt_
// frozen bytecode for file requests/__init__.py, scope requests___init___delete
static const byte fun_data_requests___init___delete[18] = {
    0xb9,0x80,0x40,0x04, // prelude
    0x3e,0x53, // names: delete, url
     // code info
    0x12,0x05, // LOAD_GLOBAL 'request'
    0x10,0x3f, // LOAD_CONST_STRING 'DELETE'
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x82,0x02, // CALL_FUNCTION_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_requests___init___delete = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init___delete,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 62,
        .line_info = fun_data_requests___init___delete + 6,
        .line_info_top = fun_data_requests___init___delete + 6,
        .opcodes = fun_data_requests___init___delete + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_requests___init___delete fun_data_requests___init___delete[0]
#endif

static const mp_raw_code_t *const children_requests___init____lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_requests___init___BodyStream,
    (const mp_raw_code_t *)&proto_fun_requests___init___Response,
    (const mp_raw_code_t *)&proto_fun_requests___init___request,
    (const mp_raw_code_t *)&proto_fun_requests___init___head,
    (const mp_raw_code_t *)&proto_fun_requests___init___get,
    (const mp_raw_code_t *)&proto_fun_requests___init___post,
    (const mp_raw_code_t *)&proto_fun_requests___init___put,
    (const mp_raw_code_t *)&proto_fun_requests___init___patch,
    (const mp_raw_code_t *)&proto_fun_requests___init___delete,
};

static const mp_raw_code_truncated_t proto_fun_requests___init____lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_requests___init____lt_module_gt_,
    .children = (void *)&children_requests___init____lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 68,
    .n_children = 9,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_requests___init____lt_module_gt_ + 3,
        .line_info_top = fun_data_requests___init____lt_module_gt_ + 3,
        .opcodes = fun_data_requests___init____lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_requests___init__[110] = {
    MP_QSTR_requests_slash___init___dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_socket,
    MP_QSTR_BodyStream,
    MP_QSTR_Response,
    MP_QSTR_request,
    MP_QSTR_copy,
    MP_QSTR___next__,
    MP_QSTR___len__,
    MP_QSTR_binascii,
    MP_QSTR_format,
    MP_QSTR_b2a_base64,
    MP_QSTR_ascii,
    MP_QSTR_Basic_space__brace_open__brace_close_,
    MP_QSTR_split,
    MP_QSTR__slash_,
    MP_QSTR_,
    MP_QSTR_http_colon_,
    MP_QSTR_https_colon_,
    MP_QSTR_tls,
    MP_QSTR__question_,
    MP_QSTR__hash_,
    MP_QSTR__colon_,
    MP_QSTR_getaddrinfo,
    MP_QSTR_SOCK_STREAM,
    MP_QSTR_settimeout,
    MP_QSTR_connect,
    MP_QSTR_SSLContext,
    MP_QSTR_PROTOCOL_TLS_CLIENT,
    MP_QSTR_CERT_NONE,
    MP_QSTR_verify_mode,
    MP_QSTR_wrap_socket,
    MP_QSTR_server_hostname,
    MP_QSTR_write,
    MP_QSTR_Host,
    MP_QSTR_dumps,
    MP_QSTR_json,
    MP_QSTR_chunked,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR_Connection,
    MP_QSTR_close,
    MP_QSTR_get,
    MP_QSTR_0_0x0d__0x0a__0x0d__0x0a_,
    MP_QSTR_readline,
    MP_QSTR_rstrip,
    MP_QSTR_lower,
    MP_QSTR_startswith,
    MP_QSTR__slash__slash_,
    MP_QSTR_strip,
    MP_QSTR_pop,
    MP_QSTR_GET,
    MP_QSTR_status_code,
    MP_QSTR_reason,
    MP_QSTR_headers,
    MP_QSTR_head,
    MP_QSTR_HEAD,
    MP_QSTR_post,
    MP_QSTR_POST,
    MP_QSTR_put,
    MP_QSTR_PUT,
    MP_QSTR_patch,
    MP_QSTR_PATCH,
    MP_QSTR_delete,
    MP_QSTR_DELETE,
    MP_QSTR___init__,
    MP_QSTR__sock,
    MP_QSTR__chunk,
    MP_QSTR__remaining,
    MP_QSTR_read,
    MP_QSTR_readinto,
    MP_QSTR_raw,
    MP_QSTR_encoding,
    MP_QSTR__cached,
    MP_QSTR_content,
    MP_QSTR_text,
    MP_QSTR_loads,
    MP_QSTR___enter__,
    MP_QSTR___exit__,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_property,
    MP_QSTR_method,
    MP_QSTR_url,
    MP_QSTR_data,
    MP_QSTR_stream,
    MP_QSTR_auth,
    MP_QSTR_timeout,
    MP_QSTR_parse_headers,
    MP_QSTR_verify,
    MP_QSTR_getattr,
    MP_QSTR_str,
    MP_QSTR_ValueError,
    MP_QSTR_int,
    MP_QSTR_isinstance,
    MP_QSTR_bytes,
    MP_QSTR_len,
    MP_QSTR_NotImplementedError,
    MP_QSTR_OSError,
    MP_QSTR_self,
    MP_QSTR_sock,
    MP_QSTR_remaining,
    MP_QSTR_n,
    MP_QSTR_bytearray,
    MP_QSTR_buf,
    MP_QSTR_memoryview,
    MP_QSTR_f,
    MP_QSTR_exc_type,
    MP_QSTR_exc_val,
    MP_QSTR_exc_tb,
};

// constants
static const mp_obj_str_t const_obj_requests___init___0 = {{&mp_type_bytes}, 14943, 5, (const byte*)"\x7b\x7d\x3a\x7b\x7d"};
static const mp_obj_str_t const_obj_requests___init___3 = {{&mp_type_bytes}, 48500, 17, (const byte*)"\x25\x73\x20\x2f\x25\x73\x20\x48\x54\x54\x50\x2f\x31\x2e\x31\x0d\x0a"};
static const mp_obj_str_t const_obj_requests___init___8 = {{&mp_type_bytes}, 26975, 2, (const byte*)"\x3a\x20"};
static const mp_obj_str_t const_obj_requests___init___9 = {{&mp_type_bytes}, 27298, 2, (const byte*)"\x0d\x0a"};
static const mp_obj_str_t const_obj_requests___init___10 = {{&mp_type_bytes}, 50079, 4, (const byte*)"\x25\x78\x0d\x0a"};
static const mp_obj_str_t const_obj_requests___init___11 = {{&mp_type_str}, 62148, 29, (const byte*)"\x48\x54\x54\x50\x20\x65\x72\x72\x6f\x72\x3a\x20\x42\x61\x64\x53\x74\x61\x74\x75\x73\x4c\x69\x6e\x65\x3a\x0a\x25\x73"};
static const mp_obj_str_t const_obj_requests___init___12 = {{&mp_type_bytes}, 8890, 18, (const byte*)"\x74\x72\x61\x6e\x73\x66\x65\x72\x2d\x65\x6e\x63\x6f\x64\x69\x6e\x67\x3a"};
static const mp_obj_str_t const_obj_requests___init___13 = {{&mp_type_bytes}, 3583, 7, (const byte*)"\x63\x68\x75\x6e\x6b\x65\x64"};
static const mp_obj_str_t const_obj_requests___init___14 = {{&mp_type_bytes}, 674, 9, (const byte*)"\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x3a"};
static const mp_obj_str_t const_obj_requests___init___15 = {{&mp_type_str}, 18157, 29, (const byte*)"\x52\x65\x64\x69\x72\x65\x63\x74\x20\x25\x64\x20\x6e\x6f\x74\x20\x79\x65\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64"};
static const mp_obj_str_t const_obj_requests___init___16 = {{&mp_type_bytes}, 64711, 15, (const byte*)"\x63\x6f\x6e\x74\x65\x6e\x74\x2d\x6c\x65\x6e\x67\x74\x68\x3a"};
static const mp_obj_str_t const_obj_requests___init___18 = {{&mp_type_bytes}, 46494, 1, (const byte*)"\x3b"};
static const mp_obj_str_t const_obj_requests___init___19 = {{&mp_type_str}, 14625, 38, (const byte*)"\x43\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x20\x63\x6c\x6f\x73\x65\x64\x20\x62\x65\x66\x6f\x72\x65\x20\x62\x6f\x64\x79\x20\x63\x6f\x6d\x70\x6c\x65\x74\x65"};

// constant table
static const mp_rom_obj_t const_obj_table_data_requests___init__[20] = {
    MP_ROM_PTR(&const_obj_requests___init___0),
    MP_ROM_QSTR(MP_QSTR_Authorization),
    MP_ROM_QSTR(MP_QSTR_Unsupported_space_protocol_colon__space_),
    MP_ROM_PTR(&const_obj_requests___init___3),
    MP_ROM_QSTR(MP_QSTR_Content_hyphen_Type),
    MP_ROM_QSTR(MP_QSTR_application_slash_json),
    MP_ROM_QSTR(MP_QSTR_Transfer_hyphen_Encoding),
    MP_ROM_QSTR(MP_QSTR_Content_hyphen_Length),
    MP_ROM_PTR(&const_obj_requests___init___8),
    MP_ROM_PTR(&const_obj_requests___init___9),
    MP_ROM_PTR(&const_obj_requests___init___10),
    MP_ROM_PTR(&const_obj_requests___init___11),
    MP_ROM_PTR(&const_obj_requests___init___12),
    MP_ROM_PTR(&const_obj_requests___init___13),
    MP_ROM_PTR(&const_obj_requests___init___14),
    MP_ROM_PTR(&const_obj_requests___init___15),
    MP_ROM_PTR(&const_obj_requests___init___16),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_requests___init___18),
    MP_ROM_PTR(&const_obj_requests___init___19),
};

static const mp_frozen_module_t frozen_module_requests___init__ = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_requests___init__,
        .obj_table = (mp_obj_t *)&const_obj_table_data_requests___init__,
    },
    .proto_fun = &proto_fun_requests___init____lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module ssl
// - original source file: build/frozen_mpy/ssl.mpy
// - frozen file name: ssl.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file ssl.py, scope ssl__lt_module_gt_
static const byte fun_data_ssl__lt_module_gt_[60] = {
    0x30,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'tls'
    0x16,0x02, // STORE_NAME 'tls'
    0x11,0x12, // LOAD_NAME 'hasattr'
    0x11,0x02, // LOAD_NAME 'tls'
    0x10,0x03, // LOAD_CONST_STRING 'SSLContext'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x11,0x13, // LOAD_NAME 'ImportError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x04, // LOAD_CONST_STRING '*'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x02, // IMPORT_NAME 'tls'
    0x69, // IMPORT_STAR
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x03, // LOAD_CONST_STRING 'SSLContext'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x03, // STORE_NAME 'SSLContext'
    0x50, // LOAD_CONST_FALSE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x11,0x14, // LOAD_NAME 'CERT_NONE'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x52, // LOAD_CONST_TRUE
    0x2a,0x07, // BUILD_TUPLE 7
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x06, // STORE_NAME 'wrap_socket'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ssl__lt_module_gt_
// frozen bytecode for file ssl.py, scope ssl_SSLContext
static const byte fun_data_ssl_SSLContext[58] = {
    0x10,0x02, // prelude
    0x03, // names: SSLContext
     // code info
    0x11,0x15, // LOAD_NAME '__name__'
    0x16,0x16, // STORE_NAME '__module__'
    0x10,0x03, // LOAD_CONST_STRING 'SSLContext'
    0x16,0x17, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x0e, // STORE_NAME '__init__'
    0x11,0x18, // LOAD_NAME 'property'
    0x32,0x01, // MAKE_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x0a, // STORE_NAME 'verify_mode'
    0x11,0x0a, // LOAD_NAME 'verify_mode'
    0x13,0x05, // LOAD_ATTR 'setter'
    0x32,0x02, // MAKE_FUNCTION 2
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x0a, // STORE_NAME 'verify_mode'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x07, // STORE_NAME 'load_cert_chain'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x08, // STORE_NAME 'load_verify_locations'
    0x50, // LOAD_CONST_FALSE
    0x52, // LOAD_CONST_TRUE
    0x51, // LOAD_CONST_NONE
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x06, // STORE_NAME 'wrap_socket'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext___init__
static const byte fun_data_ssl_SSLContext___init__[20] = {
    0xa9,0x80,0x80,0x40,0x04, // prelude
    0x0e,0x20, // names: __init__, self
     // code info
    0x12,0x02, // LOAD_GLOBAL 'tls'
    0x14,0x03, // LOAD_METHOD 'SSLContext'
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x37,0x01, // CALL_METHOD_VAR_KW 1
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR '_context'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_ssl_SSLContext___init__ + 7,
        .line_info_top = fun_data_ssl_SSLContext___init__ + 7,
        .opcodes = fun_data_ssl_SSLContext___init__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext___init__ fun_data_ssl_SSLContext___init__[0]
#endif

// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext_verify_mode
static const byte fun_data_ssl_SSLContext_verify_mode[10] = {
    0x09,0x04, // prelude
    0x0a,0x20, // names: verify_mode, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR '_context'
    0x13,0x0a, // LOAD_ATTR 'verify_mode'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext_verify_mode = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext_verify_mode,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_ssl_SSLContext_verify_mode + 4,
        .line_info_top = fun_data_ssl_SSLContext_verify_mode + 4,
        .opcodes = fun_data_ssl_SSLContext_verify_mode + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext_verify_mode fun_data_ssl_SSLContext_verify_mode[0]
#endif

// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext_verify_mode2
static const byte fun_data_ssl_SSLContext_verify_mode2[13] = {
    0x1a,0x06, // prelude
    0x0a,0x20,0x21, // names: verify_mode, self, val
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR '_context'
    0x18,0x0a, // STORE_ATTR 'verify_mode'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext_verify_mode2 = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext_verify_mode2,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_ssl_SSLContext_verify_mode2 + 5,
        .line_info_top = fun_data_ssl_SSLContext_verify_mode2 + 5,
        .opcodes = fun_data_ssl_SSLContext_verify_mode2 + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext_verify_mode2 fun_data_ssl_SSLContext_verify_mode2[0]
#endif

// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext_load_cert_chain
static const byte fun_data_ssl_SSLContext_load_cert_chain[74] = {
    0x47,0x08, // prelude
    0x07,0x20,0x22,0x23, // names: load_cert_chain, self, certfile, keyfile
     // code info
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x25, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x26, // LOAD_GLOBAL 'open'
    0xb1, // LOAD_FAST 1
    0x10,0x10, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x08, // SETUP_WITH 8
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x11, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0xc1, // STORE_FAST 1
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x12,0x24, // LOAD_GLOBAL 'isinstance'
    0xb2, // LOAD_FAST 2
    0x12,0x25, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x26, // LOAD_GLOBAL 'open'
    0xb2, // LOAD_FAST 2
    0x10,0x10, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x08, // SETUP_WITH 8
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x11, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR '_context'
    0x14,0x07, // LOAD_METHOD 'load_cert_chain'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext_load_cert_chain = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext_load_cert_chain,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 74,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 7,
        .line_info = fun_data_ssl_SSLContext_load_cert_chain + 6,
        .line_info_top = fun_data_ssl_SSLContext_load_cert_chain + 6,
        .opcodes = fun_data_ssl_SSLContext_load_cert_chain + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext_load_cert_chain fun_data_ssl_SSLContext_load_cert_chain[0]
#endif

// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext_load_verify_locations
static const byte fun_data_ssl_SSLContext_load_verify_locations[41] = {
    0xc7,0x80,0x01,0x08, // prelude
    0x08,0x20,0x27,0x09, // names: load_verify_locations, self, cafile, cadata
     // code info
    0xb1, // LOAD_FAST 1
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x26, // LOAD_GLOBAL 'open'
    0xb1, // LOAD_FAST 1
    0x10,0x10, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x08, // SETUP_WITH 8
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x11, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR '_context'
    0x14,0x08, // LOAD_METHOD 'load_verify_locations'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext_load_verify_locations = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext_load_verify_locations,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 41,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_ssl_SSLContext_load_verify_locations + 8,
        .line_info_top = fun_data_ssl_SSLContext_load_verify_locations + 8,
        .opcodes = fun_data_ssl_SSLContext_load_verify_locations + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext_load_verify_locations fun_data_ssl_SSLContext_load_verify_locations[0]
#endif

// child of ssl_SSLContext
// frozen bytecode for file ssl.py, scope ssl_SSLContext_wrap_socket
static const byte fun_data_ssl_SSLContext_wrap_socket[29] = {
    0xe9,0x85,0x01,0x0c, // prelude
    0x06,0x20,0x19,0x0b,0x0c,0x0d, // names: wrap_socket, self, sock, server_side, do_handshake_on_connect, server_hostname
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR '_context'
    0x14,0x06, // LOAD_METHOD 'wrap_socket'
    0xb1, // LOAD_FAST 1
    0x10,0x0b, // LOAD_CONST_STRING 'server_side'
    0xb2, // LOAD_FAST 2
    0x10,0x0c, // LOAD_CONST_STRING 'do_handshake_on_connect'
    0xb3, // LOAD_FAST 3
    0x10,0x0d, // LOAD_CONST_STRING 'server_hostname'
    0xb4, // LOAD_FAST 4
    0x36,0x86,0x01, // CALL_METHOD 769
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext_wrap_socket = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext_wrap_socket,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 29,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_ssl_SSLContext_wrap_socket + 10,
        .line_info_top = fun_data_ssl_SSLContext_wrap_socket + 10,
        .opcodes = fun_data_ssl_SSLContext_wrap_socket + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLContext_wrap_socket fun_data_ssl_SSLContext_wrap_socket[0]
#endif

static const mp_raw_code_t *const children_ssl_SSLContext[] = {
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext___init__,
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext_verify_mode,
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext_verify_mode2,
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext_load_cert_chain,
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext_load_verify_locations,
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext_wrap_socket,
};

static const mp_raw_code_truncated_t proto_fun_ssl_SSLContext = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLContext,
    .children = (void *)&children_ssl_SSLContext,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 58,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 3,
        .line_info = fun_data_ssl_SSLContext + 3,
        .line_info_top = fun_data_ssl_SSLContext + 3,
        .opcodes = fun_data_ssl_SSLContext + 3,
    },
    #endif
    #endif
};

// child of ssl__lt_module_gt_
// frozen bytecode for file ssl.py, scope ssl_wrap_socket
static const byte fun_data_ssl_wrap_socket[76] = {
    0x88,0x91,0x85,0x01,0x12, // prelude
    0x06,0x19,0x0b,0x1a,0x1b,0x1c,0x09,0x0d,0x1d, // names: wrap_socket, sock, server_side, key, cert, cert_reqs, cadata, server_hostname, do_handshake
     // code info
    0x12,0x03, // LOAD_GLOBAL 'SSLContext'
    0xb1, // LOAD_FAST 1
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x12,0x1e, // LOAD_GLOBAL 'PROTOCOL_TLS_SERVER'
    0x42,0x42, // JUMP 2
    0x12,0x1f, // LOAD_GLOBAL 'PROTOCOL_TLS_CLIENT'
    0x34,0x01, // CALL_FUNCTION 1
    0xc8, // STORE_FAST 8
    0xb3, // LOAD_FAST 3
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0xb2, // LOAD_FAST 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb8, // LOAD_FAST 8
    0x14,0x07, // LOAD_METHOD 'load_cert_chain'
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb8, // LOAD_FAST 8
    0x14,0x08, // LOAD_METHOD 'load_verify_locations'
    0x10,0x09, // LOAD_CONST_STRING 'cadata'
    0xb5, // LOAD_FAST 5
    0x36,0x82,0x00, // CALL_METHOD 256
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0xb8, // LOAD_FAST 8
    0x18,0x0a, // STORE_ATTR 'verify_mode'
    0xb8, // LOAD_FAST 8
    0x14,0x06, // LOAD_METHOD 'wrap_socket'
    0xb0, // LOAD_FAST 0
    0x10,0x0b, // LOAD_CONST_STRING 'server_side'
    0xb1, // LOAD_FAST 1
    0x10,0x0c, // LOAD_CONST_STRING 'do_handshake_on_connect'
    0xb7, // LOAD_FAST 7
    0x10,0x0d, // LOAD_CONST_STRING 'server_hostname'
    0xb6, // LOAD_FAST 6
    0x36,0x86,0x01, // CALL_METHOD 769
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_wrap_socket = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_wrap_socket,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 76,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 18,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 8,
        .n_kwonly_args = 0,
        .n_def_pos_args = 7,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_ssl_wrap_socket + 14,
        .line_info_top = fun_data_ssl_wrap_socket + 14,
        .opcodes = fun_data_ssl_wrap_socket + 14,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_wrap_socket fun_data_ssl_wrap_socket[0]
#endif

static const mp_raw_code_t *const children_ssl__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_ssl_SSLContext,
    (const mp_raw_code_t *)&proto_fun_ssl_wrap_socket,
};

static const mp_raw_code_truncated_t proto_fun_ssl__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl__lt_module_gt_,
    .children = (void *)&children_ssl__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 60,
    .n_children = 2,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_ssl__lt_module_gt_ + 3,
        .line_info_top = fun_data_ssl__lt_module_gt_ + 3,
        .opcodes = fun_data_ssl__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_ssl[40] = {
    MP_QSTR_ssl_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_tls,
    MP_QSTR_SSLContext,
    MP_QSTR__star_,
    MP_QSTR_setter,
    MP_QSTR_wrap_socket,
    MP_QSTR_load_cert_chain,
    MP_QSTR_load_verify_locations,
    MP_QSTR_cadata,
    MP_QSTR_verify_mode,
    MP_QSTR_server_side,
    MP_QSTR_do_handshake_on_connect,
    MP_QSTR_server_hostname,
    MP_QSTR___init__,
    MP_QSTR__context,
    MP_QSTR_rb,
    MP_QSTR_read,
    MP_QSTR_hasattr,
    MP_QSTR_ImportError,
    MP_QSTR_CERT_NONE,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_property,
    MP_QSTR_sock,
    MP_QSTR_key,
    MP_QSTR_cert,
    MP_QSTR_cert_reqs,
    MP_QSTR_do_handshake,
    MP_QSTR_PROTOCOL_TLS_SERVER,
    MP_QSTR_PROTOCOL_TLS_CLIENT,
    MP_QSTR_self,
    MP_QSTR_val,
    MP_QSTR_certfile,
    MP_QSTR_keyfile,
    MP_QSTR_isinstance,
    MP_QSTR_str,
    MP_QSTR_open,
    MP_QSTR_cafile,
};

// constants
static const mp_obj_str_t const_obj_ssl_0 = {{&mp_type_str}, 42518, 44, (const byte*)"\x6e\x6f\x20\x54\x4c\x53\x20\x69\x6e\x20\x74\x68\x69\x73\x20\x62\x75\x69\x6c\x64\x20\x28\x62\x75\x69\x6c\x74\x20\x77\x69\x74\x68\x6f\x75\x74\x20\x6d\x62\x65\x64\x54\x4c\x53\x29"};

// constant table
static const mp_rom_obj_t const_obj_table_data_ssl[1] = {
    MP_ROM_PTR(&const_obj_ssl_0),
};

static const mp_frozen_module_t frozen_module_ssl = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_ssl,
        .obj_table = (mp_obj_t *)&const_obj_table_data_ssl,
    },
    .proto_fun = &proto_fun_ssl__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module websocket
// - original source file: build/frozen_mpy/websocket.mpy
// - frozen file name: websocket.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file websocket.py, scope websocket__lt_module_gt_
static const byte fun_data_websocket__lt_module_gt_[96] = {
    0x18,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'binascii'
    0x16,0x02, // STORE_NAME 'binascii'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'random'
    0x16,0x03, // STORE_NAME 'random'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x04, // IMPORT_NAME 'socket'
    0x16,0x04, // STORE_NAME 'socket'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x05, // IMPORT_NAME 'struct'
    0x16,0x05, // STORE_NAME 'struct'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x3e, // STORE_NAME 'OP_CONT'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x3f, // STORE_NAME 'OP_TEXT'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x40, // STORE_NAME 'OP_BINARY'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x16,0x41, // STORE_NAME 'OP_CLOSE'
    0x89, // LOAD_CONST_SMALL_INT 9
    0x16,0x42, // STORE_NAME 'OP_PING'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x16,0x43, // STORE_NAME 'OP_PONG'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x09, // STORE_NAME '_rand'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x06, // LOAD_CONST_STRING 'WebSocketException'
    0x11,0x44, // LOAD_NAME 'Exception'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x06, // STORE_NAME 'WebSocketException'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x07, // LOAD_CONST_STRING 'WebSocketConnectionClosedException'
    0x11,0x06, // LOAD_NAME 'WebSocketException'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x07, // STORE_NAME 'WebSocketConnectionClosedException'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0a, // STORE_NAME '_split_url'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x04, // MAKE_FUNCTION 4
    0x10,0x08, // LOAD_CONST_STRING 'WebSocket'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x08, // STORE_NAME 'WebSocket'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x52, // LOAD_CONST_TRUE
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x12, // STORE_NAME 'create_connection'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket__rand
static const byte fun_data_websocket__rand[19] = {
    0x21,0x04, // prelude
    0x09,0x45, // names: _rand, n
     // code info
    0x12,0x46, // LOAD_GLOBAL 'bytes'
    0x32,0x00, // MAKE_FUNCTION 0
    0x12,0x47, // LOAD_GLOBAL 'range'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
// child of websocket__rand
// frozen bytecode for file websocket.py, scope websocket__rand__lt_genexpr_gt_
static const byte fun_data_websocket__rand__lt_genexpr_gt_[25] = {
    0xc1,0x40,0x04, // prelude
    0x27,0x53, // names: <genexpr>, *
     // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0c, // FOR_ITER 12
    0xc1, // STORE_FAST 1
    0x12,0x03, // LOAD_GLOBAL 'random'
    0x14,0x28, // LOAD_METHOD 'getrandbits'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x32, // JUMP -14
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket__rand__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_websocket__rand__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data_websocket__rand__lt_genexpr_gt_ + 5,
        .line_info_top = fun_data_websocket__rand__lt_genexpr_gt_ + 5,
        .opcodes = fun_data_websocket__rand__lt_genexpr_gt_ + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket__rand__lt_genexpr_gt_ fun_data_websocket__rand__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_websocket__rand[] = {
    (const mp_raw_code_t *)&proto_fun_websocket__rand__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_websocket__rand = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket__rand,
    .children = (void *)&children_websocket__rand,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_websocket__rand + 4,
        .line_info_top = fun_data_websocket__rand + 4,
        .opcodes = fun_data_websocket__rand + 4,
    },
    #endif
    #endif
};

// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket_WebSocketException
static const byte fun_data_websocket_WebSocketException[13] = {
    0x00,0x02, // prelude
    0x06, // names: WebSocketException
     // code info
    0x11,0x48, // LOAD_NAME '__name__'
    0x16,0x49, // STORE_NAME '__module__'
    0x10,0x06, // LOAD_CONST_STRING 'WebSocketException'
    0x16,0x4a, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocketException = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocketException,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_websocket_WebSocketException + 3,
        .line_info_top = fun_data_websocket_WebSocketException + 3,
        .opcodes = fun_data_websocket_WebSocketException + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocketException fun_data_websocket_WebSocketException[0]
#endif

// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket_WebSocketConnectionClosedException
static const byte fun_data_websocket_WebSocketConnectionClosedException[13] = {
    0x00,0x02, // prelude
    0x07, // names: WebSocketConnectionClosedException
     // code info
    0x11,0x48, // LOAD_NAME '__name__'
    0x16,0x49, // STORE_NAME '__module__'
    0x10,0x07, // LOAD_CONST_STRING 'WebSocketConnectionClosedException'
    0x16,0x4a, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocketConnectionClosedException = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocketConnectionClosedException,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 7,
        .line_info = fun_data_websocket_WebSocketConnectionClosedException + 3,
        .line_info_top = fun_data_websocket_WebSocketConnectionClosedException + 3,
        .opcodes = fun_data_websocket_WebSocketConnectionClosedException + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocketConnectionClosedException fun_data_websocket_WebSocketConnectionClosedException[0]
#endif

// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket__split_url
static const byte fun_data_websocket__split_url[109] = {
    0x61,0x04, // prelude
    0x0a,0x4b, // names: _split_url, url
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0b, // LOAD_METHOD 'startswith'
    0x10,0x0c, // LOAD_CONST_STRING 'wss://'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x86, // LOAD_CONST_SMALL_INT 6
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x22,0x83,0x3b, // LOAD_CONST_SMALL_INT 443
    0x5b, // ROT_THREE
    0x5a, // ROT_TWO
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x42,0x61, // JUMP 33
    0xb0, // LOAD_FAST 0
    0x14,0x0b, // LOAD_METHOD 'startswith'
    0x10,0x0d, // LOAD_CONST_STRING 'ws://'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x85, // LOAD_CONST_SMALL_INT 5
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x22,0x80,0x50, // LOAD_CONST_SMALL_INT 80
    0x5b, // ROT_THREE
    0x5a, // ROT_TWO
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x42,0x47, // JUMP 7
    0x12,0x4c, // LOAD_GLOBAL 'ValueError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb2, // LOAD_FAST 2
    0x14,0x0e, // LOAD_METHOD 'partition'
    0x10,0x0f, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xc6, // STORE_FAST 6
    0x10,0x10, // LOAD_CONST_STRING ':'
    0xb4, // LOAD_FAST 4
    0xdd, // BINARY_OP 6 <in>
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xb4, // LOAD_FAST 4
    0x14,0x11, // LOAD_METHOD 'rsplit'
    0x10,0x10, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc4, // STORE_FAST 4
    0xc7, // STORE_FAST 7
    0x12,0x4d, // LOAD_GLOBAL 'int'
    0xb7, // LOAD_FAST 7
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0xb4, // LOAD_FAST 4
    0xb3, // LOAD_FAST 3
    0x10,0x0f, // LOAD_CONST_STRING '/'
    0xb6, // LOAD_FAST 6
    0xf2, // BINARY_OP 27 __add__
    0x2a,0x04, // BUILD_TUPLE 4
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket__split_url = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket__split_url,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 109,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_websocket__split_url + 4,
        .line_info_top = fun_data_websocket__split_url + 4,
        .opcodes = fun_data_websocket__split_url + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket__split_url fun_data_websocket__split_url[0]
#endif

// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket_WebSocket
static const byte fun_data_websocket_WebSocket[77] = {
    0x08,0x02, // prelude
    0x08, // names: WebSocket
     // code info
    0x11,0x48, // LOAD_NAME '__name__'
    0x16,0x49, // STORE_NAME '__module__'
    0x10,0x08, // LOAD_CONST_STRING 'WebSocket'
    0x16,0x4a, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x29, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2c, // STORE_NAME '_read_exact'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x2e, // STORE_NAME 'send_frame'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x33, // STORE_NAME 'send'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x34, // STORE_NAME 'send_binary'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x35, // STORE_NAME 'ping'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x36, // STORE_NAME 'recv_frame'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x38, // STORE_NAME 'recv'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x08, // MAKE_FUNCTION_DEFARGS 8
    0x16,0x26, // STORE_NAME 'close'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x15, // STORE_NAME 'settimeout'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x3a, // STORE_NAME '__enter__'
    0x32,0x0b, // MAKE_FUNCTION 11
    0x16,0x3b, // STORE_NAME '__exit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket___init__
static const byte fun_data_websocket_WebSocket___init__[15] = {
    0x1a,0x06, // prelude
    0x29,0x54,0x2a, // names: __init__, self, sock
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 'sock'
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'connected'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_websocket_WebSocket___init__ + 5,
        .line_info_top = fun_data_websocket_WebSocket___init__ + 5,
        .opcodes = fun_data_websocket_WebSocket___init__ + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket___init__ fun_data_websocket_WebSocket___init__[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket__read_exact
static const byte fun_data_websocket_WebSocket__read_exact[54] = {
    0x42,0x06, // prelude
    0x2c,0x54,0x45, // names: _read_exact, self, n
     // code info
    0x23,0x01, // LOAD_CONST_OBJ 1
    0xc2, // STORE_FAST 2
    0x42,0x61, // JUMP 33
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'sock'
    0x14,0x2d, // LOAD_METHOD 'read'
    0xb1, // LOAD_FAST 1
    0x12,0x55, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xf3, // BINARY_OP 28 __sub__
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'connected'
    0x12,0x07, // LOAD_GLOBAL 'WebSocketConnectionClosedException'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x12,0x55, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xb1, // LOAD_FAST 1
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x16, // POP_JUMP_IF_TRUE -42
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket__read_exact = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket__read_exact,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 54,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_websocket_WebSocket__read_exact + 5,
        .line_info_top = fun_data_websocket_WebSocket__read_exact + 5,
        .opcodes = fun_data_websocket_WebSocket__read_exact + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket__read_exact fun_data_websocket_WebSocket__read_exact[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_send_frame
static const byte fun_data_websocket_WebSocket_send_frame[168] = {
    0xfb,0x01,0x08, // prelude
    0x2e,0x54,0x56,0x57, // names: send_frame, self, opcode, data
     // code info
    0x12,0x51, // LOAD_GLOBAL 'isinstance'
    0xb2, // LOAD_FAST 2
    0x12,0x58, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb2, // LOAD_FAST 2
    0x14,0x24, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x12,0x55, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0x12,0x59, // LOAD_GLOBAL 'bytearray'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xb1, // LOAD_FAST 1
    0xed, // BINARY_OP 22 __or__
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7e, // LOAD_CONST_SMALL_INT 126
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb4, // LOAD_FAST 4
    0x14,0x2f, // LOAD_METHOD 'append'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xb3, // LOAD_FAST 3
    0xed, // BINARY_OP 22 __or__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x74, // JUMP 52
    0xb3, // LOAD_FAST 3
    0x22,0x84,0x80,0x00, // LOAD_CONST_SMALL_INT 65536
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb4, // LOAD_FAST 4
    0x14,0x2f, // LOAD_METHOD 'append'
    0x22,0x81,0x7e, // LOAD_CONST_SMALL_INT 254
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x12,0x05, // LOAD_GLOBAL 'struct'
    0x14,0x30, // LOAD_METHOD 'pack'
    0x10,0x31, // LOAD_CONST_STRING '!H'
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0x42,0x55, // JUMP 21
    0xb4, // LOAD_FAST 4
    0x14,0x2f, // LOAD_METHOD 'append'
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x12,0x05, // LOAD_GLOBAL 'struct'
    0x14,0x30, // LOAD_METHOD 'pack'
    0x10,0x32, // LOAD_CONST_STRING '!Q'
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0x12,0x09, // LOAD_GLOBAL '_rand'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0x12,0x59, // LOAD_GLOBAL 'bytearray'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x50, // JUMP 16
    0x57, // DUP_TOP
    0xc7, // STORE_FAST 7
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb5, // LOAD_FAST 5
    0xb7, // LOAD_FAST 7
    0x83, // LOAD_CONST_SMALL_INT 3
    0xef, // BINARY_OP 24 __and__
    0x55, // LOAD_SUBSCR
    0xe1, // BINARY_OP 10 __ixor__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x2b, // POP_JUMP_IF_TRUE -21
    0x59, // POP_TOP
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'sock'
    0x14,0x23, // LOAD_METHOD 'write'
    0xb4, // LOAD_FAST 4
    0xb6, // LOAD_FAST 6
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_send_frame = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_send_frame,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 168,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_websocket_WebSocket_send_frame + 7,
        .line_info_top = fun_data_websocket_WebSocket_send_frame + 7,
        .opcodes = fun_data_websocket_WebSocket_send_frame + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_send_frame fun_data_websocket_WebSocket_send_frame[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_send
static const byte fun_data_websocket_WebSocket_send[41] = {
    0x32,0x06, // prelude
    0x33,0x54,0x57, // names: send, self, data
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'connected'
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x07, // LOAD_GLOBAL 'WebSocketConnectionClosedException'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x51, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x58, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x12,0x3f, // LOAD_GLOBAL 'OP_TEXT'
    0x42,0x42, // JUMP 2
    0x12,0x40, // LOAD_GLOBAL 'OP_BINARY'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_send = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_send,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 41,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 51,
        .line_info = fun_data_websocket_WebSocket_send + 5,
        .line_info_top = fun_data_websocket_WebSocket_send + 5,
        .opcodes = fun_data_websocket_WebSocket_send + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_send fun_data_websocket_WebSocket_send[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_send_binary
static const byte fun_data_websocket_WebSocket_send_binary[16] = {
    0x2a,0x06, // prelude
    0x34,0x54,0x57, // names: send_binary, self, data
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x40, // LOAD_GLOBAL 'OP_BINARY'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_send_binary = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_send_binary,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_websocket_WebSocket_send_binary + 5,
        .line_info_top = fun_data_websocket_WebSocket_send_binary + 5,
        .opcodes = fun_data_websocket_WebSocket_send_binary + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_send_binary fun_data_websocket_WebSocket_send_binary[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_ping
static const byte fun_data_websocket_WebSocket_ping[17] = {
    0xaa,0x01,0x06, // prelude
    0x35,0x54,0x57, // names: ping, self, data
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x42, // LOAD_GLOBAL 'OP_PING'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_ping = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_ping,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 53,
        .line_info = fun_data_websocket_WebSocket_ping + 6,
        .line_info_top = fun_data_websocket_WebSocket_ping + 6,
        .opcodes = fun_data_websocket_WebSocket_ping + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_ping fun_data_websocket_WebSocket_ping[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_recv_frame
static const byte fun_data_websocket_WebSocket_recv_frame[157] = {
    0x71,0x04, // prelude
    0x36,0x54, // names: recv_frame, self
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_read_exact'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xef, // BINARY_OP 24 __and__
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7e, // LOAD_CONST_SMALL_INT 126
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x05, // LOAD_GLOBAL 'struct'
    0x14,0x37, // LOAD_METHOD 'unpack'
    0x10,0x31, // LOAD_CONST_STRING '!H'
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_read_exact'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0x42,0x5a, // JUMP 26
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x05, // LOAD_GLOBAL 'struct'
    0x14,0x37, // LOAD_METHOD 'unpack'
    0x10,0x32, // LOAD_CONST_STRING '!Q'
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_read_exact'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x36,0x01, // CALL_METHOD 1
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0x42,0x40, // JUMP 0
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xef, // BINARY_OP 24 __and__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_read_exact'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x36,0x01, // CALL_METHOD 1
    0x42,0x41, // JUMP 1
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_read_exact'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x42,0x42, // JUMP 2
    0x23,0x01, // LOAD_CONST_OBJ 1
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0x44,0x67, // POP_JUMP_IF_FALSE 39
    0x12,0x59, // LOAD_GLOBAL 'bytearray'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x50, // JUMP 16
    0x57, // DUP_TOP
    0xc6, // STORE_FAST 6
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb4, // LOAD_FAST 4
    0xb6, // LOAD_FAST 6
    0x83, // LOAD_CONST_SMALL_INT 3
    0xef, // BINARY_OP 24 __and__
    0x55, // LOAD_SUBSCR
    0xe1, // BINARY_OP 10 __ixor__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x2b, // POP_JUMP_IF_TRUE -21
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x12,0x46, // LOAD_GLOBAL 'bytes'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xef, // BINARY_OP 24 __and__
    0xb1, // LOAD_FAST 1
    0x8f, // LOAD_CONST_SMALL_INT 15
    0xef, // BINARY_OP 24 __and__
    0xb5, // LOAD_FAST 5
    0x2a,0x03, // BUILD_TUPLE 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_recv_frame = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_recv_frame,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 157,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 54,
        .line_info = fun_data_websocket_WebSocket_recv_frame + 4,
        .line_info_top = fun_data_websocket_WebSocket_recv_frame + 4,
        .opcodes = fun_data_websocket_WebSocket_recv_frame + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_recv_frame fun_data_websocket_WebSocket_recv_frame[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_recv
static const byte fun_data_websocket_WebSocket_recv[150] = {
    0x65,0x04, // prelude
    0x38,0x54, // names: recv, self
     // code info
    0x51, // LOAD_CONST_NONE
    0x2b,0x00, // BUILD_LIST 0
    0x5a, // ROT_TWO
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x14,0x36, // LOAD_METHOD 'recv_frame'
    0x36,0x00, // CALL_METHOD 0
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc3, // STORE_FAST 3
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0x12,0x42, // LOAD_GLOBAL 'OP_PING'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x43, // LOAD_GLOBAL 'OP_PONG'
    0xb5, // LOAD_FAST 5
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x42,0xeb,0x80, // JUMP 107
    0xb4, // LOAD_FAST 4
    0x12,0x43, // LOAD_GLOBAL 'OP_PONG'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x42,0xe2,0x80, // JUMP 98
    0xb4, // LOAD_FAST 4
    0x12,0x41, // LOAD_GLOBAL 'OP_CLOSE'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x74, // POP_JUMP_IF_FALSE 52
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'connected'
    0x44,0x5c, // POP_JUMP_IF_FALSE 28
    0x48,0x10, // SETUP_EXCEPT 16
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x41, // LOAD_GLOBAL 'OP_CLOSE'
    0xb5, // LOAD_FAST 5
    0x51, // LOAD_CONST_NONE
    0x82, // LOAD_CONST_SMALL_INT 2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x12,0x5a, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'connected'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'sock'
    0x14,0x26, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x12,0x07, // LOAD_GLOBAL 'WebSocketConnectionClosedException'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb4, // LOAD_FAST 4
    0x12,0x3e, // LOAD_GLOBAL 'OP_CONT'
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb4, // LOAD_FAST 4
    0xc1, // STORE_FAST 1
    0xb2, // LOAD_FAST 2
    0x14,0x2f, // LOAD_METHOD 'append'
    0xb5, // LOAD_FAST 5
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x14,0x39, // LOAD_METHOD 'join'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc6, // STORE_FAST 6
    0xb1, // LOAD_FAST 1
    0x12,0x3f, // LOAD_GLOBAL 'OP_TEXT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb6, // LOAD_FAST 6
    0x14,0x20, // LOAD_METHOD 'decode'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0xb6, // LOAD_FAST 6
    0x63, // RETURN_VALUE
    0x42,0xf6,0x7e, // JUMP -138
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_recv = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_recv,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 150,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 56,
        .line_info = fun_data_websocket_WebSocket_recv + 4,
        .line_info_top = fun_data_websocket_WebSocket_recv + 4,
        .opcodes = fun_data_websocket_WebSocket_recv + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_recv fun_data_websocket_WebSocket_recv[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_close
static const byte fun_data_websocket_WebSocket_close[56] = {
    0xc6,0x01,0x06, // prelude
    0x26,0x54,0x5b, // names: close, self, status
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'connected'
    0x44,0x63, // POP_JUMP_IF_FALSE 35
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'connected'
    0x48,0x13, // SETUP_EXCEPT 19
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD 'send_frame'
    0x12,0x41, // LOAD_GLOBAL 'OP_CLOSE'
    0x12,0x05, // LOAD_GLOBAL 'struct'
    0x14,0x30, // LOAD_METHOD 'pack'
    0x10,0x31, // LOAD_CONST_STRING '!H'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x12,0x5a, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'sock'
    0x14,0x26, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 56,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 38,
        .line_info = fun_data_websocket_WebSocket_close + 6,
        .line_info_top = fun_data_websocket_WebSocket_close + 6,
        .opcodes = fun_data_websocket_WebSocket_close + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_close fun_data_websocket_WebSocket_close[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket_settimeout
static const byte fun_data_websocket_WebSocket_settimeout[16] = {
    0x22,0x06, // prelude
    0x15,0x54,0x5c, // names: settimeout, self, t
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'sock'
    0x14,0x15, // LOAD_METHOD 'settimeout'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket_settimeout = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket_settimeout,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 21,
        .line_info = fun_data_websocket_WebSocket_settimeout + 5,
        .line_info_top = fun_data_websocket_WebSocket_settimeout + 5,
        .opcodes = fun_data_websocket_WebSocket_settimeout + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket_settimeout fun_data_websocket_WebSocket_settimeout[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket___enter__
static const byte fun_data_websocket_WebSocket___enter__[6] = {
    0x09,0x04, // prelude
    0x3a,0x54, // names: __enter__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket___enter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket___enter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 6,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_websocket_WebSocket___enter__ + 4,
        .line_info_top = fun_data_websocket_WebSocket___enter__ + 4,
        .opcodes = fun_data_websocket_WebSocket___enter__ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket___enter__ fun_data_websocket_WebSocket___enter__[0]
#endif

// child of websocket_WebSocket
// frozen bytecode for file websocket.py, scope websocket_WebSocket___exit__
static const byte fun_data_websocket_WebSocket___exit__[15] = {
    0x99,0x80,0x80,0x40,0x04, // prelude
    0x3b,0x54, // names: __exit__, self
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x26, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket___exit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket___exit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 59,
        .line_info = fun_data_websocket_WebSocket___exit__ + 7,
        .line_info_top = fun_data_websocket_WebSocket___exit__ + 7,
        .opcodes = fun_data_websocket_WebSocket___exit__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_WebSocket___exit__ fun_data_websocket_WebSocket___exit__[0]
#endif

static const mp_raw_code_t *const children_websocket_WebSocket[] = {
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket___init__,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket__read_exact,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_send_frame,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_send,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_send_binary,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_ping,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_recv_frame,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_recv,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_close,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket_settimeout,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket___enter__,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket___exit__,
};

static const mp_raw_code_truncated_t proto_fun_websocket_WebSocket = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_WebSocket,
    .children = (void *)&children_websocket_WebSocket,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 77,
    .n_children = 12,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_websocket_WebSocket + 3,
        .line_info_top = fun_data_websocket_WebSocket + 3,
        .opcodes = fun_data_websocket_WebSocket + 3,
    },
    #endif
    #endif
};

// child of websocket__lt_module_gt_
// frozen bytecode for file websocket.py, scope websocket_create_connection
static const byte fun_data_websocket_create_connection[251] = {
    0xb4,0x95,0x01,0x0a, // prelude
    0x12,0x4b,0x4e,0x4f,0x50, // names: create_connection, url, timeout, header, verify
     // code info
    0x12,0x0a, // LOAD_GLOBAL '_split_url'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x30,0x04, // UNPACK_SEQUENCE 4
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xc6, // STORE_FAST 6
    0xc7, // STORE_FAST 7
    0x12,0x04, // LOAD_GLOBAL 'socket'
    0x14,0x13, // LOAD_METHOD 'getaddrinfo'
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0x12,0x04, // LOAD_GLOBAL 'socket'
    0x13,0x14, // LOAD_ATTR 'SOCK_STREAM'
    0x36,0x04, // CALL_METHOD 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0x12,0x04, // LOAD_GLOBAL 'socket'
    0x14,0x04, // LOAD_METHOD 'socket'
    0xb8, // LOAD_FAST 8
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x12,0x04, // LOAD_GLOBAL 'socket'
    0x13,0x14, // LOAD_ATTR 'SOCK_STREAM'
    0xb8, // LOAD_FAST 8
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x36,0x03, // CALL_METHOD 3
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x14,0x15, // LOAD_METHOD 'settimeout'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x48,0xad,0x01, // SETUP_EXCEPT 173
    0xb9, // LOAD_FAST 9
    0x14,0x16, // LOAD_METHOD 'connect'
    0xb8, // LOAD_FAST 8
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x44,0x62, // POP_JUMP_IF_FALSE 34
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x17, // IMPORT_NAME 'tls'
    0xca, // STORE_FAST 10
    0xba, // LOAD_FAST 10
    0x14,0x18, // LOAD_METHOD 'SSLContext'
    0xba, // LOAD_FAST 10
    0x13,0x19, // LOAD_ATTR 'PROTOCOL_TLS_CLIENT'
    0x36,0x01, // CALL_METHOD 1
    0xcb, // STORE_FAST 11
    0xb3, // LOAD_FAST 3
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0xba, // LOAD_FAST 10
    0x13,0x1a, // LOAD_ATTR 'CERT_NONE'
    0xbb, // LOAD_FAST 11
    0x18,0x1b, // STORE_ATTR 'verify_mode'
    0xbb, // LOAD_FAST 11
    0x14,0x1c, // LOAD_METHOD 'wrap_socket'
    0xb9, // LOAD_FAST 9
    0x10,0x1d, // LOAD_CONST_STRING 'server_hostname'
    0xb5, // LOAD_FAST 5
    0x36,0x82,0x01, // CALL_METHOD 257
    0xc9, // STORE_FAST 9
    0x12,0x02, // LOAD_GLOBAL 'binascii'
    0x14,0x1e, // LOAD_METHOD 'b2a_base64'
    0x12,0x09, // LOAD_GLOBAL '_rand'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x14,0x1f, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0xcc, // STORE_FAST 12
    0x23,0x02, // LOAD_CONST_OBJ 2
    0xb7, // LOAD_FAST 7
    0xb5, // LOAD_FAST 5
    0xbc, // LOAD_FAST 12
    0x14,0x20, // LOAD_METHOD 'decode'
    0x36,0x00, // CALL_METHOD 0
    0x2a,0x03, // BUILD_TUPLE 3
    0xf8, // BINARY_OP 33 __mod__
    0xcd, // STORE_FAST 13
    0x12,0x51, // LOAD_GLOBAL 'isinstance'
    0xb2, // LOAD_FAST 2
    0x12,0x52, // LOAD_GLOBAL 'dict'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x32,0x00, // MAKE_FUNCTION 0
    0xb2, // LOAD_FAST 2
    0x14,0x21, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x45,0x02, // JUMP_IF_TRUE_OR_POP 2
    0x2a,0x00, // BUILD_TUPLE 0
    0x5f, // GET_ITER_STACK
    0x4b,0x0a, // FOR_ITER 10
    0xce, // STORE_FAST 14
    0xbd, // LOAD_FAST 13
    0xbe, // LOAD_FAST 14
    0x10,0x22, // LOAD_CONST_STRING '\r\n'
    0xf2, // BINARY_OP 27 __add__
    0xe5, // BINARY_OP 14 __iadd__
    0xcd, // STORE_FAST 13
    0x42,0x34, // JUMP -12
    0xb9, // LOAD_FAST 9
    0x14,0x23, // LOAD_METHOD 'write'
    0xbd, // LOAD_FAST 13
    0x10,0x22, // LOAD_CONST_STRING '\r\n'
    0xf2, // BINARY_OP 27 __add__
    0x14,0x24, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb9, // LOAD_FAST 9
    0x14,0x25, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0xcf, // STORE_FAST 15
    0xbf, // LOAD_FAST 15
    0x14,0x0b, // LOAD_METHOD 'startswith'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x36,0x01, // CALL_METHOD 1
    0x43,0x51, // POP_JUMP_IF_TRUE 17
    0x12,0x06, // LOAD_GLOBAL 'WebSocketException'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xbf, // LOAD_FAST 15
    0x14,0x20, // LOAD_METHOD 'decode'
    0x36,0x00, // CALL_METHOD 0
    0x14,0x1f, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x40, // JUMP 0
    0xb9, // LOAD_FAST 9
    0x14,0x25, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x23,0x05, // LOAD_CONST_OBJ 5
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x43,0x35, // POP_JUMP_IF_TRUE -11
    0x4a,0x09, // POP_EXCEPT_JUMP 9
    0x59, // POP_TOP
    0xb9, // LOAD_FAST 9
    0x14,0x26, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x64, // RAISE_LAST
    0x5d, // END_FINALLY
    0x12,0x08, // LOAD_GLOBAL 'WebSocket'
    0xb9, // LOAD_FAST 9
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
// child of websocket_create_connection
// frozen bytecode for file websocket.py, scope websocket_create_connection__lt_listcomp_gt_
static const byte fun_data_websocket_create_connection__lt_listcomp_gt_[20] = {
    0x41,0x04, // prelude
    0x3c,0x53, // names: <listcomp>, *
     // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x09, // FOR_ITER 9
    0xc1, // STORE_FAST 1
    0x10,0x3d, // LOAD_CONST_STRING '%s: %s'
    0xb1, // LOAD_FAST 1
    0xf8, // BINARY_OP 33 __mod__
    0x2f,0x14, // STORE_COMP 20
    0x42,0x35, // JUMP -11
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_websocket_create_connection__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_create_connection__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 60,
        .line_info = fun_data_websocket_create_connection__lt_listcomp_gt_ + 4,
        .line_info_top = fun_data_websocket_create_connection__lt_listcomp_gt_ + 4,
        .opcodes = fun_data_websocket_create_connection__lt_listcomp_gt_ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_websocket_create_connection__lt_listcomp_gt_ fun_data_websocket_create_connection__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_websocket_create_connection[] = {
    (const mp_raw_code_t *)&proto_fun_websocket_create_connection__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_websocket_create_connection = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket_create_connection,
    .children = (void *)&children_websocket_create_connection,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 251,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 23,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_websocket_create_connection + 9,
        .line_info_top = fun_data_websocket_create_connection + 9,
        .opcodes = fun_data_websocket_create_connection + 9,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_websocket__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_websocket__rand,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocketException,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocketConnectionClosedException,
    (const mp_raw_code_t *)&proto_fun_websocket__split_url,
    (const mp_raw_code_t *)&proto_fun_websocket_WebSocket,
    (const mp_raw_code_t *)&proto_fun_websocket_create_connection,
};

static const mp_raw_code_truncated_t proto_fun_websocket__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_websocket__lt_module_gt_,
    .children = (void *)&children_websocket__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 96,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_websocket__lt_module_gt_ + 3,
        .line_info_top = fun_data_websocket__lt_module_gt_ + 3,
        .opcodes = fun_data_websocket__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_websocket[93] = {
    MP_QSTR_websocket_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_binascii,
    MP_QSTR_random,
    MP_QSTR_socket,
    MP_QSTR_struct,
    MP_QSTR_WebSocketException,
    MP_QSTR_WebSocketConnectionClosedException,
    MP_QSTR_WebSocket,
    MP_QSTR__rand,
    MP_QSTR__split_url,
    MP_QSTR_startswith,
    MP_QSTR_wss_colon__slash__slash_,
    MP_QSTR_ws_colon__slash__slash_,
    MP_QSTR_partition,
    MP_QSTR__slash_,
    MP_QSTR__colon_,
    MP_QSTR_rsplit,
    MP_QSTR_create_connection,
    MP_QSTR_getaddrinfo,
    MP_QSTR_SOCK_STREAM,
    MP_QSTR_settimeout,
    MP_QSTR_connect,
    MP_QSTR_tls,
    MP_QSTR_SSLContext,
    MP_QSTR_PROTOCOL_TLS_CLIENT,
    MP_QSTR_CERT_NONE,
    MP_QSTR_verify_mode,
    MP_QSTR_wrap_socket,
    MP_QSTR_server_hostname,
    MP_QSTR_b2a_base64,
    MP_QSTR_strip,
    MP_QSTR_decode,
    MP_QSTR_items,
    MP_QSTR__0x0d__0x0a_,
    MP_QSTR_write,
    MP_QSTR_encode,
    MP_QSTR_readline,
    MP_QSTR_close,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR_getrandbits,
    MP_QSTR___init__,
    MP_QSTR_sock,
    MP_QSTR_connected,
    MP_QSTR__read_exact,
    MP_QSTR_read,
    MP_QSTR_send_frame,
    MP_QSTR_append,
    MP_QSTR_pack,
    MP_QSTR__bang_H,
    MP_QSTR__bang_Q,
    MP_QSTR_send,
    MP_QSTR_send_binary,
    MP_QSTR_ping,
    MP_QSTR_recv_frame,
    MP_QSTR_unpack,
    MP_QSTR_recv,
    MP_QSTR_join,
    MP_QSTR___enter__,
    MP_QSTR___exit__,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR__percent_s_colon__space__percent_s,
    MP_QSTR_OP_CONT,
    MP_QSTR_OP_TEXT,
    MP_QSTR_OP_BINARY,
    MP_QSTR_OP_CLOSE,
    MP_QSTR_OP_PING,
    MP_QSTR_OP_PONG,
    MP_QSTR_Exception,
    MP_QSTR_n,
    MP_QSTR_bytes,
    MP_QSTR_range,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_url,
    MP_QSTR_ValueError,
    MP_QSTR_int,
    MP_QSTR_timeout,
    MP_QSTR_header,
    MP_QSTR_verify,
    MP_QSTR_isinstance,
    MP_QSTR_dict,
    MP_QSTR__star_,
    MP_QSTR_self,
    MP_QSTR_len,
    MP_QSTR_opcode,
    MP_QSTR_data,
    MP_QSTR_str,
    MP_QSTR_bytearray,
    MP_QSTR_OSError,
    MP_QSTR_status,
    MP_QSTR_t,
};

// constants
static const mp_obj_str_t const_obj_websocket_0 = {{&mp_type_str}, 39869, 35, (const byte*)"\x75\x72\x6c\x20\x6d\x75\x73\x74\x20\x73\x74\x61\x72\x74\x20\x77\x69\x74\x68\x20\x77\x73\x3a\x2f\x2f\x20\x6f\x72\x20\x77\x73\x73\x3a\x2f\x2f"};
static const mp_obj_str_t const_obj_websocket_2 = {{&mp_type_str}, 44426, 118, (const byte*)"\x47\x45\x54\x20\x25\x73\x20\x48\x54\x54\x50\x2f\x31\x2e\x31\x0d\x0a\x48\x6f\x73\x74\x3a\x20\x25\x73\x0d\x0a\x55\x70\x67\x72\x61\x64\x65\x3a\x20\x77\x65\x62\x73\x6f\x63\x6b\x65\x74\x0d\x0a\x43\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x3a\x20\x55\x70\x67\x72\x61\x64\x65\x0d\x0a\x53\x65\x63\x2d\x57\x65\x62\x53\x6f\x63\x6b\x65\x74\x2d\x4b\x65\x79\x3a\x20\x25\x73\x0d\x0a\x53\x65\x63\x2d\x57\x65\x62\x53\x6f\x63\x6b\x65\x74\x2d\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x31\x33\x0d\x0a"};
static const mp_obj_str_t const_obj_websocket_3 = {{&mp_type_bytes}, 50348, 12, (const byte*)"\x48\x54\x54\x50\x2f\x31\x2e\x31\x20\x31\x30\x31"};
static const mp_obj_str_t const_obj_websocket_5_0 = {{&mp_type_bytes}, 27298, 2, (const byte*)"\x0d\x0a"};
static const mp_rom_obj_tuple_t const_obj_websocket_5 = {{&mp_type_tuple}, 2, {
    MP_ROM_PTR(&const_obj_websocket_5_0),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
}};

// constant table
static const mp_rom_obj_t const_obj_table_data_websocket[8] = {
    MP_ROM_PTR(&const_obj_websocket_0),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_websocket_2),
    MP_ROM_PTR(&const_obj_websocket_3),
    MP_ROM_QSTR(MP_QSTR_handshake_space_failed_colon__space_),
    MP_ROM_PTR(&const_obj_websocket_5),
    MP_ROM_QSTR(MP_QSTR_connection_space_closed),
    MP_ROM_QSTR(MP_QSTR_closed_space_by_space_the_space_server),
};

static const mp_frozen_module_t frozen_module_websocket = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_websocket,
        .obj_table = (mp_obj_t *)&const_obj_table_data_websocket,
    },
    .proto_fun = &proto_fun_websocket__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module upip
// - original source file: build/frozen_mpy/upip.mpy
// - frozen file name: upip.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file upip.py, scope upip__lt_module_gt_
static const byte fun_data_upip__lt_module_gt_[93] = {
    0x08,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'json'
    0x16,0x02, // STORE_NAME 'json'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'os'
    0x16,0x03, // STORE_NAME 'os'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x04, // IMPORT_NAME 'sys'
    0x16,0x04, // STORE_NAME 'sys'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x05, // IMPORT_NAME 'tdsh'
    0x16,0x05, // STORE_NAME 'tdsh'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x06, // STORE_NAME '_isdir'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x08, // STORE_NAME '_exists'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x09, // STORE_NAME 'place'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x12, // STORE_NAME '_load'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x16, // STORE_NAME '_save'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x19, // STORE_NAME '_files'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x1b, // STORE_NAME '_requirements'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x1c, // STORE_NAME '_names'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x1e, // STORE_NAME 'install'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x2b, // STORE_NAME 'uninstall'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x32, // STORE_NAME 'listing'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0b, // MAKE_FUNCTION_DEFARGS 11
    0x16,0x34, // STORE_NAME 'freeze'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x16,0x44, // STORE_NAME 'USAGE'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0c, // MAKE_FUNCTION_DEFARGS 12
    0x16,0x39, // STORE_NAME 'main'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__isdir
static const byte fun_data_upip__isdir[35] = {
    0x35,0x04, // prelude
    0x06,0x45, // names: _isdir, path
     // code info
    0x48,0x11, // SETUP_EXCEPT 17
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x07, // LOAD_METHOD 'stat'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x22,0x81,0x80,0x00, // LOAD_CONST_SMALL_INT 16384
    0xef, // BINARY_OP 24 __and__
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__isdir = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__isdir,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 35,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_upip__isdir + 4,
        .line_info_top = fun_data_upip__isdir + 4,
        .opcodes = fun_data_upip__isdir + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__isdir fun_data_upip__isdir[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__exists
static const byte fun_data_upip__exists[28] = {
    0x35,0x04, // prelude
    0x08,0x45, // names: _exists, path
     // code info
    0x48,0x0a, // SETUP_EXCEPT 10
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x07, // LOAD_METHOD 'stat'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__exists = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__exists,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_upip__exists + 4,
        .line_info_top = fun_data_upip__exists + 4,
        .opcodes = fun_data_upip__exists + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__exists fun_data_upip__exists[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_place
static const byte fun_data_upip_place[70] = {
    0x38,0x02, // prelude
    0x09, // names: place
     // code info
    0x12,0x05, // LOAD_GLOBAL 'tdsh'
    0x14,0x0a, // LOAD_METHOD 'getvar'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x36,0x01, // CALL_METHOD 1
    0xc0, // STORE_FAST 0
    0xb0, // LOAD_FAST 0
    0x44,0x55, // POP_JUMP_IF_FALSE 21
    0xb0, // LOAD_FAST 0
    0x10,0x0b, // LOAD_CONST_STRING '/lib'
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x10,0x0c, // LOAD_CONST_STRING '/venv.json'
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x14,0x0d, // LOAD_METHOD 'rsplit'
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x2a,0x03, // BUILD_TUPLE 3
    0x63, // RETURN_VALUE
    0x12,0x05, // LOAD_GLOBAL 'tdsh'
    0x14,0x0f, // LOAD_METHOD 'user'
    0x36,0x00, // CALL_METHOD 0
    0x10,0x10, // LOAD_CONST_STRING 'root'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x10,0x0b, // LOAD_CONST_STRING '/lib'
    0x42,0x49, // JUMP 9
    0x12,0x05, // LOAD_GLOBAL 'tdsh'
    0x14,0x11, // LOAD_METHOD 'home'
    0x36,0x00, // CALL_METHOD 0
    0x10,0x0b, // LOAD_CONST_STRING '/lib'
    0xf2, // BINARY_OP 27 __add__
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0xb1, // LOAD_FAST 1
    0x23,0x02, // LOAD_CONST_OBJ 2
    0xf2, // BINARY_OP 27 __add__
    0x51, // LOAD_CONST_NONE
    0x2a,0x03, // BUILD_TUPLE 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_place = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_place,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 70,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_upip_place + 3,
        .line_info_top = fun_data_upip_place + 3,
        .opcodes = fun_data_upip_place + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_place fun_data_upip_place[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__load
static const byte fun_data_upip__load[57] = {
    0xc9,0x02,0x04, // prelude
    0x12,0x47, // names: _load, record
     // code info
    0x48,0x15, // SETUP_EXCEPT 21
    0x12,0x48, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x47,0x0a, // SETUP_WITH 10
    0xc1, // STORE_FAST 1
    0x12,0x02, // LOAD_GLOBAL 'json'
    0x14,0x13, // LOAD_METHOD 'load'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x4a,0x11, // POP_EXCEPT_JUMP 17
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0x12,0x49, // LOAD_GLOBAL 'ValueError'
    0x2a,0x02, // BUILD_TUPLE 2
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x59, // POP_TOP
    0x2c,0x00, // BUILD_MAP 0
    0xc2, // STORE_FAST 2
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb2, // LOAD_FAST 2
    0x14,0x14, // LOAD_METHOD 'setdefault'
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x2c,0x00, // BUILD_MAP 0
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__load = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__load,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 57,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_upip__load + 5,
        .line_info_top = fun_data_upip__load + 5,
        .opcodes = fun_data_upip__load + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__load fun_data_upip__load[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__save
static const byte fun_data_upip__save[29] = {
    0x46,0x06, // prelude
    0x16,0x47,0x4a, // names: _save, record, data
     // code info
    0x12,0x48, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x17, // LOAD_CONST_STRING 'w'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x0b, // SETUP_WITH 11
    0xc2, // STORE_FAST 2
    0x12,0x02, // LOAD_GLOBAL 'json'
    0x14,0x18, // LOAD_METHOD 'dump'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__save = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__save,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 29,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 22,
        .line_info = fun_data_upip__save + 5,
        .line_info_top = fun_data_upip__save + 5,
        .opcodes = fun_data_upip__save + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__save fun_data_upip__save[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__files
static const byte fun_data_upip__files[42] = {
    0x29,0x85,0x01, // prelude
    0x19,0x4b, // names: _files, top
    0x00,0x01,0x02, // code info
    0x2b,0x00, // BUILD_LIST 0
    0x27,0x01, // STORE_DEREF 1
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x20,0x00,0x03, // MAKE_CLOSURE 0
    0x27,0x02, // STORE_DEREF 2
    0x12,0x06, // LOAD_GLOBAL '_isdir'
    0x25,0x00, // LOAD_DEREF 0
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x25,0x02, // LOAD_DEREF 2
    0x10,0x1a, // LOAD_CONST_STRING ''
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x4c, // LOAD_GLOBAL 'set'
    0x25,0x01, // LOAD_DEREF 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
// child of upip__files
// frozen bytecode for file upip.py, scope upip__files_walk
static const byte fun_data_upip__files_walk[79] = {
    0xe8,0x04,0x0a, // prelude
    0x3d,0x52,0x52,0x52,0x53, // names: walk, *, *, *, rel
     // code info
    0x25,0x00, // LOAD_DEREF 0
    0xb3, // LOAD_FAST 3
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xb3, // LOAD_FAST 3
    0xf2, // BINARY_OP 27 __add__
    0x42,0x42, // JUMP 2
    0x10,0x1a, // LOAD_CONST_STRING ''
    0xf2, // BINARY_OP 27 __add__
    0xc4, // STORE_FAST 4
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x3e, // LOAD_METHOD 'listdir'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0x5f, // GET_ITER_STACK
    0x4b,0x2c, // FOR_ITER 44
    0xc5, // STORE_FAST 5
    0xb3, // LOAD_FAST 3
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb3, // LOAD_FAST 3
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0x42,0x41, // JUMP 1
    0xb5, // LOAD_FAST 5
    0xc6, // STORE_FAST 6
    0x12,0x06, // LOAD_GLOBAL '_isdir'
    0xb4, // LOAD_FAST 4
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x25,0x02, // LOAD_DEREF 2
    0xb6, // LOAD_FAST 6
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x48, // JUMP 8
    0x25,0x01, // LOAD_DEREF 1
    0x14,0x3f, // LOAD_METHOD 'append'
    0xb6, // LOAD_FAST 6
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x12, // JUMP -46
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__files_walk = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__files_walk,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 79,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 61,
        .line_info = fun_data_upip__files_walk + 8,
        .line_info_top = fun_data_upip__files_walk + 8,
        .opcodes = fun_data_upip__files_walk + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__files_walk fun_data_upip__files_walk[0]
#endif

static const mp_raw_code_t *const children_upip__files[] = {
    (const mp_raw_code_t *)&proto_fun_upip__files_walk,
};

static const mp_raw_code_truncated_t proto_fun_upip__files = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__files,
    .children = (void *)&children_upip__files,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 42,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 25,
        .line_info = fun_data_upip__files + 5,
        .line_info_top = fun_data_upip__files + 5,
        .opcodes = fun_data_upip__files + 8,
    },
    #endif
    #endif
};

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__requirements
static const byte fun_data_upip__requirements[22] = {
    0x35,0x04, // prelude
    0x1b,0x45, // names: _requirements, path
     // code info
    0x12,0x48, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x47,0x07, // SETUP_WITH 7
    0xc1, // STORE_FAST 1
    0x32,0x00, // MAKE_FUNCTION 0
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of upip__requirements
// frozen bytecode for file upip.py, scope upip__requirements__lt_listcomp_gt_
static const byte fun_data_upip__requirements__lt_listcomp_gt_[44] = {
    0x49,0x04, // prelude
    0x40,0x52, // names: <listcomp>, *
     // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x21, // FOR_ITER 33
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x41, // LOAD_METHOD 'split'
    0x10,0x42, // LOAD_CONST_STRING '#'
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x14,0x43, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x2e, // POP_JUMP_IF_FALSE -18
    0xb1, // LOAD_FAST 1
    0x14,0x41, // LOAD_METHOD 'split'
    0x10,0x42, // LOAD_CONST_STRING '#'
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x14,0x43, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0x2f,0x14, // STORE_COMP 20
    0x42,0x1d, // JUMP -35
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__requirements__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__requirements__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 44,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_upip__requirements__lt_listcomp_gt_ + 4,
        .line_info_top = fun_data_upip__requirements__lt_listcomp_gt_ + 4,
        .opcodes = fun_data_upip__requirements__lt_listcomp_gt_ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__requirements__lt_listcomp_gt_ fun_data_upip__requirements__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_upip__requirements[] = {
    (const mp_raw_code_t *)&proto_fun_upip__requirements__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_upip__requirements = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__requirements,
    .children = (void *)&children_upip__requirements,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 27,
        .line_info = fun_data_upip__requirements + 4,
        .line_info_top = fun_data_upip__requirements + 4,
        .opcodes = fun_data_upip__requirements + 4,
    },
    #endif
    #endif
};

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip__names
static const byte fun_data_upip__names[43] = {
    0x19,0x04, // prelude
    0x1c,0x4d, // names: _names, args
     // code info
    0xb0, // LOAD_FAST 0
    0x51, // LOAD_CONST_NONE
    0x81, // LOAD_CONST_SMALL_INT 1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x10,0x1d, // LOAD_CONST_STRING '-r'
    0x2b,0x01, // BUILD_LIST 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0x12,0x4e, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x49, // LOAD_GLOBAL 'ValueError'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x1b, // LOAD_GLOBAL '_requirements'
    0xb0, // LOAD_FAST 0
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip__names = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__names,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 43,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 28,
        .line_info = fun_data_upip__names + 4,
        .line_info_top = fun_data_upip__names + 4,
        .opcodes = fun_data_upip__names + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip__names fun_data_upip__names[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_install
static const byte fun_data_upip_install[211] = {
    0xdd,0x10,0x04, // prelude
    0x1e,0x15, // names: install, packages
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x1f, // IMPORT_NAME 'mip'
    0xc1, // STORE_FAST 1
    0x12,0x09, // LOAD_GLOBAL 'place'
    0x34,0x00, // CALL_FUNCTION 0
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0xc4, // STORE_FAST 4
    0x12,0x06, // LOAD_GLOBAL '_isdir'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x20, // LOAD_METHOD 'mkdir'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x12, // LOAD_GLOBAL '_load'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0x52, // LOAD_CONST_TRUE
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x9d,0x01, // FOR_ITER 157
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x14,0x21, // LOAD_METHOD 'partition'
    0x10,0x22, // LOAD_CONST_STRING '@'
    0x36,0x01, // CALL_METHOD 1
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc8, // STORE_FAST 8
    0xc4, // STORE_FAST 4
    0xc9, // STORE_FAST 9
    0x12,0x19, // LOAD_GLOBAL '_files'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xca, // STORE_FAST 10
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x23, // LOAD_METHOD 'getcwd'
    0x36,0x00, // CALL_METHOD 0
    0xcb, // STORE_FAST 11
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x24, // LOAD_METHOD 'chdir'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x49,0x13, // SETUP_FINALLY 19
    0xb1, // LOAD_FAST 1
    0x14,0x1e, // LOAD_METHOD 'install'
    0xb8, // LOAD_FAST 8
    0x10,0x25, // LOAD_CONST_STRING 'target'
    0x10,0x26, // LOAD_CONST_STRING '.'
    0x10,0x27, // LOAD_CONST_STRING 'version'
    0xb9, // LOAD_FAST 9
    0x45,0x01, // JUMP_IF_TRUE_OR_POP 1
    0x51, // LOAD_CONST_NONE
    0x36,0x84,0x01, // CALL_METHOD 513
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x24, // LOAD_METHOD 'chdir'
    0xbb, // LOAD_FAST 11
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x5d, // END_FINALLY
    0x12,0x4f, // LOAD_GLOBAL 'sorted'
    0x12,0x19, // LOAD_GLOBAL '_files'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xba, // LOAD_FAST 10
    0xf3, // BINARY_OP 28 __sub__
    0x34,0x01, // CALL_FUNCTION 1
    0xcc, // STORE_FAST 12
    0xbc, // LOAD_FAST 12
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xb7, // LOAD_FAST 7
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0xc6, // STORE_FAST 6
    0x42,0xa0,0x7f, // JUMP -96
    0xb5, // LOAD_FAST 5
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0x14,0x28, // LOAD_METHOD 'get'
    0xb8, // LOAD_FAST 8
    0x2c,0x00, // BUILD_MAP 0
    0x36,0x02, // CALL_METHOD 2
    0x14,0x28, // LOAD_METHOD 'get'
    0x10,0x29, // LOAD_CONST_STRING 'files'
    0x2b,0x00, // BUILD_LIST 0
    0x36,0x02, // CALL_METHOD 2
    0xcd, // STORE_FAST 13
    0x2c,0x02, // BUILD_MAP 2
    0xb9, // LOAD_FAST 9
    0x45,0x02, // JUMP_IF_TRUE_OR_POP 2
    0x10,0x2a, // LOAD_CONST_STRING 'latest'
    0x10,0x27, // LOAD_CONST_STRING 'version'
    0x62, // STORE_MAP
    0x12,0x4f, // LOAD_GLOBAL 'sorted'
    0x12,0x4c, // LOAD_GLOBAL 'set'
    0xbd, // LOAD_FAST 13
    0x34,0x01, // CALL_FUNCTION 1
    0x12,0x4c, // LOAD_GLOBAL 'set'
    0xbc, // LOAD_FAST 12
    0x34,0x01, // CALL_FUNCTION 1
    0xed, // BINARY_OP 22 __or__
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x29, // LOAD_CONST_STRING 'files'
    0x62, // STORE_MAP
    0xb5, // LOAD_FAST 5
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0xb8, // LOAD_FAST 8
    0x56, // STORE_SUBSCR
    0x12,0x16, // LOAD_GLOBAL '_save'
    0xb3, // LOAD_FAST 3
    0xb5, // LOAD_FAST 5
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x42,0xe0,0x7e, // JUMP -160
    0xb6, // LOAD_FAST 6
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_install = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_install,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 211,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 28,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 30,
        .line_info = fun_data_upip_install + 5,
        .line_info_top = fun_data_upip_install + 5,
        .opcodes = fun_data_upip_install + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_install fun_data_upip_install[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_uninstall
static const byte fun_data_upip_uninstall[217] = {
    0xc5,0x10,0x04, // prelude
    0x2b,0x15, // names: uninstall, packages
     // code info
    0x12,0x09, // LOAD_GLOBAL 'place'
    0x34,0x00, // CALL_FUNCTION 0
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x12,0x12, // LOAD_GLOBAL '_load'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xc4, // STORE_FAST 4
    0x52, // LOAD_CONST_TRUE
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0xb0,0x01, // FOR_ITER 176
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x14,0x21, // LOAD_METHOD 'partition'
    0x10,0x22, // LOAD_CONST_STRING '@'
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc6, // STORE_FAST 6
    0xb4, // LOAD_FAST 4
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0x14,0x2c, // LOAD_METHOD 'pop'
    0xb6, // LOAD_FAST 6
    0x51, // LOAD_CONST_NONE
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0xb6, // LOAD_FAST 6
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0xc5, // STORE_FAST 5
    0x42,0x15, // JUMP -43
    0x12,0x4c, // LOAD_GLOBAL 'set'
    0x34,0x00, // CALL_FUNCTION 0
    0xc8, // STORE_FAST 8
    0xb7, // LOAD_FAST 7
    0x10,0x29, // LOAD_CONST_STRING 'files'
    0x55, // LOAD_SUBSCR
    0x5f, // GET_ITER_STACK
    0x4b,0x38, // FOR_ITER 56
    0xc9, // STORE_FAST 9
    0x48,0x0f, // SETUP_EXCEPT 15
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x2d, // LOAD_METHOD 'remove'
    0xb1, // LOAD_FAST 1
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb9, // LOAD_FAST 9
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x42,0x52, // JUMP 18
    0xb9, // LOAD_FAST 9
    0x14,0x0d, // LOAD_METHOD 'rsplit'
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc9, // STORE_FAST 9
    0xb8, // LOAD_FAST 8
    0x14,0x2e, // LOAD_METHOD 'add'
    0xb9, // LOAD_FAST 9
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xb9, // LOAD_FAST 9
    0xdd, // BINARY_OP 6 <in>
    0x43,0x28, // POP_JUMP_IF_TRUE -24
    0x42,0x06, // JUMP -58
    0x12,0x4f, // LOAD_GLOBAL 'sorted'
    0xb8, // LOAD_FAST 8
    0x10,0x2f, // LOAD_CONST_STRING 'key'
    0x12,0x4e, // LOAD_GLOBAL 'len'
    0x10,0x30, // LOAD_CONST_STRING 'reverse'
    0x52, // LOAD_CONST_TRUE
    0x34,0x84,0x01, // CALL_FUNCTION 513
    0x5f, // GET_ITER_STACK
    0x4b,0x1e, // FOR_ITER 30
    0xca, // STORE_FAST 10
    0x48,0x0f, // SETUP_EXCEPT 15
    0x12,0x03, // LOAD_GLOBAL 'os'
    0x14,0x31, // LOAD_METHOD 'rmdir'
    0xb1, // LOAD_FAST 1
    0x10,0x0e, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xba, // LOAD_FAST 10
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x42,0x20, // JUMP -32
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xb6, // LOAD_FAST 6
    0x12,0x4e, // LOAD_GLOBAL 'len'
    0xb7, // LOAD_FAST 7
    0x10,0x29, // LOAD_CONST_STRING 'files'
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0xcd,0x7e, // JUMP -179
    0x12,0x16, // LOAD_GLOBAL '_save'
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_uninstall = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_uninstall,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 217,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 25,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 43,
        .line_info = fun_data_upip_uninstall + 5,
        .line_info_top = fun_data_upip_uninstall + 5,
        .opcodes = fun_data_upip_uninstall + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_uninstall fun_data_upip_uninstall[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_listing
static const byte fun_data_upip_listing[100] = {
    0x80,0x10,0x02, // prelude
    0x32, // names: listing
     // code info
    0x12,0x09, // LOAD_GLOBAL 'place'
    0x34,0x00, // CALL_FUNCTION 0
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc0, // STORE_FAST 0
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0x12,0x12, // LOAD_GLOBAL '_load'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x10,0x33, // LOAD_CONST_STRING '%s (%s):'
    0xb0, // LOAD_FAST 0
    0xb2, // LOAD_FAST 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x23,0x07, // LOAD_CONST_OBJ 7
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0x42,0x42, // JUMP 2
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x4f, // LOAD_GLOBAL 'sorted'
    0xb3, // LOAD_FAST 3
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x5f, // GET_ITER_STACK
    0x4b,0x21, // FOR_ITER 33
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xc5, // STORE_FAST 5
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x10,0x27, // LOAD_CONST_STRING 'version'
    0x55, // LOAD_SUBSCR
    0x12,0x4e, // LOAD_GLOBAL 'len'
    0xb5, // LOAD_FAST 5
    0x10,0x29, // LOAD_CONST_STRING 'files'
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x2a,0x03, // BUILD_TUPLE 3
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x1d, // JUMP -35
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_listing = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_listing,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 100,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 50,
        .line_info = fun_data_upip_listing + 4,
        .line_info_top = fun_data_upip_listing + 4,
        .opcodes = fun_data_upip_listing + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_listing fun_data_upip_listing[0]
#endif

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_freeze
static const byte fun_data_upip_freeze[89] = {
    0xdd,0x01,0x04, // prelude
    0x34,0x51, // names: freeze, out
     // code info
    0x12,0x12, // LOAD_GLOBAL '_load'
    0x12,0x09, // LOAD_GLOBAL 'place'
    0x34,0x00, // CALL_FUNCTION 0
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0x32,0x00, // MAKE_FUNCTION 0
    0x12,0x4f, // LOAD_GLOBAL 'sorted'
    0xb1, // LOAD_FAST 1
    0x10,0x15, // LOAD_CONST_STRING 'packages'
    0x55, // LOAD_SUBSCR
    0x14,0x35, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x44,0x66, // POP_JUMP_IF_FALSE 38
    0x12,0x48, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x17, // LOAD_CONST_STRING 'w'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x19, // SETUP_WITH 25
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x36, // LOAD_METHOD 'write'
    0x10,0x37, // LOAD_CONST_STRING '\n'
    0x14,0x38, // LOAD_METHOD 'join'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xb2, // LOAD_FAST 2
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x10,0x37, // LOAD_CONST_STRING '\n'
    0x42,0x42, // JUMP 2
    0x10,0x1a, // LOAD_CONST_STRING ''
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x42,0x4d, // JUMP 13
    0xb2, // LOAD_FAST 2
    0x5f, // GET_ITER_STACK
    0x4b,0x09, // FOR_ITER 9
    0xc4, // STORE_FAST 4
    0x12,0x50, // LOAD_GLOBAL 'print'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x35, // JUMP -11
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
};
// child of upip_freeze
// frozen bytecode for file upip.py, scope upip_freeze__lt_listcomp_gt_
static const byte fun_data_upip_freeze__lt_listcomp_gt_[40] = {
    0x51,0x04, // prelude
    0x40,0x52, // names: <listcomp>, *
     // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x1d, // FOR_ITER 29
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x10,0x27, // LOAD_CONST_STRING 'version'
    0x55, // LOAD_SUBSCR
    0x10,0x2a, // LOAD_CONST_STRING 'latest'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb1, // LOAD_FAST 1
    0x42,0x49, // JUMP 9
    0xb1, // LOAD_FAST 1
    0x10,0x22, // LOAD_CONST_STRING '@'
    0xf2, // BINARY_OP 27 __add__
    0xb2, // LOAD_FAST 2
    0x10,0x27, // LOAD_CONST_STRING 'version'
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x2f,0x14, // STORE_COMP 20
    0x42,0x21, // JUMP -31
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_freeze__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_freeze__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_upip_freeze__lt_listcomp_gt_ + 4,
        .line_info_top = fun_data_upip_freeze__lt_listcomp_gt_ + 4,
        .opcodes = fun_data_upip_freeze__lt_listcomp_gt_ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_freeze__lt_listcomp_gt_ fun_data_upip_freeze__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_upip_freeze[] = {
    (const mp_raw_code_t *)&proto_fun_upip_freeze__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_upip_freeze = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_freeze,
    .children = (void *)&children_upip_freeze,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 89,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_upip_freeze + 5,
        .line_info_top = fun_data_upip_freeze + 5,
        .opcodes = fun_data_upip_freeze + 5,
    },
    #endif
    #endif
};

// child of upip__lt_module_gt_
// frozen bytecode for file upip.py, scope upip_main
static const byte fun_data_upip_main[189] = {
    0xd9,0x03,0x04, // prelude
    0x39,0x3a, // names: main, argv
     // code info
    0x12,0x3b, // LOAD_GLOBAL 'list'
    0xb0, // LOAD_FAST 0
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x04, // LOAD_GLOBAL 'sys'
    0x13,0x3a, // LOAD_ATTR 'argv'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x42,0x41, // JUMP 1
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0xdd, // BINARY_OP 6 <in>
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x12,0x44, // LOAD_GLOBAL 'USAGE'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x82, // LOAD_CONST_SMALL_INT 2
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x5a, // ROT_TWO
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x48,0x53, // SETUP_EXCEPT 83
    0xb2, // LOAD_FAST 2
    0x10,0x1e, // LOAD_CONST_STRING 'install'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb3, // LOAD_FAST 3
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x1e, // LOAD_GLOBAL 'install'
    0x12,0x1c, // LOAD_GLOBAL '_names'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x10,0x2b, // LOAD_CONST_STRING 'uninstall'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb3, // LOAD_FAST 3
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x2b, // LOAD_GLOBAL 'uninstall'
    0x12,0x1c, // LOAD_GLOBAL '_names'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x10,0x3b, // LOAD_CONST_STRING 'list'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb3, // LOAD_FAST 3
    0x43,0x45, // POP_JUMP_IF_TRUE 5
    0x12,0x32, // LOAD_GLOBAL 'listing'
    0x34,0x00, // CALL_FUNCTION 0
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x10,0x34, // LOAD_CONST_STRING 'freeze'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0x12,0x4e, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xda, // BINARY_OP 3 __le__
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0x12,0x34, // LOAD_GLOBAL 'freeze'
    0xb3, // LOAD_FAST 3
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x42,0x41, // JUMP 1
    0x51, // LOAD_CONST_NONE
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
    0x4a,0x1f, // POP_EXCEPT_JUMP 31
    0x57, // DUP_TOP
    0x12,0x46, // LOAD_GLOBAL 'OSError'
    0x12,0x49, // LOAD_GLOBAL 'ValueError'
    0x2a,0x02, // BUILD_TUPLE 2
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xc4, // STORE_FAST 4
    0x49,0x0a, // SETUP_FINALLY 10
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x10,0x3c, // LOAD_CONST_STRING 'upip:'
    0xb4, // LOAD_FAST 4
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x81, // LOAD_CONST_SMALL_INT 1
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x28,0x04, // DELETE_FAST 4
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x12,0x50, // LOAD_GLOBAL 'print'
    0x12,0x44, // LOAD_GLOBAL 'USAGE'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x82, // LOAD_CONST_SMALL_INT 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_upip_main = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip_main,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 189,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 57,
        .line_info = fun_data_upip_main + 5,
        .line_info_top = fun_data_upip_main + 5,
        .opcodes = fun_data_upip_main + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_upip_main fun_data_upip_main[0]
#endif

static const mp_raw_code_t *const children_upip__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_upip__isdir,
    (const mp_raw_code_t *)&proto_fun_upip__exists,
    (const mp_raw_code_t *)&proto_fun_upip_place,
    (const mp_raw_code_t *)&proto_fun_upip__load,
    (const mp_raw_code_t *)&proto_fun_upip__save,
    (const mp_raw_code_t *)&proto_fun_upip__files,
    (const mp_raw_code_t *)&proto_fun_upip__requirements,
    (const mp_raw_code_t *)&proto_fun_upip__names,
    (const mp_raw_code_t *)&proto_fun_upip_install,
    (const mp_raw_code_t *)&proto_fun_upip_uninstall,
    (const mp_raw_code_t *)&proto_fun_upip_listing,
    (const mp_raw_code_t *)&proto_fun_upip_freeze,
    (const mp_raw_code_t *)&proto_fun_upip_main,
};

static const mp_raw_code_truncated_t proto_fun_upip__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_upip__lt_module_gt_,
    .children = (void *)&children_upip__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 93,
    .n_children = 13,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_upip__lt_module_gt_ + 3,
        .line_info_top = fun_data_upip__lt_module_gt_ + 3,
        .opcodes = fun_data_upip__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_upip[84] = {
    MP_QSTR_upip_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_json,
    MP_QSTR_os,
    MP_QSTR_sys,
    MP_QSTR_tdsh,
    MP_QSTR__isdir,
    MP_QSTR_stat,
    MP_QSTR__exists,
    MP_QSTR_place,
    MP_QSTR_getvar,
    MP_QSTR__slash_lib,
    MP_QSTR__slash_venv_dot_json,
    MP_QSTR_rsplit,
    MP_QSTR__slash_,
    MP_QSTR_user,
    MP_QSTR_root,
    MP_QSTR_home,
    MP_QSTR__load,
    MP_QSTR_load,
    MP_QSTR_setdefault,
    MP_QSTR_packages,
    MP_QSTR__save,
    MP_QSTR_w,
    MP_QSTR_dump,
    MP_QSTR__files,
    MP_QSTR_,
    MP_QSTR__requirements,
    MP_QSTR__names,
    MP_QSTR__hyphen_r,
    MP_QSTR_install,
    MP_QSTR_mip,
    MP_QSTR_mkdir,
    MP_QSTR_partition,
    MP_QSTR__at_sign_,
    MP_QSTR_getcwd,
    MP_QSTR_chdir,
    MP_QSTR_target,
    MP_QSTR__dot_,
    MP_QSTR_version,
    MP_QSTR_get,
    MP_QSTR_files,
    MP_QSTR_latest,
    MP_QSTR_uninstall,
    MP_QSTR_pop,
    MP_QSTR_remove,
    MP_QSTR_add,
    MP_QSTR_key,
    MP_QSTR_reverse,
    MP_QSTR_rmdir,
    MP_QSTR_listing,
    MP_QSTR__percent_s_space__paren_open__percent_s_paren_close__colon_,
    MP_QSTR_freeze,
    MP_QSTR_items,
    MP_QSTR_write,
    MP_QSTR__0x0a_,
    MP_QSTR_join,
    MP_QSTR_main,
    MP_QSTR_argv,
    MP_QSTR_list,
    MP_QSTR_upip_colon_,
    MP_QSTR_walk,
    MP_QSTR_listdir,
    MP_QSTR_append,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR_split,
    MP_QSTR__hash_,
    MP_QSTR_strip,
    MP_QSTR_USAGE,
    MP_QSTR_path,
    MP_QSTR_OSError,
    MP_QSTR_record,
    MP_QSTR_open,
    MP_QSTR_ValueError,
    MP_QSTR_data,
    MP_QSTR_top,
    MP_QSTR_set,
    MP_QSTR_args,
    MP_QSTR_len,
    MP_QSTR_sorted,
    MP_QSTR_print,
    MP_QSTR_out,
    MP_QSTR__star_,
    MP_QSTR_rel,
};

// constants
static const mp_obj_str_t const_obj_upip_0 = {{&mp_type_str}, 25944, 220, (const byte*)"\x75\x73\x61\x67\x65\x3a\x20\x75\x70\x69\x70\x20\x69\x6e\x73\x74\x61\x6c\x6c\x20\x50\x4b\x47\x5b\x40\x56\x45\x52\x53\x49\x4f\x4e\x5d\x2e\x2e\x2e\x20\x7c\x20\x69\x6e\x73\x74\x61\x6c\x6c\x20\x2d\x72\x20\x46\x49\x4c\x45\x0a\x20\x20\x20\x20\x20\x20\x20\x75\x70\x69\x70\x20\x75\x6e\x69\x6e\x73\x74\x61\x6c\x6c\x20\x50\x4b\x47\x2e\x2e\x2e\x20\x7c\x20\x75\x6e\x69\x6e\x73\x74\x61\x6c\x6c\x20\x2d\x72\x20\x46\x49\x4c\x45\x0a\x20\x20\x20\x20\x20\x20\x20\x75\x70\x69\x70\x20\x6c\x69\x73\x74\x0a\x20\x20\x20\x20\x20\x20\x20\x75\x70\x69\x70\x20\x66\x72\x65\x65\x7a\x65\x20\x5b\x46\x49\x4c\x45\x5d\x0a\x50\x61\x63\x6b\x61\x67\x65\x73\x20\x67\x6f\x20\x74\x6f\x20\x74\x68\x65\x20\x61\x63\x74\x69\x76\x65\x20\x76\x69\x72\x74\x75\x61\x6c\x20\x65\x6e\x76\x69\x72\x6f\x6e\x6d\x65\x6e\x74\x20\x28\x61\x63\x74\x69\x76\x61\x74\x65\x20\x44\x49\x52\x29\x2c\x20\x65\x6c\x73\x65\x20\x7e\x2f\x6c\x69\x62\x2e"};
static const mp_obj_str_t const_obj_upip_4 = {{&mp_type_str}, 54273, 27, (const byte*)"\x75\x70\x69\x70\x3a\x20\x25\x73\x20\x69\x6e\x73\x74\x61\x6c\x6c\x65\x64\x20\x6e\x6f\x20\x66\x69\x6c\x65\x73"};
static const mp_obj_str_t const_obj_upip_5 = {{&mp_type_str}, 43359, 42, (const byte*)"\x75\x70\x69\x70\x3a\x20\x25\x73\x20\x69\x73\x20\x6e\x6f\x74\x20\x69\x6e\x73\x74\x61\x6c\x6c\x65\x64\x20\x68\x65\x72\x65\x20\x28\x75\x70\x69\x70\x20\x6c\x69\x73\x74\x29"};
static const mp_rom_obj_tuple_t const_obj_upip_11 = {{&mp_type_tuple}, 3, {
    MP_ROM_QSTR(MP_QSTR__hyphen_h),
    MP_ROM_QSTR(MP_QSTR__hyphen__hyphen_help),
    MP_ROM_QSTR(MP_QSTR_help),
}};

// constant table
static const mp_rom_obj_t const_obj_table_data_upip[12] = {
    MP_ROM_PTR(&const_obj_upip_0),
    MP_ROM_QSTR(MP_QSTR_VIRTUAL_ENV),
    MP_ROM_QSTR(MP_QSTR__slash__dot_upip_dot_json),
    MP_ROM_QSTR(MP_QSTR__hyphen_r_space_takes_space_one_space_file),
    MP_ROM_PTR(&const_obj_upip_4),
    MP_ROM_PTR(&const_obj_upip_5),
    MP_ROM_QSTR(MP_QSTR_Removed_space__percent_s_space__paren_open__percent_d_space_files_paren_close_),
    MP_ROM_QSTR(MP_QSTR_environment_space_),
    MP_ROM_QSTR(MP_QSTR_no_space_environment_space_active),
    MP_ROM_QSTR(MP_QSTR__space__space_nothing_space_installed),
    MP_ROM_QSTR(MP_QSTR__space__space__percent__hyphen_24s_space__percent__hyphen_8s_space__percent_d_space_files),
    MP_ROM_PTR(&const_obj_upip_11),
};

static const mp_frozen_module_t frozen_module_upip = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_upip,
        .obj_table = (mp_obj_t *)&const_obj_table_data_upip,
    },
    .proto_fun = &proto_fun_upip__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module mip___init__
// - original source file: build/frozen_mpy/mip/__init__.mpy
// - frozen file name: mip/__init__.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file mip/__init__.py, scope mip___init____lt_module_gt_
static const byte fun_data_mip___init____lt_module_gt_[91] = {
    0x18,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'sys'
    0x16,0x02, // STORE_NAME 'sys'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'requests'
    0x16,0x03, // STORE_NAME 'requests'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x04, // LOAD_CONST_STRING 'const'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x05, // IMPORT_NAME 'micropython'
    0x1c,0x04, // IMPORT_FROM 'const'
    0x16,0x04, // STORE_NAME 'const'
    0x59, // POP_TOP
    0x2c,0x03, // BUILD_MAP 3
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x10,0x06, // LOAD_CONST_STRING 'codeberg:'
    0x62, // STORE_MAP
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x10,0x07, // LOAD_CONST_STRING 'github:'
    0x62, // STORE_MAP
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x10,0x08, // LOAD_CONST_STRING 'gitlab:'
    0x62, // STORE_MAP
    0x16,0x46, // STORE_NAME '_HOSTS'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x09, // STORE_NAME '_ensure_path_exists'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x11, // STORE_NAME '_chunk'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x13, // STORE_NAME '_check_exists'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x1c, // STORE_NAME '_rewrite_url'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x23, // STORE_NAME '_download_file'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x2d, // STORE_NAME '_install_json'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x35, // STORE_NAME '_install_package'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x52, // LOAD_CONST_TRUE
    0x2a,0x04, // BUILD_TUPLE 4
    0x53, // LOAD_NULL
    0x33,0x07, // MAKE_FUNCTION_DEFARGS 7
    0x16,0x3f, // STORE_NAME 'install'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____ensure_path_exists
static const byte fun_data_mip___init____ensure_path_exists[97] = {
    0x65,0x04, // prelude
    0x09,0x40, // names: _ensure_path_exists, path
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x0a, // IMPORT_NAME 'os'
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x14,0x0b, // LOAD_METHOD 'split'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x43,0x50, // POP_JUMP_IF_TRUE 16
    0xb2, // LOAD_FAST 2
    0x14,0x0d, // LOAD_METHOD 'pop'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x56, // STORE_SUBSCR
    0x10,0x0e, // LOAD_CONST_STRING ''
    0xc3, // STORE_FAST 3
    0x12,0x47, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf3, // BINARY_OP 28 __sub__
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x65, // JUMP 37
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xe5, // BINARY_OP 14 __iadd__
    0xc3, // STORE_FAST 3
    0x48,0x09, // SETUP_EXCEPT 9
    0xb1, // LOAD_FAST 1
    0x14,0x0f, // LOAD_METHOD 'stat'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x0b, // POP_EXCEPT_JUMP 11
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x14,0x10, // LOAD_METHOD 'mkdir'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb3, // LOAD_FAST 3
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xe5, // BINARY_OP 14 __iadd__
    0xc3, // STORE_FAST 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x16, // POP_JUMP_IF_TRUE -42
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____ensure_path_exists = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____ensure_path_exists,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 97,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_mip___init____ensure_path_exists + 4,
        .line_info_top = fun_data_mip___init____ensure_path_exists + 4,
        .opcodes = fun_data_mip___init____ensure_path_exists + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____ensure_path_exists fun_data_mip___init____ensure_path_exists[0]
#endif

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____chunk
static const byte fun_data_mip___init____chunk[55] = {
    0x3a,0x06, // prelude
    0x11,0x48,0x49, // names: _chunk, src, dest
     // code info
    0x12,0x4a, // LOAD_GLOBAL 'memoryview'
    0x12,0x4b, // LOAD_GLOBAL 'bytearray'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x14,0x12, // LOAD_METHOD 'readinto'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x56, // JUMP 22
    0xb1, // LOAD_FAST 1
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb2, // LOAD_FAST 2
    0x42,0x46, // JUMP 6
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xb3, // LOAD_FAST 3
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x1c, // JUMP -36
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____chunk = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____chunk,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 17,
        .line_info = fun_data_mip___init____chunk + 5,
        .line_info_top = fun_data_mip___init____chunk + 5,
        .opcodes = fun_data_mip___init____chunk + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____chunk fun_data_mip___init____chunk[0]
#endif

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____check_exists
static const byte fun_data_mip___init____check_exists[88] = {
    0xf2,0x02,0x06, // prelude
    0x13,0x40,0x4c, // names: _check_exists, path, short_hash
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x0a, // IMPORT_NAME 'os'
    0xc2, // STORE_FAST 2
    0x48,0x45, // SETUP_EXCEPT 69
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x14, // IMPORT_NAME 'binascii'
    0xc3, // STORE_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x15, // IMPORT_NAME 'hashlib'
    0xc4, // STORE_FAST 4
    0x12,0x4d, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x16, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x2e, // SETUP_WITH 46
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0x14,0x17, // LOAD_METHOD 'sha256'
    0x36,0x00, // CALL_METHOD 0
    0xc6, // STORE_FAST 6
    0x12,0x11, // LOAD_GLOBAL '_chunk'
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x13,0x18, // LOAD_ATTR 'update'
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0xb3, // LOAD_FAST 3
    0x14,0x19, // LOAD_METHOD 'hexlify'
    0xb6, // LOAD_FAST 6
    0x14,0x1a, // LOAD_METHOD 'digest'
    0x36,0x00, // CALL_METHOD 0
    0x36,0x01, // CALL_METHOD 1
    0x51, // LOAD_CONST_NONE
    0x12,0x47, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x10,0x1b, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0xb1, // LOAD_FAST 1
    0xd9, // BINARY_OP 2 __eq__
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x4a,0x04, // POP_EXCEPT_JUMP 4
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____check_exists = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____check_exists,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 88,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_mip___init____check_exists + 6,
        .line_info_top = fun_data_mip___init____check_exists + 6,
        .opcodes = fun_data_mip___init____check_exists + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____check_exists fun_data_mip___init____check_exists[0]
#endif

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____rewrite_url
static const byte fun_data_mip___init____rewrite_url[85] = {
    0xa2,0x11,0x06, // prelude
    0x1c,0x4f,0x50, // names: _rewrite_url, url, branch
     // code info
    0x12,0x46, // LOAD_GLOBAL '_HOSTS'
    0x14,0x1d, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x5f, // GET_ITER_STACK
    0x4b,0x44, // FOR_ITER 68
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x14,0x1e, // LOAD_METHOD 'startswith'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x42,0x30, // JUMP -16
    0xb0, // LOAD_FAST 0
    0x12,0x47, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x14,0x0b, // LOAD_METHOD 'split'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xb3, // LOAD_FAST 3
    0x14,0x1f, // LOAD_METHOD 'format'
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xb1, // LOAD_FAST 1
    0x45,0x02, // JUMP_IF_TRUE_OR_POP 2
    0x10,0x20, // LOAD_CONST_STRING 'HEAD'
    0x10,0x21, // LOAD_CONST_STRING 'p'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x14,0x22, // LOAD_METHOD 'join'
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x36,0x82,0x03, // CALL_METHOD 259
    0xf2, // BINARY_OP 27 __add__
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____rewrite_url = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____rewrite_url,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 85,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 21,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 28,
        .line_info = fun_data_mip___init____rewrite_url + 6,
        .line_info_top = fun_data_mip___init____rewrite_url + 6,
        .opcodes = fun_data_mip___init____rewrite_url + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____rewrite_url fun_data_mip___init____rewrite_url[0]
#endif

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____download_file
static const byte fun_data_mip___init____download_file[89] = {
    0xda,0x02,0x06, // prelude
    0x23,0x4f,0x49, // names: _download_file, url, dest
     // code info
    0x12,0x03, // LOAD_GLOBAL 'requests'
    0x14,0x24, // LOAD_METHOD 'get'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0x49,0x40, // SETUP_FINALLY 64
    0xb2, // LOAD_FAST 2
    0x13,0x25, // LOAD_ATTR 'status_code'
    0x22,0x81,0x48, // LOAD_CONST_SMALL_INT 200
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x10,0x26, // LOAD_CONST_STRING 'Error'
    0xb2, // LOAD_FAST 2
    0x13,0x25, // LOAD_ATTR 'status_code'
    0x10,0x27, // LOAD_CONST_STRING 'requesting'
    0xb0, // LOAD_FAST 0
    0x34,0x04, // CALL_FUNCTION 4
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x10,0x28, // LOAD_CONST_STRING 'Copying:'
    0xb1, // LOAD_FAST 1
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x12,0x09, // LOAD_GLOBAL '_ensure_path_exists'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x4d, // LOAD_GLOBAL 'open'
    0xb1, // LOAD_FAST 1
    0x10,0x29, // LOAD_CONST_STRING 'wb'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x0d, // SETUP_WITH 13
    0xc3, // STORE_FAST 3
    0x12,0x11, // LOAD_GLOBAL '_chunk'
    0xb2, // LOAD_FAST 2
    0x13,0x2a, // LOAD_ATTR 'raw'
    0xb3, // LOAD_FAST 3
    0x13,0x2b, // LOAD_ATTR 'write'
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x14,0x2c, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____download_file = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____download_file,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 89,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 35,
        .line_info = fun_data_mip___init____download_file + 6,
        .line_info_top = fun_data_mip___init____download_file + 6,
        .opcodes = fun_data_mip___init____download_file + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____download_file fun_data_mip___init____download_file[0]
#endif

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____install_json
static const byte fun_data_mip___init____install_json[271] = {
    0xcd,0x14,0x0d, // prelude
    0x2d,0x52,0x53,0x54,0x55,0x56, // names: _install_json, package_json_url, index, target, version, mpy
    0x0f, // code info
    0x12,0x03, // LOAD_GLOBAL 'requests'
    0x14,0x24, // LOAD_METHOD 'get'
    0x12,0x1c, // LOAD_GLOBAL '_rewrite_url'
    0xb0, // LOAD_FAST 0
    0xb3, // LOAD_FAST 3
    0x34,0x02, // CALL_FUNCTION 2
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0x49,0x1a, // SETUP_FINALLY 26
    0xb5, // LOAD_FAST 5
    0x13,0x25, // LOAD_ATTR 'status_code'
    0x22,0x81,0x48, // LOAD_CONST_SMALL_INT 200
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xb0, // LOAD_FAST 0
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0xb5, // LOAD_FAST 5
    0x14,0x2e, // LOAD_METHOD 'json'
    0x36,0x00, // CALL_METHOD 0
    0xc6, // STORE_FAST 6
    0x51, // LOAD_CONST_NONE
    0xb5, // LOAD_FAST 5
    0x14,0x2c, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x5d, // END_FINALLY
    0xb6, // LOAD_FAST 6
    0x14,0x24, // LOAD_METHOD 'get'
    0x10,0x2f, // LOAD_CONST_STRING 'hashes'
    0x2a,0x00, // BUILD_TUPLE 0
    0x36,0x02, // CALL_METHOD 2
    0x5f, // GET_ITER_STACK
    0x4b,0x46, // FOR_ITER 70
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc7, // STORE_FAST 7
    0xc8, // STORE_FAST 8
    0xb2, // LOAD_FAST 2
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb7, // LOAD_FAST 7
    0xf2, // BINARY_OP 27 __add__
    0xc9, // STORE_FAST 9
    0x12,0x13, // LOAD_GLOBAL '_check_exists'
    0xb9, // LOAD_FAST 9
    0xb8, // LOAD_FAST 8
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x10,0x30, // LOAD_CONST_STRING 'Exists:'
    0xb9, // LOAD_FAST 9
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x42,0x66, // JUMP 38
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x14,0x1f, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0x82, // LOAD_CONST_SMALL_INT 2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xb8, // LOAD_FAST 8
    0x36,0x03, // CALL_METHOD 3
    0xca, // STORE_FAST 10
    0x12,0x23, // LOAD_GLOBAL '_download_file'
    0xba, // LOAD_FAST 10
    0xb9, // LOAD_FAST 9
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x4f, // POP_JUMP_IF_TRUE 15
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x14,0x1f, // LOAD_METHOD 'format'
    0xb7, // LOAD_FAST 7
    0xb8, // LOAD_FAST 8
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0xb8,0x7f, // JUMP -72
    0xb0, // LOAD_FAST 0
    0x14,0x31, // LOAD_METHOD 'rpartition'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xcb, // STORE_FAST 11
    0xb6, // LOAD_FAST 6
    0x14,0x24, // LOAD_METHOD 'get'
    0x10,0x32, // LOAD_CONST_STRING 'urls'
    0x2a,0x00, // BUILD_TUPLE 0
    0x36,0x02, // CALL_METHOD 2
    0x5f, // GET_ITER_STACK
    0x4b,0x4c, // FOR_ITER 76
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc7, // STORE_FAST 7
    0x27,0x0f, // STORE_DEREF 15
    0xb2, // LOAD_FAST 2
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb7, // LOAD_FAST 7
    0xf2, // BINARY_OP 27 __add__
    0xc9, // STORE_FAST 9
    0x12,0x57, // LOAD_GLOBAL 'any'
    0xbf, // LOAD_FAST 15
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xcc, // STORE_FAST 12
    0xbb, // LOAD_FAST 11
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0xbc, // LOAD_FAST 12
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0x10,0x33, // LOAD_CONST_STRING '{}/{}'
    0x14,0x1f, // LOAD_METHOD 'format'
    0xbb, // LOAD_FAST 11
    0x25,0x0f, // LOAD_DEREF 15
    0x36,0x02, // CALL_METHOD 2
    0x27,0x0f, // STORE_DEREF 15
    0x12,0x23, // LOAD_GLOBAL '_download_file'
    0x12,0x1c, // LOAD_GLOBAL '_rewrite_url'
    0x25,0x0f, // LOAD_DEREF 15
    0xb3, // LOAD_FAST 3
    0x34,0x02, // CALL_FUNCTION 2
    0xb9, // LOAD_FAST 9
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x50, // POP_JUMP_IF_TRUE 16
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x14,0x1f, // LOAD_METHOD 'format'
    0xb7, // LOAD_FAST 7
    0x25,0x0f, // LOAD_DEREF 15
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0xb2,0x7f, // JUMP -78
    0xb6, // LOAD_FAST 6
    0x14,0x24, // LOAD_METHOD 'get'
    0x10,0x34, // LOAD_CONST_STRING 'deps'
    0x2a,0x00, // BUILD_TUPLE 0
    0x36,0x02, // CALL_METHOD 2
    0x5f, // GET_ITER_STACK
    0x4b,0x13, // FOR_ITER 19
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xcd, // STORE_FAST 13
    0xce, // STORE_FAST 14
    0x12,0x35, // LOAD_GLOBAL '_install_package'
    0xbd, // LOAD_FAST 13
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xbe, // LOAD_FAST 14
    0xb4, // LOAD_FAST 4
    0x34,0x05, // CALL_FUNCTION 5
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0x2b, // JUMP -21
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
// child of mip___init____install_json
// frozen bytecode for file mip/__init__.py, scope mip___init____install_json__lt_genexpr_gt_
static const byte fun_data_mip___init____install_json__lt_genexpr_gt_[26] = {
    0xca,0x40,0x06, // prelude
    0x45,0x5a,0x5a, // names: <genexpr>, *, *
     // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0c, // FOR_ITER 12
    0xc2, // STORE_FAST 2
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x1e, // LOAD_METHOD 'startswith'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x32, // JUMP -14
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____install_json__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_mip___init____install_json__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 69,
        .line_info = fun_data_mip___init____install_json__lt_genexpr_gt_ + 6,
        .line_info_top = fun_data_mip___init____install_json__lt_genexpr_gt_ + 6,
        .opcodes = fun_data_mip___init____install_json__lt_genexpr_gt_ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____install_json__lt_genexpr_gt_ fun_data_mip___init____install_json__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_mip___init____install_json[] = {
    (const mp_raw_code_t *)&proto_fun_mip___init____install_json__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_mip___init____install_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____install_json,
    .children = (void *)&children_mip___init____install_json,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 271,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 26,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_mip___init____install_json + 9,
        .line_info_top = fun_data_mip___init____install_json + 9,
        .opcodes = fun_data_mip___init____install_json + 10,
    },
    #endif
    #endif
};

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init____install_package
static const byte fun_data_mip___init____install_package[214] = {
    0xe1,0x04,0x0d, // prelude
    0x35,0x58,0x53,0x54,0x55,0x56, // names: _install_package, package, index, target, version, mpy
    0x00, // code info
    0x12,0x57, // LOAD_GLOBAL 'any'
    0xb0, // LOAD_FAST 0
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0xf0,0x80, // POP_JUMP_IF_FALSE 112
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x36, // LOAD_METHOD 'endswith'
    0x10,0x37, // LOAD_CONST_STRING '.py'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x4a, // POP_JUMP_IF_TRUE 10
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x36, // LOAD_METHOD 'endswith'
    0x10,0x38, // LOAD_CONST_STRING '.mpy'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x69, // POP_JUMP_IF_FALSE 41
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x14,0x1f, // LOAD_METHOD 'format'
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x23, // LOAD_GLOBAL '_download_file'
    0x12,0x1c, // LOAD_GLOBAL '_rewrite_url'
    0x25,0x00, // LOAD_DEREF 0
    0xb3, // LOAD_FAST 3
    0x34,0x02, // CALL_FUNCTION 2
    0xb2, // LOAD_FAST 2
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x39, // LOAD_METHOD 'rsplit'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x36, // LOAD_METHOD 'endswith'
    0x10,0x3a, // LOAD_CONST_STRING '.json'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x58, // POP_JUMP_IF_TRUE 24
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x36, // LOAD_METHOD 'endswith'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x25,0x00, // LOAD_DEREF 0
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0xe5, // BINARY_OP 14 __iadd__
    0x27,0x00, // STORE_DEREF 0
    0x25,0x00, // LOAD_DEREF 0
    0x23,0x08, // LOAD_CONST_OBJ 8
    0xe5, // BINARY_OP 14 __iadd__
    0x27,0x00, // STORE_DEREF 0
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x14,0x1f, // LOAD_METHOD 'format'
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0xc1,0x80, // JUMP 65
    0xb3, // LOAD_FAST 3
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x10,0x3b, // LOAD_CONST_STRING 'latest'
    0xc3, // STORE_FAST 3
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0x14,0x1f, // LOAD_METHOD 'format'
    0x25,0x00, // LOAD_DEREF 0
    0xb3, // LOAD_FAST 3
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x04, // CALL_METHOD 4
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0x12,0x59, // LOAD_GLOBAL 'hasattr'
    0x12,0x02, // LOAD_GLOBAL 'sys'
    0x13,0x3c, // LOAD_ATTR 'implementation'
    0x10,0x3d, // LOAD_CONST_STRING '_mpy'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x02, // LOAD_GLOBAL 'sys'
    0x13,0x3c, // LOAD_ATTR 'implementation'
    0x13,0x3d, // LOAD_ATTR '_mpy'
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x42,0x42, // JUMP 2
    0x10,0x3e, // LOAD_CONST_STRING 'py'
    0xc5, // STORE_FAST 5
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x14,0x1f, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0xb5, // LOAD_FAST 5
    0x25,0x00, // LOAD_DEREF 0
    0xb3, // LOAD_FAST 3
    0x36,0x04, // CALL_METHOD 4
    0x27,0x00, // STORE_DEREF 0
    0x12,0x2d, // LOAD_GLOBAL '_install_json'
    0x25,0x00, // LOAD_DEREF 0
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x34,0x05, // CALL_FUNCTION 5
    0x63, // RETURN_VALUE
};
// child of mip___init____install_package
// frozen bytecode for file mip/__init__.py, scope mip___init____install_package__lt_genexpr_gt_
static const byte fun_data_mip___init____install_package__lt_genexpr_gt_[26] = {
    0xca,0x40,0x06, // prelude
    0x45,0x5a,0x5a, // names: <genexpr>, *, *
     // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0c, // FOR_ITER 12
    0xc2, // STORE_FAST 2
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x1e, // LOAD_METHOD 'startswith'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x32, // JUMP -14
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init____install_package__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_mip___init____install_package__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 69,
        .line_info = fun_data_mip___init____install_package__lt_genexpr_gt_ + 6,
        .line_info_top = fun_data_mip___init____install_package__lt_genexpr_gt_ + 6,
        .opcodes = fun_data_mip___init____install_package__lt_genexpr_gt_ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init____install_package__lt_genexpr_gt_ fun_data_mip___init____install_package__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_mip___init____install_package[] = {
    (const mp_raw_code_t *)&proto_fun_mip___init____install_package__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_mip___init____install_package = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____install_package,
    .children = (void *)&children_mip___init____install_package,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 214,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 53,
        .line_info = fun_data_mip___init____install_package + 9,
        .line_info_top = fun_data_mip___init____install_package + 9,
        .opcodes = fun_data_mip___init____install_package + 10,
    },
    #endif
    #endif
};

// child of mip___init____lt_module_gt_
// frozen bytecode for file mip/__init__.py, scope mip___init___install
static const byte fun_data_mip___init___install[100] = {
    0xe1,0x84,0x80,0x01,0x0c, // prelude
    0x3f,0x58,0x53,0x54,0x55,0x56, // names: install, package, index, target, version, mpy
     // code info
    0xb2, // LOAD_FAST 2
    0x43,0x6d, // POP_JUMP_IF_TRUE 45
    0x12,0x02, // LOAD_GLOBAL 'sys'
    0x13,0x40, // LOAD_ATTR 'path'
    0x5f, // GET_ITER_STACK
    0x4b,0x1d, // FOR_ITER 29
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x1e, // LOAD_METHOD 'startswith'
    0x10,0x41, // LOAD_CONST_STRING '/rom'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x51, // POP_JUMP_IF_TRUE 17
    0xb5, // LOAD_FAST 5
    0x14,0x36, // LOAD_METHOD 'endswith'
    0x10,0x42, // LOAD_CONST_STRING '/lib'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb5, // LOAD_FAST 5
    0xc2, // STORE_FAST 2
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x42,0x4b, // JUMP 11
    0x42,0x21, // JUMP -31
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0xc1, // STORE_FAST 1
    0x12,0x35, // LOAD_GLOBAL '_install_package'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x14,0x43, // LOAD_METHOD 'rstrip'
    0x10,0x0c, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x34,0x05, // CALL_FUNCTION 5
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x10,0x44, // LOAD_CONST_STRING 'Done'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x47, // JUMP 7
    0x12,0x51, // LOAD_GLOBAL 'print'
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_mip___init___install = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init___install,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 100,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 4,
        .qstr_block_name_idx = 63,
        .line_info = fun_data_mip___init___install + 11,
        .line_info_top = fun_data_mip___init___install + 11,
        .opcodes = fun_data_mip___init___install + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_mip___init___install fun_data_mip___init___install[0]
#endif

static const mp_raw_code_t *const children_mip___init____lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_mip___init____ensure_path_exists,
    (const mp_raw_code_t *)&proto_fun_mip___init____chunk,
    (const mp_raw_code_t *)&proto_fun_mip___init____check_exists,
    (const mp_raw_code_t *)&proto_fun_mip___init____rewrite_url,
    (const mp_raw_code_t *)&proto_fun_mip___init____download_file,
    (const mp_raw_code_t *)&proto_fun_mip___init____install_json,
    (const mp_raw_code_t *)&proto_fun_mip___init____install_package,
    (const mp_raw_code_t *)&proto_fun_mip___init___install,
};

static const mp_raw_code_truncated_t proto_fun_mip___init____lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_mip___init____lt_module_gt_,
    .children = (void *)&children_mip___init____lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 91,
    .n_children = 8,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_mip___init____lt_module_gt_ + 3,
        .line_info_top = fun_data_mip___init____lt_module_gt_ + 3,
        .opcodes = fun_data_mip___init____lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_mip___init__[91] = {
    MP_QSTR_mip_slash___init___dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_sys,
    MP_QSTR_requests,
    MP_QSTR_const,
    MP_QSTR_micropython,
    MP_QSTR_codeberg_colon_,
    MP_QSTR_github_colon_,
    MP_QSTR_gitlab_colon_,
    MP_QSTR__ensure_path_exists,
    MP_QSTR_os,
    MP_QSTR_split,
    MP_QSTR__slash_,
    MP_QSTR_pop,
    MP_QSTR_,
    MP_QSTR_stat,
    MP_QSTR_mkdir,
    MP_QSTR__chunk,
    MP_QSTR_readinto,
    MP_QSTR__check_exists,
    MP_QSTR_binascii,
    MP_QSTR_hashlib,
    MP_QSTR_rb,
    MP_QSTR_sha256,
    MP_QSTR_update,
    MP_QSTR_hexlify,
    MP_QSTR_digest,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR__rewrite_url,
    MP_QSTR_items,
    MP_QSTR_startswith,
    MP_QSTR_format,
    MP_QSTR_HEAD,
    MP_QSTR_p,
    MP_QSTR_join,
    MP_QSTR__download_file,
    MP_QSTR_get,
    MP_QSTR_status_code,
    MP_QSTR_Error,
    MP_QSTR_requesting,
    MP_QSTR_Copying_colon_,
    MP_QSTR_wb,
    MP_QSTR_raw,
    MP_QSTR_write,
    MP_QSTR_close,
    MP_QSTR__install_json,
    MP_QSTR_json,
    MP_QSTR_hashes,
    MP_QSTR_Exists_colon_,
    MP_QSTR_rpartition,
    MP_QSTR_urls,
    MP_QSTR__brace_open__brace_close__slash__brace_open__brace_close_,
    MP_QSTR_deps,
    MP_QSTR__install_package,
    MP_QSTR_endswith,
    MP_QSTR__dot_py,
    MP_QSTR__dot_mpy,
    MP_QSTR_rsplit,
    MP_QSTR__dot_json,
    MP_QSTR_latest,
    MP_QSTR_implementation,
    MP_QSTR__mpy,
    MP_QSTR_py,
    MP_QSTR_install,
    MP_QSTR_path,
    MP_QSTR__slash_rom,
    MP_QSTR__slash_lib,
    MP_QSTR_rstrip,
    MP_QSTR_Done,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR__HOSTS,
    MP_QSTR_len,
    MP_QSTR_src,
    MP_QSTR_dest,
    MP_QSTR_memoryview,
    MP_QSTR_bytearray,
    MP_QSTR_short_hash,
    MP_QSTR_open,
    MP_QSTR_str,
    MP_QSTR_url,
    MP_QSTR_branch,
    MP_QSTR_print,
    MP_QSTR_package_json_url,
    MP_QSTR_index,
    MP_QSTR_target,
    MP_QSTR_version,
    MP_QSTR_mpy,
    MP_QSTR_any,
    MP_QSTR_package,
    MP_QSTR_hasattr,
    MP_QSTR__star_,
};

// constants
static const mp_obj_str_t const_obj_mip___init___0 = {{&mp_type_str}, 9474, 46, (const byte*)"\x63\x6f\x64\x65\x62\x65\x72\x67\x2e\x6f\x72\x67\x2f\x61\x70\x69\x2f\x76\x31\x2f\x72\x65\x70\x6f\x73\x2f\x7b\x7d\x2f\x7b\x7d\x2f\x72\x61\x77\x2f\x7b\x70\x7d\x3f\x72\x65\x66\x3d\x7b\x7d"};
static const mp_obj_str_t const_obj_mip___init___1 = {{&mp_type_str}, 27853, 38, (const byte*)"\x72\x61\x77\x2e\x67\x69\x74\x68\x75\x62\x75\x73\x65\x72\x63\x6f\x6e\x74\x65\x6e\x74\x2e\x63\x6f\x6d\x2f\x7b\x7d\x2f\x7b\x7d\x2f\x7b\x7d\x2f\x7b\x70\x7d"};
static const mp_obj_str_t const_obj_mip___init___2 = {{&mp_type_str}, 20934, 29, (const byte*)"\x67\x69\x74\x6c\x61\x62\x2e\x63\x6f\x6d\x2f\x7b\x7d\x2f\x7b\x7d\x2f\x2d\x2f\x72\x61\x77\x2f\x7b\x7d\x2f\x7b\x70\x7d"};
static const mp_rom_obj_tuple_t const_obj_mip___init___3 = {{&mp_type_tuple}, 5, {
    MP_ROM_QSTR(MP_QSTR_http_colon__slash__slash_),
    MP_ROM_QSTR(MP_QSTR_https_colon__slash__slash_),
    MP_ROM_QSTR(MP_QSTR_codeberg_colon_),
    MP_ROM_QSTR(MP_QSTR_github_colon_),
    MP_ROM_QSTR(MP_QSTR_gitlab_colon_),
}};
static const mp_obj_str_t const_obj_mip___init___10 = {{&mp_type_str}, 17480, 32, (const byte*)"\x49\x6e\x73\x74\x61\x6c\x6c\x69\x6e\x67\x20\x7b\x7d\x20\x28\x7b\x7d\x29\x20\x66\x72\x6f\x6d\x20\x7b\x7d\x20\x74\x6f\x20\x7b\x7d"};
static const mp_obj_str_t const_obj_mip___init___12 = {{&mp_type_str}, 43215, 34, (const byte*)"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x66\x69\x6e\x64\x20\x6c\x69\x62\x20\x64\x69\x72\x20\x69\x6e\x20\x73\x79\x73\x2e\x70\x61\x74\x68"};
static const mp_obj_str_t const_obj_mip___init___13 = {{&mp_type_str}, 61939, 29, (const byte*)"\x68\x74\x74\x70\x73\x3a\x2f\x2f\x6d\x69\x63\x72\x6f\x70\x79\x74\x68\x6f\x6e\x2e\x6f\x72\x67\x2f\x70\x69\x2f\x76\x32"};
static const mp_obj_str_t const_obj_mip___init___14 = {{&mp_type_str}, 57771, 34, (const byte*)"\x50\x61\x63\x6b\x61\x67\x65\x20\x6d\x61\x79\x20\x62\x65\x20\x70\x61\x72\x74\x69\x61\x6c\x6c\x79\x20\x69\x6e\x73\x74\x61\x6c\x6c\x65\x64"};

// constant table
static const mp_rom_obj_t const_obj_table_data_mip___init__[15] = {
    MP_ROM_PTR(&const_obj_mip___init___0),
    MP_ROM_PTR(&const_obj_mip___init___1),
    MP_ROM_PTR(&const_obj_mip___init___2),
    MP_ROM_PTR(&const_obj_mip___init___3),
    MP_ROM_QSTR(MP_QSTR_Package_space_not_space_found_colon_),
    MP_ROM_QSTR(MP_QSTR__brace_open__brace_close__slash_file_slash__brace_open__brace_close__slash__brace_open__brace_close_),
    MP_ROM_QSTR(MP_QSTR_File_space_not_space_found_colon__space__brace_open__brace_close__space__brace_open__brace_close_),
    MP_ROM_QSTR(MP_QSTR_Downloading_space__brace_open__brace_close__space_to_space__brace_open__brace_close_),
    MP_ROM_QSTR(MP_QSTR_package_dot_json),
    MP_ROM_QSTR(MP_QSTR_Installing_space__brace_open__brace_close__space_to_space__brace_open__brace_close_),
    MP_ROM_PTR(&const_obj_mip___init___10),
    MP_ROM_QSTR(MP_QSTR__brace_open__brace_close__slash_package_slash__brace_open__brace_close__slash__brace_open__brace_close__slash__brace_open__brace_close__dot_json),
    MP_ROM_PTR(&const_obj_mip___init___12),
    MP_ROM_PTR(&const_obj_mip___init___13),
    MP_ROM_PTR(&const_obj_mip___init___14),
};

static const mp_frozen_module_t frozen_module_mip___init__ = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_mip___init__,
        .obj_table = (mp_obj_t *)&const_obj_table_data_mip___init__,
    },
    .proto_fun = &proto_fun_mip___init____lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module umqtt_simple
// - original source file: build/frozen_mpy/umqtt/simple.mpy
// - frozen file name: umqtt/simple.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file umqtt/simple.py, scope umqtt_simple__lt_module_gt_
static const byte fun_data_umqtt_simple__lt_module_gt_[53] = {
    0x18,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'socket'
    0x16,0x02, // STORE_NAME 'socket'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'struct'
    0x16,0x03, // STORE_NAME 'struct'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x04, // LOAD_CONST_STRING 'hexlify'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x05, // IMPORT_NAME 'binascii'
    0x1c,0x04, // IMPORT_FROM 'hexlify'
    0x16,0x04, // STORE_NAME 'hexlify'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x06, // LOAD_CONST_STRING 'MQTTException'
    0x11,0x31, // LOAD_NAME 'Exception'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x06, // STORE_NAME 'MQTTException'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x08, // STORE_NAME '_encode_len'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x07, // LOAD_CONST_STRING 'MQTTClient'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x07, // STORE_NAME 'MQTTClient'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of umqtt_simple__lt_module_gt_
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTException
static const byte fun_data_umqtt_simple_MQTTException[13] = {
    0x00,0x02, // prelude
    0x06, // names: MQTTException
     // code info
    0x11,0x32, // LOAD_NAME '__name__'
    0x16,0x33, // STORE_NAME '__module__'
    0x10,0x06, // LOAD_CONST_STRING 'MQTTException'
    0x16,0x34, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTException = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTException,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_umqtt_simple_MQTTException + 3,
        .line_info_top = fun_data_umqtt_simple_MQTTException + 3,
        .opcodes = fun_data_umqtt_simple_MQTTException + 3,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTException fun_data_umqtt_simple_MQTTException[0]
#endif

// child of umqtt_simple__lt_module_gt_
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple__encode_len
static const byte fun_data_umqtt_simple__encode_len[42] = {
    0x2a,0x06, // prelude
    0x08,0x35,0x36, // names: _encode_len, pkt, sz
     // code info
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc2, // STORE_FAST 2
    0x42,0x54, // JUMP 20
    0xb1, // LOAD_FAST 1
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xef, // BINARY_OP 24 __and__
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xed, // BINARY_OP 22 __or__
    0xb0, // LOAD_FAST 0
    0xb2, // LOAD_FAST 2
    0x56, // STORE_SUBSCR
    0xb1, // LOAD_FAST 1
    0x87, // LOAD_CONST_SMALL_INT 7
    0xe4, // BINARY_OP 13 __irshift__
    0xc1, // STORE_FAST 1
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xd8, // BINARY_OP 1 __gt__
    0x43,0x25, // POP_JUMP_IF_TRUE -27
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0xb2, // LOAD_FAST 2
    0x56, // STORE_SUBSCR
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple__encode_len = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple__encode_len,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 42,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_umqtt_simple__encode_len + 5,
        .line_info_top = fun_data_umqtt_simple__encode_len + 5,
        .opcodes = fun_data_umqtt_simple__encode_len + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple__encode_len fun_data_umqtt_simple__encode_len[0]
#endif

// child of umqtt_simple__lt_module_gt_
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient
static const byte fun_data_umqtt_simple_MQTTClient[102] = {
    0x28,0x02, // prelude
    0x07, // names: MQTTClient
     // code info
    0x11,0x32, // LOAD_NAME '__name__'
    0x16,0x33, // STORE_NAME '__module__'
    0x10,0x07, // LOAD_CONST_STRING 'MQTTClient'
    0x16,0x34, // STORE_NAME '__qualname__'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x2c,0x00, // BUILD_MAP 0
    0x2a,0x06, // BUILD_TUPLE 6
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x09, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x19, // STORE_NAME '_send_str'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x1d, // STORE_NAME '_recv_len'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x1f, // STORE_NAME 'set_callback'
    0x50, // LOAD_CONST_FALSE
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x20, // STORE_NAME 'set_last_will'
    0x52, // LOAD_CONST_TRUE
    0x51, // LOAD_CONST_NONE
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x21, // STORE_NAME 'connect'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x27, // STORE_NAME 'disconnect'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x28, // STORE_NAME 'ping'
    0x50, // LOAD_CONST_FALSE
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x08, // MAKE_FUNCTION_DEFARGS 8
    0x16,0x29, // STORE_NAME 'publish'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x09, // MAKE_FUNCTION_DEFARGS 9
    0x16,0x2c, // STORE_NAME '_send_subunsub'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0a, // MAKE_FUNCTION_DEFARGS 10
    0x16,0x2d, // STORE_NAME 'subscribe'
    0x32,0x0b, // MAKE_FUNCTION 11
    0x16,0x2e, // STORE_NAME 'unsubscribe'
    0x32,0x0c, // MAKE_FUNCTION 12
    0x16,0x2b, // STORE_NAME 'wait_msg'
    0x32,0x0d, // MAKE_FUNCTION 13
    0x16,0x30, // STORE_NAME 'check_msg'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient___init__
static const byte fun_data_umqtt_simple_MQTTClient___init__[95] = {
    0xd1,0x80,0x85,0x01,0x14, // prelude
    0x09,0x37,0x0a,0x0c,0x0d,0x12,0x38,0x14,0x0e,0x0f, // names: __init__, self, client_id, server, port, user, password, keepalive, ssl, ssl_params
     // code info
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb7, // LOAD_FAST 7
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x22,0x80,0xc5,0x33, // LOAD_CONST_SMALL_INT 8883
    0x42,0x43, // JUMP 3
    0x22,0x8e,0x5b, // LOAD_CONST_SMALL_INT 1883
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x0a, // STORE_ATTR 'client_id'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x0b, // STORE_ATTR 'sock'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0c, // STORE_ATTR 'server'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'port'
    0xb7, // LOAD_FAST 7
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'ssl'
    0xb8, // LOAD_FAST 8
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'ssl_params'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x10, // STORE_ATTR 'pid'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x11, // STORE_ATTR 'cb'
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x12, // STORE_ATTR 'user'
    0xb5, // LOAD_FAST 5
    0xb0, // LOAD_FAST 0
    0x18,0x13, // STORE_ATTR 'pswd'
    0xb6, // LOAD_FAST 6
    0xb0, // LOAD_FAST 0
    0x18,0x14, // STORE_ATTR 'keepalive'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x15, // STORE_ATTR 'lw_topic'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x16, // STORE_ATTR 'lw_msg'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x17, // STORE_ATTR 'lw_qos'
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x18, // STORE_ATTR 'lw_retain'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 95,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 9,
        .n_kwonly_args = 0,
        .n_def_pos_args = 6,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_umqtt_simple_MQTTClient___init__ + 15,
        .line_info_top = fun_data_umqtt_simple_MQTTClient___init__ + 15,
        .opcodes = fun_data_umqtt_simple_MQTTClient___init__ + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient___init__ fun_data_umqtt_simple_MQTTClient___init__[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient__send_str
static const byte fun_data_umqtt_simple_MQTTClient__send_str[37] = {
    0x42,0x06, // prelude
    0x19,0x37,0x39, // names: _send_str, self, s
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0x12,0x03, // LOAD_GLOBAL 'struct'
    0x14,0x1b, // LOAD_METHOD 'pack'
    0x10,0x1c, // LOAD_CONST_STRING '!H'
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient__send_str = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient__send_str,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 25,
        .line_info = fun_data_umqtt_simple_MQTTClient__send_str + 5,
        .line_info_top = fun_data_umqtt_simple_MQTTClient__send_str + 5,
        .opcodes = fun_data_umqtt_simple_MQTTClient__send_str + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient__send_str fun_data_umqtt_simple_MQTTClient__send_str[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient__recv_len
static const byte fun_data_umqtt_simple_MQTTClient__recv_len[46] = {
    0x31,0x04, // prelude
    0x1d,0x37, // names: _recv_len, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0xf0, // BINARY_OP 25 __lshift__
    0xe0, // BINARY_OP 9 __ior__
    0xc1, // STORE_FAST 1
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xef, // BINARY_OP 24 __and__
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x87, // LOAD_CONST_SMALL_INT 7
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x42,0x1c, // JUMP -36
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient__recv_len = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient__recv_len,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 29,
        .line_info = fun_data_umqtt_simple_MQTTClient__recv_len + 4,
        .line_info_top = fun_data_umqtt_simple_MQTTClient__recv_len + 4,
        .opcodes = fun_data_umqtt_simple_MQTTClient__recv_len + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient__recv_len fun_data_umqtt_simple_MQTTClient__recv_len[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_set_callback
static const byte fun_data_umqtt_simple_MQTTClient_set_callback[11] = {
    0x1a,0x06, // prelude
    0x1f,0x37,0x3b, // names: set_callback, self, f
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x11, // STORE_ATTR 'cb'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_set_callback = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_set_callback,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 11,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 31,
        .line_info = fun_data_umqtt_simple_MQTTClient_set_callback + 5,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_set_callback + 5,
        .opcodes = fun_data_umqtt_simple_MQTTClient_set_callback + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_set_callback fun_data_umqtt_simple_MQTTClient_set_callback[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_set_last_will
static const byte fun_data_umqtt_simple_MQTTClient_set_last_will[28] = {
    0xb1,0x84,0x01,0x0c, // prelude
    0x20,0x37,0x3c,0x3d,0x3e,0x3f, // names: set_last_will, self, topic, msg, retain, qos
     // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x15, // STORE_ATTR 'lw_topic'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x16, // STORE_ATTR 'lw_msg'
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x17, // STORE_ATTR 'lw_qos'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x18, // STORE_ATTR 'lw_retain'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_set_last_will = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_set_last_will,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 32,
        .line_info = fun_data_umqtt_simple_MQTTClient_set_last_will + 10,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_set_last_will + 10,
        .opcodes = fun_data_umqtt_simple_MQTTClient_set_last_will + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_set_last_will fun_data_umqtt_simple_MQTTClient_set_last_will[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_connect
static const byte fun_data_umqtt_simple_MQTTClient_connect[398] = {
    0xfb,0x80,0x01,0x08, // prelude
    0x21,0x37,0x40,0x41, // names: connect, self, clean_session, timeout
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x22, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x14,0x02, // LOAD_METHOD 'socket'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x0b, // STORE_ATTR 'sock'
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x23, // LOAD_METHOD 'settimeout'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'socket'
    0x14,0x24, // LOAD_METHOD 'getaddrinfo'
    0xb0, // LOAD_FAST 0
    0x13,0x0c, // LOAD_ATTR 'server'
    0xb0, // LOAD_FAST 0
    0x13,0x0d, // LOAD_ATTR 'port'
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x21, // LOAD_METHOD 'connect'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'ssl'
    0x52, // LOAD_CONST_TRUE
    0xde, // BINARY_OP 7 <is>
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x0e, // IMPORT_NAME 'ssl'
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x14,0x25, // LOAD_METHOD 'wrap_socket'
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR 'ssl_params'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x01, // CALL_METHOD_VAR_KW 257
    0xb0, // LOAD_FAST 0
    0x18,0x0b, // STORE_ATTR 'sock'
    0x42,0x5a, // JUMP 26
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'ssl'
    0x44,0x55, // POP_JUMP_IF_FALSE 21
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'ssl'
    0x14,0x25, // LOAD_METHOD 'wrap_socket'
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x10,0x26, // LOAD_CONST_STRING 'server_hostname'
    0xb0, // LOAD_FAST 0
    0x13,0x0c, // LOAD_ATTR 'server'
    0x36,0x82,0x01, // CALL_METHOD 257
    0xb0, // LOAD_FAST 0
    0x18,0x0b, // STORE_ATTR 'sock'
    0x42,0x40, // JUMP 0
    0x12,0x42, // LOAD_GLOBAL 'bytearray'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0x12,0x42, // LOAD_GLOBAL 'bytearray'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf2, // BINARY_OP 27 __add__
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR 'client_id'
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xc7, // STORE_FAST 7
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf0, // BINARY_OP 25 __lshift__
    0xb6, // LOAD_FAST 6
    0x86, // LOAD_CONST_SMALL_INT 6
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x12, // LOAD_ATTR 'user'
    0x44,0x60, // POP_JUMP_IF_FALSE 32
    0xb7, // LOAD_FAST 7
    0x82, // LOAD_CONST_SMALL_INT 2
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x12, // LOAD_ATTR 'user'
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf2, // BINARY_OP 27 __add__
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'pswd'
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xe5, // BINARY_OP 14 __iadd__
    0xc7, // STORE_FAST 7
    0xb6, // LOAD_FAST 6
    0x86, // LOAD_CONST_SMALL_INT 6
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0x22,0x81,0x40, // LOAD_CONST_SMALL_INT 192
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x14, // LOAD_ATTR 'keepalive'
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0xb6, // LOAD_FAST 6
    0x87, // LOAD_CONST_SMALL_INT 7
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x14, // LOAD_ATTR 'keepalive'
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0xb6, // LOAD_FAST 6
    0x88, // LOAD_CONST_SMALL_INT 8
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x14, // LOAD_ATTR 'keepalive'
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'lw_topic'
    0x44,0x7a, // POP_JUMP_IF_FALSE 58
    0xb7, // LOAD_FAST 7
    0x82, // LOAD_CONST_SMALL_INT 2
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'lw_topic'
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf2, // BINARY_OP 27 __add__
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'lw_msg'
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xe5, // BINARY_OP 14 __iadd__
    0xc7, // STORE_FAST 7
    0xb6, // LOAD_FAST 6
    0x86, // LOAD_CONST_SMALL_INT 6
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0x84, // LOAD_CONST_SMALL_INT 4
    0xb0, // LOAD_FAST 0
    0x13,0x17, // LOAD_ATTR 'lw_qos'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xef, // BINARY_OP 24 __and__
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xb0, // LOAD_FAST 0
    0x13,0x17, // LOAD_ATTR 'lw_qos'
    0x82, // LOAD_CONST_SMALL_INT 2
    0xef, // BINARY_OP 24 __and__
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0xb6, // LOAD_FAST 6
    0x86, // LOAD_CONST_SMALL_INT 6
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x18, // LOAD_ATTR 'lw_retain'
    0x85, // LOAD_CONST_SMALL_INT 5
    0xf0, // BINARY_OP 25 __lshift__
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0x12,0x08, // LOAD_GLOBAL '_encode_len'
    0xb5, // LOAD_FAST 5
    0xb7, // LOAD_FAST 7
    0x34,0x02, // CALL_FUNCTION 2
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb5, // LOAD_FAST 5
    0xb8, // LOAD_FAST 8
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf2, // BINARY_OP 27 __add__
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb6, // LOAD_FAST 6
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR 'client_id'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'lw_topic'
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'lw_topic'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'lw_msg'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x12, // LOAD_ATTR 'user'
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb0, // LOAD_FAST 0
    0x13,0x12, // LOAD_ATTR 'user'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'pswd'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x36,0x01, // CALL_METHOD 1
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x83, // LOAD_CONST_SMALL_INT 3
    0x55, // LOAD_SUBSCR
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x06, // LOAD_GLOBAL 'MQTTException'
    0xb9, // LOAD_FAST 9
    0x83, // LOAD_CONST_SMALL_INT 3
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb9, // LOAD_FAST 9
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xef, // BINARY_OP 24 __and__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_connect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_connect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 398,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 33,
        .line_info = fun_data_umqtt_simple_MQTTClient_connect + 8,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_connect + 8,
        .opcodes = fun_data_umqtt_simple_MQTTClient_connect + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_connect fun_data_umqtt_simple_MQTTClient_connect[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_disconnect
static const byte fun_data_umqtt_simple_MQTTClient_disconnect[24] = {
    0x19,0x04, // prelude
    0x27,0x37, // names: disconnect, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x22, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_disconnect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_disconnect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 24,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data_umqtt_simple_MQTTClient_disconnect + 4,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_disconnect + 4,
        .opcodes = fun_data_umqtt_simple_MQTTClient_disconnect + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_disconnect fun_data_umqtt_simple_MQTTClient_disconnect[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_ping
static const byte fun_data_umqtt_simple_MQTTClient_ping[16] = {
    0x19,0x04, // prelude
    0x28,0x37, // names: ping, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_ping = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_ping,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 40,
        .line_info = fun_data_umqtt_simple_MQTTClient_ping + 4,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_ping + 4,
        .opcodes = fun_data_umqtt_simple_MQTTClient_ping + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_ping fun_data_umqtt_simple_MQTTClient_ping[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_publish
static const byte fun_data_umqtt_simple_MQTTClient_publish[193] = {
    0x81,0x94,0x01,0x0c, // prelude
    0x29,0x37,0x3c,0x3d,0x3e,0x3f, // names: publish, self, topic, msg, retain, qos
     // code info
    0x12,0x42, // LOAD_GLOBAL 'bytearray'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x80, // LOAD_CONST_SMALL_INT 0
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf0, // BINARY_OP 25 __lshift__
    0xb3, // LOAD_FAST 3
    0xed, // BINARY_OP 22 __or__
    0xe0, // BINARY_OP 9 __ior__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0x82, // LOAD_CONST_SMALL_INT 2
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xc6, // STORE_FAST 6
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0xb6, // LOAD_FAST 6
    0x82, // LOAD_CONST_SMALL_INT 2
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x12,0x08, // LOAD_GLOBAL '_encode_len'
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x34,0x02, // CALL_FUNCTION 2
    0xc7, // STORE_FAST 7
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb5, // LOAD_FAST 5
    0xb7, // LOAD_FAST 7
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x63, // POP_JUMP_IF_FALSE 35
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x10, // LOAD_ATTR 'pid'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x10, // STORE_ATTR 'pid'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'pid'
    0xc8, // STORE_FAST 8
    0x12,0x03, // LOAD_GLOBAL 'struct'
    0x14,0x2a, // LOAD_METHOD 'pack_into'
    0x10,0x1c, // LOAD_CONST_STRING '!H'
    0xb5, // LOAD_FAST 5
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb8, // LOAD_FAST 8
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb5, // LOAD_FAST 5
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x74, // POP_JUMP_IF_FALSE 52
    0xb0, // LOAD_FAST 0
    0x14,0x2b, // LOAD_METHOD 'wait_msg'
    0x36,0x00, // CALL_METHOD 0
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x22,0x80,0x40, // LOAD_CONST_SMALL_INT 64
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x63, // POP_JUMP_IF_FALSE 35
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0xca, // STORE_FAST 10
    0xba, // LOAD_FAST 10
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xba, // LOAD_FAST 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xed, // BINARY_OP 22 __or__
    0xca, // STORE_FAST 10
    0xb8, // LOAD_FAST 8
    0xba, // LOAD_FAST 10
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x42,0x0e, // JUMP -50
    0x42,0x47, // JUMP 7
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x40, // JUMP 0
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_publish = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_publish,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 193,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_umqtt_simple_MQTTClient_publish + 10,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_publish + 10,
        .opcodes = fun_data_umqtt_simple_MQTTClient_publish + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_publish fun_data_umqtt_simple_MQTTClient_publish[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient__send_subunsub
static const byte fun_data_umqtt_simple_MQTTClient__send_subunsub[159] = {
    0x82,0x15,0x0e, // prelude
    0x2c,0x37,0x3c,0x43,0x44,0x45,0x3f, // names: _send_subunsub, self, topic, typ, ack_op, ack_n, qos
     // code info
    0x12,0x42, // LOAD_GLOBAL 'bytearray'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0xb2, // LOAD_FAST 2
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x10, // LOAD_ATTR 'pid'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x10, // STORE_ATTR 'pid'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'pid'
    0xc7, // STORE_FAST 7
    0x12,0x08, // LOAD_GLOBAL '_encode_len'
    0xb6, // LOAD_FAST 6
    0x84, // LOAD_CONST_SMALL_INT 4
    0x12,0x3a, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0xb4, // LOAD_FAST 4
    0x83, // LOAD_CONST_SMALL_INT 3
    0xd8, // BINARY_OP 1 __gt__
    0xf2, // BINARY_OP 27 __add__
    0x34,0x02, // CALL_FUNCTION 2
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb6, // LOAD_FAST 6
    0xb8, // LOAD_FAST 8
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x12,0x03, // LOAD_GLOBAL 'struct'
    0x14,0x2a, // LOAD_METHOD 'pack_into'
    0x10,0x1c, // LOAD_CONST_STRING '!H'
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb7, // LOAD_FAST 7
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb6, // LOAD_FAST 6
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x19, // LOAD_METHOD '_send_str'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x83, // LOAD_CONST_SMALL_INT 3
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0x12,0x46, // LOAD_GLOBAL 'bytes'
    0xb5, // LOAD_FAST 5
    0x2a,0x01, // BUILD_TUPLE 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x2b, // LOAD_METHOD 'wait_msg'
    0x36,0x00, // CALL_METHOD 0
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0xb3, // LOAD_FAST 3
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x61, // POP_JUMP_IF_FALSE 33
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0xca, // STORE_FAST 10
    0xb4, // LOAD_FAST 4
    0x83, // LOAD_CONST_SMALL_INT 3
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0xba, // LOAD_FAST 10
    0x83, // LOAD_CONST_SMALL_INT 3
    0x55, // LOAD_SUBSCR
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x06, // LOAD_GLOBAL 'MQTTException'
    0xba, // LOAD_FAST 10
    0x83, // LOAD_CONST_SMALL_INT 3
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x42,0x12, // JUMP -46
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient__send_subunsub = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient__send_subunsub,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 159,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_umqtt_simple_MQTTClient__send_subunsub + 10,
        .line_info_top = fun_data_umqtt_simple_MQTTClient__send_subunsub + 10,
        .opcodes = fun_data_umqtt_simple_MQTTClient__send_subunsub + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient__send_subunsub fun_data_umqtt_simple_MQTTClient__send_subunsub[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_subscribe
static const byte fun_data_umqtt_simple_MQTTClient_subscribe[24] = {
    0xcb,0x01,0x08, // prelude
    0x2d,0x37,0x3c,0x3f, // names: subscribe, self, topic, qos
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_subunsub'
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x02, // LOAD_CONST_SMALL_INT 130
    0x22,0x81,0x10, // LOAD_CONST_SMALL_INT 144
    0x84, // LOAD_CONST_SMALL_INT 4
    0xb2, // LOAD_FAST 2
    0x36,0x05, // CALL_METHOD 5
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_subscribe = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_subscribe,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 24,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_umqtt_simple_MQTTClient_subscribe + 7,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_subscribe + 7,
        .opcodes = fun_data_umqtt_simple_MQTTClient_subscribe + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_subscribe fun_data_umqtt_simple_MQTTClient_subscribe[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_unsubscribe
static const byte fun_data_umqtt_simple_MQTTClient_unsubscribe[21] = {
    0x3a,0x06, // prelude
    0x2e,0x37,0x3c, // names: unsubscribe, self, topic
     // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_subunsub'
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x22, // LOAD_CONST_SMALL_INT 162
    0x22,0x81,0x30, // LOAD_CONST_SMALL_INT 176
    0x83, // LOAD_CONST_SMALL_INT 3
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_unsubscribe = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_unsubscribe,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 21,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_umqtt_simple_MQTTClient_unsubscribe + 5,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_unsubscribe + 5,
        .opcodes = fun_data_umqtt_simple_MQTTClient_unsubscribe + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_unsubscribe fun_data_umqtt_simple_MQTTClient_unsubscribe[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_wait_msg
static const byte fun_data_umqtt_simple_MQTTClient_wait_msg[209] = {
    0x71,0x04, // prelude
    0x2b,0x37, // names: wait_msg, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x2f, // LOAD_METHOD 'setblocking'
    0x52, // LOAD_CONST_TRUE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x23,0x05, // LOAD_CONST_OBJ 5
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x47, // LOAD_GLOBAL 'OSError'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc2, // STORE_FAST 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x70, // LOAD_CONST_SMALL_INT 240
    0xef, // BINARY_OP 24 __and__
    0x22,0x30, // LOAD_CONST_SMALL_INT 48
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb3, // LOAD_FAST 3
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x14,0x1d, // LOAD_METHOD '_recv_len'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xed, // BINARY_OP 22 __or__
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf2, // BINARY_OP 27 __add__
    0xe6, // BINARY_OP 15 __isub__
    0xc2, // STORE_FAST 2
    0xb3, // LOAD_FAST 3
    0x86, // LOAD_CONST_SMALL_INT 6
    0xef, // BINARY_OP 24 __and__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xed, // BINARY_OP 22 __or__
    0xc6, // STORE_FAST 6
    0xb2, // LOAD_FAST 2
    0x82, // LOAD_CONST_SMALL_INT 2
    0xe6, // BINARY_OP 15 __isub__
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1e, // LOAD_METHOD 'read'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc7, // STORE_FAST 7
    0xb0, // LOAD_FAST 0
    0x14,0x11, // LOAD_METHOD 'cb'
    0xb5, // LOAD_FAST 5
    0xb7, // LOAD_FAST 7
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x86, // LOAD_CONST_SMALL_INT 6
    0xef, // BINARY_OP 24 __and__
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x5e, // POP_JUMP_IF_FALSE 30
    0x12,0x42, // LOAD_GLOBAL 'bytearray'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x34,0x01, // CALL_FUNCTION 1
    0xc8, // STORE_FAST 8
    0x12,0x03, // LOAD_GLOBAL 'struct'
    0x14,0x2a, // LOAD_METHOD 'pack_into'
    0x10,0x1c, // LOAD_CONST_STRING '!H'
    0xb8, // LOAD_FAST 8
    0x82, // LOAD_CONST_SMALL_INT 2
    0xb6, // LOAD_FAST 6
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x1a, // LOAD_METHOD 'write'
    0xb8, // LOAD_FAST 8
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x49, // JUMP 9
    0xb3, // LOAD_FAST 3
    0x86, // LOAD_CONST_SMALL_INT 6
    0xef, // BINARY_OP 24 __and__
    0x84, // LOAD_CONST_SMALL_INT 4
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x40, // JUMP 0
    0xb3, // LOAD_FAST 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_wait_msg = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_wait_msg,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 209,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 43,
        .line_info = fun_data_umqtt_simple_MQTTClient_wait_msg + 4,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_wait_msg + 4,
        .opcodes = fun_data_umqtt_simple_MQTTClient_wait_msg + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_wait_msg fun_data_umqtt_simple_MQTTClient_wait_msg[0]
#endif

// child of umqtt_simple_MQTTClient
// frozen bytecode for file umqtt/simple.py, scope umqtt_simple_MQTTClient_check_msg
static const byte fun_data_umqtt_simple_MQTTClient_check_msg[19] = {
    0x19,0x04, // prelude
    0x30,0x37, // names: check_msg, self
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0b, // LOAD_ATTR 'sock'
    0x14,0x2f, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x2b, // LOAD_METHOD 'wait_msg'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient_check_msg = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient_check_msg,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 48,
        .line_info = fun_data_umqtt_simple_MQTTClient_check_msg + 4,
        .line_info_top = fun_data_umqtt_simple_MQTTClient_check_msg + 4,
        .opcodes = fun_data_umqtt_simple_MQTTClient_check_msg + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_simple_MQTTClient_check_msg fun_data_umqtt_simple_MQTTClient_check_msg[0]
#endif

static const mp_raw_code_t *const children_umqtt_simple_MQTTClient[] = {
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient___init__,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient__send_str,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient__recv_len,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_set_callback,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_set_last_will,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_connect,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_disconnect,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_ping,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_publish,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient__send_subunsub,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_subscribe,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_unsubscribe,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_wait_msg,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient_check_msg,
};

static const mp_raw_code_truncated_t proto_fun_umqtt_simple_MQTTClient = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple_MQTTClient,
    .children = (void *)&children_umqtt_simple_MQTTClient,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 102,
    .n_children = 14,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 7,
        .line_info = fun_data_umqtt_simple_MQTTClient + 3,
        .line_info_top = fun_data_umqtt_simple_MQTTClient + 3,
        .opcodes = fun_data_umqtt_simple_MQTTClient + 3,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_umqtt_simple__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTException,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple__encode_len,
    (const mp_raw_code_t *)&proto_fun_umqtt_simple_MQTTClient,
};

static const mp_raw_code_truncated_t proto_fun_umqtt_simple__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_simple__lt_module_gt_,
    .children = (void *)&children_umqtt_simple__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 53,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_umqtt_simple__lt_module_gt_ + 3,
        .line_info_top = fun_data_umqtt_simple__lt_module_gt_ + 3,
        .opcodes = fun_data_umqtt_simple__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_umqtt_simple[72] = {
    MP_QSTR_umqtt_slash_simple_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_socket,
    MP_QSTR_struct,
    MP_QSTR_hexlify,
    MP_QSTR_binascii,
    MP_QSTR_MQTTException,
    MP_QSTR_MQTTClient,
    MP_QSTR__encode_len,
    MP_QSTR___init__,
    MP_QSTR_client_id,
    MP_QSTR_sock,
    MP_QSTR_server,
    MP_QSTR_port,
    MP_QSTR_ssl,
    MP_QSTR_ssl_params,
    MP_QSTR_pid,
    MP_QSTR_cb,
    MP_QSTR_user,
    MP_QSTR_pswd,
    MP_QSTR_keepalive,
    MP_QSTR_lw_topic,
    MP_QSTR_lw_msg,
    MP_QSTR_lw_qos,
    MP_QSTR_lw_retain,
    MP_QSTR__send_str,
    MP_QSTR_write,
    MP_QSTR_pack,
    MP_QSTR__bang_H,
    MP_QSTR__recv_len,
    MP_QSTR_read,
    MP_QSTR_set_callback,
    MP_QSTR_set_last_will,
    MP_QSTR_connect,
    MP_QSTR_close,
    MP_QSTR_settimeout,
    MP_QSTR_getaddrinfo,
    MP_QSTR_wrap_socket,
    MP_QSTR_server_hostname,
    MP_QSTR_disconnect,
    MP_QSTR_ping,
    MP_QSTR_publish,
    MP_QSTR_pack_into,
    MP_QSTR_wait_msg,
    MP_QSTR__send_subunsub,
    MP_QSTR_subscribe,
    MP_QSTR_unsubscribe,
    MP_QSTR_setblocking,
    MP_QSTR_check_msg,
    MP_QSTR_Exception,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_pkt,
    MP_QSTR_sz,
    MP_QSTR_self,
    MP_QSTR_password,
    MP_QSTR_s,
    MP_QSTR_len,
    MP_QSTR_f,
    MP_QSTR_topic,
    MP_QSTR_msg,
    MP_QSTR_retain,
    MP_QSTR_qos,
    MP_QSTR_clean_session,
    MP_QSTR_timeout,
    MP_QSTR_bytearray,
    MP_QSTR_typ,
    MP_QSTR_ack_op,
    MP_QSTR_ack_n,
    MP_QSTR_bytes,
    MP_QSTR_OSError,
};

// constants
static const mp_obj_str_t const_obj_umqtt_simple_0 = {{&mp_type_bytes}, 36565, 6, (const byte*)"\x10\x00\x00\x00\x00\x00"};
static const mp_obj_str_t const_obj_umqtt_simple_1 = {{&mp_type_bytes}, 14619, 9, (const byte*)"\x04\x4d\x51\x54\x54\x04\x02\x00\x00"};
static const mp_obj_str_t const_obj_umqtt_simple_2 = {{&mp_type_bytes}, 24037, 2, (const byte*)"\xe0\x00"};
static const mp_obj_str_t const_obj_umqtt_simple_3 = {{&mp_type_bytes}, 25093, 2, (const byte*)"\xc0\x00"};
static const mp_obj_str_t const_obj_umqtt_simple_4 = {{&mp_type_bytes}, 18805, 4, (const byte*)"\x30\x00\x00\x00"};
static const mp_obj_str_t const_obj_umqtt_simple_6 = {{&mp_type_bytes}, 46453, 1, (const byte*)"\xd0"};
static const mp_obj_str_t const_obj_umqtt_simple_7 = {{&mp_type_bytes}, 12359, 4, (const byte*)"\x40\x02\x00\x00"};

// constant table
static const mp_rom_obj_t const_obj_table_data_umqtt_simple[8] = {
    MP_ROM_PTR(&const_obj_umqtt_simple_0),
    MP_ROM_PTR(&const_obj_umqtt_simple_1),
    MP_ROM_PTR(&const_obj_umqtt_simple_2),
    MP_ROM_PTR(&const_obj_umqtt_simple_3),
    MP_ROM_PTR(&const_obj_umqtt_simple_4),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_umqtt_simple_6),
    MP_ROM_PTR(&const_obj_umqtt_simple_7),
};

static const mp_frozen_module_t frozen_module_umqtt_simple = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_umqtt_simple,
        .obj_table = (mp_obj_t *)&const_obj_table_data_umqtt_simple,
    },
    .proto_fun = &proto_fun_umqtt_simple__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module umqtt_robust
// - original source file: build/frozen_mpy/umqtt/robust.mpy
// - frozen file name: umqtt/robust.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file umqtt/robust.py, scope umqtt_robust__lt_module_gt_
static const byte fun_data_umqtt_robust__lt_module_gt_[36] = {
    0x18,0x02, // prelude
    0x01, // names: <module>
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'time'
    0x16,0x02, // STORE_NAME 'time'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x03, // LOAD_CONST_STRING 'simple'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x04, // IMPORT_NAME ''
    0x1c,0x03, // IMPORT_FROM 'simple'
    0x16,0x03, // STORE_NAME 'simple'
    0x59, // POP_TOP
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x05, // LOAD_CONST_STRING 'MQTTClient'
    0x11,0x03, // LOAD_NAME 'simple'
    0x13,0x05, // LOAD_ATTR 'MQTTClient'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x05, // STORE_NAME 'MQTTClient'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of umqtt_robust__lt_module_gt_
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient
static const byte fun_data_umqtt_robust_MQTTClient[59] = {
    0x18,0x03, // prelude
    0x05, // names: MQTTClient
    0x00, // code info
    0x11,0x13, // LOAD_NAME '__name__'
    0x16,0x14, // STORE_NAME '__module__'
    0x10,0x05, // LOAD_CONST_STRING 'MQTTClient'
    0x16,0x15, // STORE_NAME '__qualname__'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x08, // STORE_NAME 'DELAY'
    0x50, // LOAD_CONST_FALSE
    0x16,0x0a, // STORE_NAME 'DEBUG'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x06, // STORE_NAME 'delay'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x09, // STORE_NAME 'log'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0c, // STORE_NAME 'reconnect'
    0x50, // LOAD_CONST_FALSE
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x21,0x03,0x01, // MAKE_CLOSURE_DEFARGS 3
    0x16,0x0e, // STORE_NAME 'publish'
    0xb0, // LOAD_FAST 0
    0x20,0x04,0x01, // MAKE_CLOSURE 4
    0x16,0x0f, // STORE_NAME 'wait_msg'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x21,0x05,0x01, // MAKE_CLOSURE_DEFARGS 5
    0x16,0x10, // STORE_NAME 'check_msg'
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_delay
static const byte fun_data_umqtt_robust_MQTTClient_delay[17] = {
    0x22,0x06, // prelude
    0x06,0x16,0x17, // names: delay, self, i
     // code info
    0x12,0x02, // LOAD_GLOBAL 'time'
    0x14,0x07, // LOAD_METHOD 'sleep'
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR 'DELAY'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_delay = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_delay,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_umqtt_robust_MQTTClient_delay + 5,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_delay + 5,
        .opcodes = fun_data_umqtt_robust_MQTTClient_delay + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_delay fun_data_umqtt_robust_MQTTClient_delay[0]
#endif

// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_log
static const byte fun_data_umqtt_robust_MQTTClient_log[36] = {
    0x2b,0x08, // prelude
    0x09,0x16,0x18,0x19, // names: log, self, in_reconnect, e
     // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR 'DEBUG'
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb1, // LOAD_FAST 1
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x1a, // LOAD_GLOBAL 'print'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xb2, // LOAD_FAST 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x49, // JUMP 9
    0x12,0x1a, // LOAD_GLOBAL 'print'
    0x10,0x0b, // LOAD_CONST_STRING 'mqtt: %r'
    0xb2, // LOAD_FAST 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_log = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_log,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 9,
        .line_info = fun_data_umqtt_robust_MQTTClient_log + 6,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_log + 6,
        .opcodes = fun_data_umqtt_robust_MQTTClient_log + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_log fun_data_umqtt_robust_MQTTClient_log[0]
#endif

// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_reconnect
static const byte fun_data_umqtt_robust_MQTTClient_reconnect[57] = {
    0xc9,0x02,0x04, // prelude
    0x0c,0x16, // names: reconnect, self
     // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc1, // STORE_FAST 1
    0x48,0x07, // SETUP_EXCEPT 7
    0xb0, // LOAD_FAST 0
    0x14,0x0d, // LOAD_METHOD 'connect'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x5e, // POP_JUMP_IF_FALSE 30
    0xc2, // STORE_FAST 2
    0x49,0x14, // SETUP_FINALLY 20
    0xb0, // LOAD_FAST 0
    0x14,0x09, // LOAD_METHOD 'log'
    0x52, // LOAD_CONST_TRUE
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x14,0x06, // LOAD_METHOD 'delay'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc2, // STORE_FAST 2
    0x28,0x02, // DELETE_FAST 2
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x42,0x10, // JUMP -48
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_reconnect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_reconnect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 57,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_umqtt_robust_MQTTClient_reconnect + 5,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_reconnect + 5,
        .opcodes = fun_data_umqtt_robust_MQTTClient_reconnect + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_reconnect fun_data_umqtt_robust_MQTTClient_reconnect[0]
#endif

// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_publish
static const byte fun_data_umqtt_robust_MQTTClient_publish[63] = {
    0xea,0x86,0x01,0x0e, // prelude
    0x0e,0x1c,0x16,0x1d,0x1e,0x1f,0x20, // names: publish, *, self, topic, msg, retain, qos
     // code info
    0x48,0x0e, // SETUP_EXCEPT 14
    0x12,0x21, // LOAD_GLOBAL 'super'
    0x25,0x00, // LOAD_DEREF 0
    0xb1, // LOAD_FAST 1
    0x15,0x0e, // LOAD_SUPER_METHOD 'publish'
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x36,0x04, // CALL_METHOD 4
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0xc6, // STORE_FAST 6
    0x49,0x09, // SETUP_FINALLY 9
    0xb1, // LOAD_FAST 1
    0x14,0x09, // LOAD_METHOD 'log'
    0x50, // LOAD_CONST_FALSE
    0xb6, // LOAD_FAST 6
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc6, // STORE_FAST 6
    0x28,0x06, // DELETE_FAST 6
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb1, // LOAD_FAST 1
    0x14,0x0c, // LOAD_METHOD 'reconnect'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x42,0x0e, // JUMP -50
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_publish = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_publish,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 63,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_umqtt_robust_MQTTClient_publish + 11,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_publish + 11,
        .opcodes = fun_data_umqtt_robust_MQTTClient_publish + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_publish fun_data_umqtt_robust_MQTTClient_publish[0]
#endif

// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_wait_msg
static const byte fun_data_umqtt_robust_MQTTClient_wait_msg[54] = {
    0xca,0x02,0x06, // prelude
    0x0f,0x1c,0x16, // names: wait_msg, *, self
     // code info
    0x48,0x0a, // SETUP_EXCEPT 10
    0x12,0x21, // LOAD_GLOBAL 'super'
    0x25,0x00, // LOAD_DEREF 0
    0xb1, // LOAD_FAST 1
    0x15,0x0f, // LOAD_SUPER_METHOD 'wait_msg'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0xc2, // STORE_FAST 2
    0x49,0x09, // SETUP_FINALLY 9
    0xb1, // LOAD_FAST 1
    0x14,0x09, // LOAD_METHOD 'log'
    0x50, // LOAD_CONST_FALSE
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc2, // STORE_FAST 2
    0x28,0x02, // DELETE_FAST 2
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb1, // LOAD_FAST 1
    0x14,0x0c, // LOAD_METHOD 'reconnect'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x42,0x12, // JUMP -46
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_wait_msg = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_wait_msg,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 54,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_umqtt_robust_MQTTClient_wait_msg + 6,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_wait_msg + 6,
        .opcodes = fun_data_umqtt_robust_MQTTClient_wait_msg + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_wait_msg fun_data_umqtt_robust_MQTTClient_wait_msg[0]
#endif

// child of umqtt_robust_MQTTClient
// frozen bytecode for file umqtt/robust.py, scope umqtt_robust_MQTTClient_check_msg
static const byte fun_data_umqtt_robust_MQTTClient_check_msg[71] = {
    0xd3,0x03,0x08, // prelude
    0x10,0x1c,0x16,0x22, // names: check_msg, *, self, attempts
     // code info
    0x42,0x79, // JUMP 57
    0xb1, // LOAD_FAST 1
    0x13,0x11, // LOAD_ATTR 'sock'
    0x14,0x12, // LOAD_METHOD 'setblocking'
    0x50, // LOAD_CONST_FALSE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x48,0x0a, // SETUP_EXCEPT 10
    0x12,0x21, // LOAD_GLOBAL 'super'
    0x25,0x00, // LOAD_DEREF 0
    0xb1, // LOAD_FAST 1
    0x15,0x0f, // LOAD_SUPER_METHOD 'wait_msg'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x57, // DUP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'OSError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0xc3, // STORE_FAST 3
    0x49,0x09, // SETUP_FINALLY 9
    0xb1, // LOAD_FAST 1
    0x14,0x09, // LOAD_METHOD 'log'
    0x50, // LOAD_CONST_FALSE
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc3, // STORE_FAST 3
    0x28,0x03, // DELETE_FAST 3
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb1, // LOAD_FAST 1
    0x14,0x0c, // LOAD_METHOD 'reconnect'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe6, // BINARY_OP 15 __isub__
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x43,0x04, // POP_JUMP_IF_TRUE -60
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient_check_msg = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient_check_msg,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 71,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 16,
        .line_info = fun_data_umqtt_robust_MQTTClient_check_msg + 7,
        .line_info_top = fun_data_umqtt_robust_MQTTClient_check_msg + 7,
        .opcodes = fun_data_umqtt_robust_MQTTClient_check_msg + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_umqtt_robust_MQTTClient_check_msg fun_data_umqtt_robust_MQTTClient_check_msg[0]
#endif

static const mp_raw_code_t *const children_umqtt_robust_MQTTClient[] = {
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_delay,
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_log,
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_reconnect,
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_publish,
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_wait_msg,
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient_check_msg,
};

static const mp_raw_code_truncated_t proto_fun_umqtt_robust_MQTTClient = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust_MQTTClient,
    .children = (void *)&children_umqtt_robust_MQTTClient,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 59,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 5,
        .line_info = fun_data_umqtt_robust_MQTTClient + 3,
        .line_info_top = fun_data_umqtt_robust_MQTTClient + 3,
        .opcodes = fun_data_umqtt_robust_MQTTClient + 4,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_umqtt_robust__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_umqtt_robust_MQTTClient,
};

static const mp_raw_code_truncated_t proto_fun_umqtt_robust__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_umqtt_robust__lt_module_gt_,
    .children = (void *)&children_umqtt_robust__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_umqtt_robust__lt_module_gt_ + 3,
        .line_info_top = fun_data_umqtt_robust__lt_module_gt_ + 3,
        .opcodes = fun_data_umqtt_robust__lt_module_gt_ + 3,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_umqtt_robust[35] = {
    MP_QSTR_umqtt_slash_robust_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_time,
    MP_QSTR_simple,
    MP_QSTR_,
    MP_QSTR_MQTTClient,
    MP_QSTR_delay,
    MP_QSTR_sleep,
    MP_QSTR_DELAY,
    MP_QSTR_log,
    MP_QSTR_DEBUG,
    MP_QSTR_mqtt_colon__space__percent_r,
    MP_QSTR_reconnect,
    MP_QSTR_connect,
    MP_QSTR_publish,
    MP_QSTR_wait_msg,
    MP_QSTR_check_msg,
    MP_QSTR_sock,
    MP_QSTR_setblocking,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_i,
    MP_QSTR_in_reconnect,
    MP_QSTR_e,
    MP_QSTR_print,
    MP_QSTR_OSError,
    MP_QSTR__star_,
    MP_QSTR_topic,
    MP_QSTR_msg,
    MP_QSTR_retain,
    MP_QSTR_qos,
    MP_QSTR_super,
    MP_QSTR_attempts,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data_umqtt_robust[1] = {
    MP_ROM_QSTR(MP_QSTR_mqtt_space_reconnect_colon__space__percent_r),
};

static const mp_frozen_module_t frozen_module_umqtt_robust = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_umqtt_robust,
        .obj_table = (mp_obj_t *)&const_obj_table_data_umqtt_robust,
    },
    .proto_fun = &proto_fun_umqtt_robust__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module aiohttp_aiohttp_ws
// - original source file: build/frozen_mpy/aiohttp/aiohttp_ws.mpy
// - frozen file name: aiohttp/aiohttp_ws.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws__lt_module_gt_
static const byte fun_data_aiohttp_aiohttp_ws__lt_module_gt_[149] = {
    0x10,0x30, // prelude
    0x01, // names: <module>
    0x60,0x40,0x26,0x26,0x26,0x26,0x26,0x26,0x4c,0x2a,0x6a,0x84,0x15,0x69,0x60,0x69,0x60,0x89,0xa5,0x89,0x2f,0x89,0x0d, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'asyncio'
    0x16,0x02, // STORE_NAME 'asyncio'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'random'
    0x16,0x03, // STORE_NAME 'random'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x04, // IMPORT_NAME 'json'
    0x16,0x66, // STORE_NAME '_json'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x05, // IMPORT_NAME 'binascii'
    0x16,0x05, // STORE_NAME 'binascii'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x06, // IMPORT_NAME 're'
    0x16,0x06, // STORE_NAME 're'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x07, // IMPORT_NAME 'struct'
    0x16,0x07, // STORE_NAME 'struct'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x08, // LOAD_CONST_STRING 'namedtuple'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x09, // IMPORT_NAME 'collections'
    0x1c,0x08, // IMPORT_FROM 'namedtuple'
    0x16,0x08, // STORE_NAME 'namedtuple'
    0x59, // POP_TOP
    0x11,0x06, // LOAD_NAME 're'
    0x14,0x0a, // LOAD_METHOD 'compile'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x36,0x01, // CALL_METHOD 1
    0x16,0x67, // STORE_NAME 'URL_RE'
    0x11,0x08, // LOAD_NAME 'namedtuple'
    0x10,0x0b, // LOAD_CONST_STRING 'URI'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0b, // STORE_NAME 'URI'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x12, // STORE_NAME 'urlparse'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x0c, // LOAD_CONST_STRING 'WebSocketMessage'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0c, // STORE_NAME 'WebSocketMessage'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x0d, // LOAD_CONST_STRING 'WSMsgType'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0d, // STORE_NAME 'WSMsgType'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x03, // MAKE_FUNCTION 3
    0x10,0x0e, // LOAD_CONST_STRING 'WebSocketClient'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0e, // STORE_NAME 'WebSocketClient'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x04, // MAKE_FUNCTION 4
    0x10,0x0f, // LOAD_CONST_STRING 'ClientWebSocketResponse'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0f, // STORE_NAME 'ClientWebSocketResponse'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x05, // MAKE_FUNCTION 5
    0x10,0x10, // LOAD_CONST_STRING '_WSRequestContextManager'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x10, // STORE_NAME '_WSRequestContextManager'
    0x10,0x11, // LOAD_CONST_STRING '0.0.8'
    0x16,0x68, // STORE_NAME '__version__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_urlparse
static const byte fun_data_aiohttp_aiohttp_ws_urlparse[121] = {
    0x51,0x24, // prelude
    0x12,0x69, // names: urlparse, uri
    0x80,0x12,0x20,0x28,0x24,0x27,0x27,0x27,0x47,0x26,0x25,0x26,0x26,0x25,0x46,0x4c, // code info
    0x12,0x67, // LOAD_GLOBAL 'URL_RE'
    0x14,0x13, // LOAD_METHOD 'match'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x44,0xd7,0x80, // POP_JUMP_IF_FALSE 87
    0xb1, // LOAD_FAST 1
    0x14,0x14, // LOAD_METHOD 'group'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x14,0x14, // LOAD_METHOD 'group'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0x14,0x14, // LOAD_METHOD 'group'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb1, // LOAD_FAST 1
    0x14,0x14, // LOAD_METHOD 'group'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0xb2, // LOAD_FAST 2
    0x10,0x15, // LOAD_CONST_STRING 'wss'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x83,0x3b, // LOAD_CONST_SMALL_INT 443
    0xc4, // STORE_FAST 4
    0x42,0x5d, // JUMP 29
    0xb2, // LOAD_FAST 2
    0x10,0x16, // LOAD_CONST_STRING 'ws'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x80,0x50, // LOAD_CONST_SMALL_INT 80
    0xc4, // STORE_FAST 4
    0x42,0x4c, // JUMP 12
    0x12,0x6a, // LOAD_GLOBAL 'ValueError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x14,0x17, // LOAD_METHOD 'format'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x0b, // LOAD_GLOBAL 'URI'
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x12,0x6b, // LOAD_GLOBAL 'int'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0xb5, // LOAD_FAST 5
    0x34,0x04, // CALL_FUNCTION 4
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_urlparse = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_urlparse,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 121,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_aiohttp_aiohttp_ws_urlparse + 4,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_urlparse + 20,
        .opcodes = fun_data_aiohttp_aiohttp_ws_urlparse + 20,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_urlparse fun_data_aiohttp_aiohttp_ws_urlparse[0]
#endif

// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketMessage
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketMessage[19] = {
    0x00,0x06, // prelude
    0x0c, // names: WebSocketMessage
    0x88,0x27, // code info
    0x11,0x6c, // LOAD_NAME '__name__'
    0x16,0x6d, // STORE_NAME '__module__'
    0x10,0x0c, // LOAD_CONST_STRING 'WebSocketMessage'
    0x16,0x6e, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x18, // STORE_NAME '__init__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_WebSocketMessage
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketMessage___init__
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__[19] = {
    0x23,0x0e, // prelude
    0x18,0x72,0x73,0x1a, // names: __init__, self, opcode, data
    0x80,0x28,0x24, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x19, // STORE_ATTR 'type'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x1a, // STORE_ATTR 'data'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketMessage___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__ + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__ + 9,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__ + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketMessage___init__ fun_data_aiohttp_aiohttp_ws_WebSocketMessage___init__[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_WebSocketMessage[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketMessage___init__,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketMessage = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketMessage,
    .children = (void *)&children_aiohttp_aiohttp_ws_WebSocketMessage,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketMessage + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketMessage + 5,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketMessage + 5,
    },
    #endif
    #endif
};

// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WSMsgType
static const byte fun_data_aiohttp_aiohttp_ws_WSMsgType[28] = {
    0x00,0x0a, // prelude
    0x0d, // names: WSMsgType
    0x88,0x2d,0x23,0x23, // code info
    0x11,0x6c, // LOAD_NAME '__name__'
    0x16,0x6d, // STORE_NAME '__module__'
    0x10,0x0d, // LOAD_CONST_STRING 'WSMsgType'
    0x16,0x6e, // STORE_NAME '__qualname__'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x27, // STORE_NAME 'TEXT'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x29, // STORE_NAME 'BINARY'
    0x22,0x82,0x02, // LOAD_CONST_SMALL_INT 258
    0x16,0x6f, // STORE_NAME 'ERROR'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WSMsgType = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WSMsgType,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_aiohttp_aiohttp_ws_WSMsgType + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WSMsgType + 7,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WSMsgType + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WSMsgType fun_data_aiohttp_aiohttp_ws_WSMsgType[0]
#endif

// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient[114] = {
    0x08,0x36, // prelude
    0x0e, // names: WebSocketClient
    0x88,0x33,0x23,0x23,0x23,0x23,0x23,0x43,0x64,0x60,0x89,0x08,0x88,0x0e,0x84,0x0e,0x88,0x25,0x84,0x1d,0x84,0x10,0x88,0x07,0x64,0x40, // code info
    0x11,0x6c, // LOAD_NAME '__name__'
    0x16,0x6d, // STORE_NAME '__module__'
    0x10,0x0e, // LOAD_CONST_STRING 'WebSocketClient'
    0x16,0x6e, // STORE_NAME '__qualname__'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x70, // STORE_NAME 'CONT'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x27, // STORE_NAME 'TEXT'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x29, // STORE_NAME 'BINARY'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x16,0x2a, // STORE_NAME 'CLOSE'
    0x89, // LOAD_CONST_SMALL_INT 9
    0x16,0x2b, // STORE_NAME 'PING'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x16,0x2c, // STORE_NAME 'PONG'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x18, // STORE_NAME '__init__'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x1f, // STORE_NAME 'connect'
    0x11,0x71, // LOAD_NAME 'classmethod'
    0x32,0x02, // MAKE_FUNCTION 2
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x23, // STORE_NAME '_parse_frame_header'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x26, // STORE_NAME '_process_websocket_frame'
    0x11,0x71, // LOAD_NAME 'classmethod'
    0x32,0x04, // MAKE_FUNCTION 4
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x2d, // STORE_NAME '_encode_websocket_frame'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x22, // STORE_NAME 'handshake'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x4b, // STORE_NAME 'receive'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x07, // MAKE_FUNCTION_DEFARGS 7
    0x16,0x4d, // STORE_NAME 'send'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x50, // STORE_NAME 'close'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x4c, // STORE_NAME '_read_frame'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient___init__
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__[28] = {
    0x1a,0x10, // prelude
    0x18,0x72,0x1b, // names: __init__, self, params
    0x80,0x3b,0x24,0x24,0x24, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x1b, // STORE_ATTR 'params'
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x1c, // STORE_ATTR 'closed'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x1d, // STORE_ATTR 'reader'
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x1e, // STORE_ATTR 'writer'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__ + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient___init__ fun_data_aiohttp_aiohttp_ws_WebSocketClient___init__[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_connect
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect[55] = {
    0xc0,0xc4,0x01,0x18, // prelude
    0x1f,0x72,0x69,0x44,0x74, // names: connect, self, uri, ssl, handshake_request
    0x80,0x41,0x26,0x26,0x28,0x23,0x22, // code info
    0x12,0x12, // LOAD_GLOBAL 'urlparse'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x20, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x13,0x21, // LOAD_ATTR 'protocol'
    0x10,0x15, // LOAD_CONST_STRING 'wss'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb2, // LOAD_FAST 2
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x52, // LOAD_CONST_TRUE
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x14,0x22, // LOAD_METHOD 'handshake'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x36,0x03, // CALL_METHOD 3
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_connect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 31,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect + 9,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect + 16,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect + 16,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient_connect fun_data_aiohttp_aiohttp_ws_WebSocketClient_connect[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header[62] = {
    0x5a,0x14, // prelude
    0x23,0x75,0x76, // names: _parse_frame_header, cls, header
    0x80,0x4a,0x6d,0x2a,0x64,0x2a,0x46, // code info
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x24, // LOAD_METHOD 'unpack'
    0x10,0x25, // LOAD_CONST_STRING '!BB'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x12,0x77, // LOAD_GLOBAL 'bool'
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xef, // BINARY_OP 24 __and__
    0x34,0x01, // CALL_FUNCTION 1
    0xc4, // STORE_FAST 4
    0xb2, // LOAD_FAST 2
    0x8f, // LOAD_CONST_SMALL_INT 15
    0xef, // BINARY_OP 24 __and__
    0xc5, // STORE_FAST 5
    0x12,0x77, // LOAD_GLOBAL 'bool'
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xef, // BINARY_OP 24 __and__
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xef, // BINARY_OP 24 __and__
    0xc7, // STORE_FAST 7
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0x2a,0x04, // BUILD_TUPLE 4
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 62,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 35,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header + 12,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header fun_data_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame[85] = {
    0x2b,0x20, // prelude
    0x26,0x72,0x73,0x78, // names: _process_websocket_frame, self, opcode, payload
    0x80,0x57,0x27,0x2a,0x27,0x22,0x47,0x25,0x27,0x27,0x27,0x23, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x27, // LOAD_ATTR 'TEXT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x79, // LOAD_GLOBAL 'str'
    0xb2, // LOAD_FAST 2
    0x10,0x28, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0xc2, // STORE_FAST 2
    0x42,0x6d, // JUMP 45
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR 'BINARY'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x64, // JUMP 36
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'CLOSE'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'PING'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'PONG'
    0xb2, // LOAD_FAST 2
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x2c, // LOAD_ATTR 'PONG'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xb2, // LOAD_FAST 2
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 85,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 38,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame + 18,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame fun_data_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame[201] = {
    0x7b,0x37, // prelude
    0x2d,0x75,0x73,0x78, // names: _encode_websocket_frame, cls, opcode, payload
    0x80,0x66,0x27,0x46,0x26,0x64,0x20,0x2a,0x64,0x4a,0x27,0x24,0x4d,0x28,0x26,0x4e,0x26,0x26,0x6e,0x63,0x31,0x25,0x31,0x09, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x27, // LOAD_ATTR 'TEXT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb2, // LOAD_FAST 2
    0x14,0x2e, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x12,0x7a, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0x52, // LOAD_CONST_TRUE
    0x57, // DUP_TOP
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0xb1, // LOAD_FAST 1
    0xe0, // BINARY_OP 9 __ior__
    0xc6, // STORE_FAST 6
    0xb5, // LOAD_FAST 5
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc7, // STORE_FAST 7
    0xb3, // LOAD_FAST 3
    0x22,0x80,0x7e, // LOAD_CONST_SMALL_INT 126
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0xb7, // LOAD_FAST 7
    0xb3, // LOAD_FAST 3
    0xe0, // BINARY_OP 9 __ior__
    0xc7, // STORE_FAST 7
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x2f, // LOAD_METHOD 'pack'
    0x10,0x25, // LOAD_CONST_STRING '!BB'
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0x36,0x03, // CALL_METHOD 3
    0xc8, // STORE_FAST 8
    0x42,0x79, // JUMP 57
    0xb3, // LOAD_FAST 3
    0x22,0x84,0x80,0x00, // LOAD_CONST_SMALL_INT 65536
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb7, // LOAD_FAST 7
    0x22,0x80,0x7e, // LOAD_CONST_SMALL_INT 126
    0xe0, // BINARY_OP 9 __ior__
    0xc7, // STORE_FAST 7
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x2f, // LOAD_METHOD 'pack'
    0x10,0x30, // LOAD_CONST_STRING '!BBH'
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0xb3, // LOAD_FAST 3
    0x36,0x04, // CALL_METHOD 4
    0xc8, // STORE_FAST 8
    0x42,0x5d, // JUMP 29
    0xb3, // LOAD_FAST 3
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb7, // LOAD_FAST 7
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xe0, // BINARY_OP 9 __ior__
    0xc7, // STORE_FAST 7
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x2f, // LOAD_METHOD 'pack'
    0x10,0x31, // LOAD_CONST_STRING '!BBQ'
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0xb3, // LOAD_FAST 3
    0x36,0x04, // CALL_METHOD 4
    0xc8, // STORE_FAST 8
    0x42,0x43, // JUMP 3
    0x12,0x6a, // LOAD_GLOBAL 'ValueError'
    0x65, // RAISE_OBJ
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x2f, // LOAD_METHOD 'pack'
    0x10,0x32, // LOAD_CONST_STRING '!I'
    0x12,0x03, // LOAD_GLOBAL 'random'
    0x14,0x33, // LOAD_METHOD 'getrandbits'
    0xa0, // LOAD_CONST_SMALL_INT 32
    0x36,0x01, // CALL_METHOD 1
    0x36,0x02, // CALL_METHOD 2
    0x27,0x09, // STORE_DEREF 9
    0xb8, // LOAD_FAST 8
    0x25,0x09, // LOAD_DEREF 9
    0xe5, // BINARY_OP 14 __iadd__
    0xc8, // STORE_FAST 8
    0x12,0x7b, // LOAD_GLOBAL 'bytes'
    0xb9, // LOAD_FAST 9
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x12,0x7c, // LOAD_GLOBAL 'enumerate'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb8, // LOAD_FAST 8
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_[34] = {
    0xda,0x40,0x0e, // prelude
    0x65,0x81,0x06,0x81,0x06, // names: <genexpr>, *, *
    0x80,0x86, // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x84, // LOAD_CONST_SMALL_INT 4
    0xf8, // BINARY_OP 33 __mod__
    0x55, // LOAD_SUBSCR
    0xee, // BINARY_OP 23 __xor__
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_ + 8,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_ fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame,
    .children = (void *)&children_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 201,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame + 29,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame + 30,
    },
    #endif
    #endif
};

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_handshake
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake[245] = {
    0x98,0x54,0x32, // prelude
    0x22,0x72,0x69,0x44,0x7d, // names: handshake, self, uri, ssl, req
    0x80,0x8a,0x24,0x2f,0x35,0x3a,0x30,0x26,0x26,0x2b,0x26,0x51,0x7f,0x60,0x60,0x2b,0x27,0x4f,0x22,0x2b, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x1b, // LOAD_ATTR 'params'
    0xc4, // STORE_FAST 4
    0xb1, // LOAD_FAST 1
    0x13,0x21, // LOAD_ATTR 'protocol'
    0x10,0x15, // LOAD_CONST_STRING 'wss'
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x10,0x34, // LOAD_CONST_STRING 'http'
    0x42,0x42, // JUMP 2
    0x10,0x35, // LOAD_CONST_STRING 'https'
    0xc5, // STORE_FAST 5
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x14,0x17, // LOAD_METHOD 'format'
    0xb5, // LOAD_FAST 5
    0xb1, // LOAD_FAST 1
    0x13,0x36, // LOAD_ATTR 'hostname'
    0xb1, // LOAD_FAST 1
    0x13,0x37, // LOAD_ATTR 'port'
    0xb1, // LOAD_FAST 1
    0x13,0x38, // LOAD_ATTR 'path'
    0x45,0x02, // JUMP_IF_TRUE_OR_POP 2
    0x10,0x39, // LOAD_CONST_STRING '/'
    0x36,0x04, // CALL_METHOD 4
    0xc6, // STORE_FAST 6
    0x12,0x05, // LOAD_GLOBAL 'binascii'
    0x14,0x3a, // LOAD_METHOD 'b2a_base64'
    0x12,0x7b, // LOAD_GLOBAL 'bytes'
    0x32,0x00, // MAKE_FUNCTION 0
    0x12,0x7e, // LOAD_GLOBAL 'range'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x51, // LOAD_CONST_NONE
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc7, // STORE_FAST 7
    0x10,0x3b, // LOAD_CONST_STRING '{}:{}'
    0x14,0x17, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0x13,0x36, // LOAD_ATTR 'hostname'
    0xb1, // LOAD_FAST 1
    0x13,0x37, // LOAD_ATTR 'port'
    0x36,0x02, // CALL_METHOD 2
    0xb4, // LOAD_FAST 4
    0x10,0x3c, // LOAD_CONST_STRING 'Host'
    0x56, // STORE_SUBSCR
    0x10,0x3d, // LOAD_CONST_STRING 'Upgrade'
    0xb4, // LOAD_FAST 4
    0x10,0x3e, // LOAD_CONST_STRING 'Connection'
    0x56, // STORE_SUBSCR
    0x10,0x3f, // LOAD_CONST_STRING 'websocket'
    0xb4, // LOAD_FAST 4
    0x10,0x3d, // LOAD_CONST_STRING 'Upgrade'
    0x56, // STORE_SUBSCR
    0x12,0x79, // LOAD_GLOBAL 'str'
    0xb7, // LOAD_FAST 7
    0x10,0x28, // LOAD_CONST_STRING 'utf-8'
    0x34,0x02, // CALL_FUNCTION 2
    0xb4, // LOAD_FAST 4
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x56, // STORE_SUBSCR
    0x10,0x40, // LOAD_CONST_STRING '13'
    0xb4, // LOAD_FAST 4
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x56, // STORE_SUBSCR
    0x10,0x41, // LOAD_CONST_STRING '{}://{}:{}'
    0x14,0x17, // LOAD_METHOD 'format'
    0xb5, // LOAD_FAST 5
    0xb1, // LOAD_FAST 1
    0x13,0x36, // LOAD_ATTR 'hostname'
    0xb1, // LOAD_FAST 1
    0x13,0x37, // LOAD_ATTR 'port'
    0x36,0x03, // CALL_METHOD 3
    0xb4, // LOAD_FAST 4
    0x10,0x42, // LOAD_CONST_STRING 'Origin'
    0x56, // STORE_SUBSCR
    0xb3, // LOAD_FAST 3
    0x10,0x43, // LOAD_CONST_STRING 'GET'
    0xb6, // LOAD_FAST 6
    0x10,0x44, // LOAD_CONST_STRING 'ssl'
    0xb2, // LOAD_FAST 2
    0x10,0x45, // LOAD_CONST_STRING 'headers'
    0xb4, // LOAD_FAST 4
    0x10,0x46, // LOAD_CONST_STRING 'is_handshake'
    0x52, // LOAD_CONST_TRUE
    0x10,0x47, // LOAD_CONST_STRING 'version'
    0x10,0x48, // LOAD_CONST_STRING 'HTTP/1.1'
    0x34,0x88,0x02, // CALL_FUNCTION 1026
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xb0, // LOAD_FAST 0
    0x18,0x1d, // STORE_ATTR 'reader'
    0xb0, // LOAD_FAST 0
    0x18,0x1e, // STORE_ATTR 'writer'
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x49, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x14,0x4a, // LOAD_METHOD 'startswith'
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x36,0x01, // CALL_METHOD 1
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0x12,0x20, // LOAD_GLOBAL 'AssertionError'
    0xb8, // LOAD_FAST 8
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x52, // JUMP 18
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x49, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x43,0x2b, // POP_JUMP_IF_TRUE -21
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_WebSocketClient_handshake
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_[28] = {
    0xc1,0x40,0x0a, // prelude
    0x65,0x81,0x06, // names: <genexpr>, *
    0x80,0x8d, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0c, // FOR_ITER 12
    0xc1, // STORE_FAST 1
    0x12,0x03, // LOAD_GLOBAL 'random'
    0x14,0x33, // LOAD_METHOD 'getrandbits'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x32, // JUMP -14
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_ + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_ + 8,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_ fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_WebSocketClient_handshake[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_handshake__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_handshake = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake,
    .children = (void *)&children_aiohttp_aiohttp_ws_WebSocketClient_handshake,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 245,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 20,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 34,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake + 8,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake + 28,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_handshake + 28,
    },
    #endif
    #endif
};

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_receive
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive[107] = {
    0xd9,0x40,0x1e, // prelude
    0x4b,0x72, // names: receive, self
    0x80,0xa7,0x20,0x2d,0x42,0x2d,0x27,0x2b,0x23,0x2b,0x27,0x24,0x48, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x4c, // LOAD_METHOD '_read_frame'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x42,0x51, // JUMP 17
    0xb0, // LOAD_FAST 0
    0x14,0x4c, // LOAD_METHOD '_read_frame'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0xb5, // LOAD_FAST 5
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0xb3, // LOAD_FAST 3
    0x44,0x2c, // POP_JUMP_IF_FALSE -20
    0xb0, // LOAD_FAST 0
    0x14,0x26, // LOAD_METHOD '_process_websocket_frame'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc6, // STORE_FAST 6
    0xc7, // STORE_FAST 7
    0xb6, // LOAD_FAST 6
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb0, // LOAD_FAST 0
    0x14,0x4d, // LOAD_METHOD 'send'
    0xb7, // LOAD_FAST 7
    0xb6, // LOAD_FAST 6
    0x36,0x02, // CALL_METHOD 2
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'CLOSE'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x1c, // STORE_ATTR 'closed'
    0xb1, // LOAD_FAST 1
    0xb7, // LOAD_FAST 7
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb7, // LOAD_FAST 7
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb1, // LOAD_FAST 1
    0xb7, // LOAD_FAST 7
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0x42,0xa9,0x7f, // JUMP -87
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_receive = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 107,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 75,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive + 18,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient_receive fun_data_aiohttp_aiohttp_ws_WebSocketClient_receive[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_send
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_send[61] = {
    0xc3,0x41,0x12, // prelude
    0x4d,0x72,0x1a,0x73, // names: send, self, data, opcode
    0x80,0xb7,0x23,0x58,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2d, // LOAD_METHOD '_encode_websocket_frame'
    0xb2, // LOAD_FAST 2
    0x45,0x11, // JUMP_IF_TRUE_OR_POP 17
    0x12,0x7f, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x79, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb0, // LOAD_FAST 0
    0x13,0x27, // LOAD_ATTR 'TEXT'
    0x42,0x43, // JUMP 3
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR 'BINARY'
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'writer'
    0x14,0x4e, // LOAD_METHOD 'write'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x1e, // LOAD_ATTR 'writer'
    0x14,0x4f, // LOAD_METHOD 'drain'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_send = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_send,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 61,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 77,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_send + 7,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_send + 12,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_send + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient_send fun_data_aiohttp_aiohttp_ws_WebSocketClient_send[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient_close
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient_close[34] = {
    0xa1,0x40,0x0c, // prelude
    0x50,0x72, // names: close, self
    0x80,0xbe,0x25,0x24, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x1c, // LOAD_ATTR 'closed'
    0x43,0x52, // POP_JUMP_IF_TRUE 18
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x1c, // STORE_ATTR 'closed'
    0xb0, // LOAD_FAST 0
    0x14,0x4d, // LOAD_METHOD 'send'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'CLOSE'
    0x36,0x02, // CALL_METHOD 2
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 80,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient_close + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient_close + 9,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient_close + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient_close fun_data_aiohttp_aiohttp_ws_WebSocketClient_close[0]
#endif

// child of aiohttp_aiohttp_ws_WebSocketClient
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__read_frame
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame[184] = {
    0xe9,0x40,0x27, // prelude
    0x4c,0x72, // names: _read_frame, self
    0x80,0xc3,0x2c,0x49,0x24,0x23,0x25,0x2c,0x27,0x38,0x27,0x58,0x23,0x2d,0x2c,0x23,0x31,0x07, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x51, // LOAD_METHOD 'readexactly'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc1, // STORE_FAST 1
    0x12,0x7a, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'CLOSE'
    0xc2, // STORE_FAST 2
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x14,0x23, // LOAD_METHOD '_parse_frame_header'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x30,0x04, // UNPACK_SEQUENCE 4
    0xc4, // STORE_FAST 4
    0xc2, // STORE_FAST 2
    0xc5, // STORE_FAST 5
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x22,0x80,0x7e, // LOAD_CONST_SMALL_INT 126
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x24, // LOAD_METHOD 'unpack'
    0x10,0x52, // LOAD_CONST_STRING '!H'
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x51, // LOAD_METHOD 'readexactly'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x36,0x02, // CALL_METHOD 2
    0x30,0x01, // UNPACK_SEQUENCE 1
    0xc6, // STORE_FAST 6
    0x42,0x5f, // JUMP 31
    0xb6, // LOAD_FAST 6
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0x12,0x07, // LOAD_GLOBAL 'struct'
    0x14,0x24, // LOAD_METHOD 'unpack'
    0x10,0x53, // LOAD_CONST_STRING '!Q'
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x51, // LOAD_METHOD 'readexactly'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x36,0x02, // CALL_METHOD 2
    0x30,0x01, // UNPACK_SEQUENCE 1
    0xc6, // STORE_FAST 6
    0x42,0x40, // JUMP 0
    0xb5, // LOAD_FAST 5
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x51, // LOAD_METHOD 'readexactly'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x27,0x07, // STORE_DEREF 7
    0xb0, // LOAD_FAST 0
    0x13,0x1d, // LOAD_ATTR 'reader'
    0x14,0x51, // LOAD_METHOD 'readexactly'
    0xb6, // LOAD_FAST 6
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc3, // STORE_FAST 3
    0xb5, // LOAD_FAST 5
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x12,0x7b, // LOAD_GLOBAL 'bytes'
    0xb7, // LOAD_FAST 7
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x12,0x7c, // LOAD_GLOBAL 'enumerate'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2a,0x03, // BUILD_TUPLE 3
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_WebSocketClient__read_frame
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_
static const byte fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_[34] = {
    0xda,0x40,0x0e, // prelude
    0x65,0x81,0x06,0x81,0x06, // names: <genexpr>, *, *
    0x80,0xd3, // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x84, // LOAD_CONST_SMALL_INT 4
    0xf8, // BINARY_OP 33 __mod__
    0x55, // LOAD_SUBSCR
    0xee, // BINARY_OP 23 __xor__
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_ + 8,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_ fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_WebSocketClient__read_frame[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__read_frame__lt_genexpr_gt_,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient__read_frame = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame,
    .children = (void *)&children_aiohttp_aiohttp_ws_WebSocketClient__read_frame,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 184,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 76,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame + 22,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient__read_frame + 23,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_WebSocketClient[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_connect,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__parse_frame_header,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__process_websocket_frame,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__encode_websocket_frame,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_handshake,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_receive,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_send,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient_close,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient__read_frame,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_WebSocketClient = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_WebSocketClient,
    .children = (void *)&children_aiohttp_aiohttp_ws_WebSocketClient,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 114,
    .n_children = 10,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_aiohttp_aiohttp_ws_WebSocketClient + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_WebSocketClient + 29,
        .opcodes = fun_data_aiohttp_aiohttp_ws_WebSocketClient + 29,
    },
    #endif
    #endif
};

// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse[69] = {
    0x00,0x22, // prelude
    0x0f, // names: ClientWebSocketResponse
    0x88,0xd8,0x64,0x64,0x84,0x07,0x64,0x64,0x40,0x64,0x40,0x64,0x64,0x60,0x64,0x60, // code info
    0x11,0x6c, // LOAD_NAME '__name__'
    0x16,0x6d, // STORE_NAME '__module__'
    0x10,0x0f, // LOAD_CONST_STRING 'ClientWebSocketResponse'
    0x16,0x6e, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x18, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x54, // STORE_NAME '__aiter__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x55, // STORE_NAME '__anext__'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x50, // STORE_NAME 'close'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x56, // STORE_NAME 'send_str'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x57, // STORE_NAME 'send_bytes'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x58, // STORE_NAME 'send_json'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x5a, // STORE_NAME 'receive_str'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x5b, // STORE_NAME 'receive_bytes'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x5c, // STORE_NAME 'receive_json'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse___init__
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__[14] = {
    0x1a,0x0c, // prelude
    0x18,0x72,0x81,0x00, // names: __init__, self, wsclient
    0x80,0xd9, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x16, // STORE_ATTR 'ws'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__ + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__ + 8,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__ fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__[8] = {
    0x09,0x08, // prelude
    0x54,0x72, // names: __aiter__, self
    0x80,0xdc, // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 8,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 84,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__ + 4,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__ + 6,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__ fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__[55] = {
    0xa1,0x40,0x0e, // prelude
    0x55,0x72, // names: __anext__, self
    0x80,0xdf,0x50,0x37,0x24, // code info
    0x12,0x0c, // LOAD_GLOBAL 'WebSocketMessage'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x4b, // LOAD_METHOD 'receive'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x81, // LOAD_CONST_SMALL_INT 1
    0x35,0x01, // CALL_FUNCTION_VAR_KW 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x13,0x1a, // LOAD_ATTR 'data'
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0xb1, // LOAD_FAST 1
    0x13,0x19, // LOAD_ATTR 'type'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x13,0x2a, // LOAD_ATTR 'CLOSE'
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x13,0x1c, // LOAD_ATTR 'closed'
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x12,0x81,0x01, // LOAD_GLOBAL 'StopAsyncIteration'
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 85,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__ + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__ fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_close
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close[20] = {
    0x91,0x40,0x08, // prelude
    0x50,0x72, // names: close, self
    0x80,0xe6, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x50, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 80,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close + 7,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_close fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_close[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str[47] = {
    0xaa,0x40,0x0e, // prelude
    0x56,0x72,0x1a, // names: send_str, self, data
    0x80,0xe9,0x29,0x2e, // code info
    0x12,0x7f, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x79, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x12,0x81,0x02, // LOAD_GLOBAL 'TypeError'
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0x12,0x19, // LOAD_GLOBAL 'type'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x4d, // LOAD_METHOD 'send'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 47,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 86,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes[55] = {
    0xb2,0x40,0x0e, // prelude
    0x57,0x72,0x1a, // names: send_bytes, self, data
    0x80,0xee,0x31,0x2e, // code info
    0x12,0x7f, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x7b, // LOAD_GLOBAL 'bytes'
    0x12,0x81,0x03, // LOAD_GLOBAL 'bytearray'
    0x12,0x81,0x04, // LOAD_GLOBAL 'memoryview'
    0x2a,0x03, // BUILD_TUPLE 3
    0x34,0x02, // CALL_FUNCTION 2
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x12,0x81,0x02, // LOAD_GLOBAL 'TypeError'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x12,0x19, // LOAD_GLOBAL 'type'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x4d, // LOAD_METHOD 'send'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 87,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json[26] = {
    0xb2,0x40,0x0a, // prelude
    0x58,0x72,0x1a, // names: send_json, self, data
    0x80,0xf3, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x56, // LOAD_METHOD 'send_str'
    0x12,0x66, // LOAD_GLOBAL '_json'
    0x14,0x59, // LOAD_METHOD 'dumps'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 88,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json + 6,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json + 8,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str[59] = {
    0xb1,0x40,0x0e, // prelude
    0x5a,0x72, // names: receive_str, self
    0x80,0xf6,0x30,0x2b,0x32, // code info
    0x12,0x0c, // LOAD_GLOBAL 'WebSocketMessage'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x4b, // LOAD_METHOD 'receive'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x81, // LOAD_CONST_SMALL_INT 1
    0x35,0x01, // CALL_FUNCTION_VAR_KW 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x13,0x19, // LOAD_ATTR 'type'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x13,0x27, // LOAD_ATTR 'TEXT'
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0x12,0x81,0x02, // LOAD_GLOBAL 'TypeError'
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0x14,0x17, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0x13,0x19, // LOAD_ATTR 'type'
    0xb1, // LOAD_FAST 1
    0x13,0x1a, // LOAD_ATTR 'data'
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x13,0x1a, // LOAD_ATTR 'data'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 59,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 90,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes[59] = {
    0xb1,0x40,0x0e, // prelude
    0x5b,0x72, // names: receive_bytes, self
    0x80,0xfc,0x30,0x2b,0x32, // code info
    0x12,0x0c, // LOAD_GLOBAL 'WebSocketMessage'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x14,0x4b, // LOAD_METHOD 'receive'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x81, // LOAD_CONST_SMALL_INT 1
    0x35,0x01, // CALL_FUNCTION_VAR_KW 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x13,0x19, // LOAD_ATTR 'type'
    0xb0, // LOAD_FAST 0
    0x13,0x16, // LOAD_ATTR 'ws'
    0x13,0x29, // LOAD_ATTR 'BINARY'
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0x12,0x81,0x02, // LOAD_GLOBAL 'TypeError'
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x14,0x17, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0x13,0x19, // LOAD_ATTR 'type'
    0xb1, // LOAD_FAST 1
    0x13,0x1a, // LOAD_ATTR 'data'
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x13,0x1a, // LOAD_ATTR 'data'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 59,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 91,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes[0]
#endif

// child of aiohttp_aiohttp_ws_ClientWebSocketResponse
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json
static const byte fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json[25] = {
    0xa1,0x40,0x0a, // prelude
    0x5c,0x72, // names: receive_json, self
    0x90,0x02,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x5a, // LOAD_METHOD 'receive_str'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc1, // STORE_FAST 1
    0x12,0x66, // LOAD_GLOBAL '_json'
    0x14,0x5d, // LOAD_METHOD 'loads'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 92,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json + 8,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws_ClientWebSocketResponse[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___aiter__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse___anext__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_close,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_str,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_bytes,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_send_json,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_str,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_bytes,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse_receive_json,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse,
    .children = (void *)&children_aiohttp_aiohttp_ws_ClientWebSocketResponse,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 69,
    .n_children = 10,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse + 19,
        .opcodes = fun_data_aiohttp_aiohttp_ws_ClientWebSocketResponse + 19,
    },
    #endif
    #endif
};

// child of aiohttp_aiohttp_ws__lt_module_gt_
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws__WSRequestContextManager
static const byte fun_data_aiohttp_aiohttp_ws__WSRequestContextManager[30] = {
    0x00,0x0c, // prelude
    0x10, // names: _WSRequestContextManager
    0x98,0x07,0x64,0x20,0x64, // code info
    0x11,0x6c, // LOAD_NAME '__name__'
    0x16,0x6d, // STORE_NAME '__module__'
    0x10,0x10, // LOAD_CONST_STRING '_WSRequestContextManager'
    0x16,0x6e, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x18, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x60, // STORE_NAME '__aenter__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x61, // STORE_NAME '__aexit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp_aiohttp_ws__WSRequestContextManager
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws__WSRequestContextManager___init__
static const byte fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__[20] = {
    0x23,0x10, // prelude
    0x18,0x72,0x5f,0x81,0x05, // names: __init__, self, client, request_co
    0x90,0x08,0x24, // code info
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x5e, // STORE_ATTR 'reqco'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x5f, // STORE_ATTR 'client'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__ + 7,
        .line_info_top = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___init__ fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___init__[0]
#endif

// child of aiohttp_aiohttp_ws__WSRequestContextManager
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws__WSRequestContextManager___aenter__
static const byte fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__[14] = {
    0x91,0x40,0x08, // prelude
    0x60,0x72, // names: __aenter__, self
    0x90,0x0c, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x5e, // LOAD_ATTR 'reqco'
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 96,
        .line_info = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__ + 5,
        .line_info_top = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__ + 7,
        .opcodes = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__ fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__[0]
#endif

// child of aiohttp_aiohttp_ws__WSRequestContextManager
// frozen bytecode for file aiohttp/aiohttp_ws.py, scope aiohttp_aiohttp_ws__WSRequestContextManager___aexit__
static const byte fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__[34] = {
    0xa1,0xc0,0x80,0x40,0x0a, // prelude
    0x61,0x72, // names: __aexit__, self
    0x90,0x0f,0x2d, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x5f, // LOAD_ATTR 'client'
    0x13,0x62, // LOAD_ATTR '_reader'
    0x14,0x63, // LOAD_METHOD 'aclose'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'asyncio'
    0x14,0x64, // LOAD_METHOD 'sleep'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 5,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 97,
        .line_info = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__ + 7,
        .line_info_top = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__ + 10,
        .opcodes = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__ fun_data_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__[0]
#endif

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws__WSRequestContextManager[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aenter__,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager___aexit__,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager,
    .children = (void *)&children_aiohttp_aiohttp_ws__WSRequestContextManager,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 30,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 16,
        .line_info = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager + 8,
        .opcodes = fun_data_aiohttp_aiohttp_ws__WSRequestContextManager + 8,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_aiohttp_aiohttp_ws__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_urlparse,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketMessage,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WSMsgType,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_WebSocketClient,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws_ClientWebSocketResponse,
    (const mp_raw_code_t *)&proto_fun_aiohttp_aiohttp_ws__WSRequestContextManager,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp_aiohttp_ws__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp_aiohttp_ws__lt_module_gt_,
    .children = (void *)&children_aiohttp_aiohttp_ws__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 149,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_aiohttp_aiohttp_ws__lt_module_gt_ + 3,
        .line_info_top = fun_data_aiohttp_aiohttp_ws__lt_module_gt_ + 26,
        .opcodes = fun_data_aiohttp_aiohttp_ws__lt_module_gt_ + 26,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_aiohttp_aiohttp_ws[135] = {
    MP_QSTR_aiohttp_slash_aiohttp_ws_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_asyncio,
    MP_QSTR_random,
    MP_QSTR_json,
    MP_QSTR_binascii,
    MP_QSTR_re,
    MP_QSTR_struct,
    MP_QSTR_namedtuple,
    MP_QSTR_collections,
    MP_QSTR_compile,
    MP_QSTR_URI,
    MP_QSTR_WebSocketMessage,
    MP_QSTR_WSMsgType,
    MP_QSTR_WebSocketClient,
    MP_QSTR_ClientWebSocketResponse,
    MP_QSTR__WSRequestContextManager,
    MP_QSTR_0_dot_0_dot_8,
    MP_QSTR_urlparse,
    MP_QSTR_match,
    MP_QSTR_group,
    MP_QSTR_wss,
    MP_QSTR_ws,
    MP_QSTR_format,
    MP_QSTR___init__,
    MP_QSTR_type,
    MP_QSTR_data,
    MP_QSTR_params,
    MP_QSTR_closed,
    MP_QSTR_reader,
    MP_QSTR_writer,
    MP_QSTR_connect,
    MP_QSTR_AssertionError,
    MP_QSTR_protocol,
    MP_QSTR_handshake,
    MP_QSTR__parse_frame_header,
    MP_QSTR_unpack,
    MP_QSTR__bang_BB,
    MP_QSTR__process_websocket_frame,
    MP_QSTR_TEXT,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR_BINARY,
    MP_QSTR_CLOSE,
    MP_QSTR_PING,
    MP_QSTR_PONG,
    MP_QSTR__encode_websocket_frame,
    MP_QSTR_encode,
    MP_QSTR_pack,
    MP_QSTR__bang_BBH,
    MP_QSTR__bang_BBQ,
    MP_QSTR__bang_I,
    MP_QSTR_getrandbits,
    MP_QSTR_http,
    MP_QSTR_https,
    MP_QSTR_hostname,
    MP_QSTR_port,
    MP_QSTR_path,
    MP_QSTR__slash_,
    MP_QSTR_b2a_base64,
    MP_QSTR__brace_open__brace_close__colon__brace_open__brace_close_,
    MP_QSTR_Host,
    MP_QSTR_Upgrade,
    MP_QSTR_Connection,
    MP_QSTR_websocket,
    MP_QSTR_13,
    MP_QSTR__brace_open__brace_close__colon__slash__slash__brace_open__brace_close__colon__brace_open__brace_close_,
    MP_QSTR_Origin,
    MP_QSTR_GET,
    MP_QSTR_ssl,
    MP_QSTR_headers,
    MP_QSTR_is_handshake,
    MP_QSTR_version,
    MP_QSTR_HTTP_slash_1_dot_1,
    MP_QSTR_readline,
    MP_QSTR_startswith,
    MP_QSTR_receive,
    MP_QSTR__read_frame,
    MP_QSTR_send,
    MP_QSTR_write,
    MP_QSTR_drain,
    MP_QSTR_close,
    MP_QSTR_readexactly,
    MP_QSTR__bang_H,
    MP_QSTR__bang_Q,
    MP_QSTR___aiter__,
    MP_QSTR___anext__,
    MP_QSTR_send_str,
    MP_QSTR_send_bytes,
    MP_QSTR_send_json,
    MP_QSTR_dumps,
    MP_QSTR_receive_str,
    MP_QSTR_receive_bytes,
    MP_QSTR_receive_json,
    MP_QSTR_loads,
    MP_QSTR_reqco,
    MP_QSTR_client,
    MP_QSTR___aenter__,
    MP_QSTR___aexit__,
    MP_QSTR__reader,
    MP_QSTR_aclose,
    MP_QSTR_sleep,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR__json,
    MP_QSTR_URL_RE,
    MP_QSTR___version__,
    MP_QSTR_uri,
    MP_QSTR_ValueError,
    MP_QSTR_int,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_ERROR,
    MP_QSTR_CONT,
    MP_QSTR_classmethod,
    MP_QSTR_self,
    MP_QSTR_opcode,
    MP_QSTR_handshake_request,
    MP_QSTR_cls,
    MP_QSTR_header,
    MP_QSTR_bool,
    MP_QSTR_payload,
    MP_QSTR_str,
    MP_QSTR_len,
    MP_QSTR_bytes,
    MP_QSTR_enumerate,
    MP_QSTR_req,
    MP_QSTR_range,
    MP_QSTR_isinstance,
    MP_QSTR_wsclient,
    MP_QSTR_StopAsyncIteration,
    MP_QSTR_TypeError,
    MP_QSTR_bytearray,
    MP_QSTR_memoryview,
    MP_QSTR_request_co,
    MP_QSTR__star_,
};

// constants
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_0 = {{&mp_type_str}, 57511, 49, (const byte*)"\x28\x77\x73\x73\x7c\x77\x73\x29\x3a\x2f\x2f\x28\x5b\x41\x2d\x5a\x61\x2d\x7a\x30\x2d\x39\x2d\x5c\x2e\x5d\x2b\x29\x28\x3f\x3a\x5c\x3a\x28\x5b\x30\x2d\x39\x5d\x2b\x29\x29\x3f\x28\x2f\x2e\x2b\x29\x3f"};
static const mp_rom_obj_tuple_t const_obj_aiohttp_aiohttp_ws_1 = {{&mp_type_tuple}, 4, {
    MP_ROM_QSTR(MP_QSTR_protocol),
    MP_ROM_QSTR(MP_QSTR_hostname),
    MP_ROM_QSTR(MP_QSTR_port),
    MP_ROM_QSTR(MP_QSTR_path),
}};
static const mp_rom_obj_tuple_t const_obj_aiohttp_aiohttp_ws_3 = {{&mp_type_tuple}, 2, {
    MP_ROM_NONE,
    MP_ROM_NONE,
}};
static const mp_obj_int_t const_obj_aiohttp_aiohttp_ws_4 = {{&mp_type_int}, {.neg=0, .fixed_dig=1, .alloc=5, .len=5, .dig=(uint16_t*)(const uint16_t[]){0x0,0x0,0x0,0x0,0x1}}};
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_8 = {{&mp_type_bytes}, 23052, 13, (const byte*)"\x48\x54\x54\x50\x2f\x31\x2e\x31\x20\x31\x30\x31\x20"};
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_10 = {{&mp_type_str}, 58333, 30, (const byte*)"\x64\x61\x74\x61\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x73\x74\x72\x20\x28\x25\x72\x29"};
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_11 = {{&mp_type_str}, 21181, 35, (const byte*)"\x64\x61\x74\x61\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x62\x79\x74\x65\x2d\x69\x73\x68\x20\x28\x25\x72\x29"};
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_12 = {{&mp_type_str}, 36882, 35, (const byte*)"\x52\x65\x63\x65\x69\x76\x65\x64\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x7b\x7d\x3a\x7b\x21\x72\x7d\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x74\x72"};
static const mp_obj_str_t const_obj_aiohttp_aiohttp_ws_13 = {{&mp_type_str}, 23582, 37, (const byte*)"\x52\x65\x63\x65\x69\x76\x65\x64\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x7b\x7d\x3a\x7b\x21\x72\x7d\x20\x69\x73\x20\x6e\x6f\x74\x20\x62\x79\x74\x65\x73"};

// constant table
static const mp_rom_obj_t const_obj_table_data_aiohttp_aiohttp_ws[14] = {
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_0),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_1),
    MP_ROM_QSTR(MP_QSTR_Scheme_space__brace_open__brace_close__space_is_space_invalid),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_3),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_4),
    MP_ROM_QSTR(MP_QSTR__brace_open__brace_close__colon__slash__slash__brace_open__brace_close__colon__brace_open__brace_close__brace_open__brace_close_),
    MP_ROM_QSTR(MP_QSTR_Sec_hyphen_WebSocket_hyphen_Key),
    MP_ROM_QSTR(MP_QSTR_Sec_hyphen_WebSocket_hyphen_Version),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_8),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_10),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_11),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_12),
    MP_ROM_PTR(&const_obj_aiohttp_aiohttp_ws_13),
};

static const mp_frozen_module_t frozen_module_aiohttp_aiohttp_ws = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_aiohttp_aiohttp_ws,
        .obj_table = (mp_obj_t *)&const_obj_table_data_aiohttp_aiohttp_ws,
    },
    .proto_fun = &proto_fun_aiohttp_aiohttp_ws__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module aiohttp___init__
// - original source file: build/frozen_mpy/aiohttp/__init__.mpy
// - frozen file name: aiohttp/__init__.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init____lt_module_gt_
static const byte fun_data_aiohttp___init____lt_module_gt_[113] = {
    0x20,0x22, // prelude
    0x01, // names: <module>
    0x60,0x26,0x26,0x7e,0x60,0x20,0x24,0x64,0x89,0x2a,0x8b,0x1a,0x89,0x0d,0x89,0xb7, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'asyncio'
    0x16,0x02, // STORE_NAME 'asyncio'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'json'
    0x16,0x6c, // STORE_NAME '_json'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x04, // LOAD_CONST_STRING '_WSRequestContextManager'
    0x10,0x05, // LOAD_CONST_STRING 'ClientWebSocketResponse'
    0x10,0x06, // LOAD_CONST_STRING 'WebSocketClient'
    0x10,0x07, // LOAD_CONST_STRING 'WSMsgType'
    0x2a,0x04, // BUILD_TUPLE 4
    0x1b,0x08, // IMPORT_NAME 'aiohttp_ws'
    0x1c,0x04, // IMPORT_FROM '_WSRequestContextManager'
    0x16,0x04, // STORE_NAME '_WSRequestContextManager'
    0x1c,0x05, // IMPORT_FROM 'ClientWebSocketResponse'
    0x16,0x05, // STORE_NAME 'ClientWebSocketResponse'
    0x1c,0x06, // IMPORT_FROM 'WebSocketClient'
    0x16,0x06, // STORE_NAME 'WebSocketClient'
    0x1c,0x07, // IMPORT_FROM 'WSMsgType'
    0x16,0x07, // STORE_NAME 'WSMsgType'
    0x59, // POP_TOP
    0x10,0x09, // LOAD_CONST_STRING 'HTTP/1.0'
    0x16,0x6d, // STORE_NAME 'HttpVersion10'
    0x10,0x0a, // LOAD_CONST_STRING 'HTTP/1.1'
    0x16,0x6e, // STORE_NAME 'HttpVersion11'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x0b, // LOAD_CONST_STRING 'ClientResponse'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0b, // STORE_NAME 'ClientResponse'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x01, // MAKE_FUNCTION 1
    0x10,0x0c, // LOAD_CONST_STRING 'ChunkedClientResponse'
    0x11,0x0b, // LOAD_NAME 'ClientResponse'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x0c, // STORE_NAME 'ChunkedClientResponse'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x0d, // LOAD_CONST_STRING '_RequestContextManager'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0d, // STORE_NAME '_RequestContextManager'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x03, // MAKE_FUNCTION 3
    0x10,0x0e, // LOAD_CONST_STRING 'ClientSession'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0e, // STORE_NAME 'ClientSession'
    0x10,0x0f, // LOAD_CONST_STRING '0.0.8'
    0x16,0x6f, // STORE_NAME '__version__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init____lt_module_gt_
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse
static const byte fun_data_aiohttp___init___ClientResponse[61] = {
    0x08,0x18, // prelude
    0x0b, // names: ClientResponse
    0x88,0x11,0x64,0x64,0x60,0x84,0x11,0x68,0x40,0x69,0x64, // code info
    0x11,0x70, // LOAD_NAME '__name__'
    0x16,0x71, // STORE_NAME '__module__'
    0x10,0x0b, // LOAD_CONST_STRING 'ClientResponse'
    0x16,0x72, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x12, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x14, // STORE_NAME '_get_header'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x17, // STORE_NAME '_decode'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x1d, // STORE_NAME 'read'
    0x10,0x10, // LOAD_CONST_STRING 'utf-8'
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x21, // STORE_NAME 'text'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x03, // STORE_NAME 'json'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x24, // STORE_NAME '__repr__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse___init__
static const byte fun_data_aiohttp___init___ClientResponse___init__[13] = {
    0x1a,0x0a, // prelude
    0x12,0x73,0x64, // names: __init__, self, reader
    0x80,0x12, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x13, // STORE_ATTR 'content'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientResponse___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_aiohttp___init___ClientResponse___init__ + 5,
        .line_info_top = fun_data_aiohttp___init___ClientResponse___init__ + 7,
        .opcodes = fun_data_aiohttp___init___ClientResponse___init__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse___init__ fun_data_aiohttp___init___ClientResponse___init__[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse__get_header
static const byte fun_data_aiohttp___init___ClientResponse__get_header[37] = {
    0x4b,0x12, // prelude
    0x14,0x73,0x74,0x75, // names: _get_header, self, keyname, default
    0x80,0x15,0x27,0x29,0x28, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'headers'
    0x5f, // GET_ITER_STACK
    0x4b,0x12, // FOR_ITER 18
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x16, // LOAD_METHOD 'lower'
    0x36,0x00, // CALL_METHOD 0
    0xb1, // LOAD_FAST 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'headers'
    0xb3, // LOAD_FAST 3
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
    0x42,0x2c, // JUMP -20
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse__get_header = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientResponse__get_header,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 20,
        .line_info = fun_data_aiohttp___init___ClientResponse__get_header + 6,
        .line_info_top = fun_data_aiohttp___init___ClientResponse__get_header + 11,
        .opcodes = fun_data_aiohttp___init___ClientResponse__get_header + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse__get_header fun_data_aiohttp___init___ClientResponse__get_header[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse__decode
static const byte fun_data_aiohttp___init___ClientResponse__decode[136] = {
    0xda,0x02,0x22, // prelude
    0x17,0x73,0x51, // names: _decode, self, data
    0x80,0x1b,0x29,0x27,0x22,0x25,0x45,0x26,0x31,0x2a,0x26,0x32,0x53,0x2a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x14, // LOAD_METHOD '_get_header'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x51, // LOAD_CONST_NONE
    0x36,0x02, // CALL_METHOD 2
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x23,0x01, // LOAD_CONST_OBJ 1
    0xdd, // BINARY_OP 6 <in>
    0x44,0xe2,0x80, // POP_JUMP_IF_FALSE 98
    0x48,0x4f, // SETUP_EXCEPT 79
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x18, // IMPORT_NAME 'deflate'
    0xc3, // STORE_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x19, // IMPORT_NAME 'io'
    0xc4, // STORE_FAST 4
    0xb2, // LOAD_FAST 2
    0x10,0x18, // LOAD_CONST_STRING 'deflate'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x5b, // POP_JUMP_IF_FALSE 27
    0xb3, // LOAD_FAST 3
    0x14,0x1a, // LOAD_METHOD 'DeflateIO'
    0xb4, // LOAD_FAST 4
    0x14,0x1b, // LOAD_METHOD 'BytesIO'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xb3, // LOAD_FAST 3
    0x13,0x1c, // LOAD_ATTR 'ZLIB'
    0x36,0x02, // CALL_METHOD 2
    0x47,0x07, // SETUP_WITH 7
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x1d, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x42,0x62, // JUMP 34
    0xb2, // LOAD_FAST 2
    0x10,0x1e, // LOAD_CONST_STRING 'gzip'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x5c, // POP_JUMP_IF_FALSE 28
    0xb3, // LOAD_FAST 3
    0x14,0x1a, // LOAD_METHOD 'DeflateIO'
    0xb4, // LOAD_FAST 4
    0x14,0x1b, // LOAD_METHOD 'BytesIO'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xb3, // LOAD_FAST 3
    0x13,0x1f, // LOAD_ATTR 'GZIP'
    0x8f, // LOAD_CONST_SMALL_INT 15
    0x36,0x03, // CALL_METHOD 3
    0x47,0x07, // SETUP_WITH 7
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x1d, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x42,0x40, // JUMP 0
    0x4a,0x11, // POP_EXCEPT_JUMP 17
    0x57, // DUP_TOP
    0x12,0x76, // LOAD_GLOBAL 'ImportError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x59, // POP_TOP
    0x12,0x77, // LOAD_GLOBAL 'print'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse__decode = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientResponse__decode,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 136,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 23,
        .line_info = fun_data_aiohttp___init___ClientResponse__decode + 6,
        .line_info_top = fun_data_aiohttp___init___ClientResponse__decode + 20,
        .opcodes = fun_data_aiohttp___init___ClientResponse__decode + 20,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse__decode fun_data_aiohttp___init___ClientResponse__decode[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse_read
static const byte fun_data_aiohttp___init___ClientResponse_read[41] = {
    0xb2,0x41,0x0c, // prelude
    0x1d,0x73,0x78, // names: read, self, sz
    0x80,0x2c,0x23, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x17, // LOAD_METHOD '_decode'
    0xb1, // LOAD_FAST 1
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x1d, // LOAD_METHOD 'read'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x42,0x48, // JUMP 8
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x20, // LOAD_METHOD 'readexactly'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientResponse_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 41,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 29,
        .line_info = fun_data_aiohttp___init___ClientResponse_read + 6,
        .line_info_top = fun_data_aiohttp___init___ClientResponse_read + 9,
        .opcodes = fun_data_aiohttp___init___ClientResponse_read + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse_read fun_data_aiohttp___init___ClientResponse_read[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse_text
static const byte fun_data_aiohttp___init___ClientResponse_text[34] = {
    0xc2,0x41,0x0a, // prelude
    0x21,0x73,0x79, // names: text, self, encoding
    0x80,0x31, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x1d, // LOAD_METHOD 'read'
    0x12,0x7a, // LOAD_GLOBAL 'int'
    0xb0, // LOAD_FAST 0
    0x14,0x14, // LOAD_METHOD '_get_header'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x14,0x22, // LOAD_METHOD 'decode'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse_text = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientResponse_text,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 33,
        .line_info = fun_data_aiohttp___init___ClientResponse_text + 6,
        .line_info_top = fun_data_aiohttp___init___ClientResponse_text + 8,
        .opcodes = fun_data_aiohttp___init___ClientResponse_text + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse_text fun_data_aiohttp___init___ClientResponse_text[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse_json
static const byte fun_data_aiohttp___init___ClientResponse_json[34] = {
    0xc9,0x40,0x08, // prelude
    0x03,0x73, // names: json, self
    0x80,0x34, // code info
    0x12,0x6c, // LOAD_GLOBAL '_json'
    0x14,0x23, // LOAD_METHOD 'loads'
    0xb0, // LOAD_FAST 0
    0x14,0x1d, // LOAD_METHOD 'read'
    0x12,0x7a, // LOAD_GLOBAL 'int'
    0xb0, // LOAD_FAST 0
    0x14,0x14, // LOAD_METHOD '_get_header'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientResponse_json,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 3,
        .line_info = fun_data_aiohttp___init___ClientResponse_json + 5,
        .line_info_top = fun_data_aiohttp___init___ClientResponse_json + 7,
        .opcodes = fun_data_aiohttp___init___ClientResponse_json + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse_json fun_data_aiohttp___init___ClientResponse_json[0]
#endif

// child of aiohttp___init___ClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientResponse___repr__
static const byte fun_data_aiohttp___init___ClientResponse___repr__[18] = {
    0x19,0x08, // prelude
    0x24,0x73, // names: __repr__, self
    0x80,0x37, // code info
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR 'status'
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'headers'
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse___repr__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientResponse___repr__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 36,
        .line_info = fun_data_aiohttp___init___ClientResponse___repr__ + 4,
        .line_info_top = fun_data_aiohttp___init___ClientResponse___repr__ + 6,
        .opcodes = fun_data_aiohttp___init___ClientResponse___repr__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientResponse___repr__ fun_data_aiohttp___init___ClientResponse___repr__[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init___ClientResponse[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse__get_header,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse__decode,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse_read,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse_text,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse_json,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse___repr__,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientResponse = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientResponse,
    .children = (void *)&children_aiohttp___init___ClientResponse,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 61,
    .n_children = 7,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 11,
        .line_info = fun_data_aiohttp___init___ClientResponse + 3,
        .line_info_top = fun_data_aiohttp___init___ClientResponse + 14,
        .opcodes = fun_data_aiohttp___init___ClientResponse + 14,
    },
    #endif
    #endif
};

// child of aiohttp___init____lt_module_gt_
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ChunkedClientResponse
static const byte fun_data_aiohttp___init___ChunkedClientResponse[39] = {
    0x08,0x0e, // prelude
    0x0c, // names: ChunkedClientResponse
    0x88,0x3b,0x64,0x20,0x8c,0x11, // code info
    0x11,0x70, // LOAD_NAME '__name__'
    0x16,0x71, // STORE_NAME '__module__'
    0x10,0x0c, // LOAD_CONST_STRING 'ChunkedClientResponse'
    0x16,0x72, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x12, // STORE_NAME '__init__'
    0x22,0x82,0x80,0x80,0x00, // LOAD_CONST_SMALL_INT 4194304
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x1d, // STORE_NAME 'read'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x24, // STORE_NAME '__repr__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init___ChunkedClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ChunkedClientResponse___init__
static const byte fun_data_aiohttp___init___ChunkedClientResponse___init__[18] = {
    0x1a,0x0c, // prelude
    0x12,0x73,0x64, // names: __init__, self, reader
    0x80,0x3c,0x24, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x13, // STORE_ATTR 'content'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x26, // STORE_ATTR 'chunk_size'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ChunkedClientResponse___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ChunkedClientResponse___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_aiohttp___init___ChunkedClientResponse___init__ + 5,
        .line_info_top = fun_data_aiohttp___init___ChunkedClientResponse___init__ + 8,
        .opcodes = fun_data_aiohttp___init___ChunkedClientResponse___init__ + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ChunkedClientResponse___init__ fun_data_aiohttp___init___ChunkedClientResponse___init__[0]
#endif

// child of aiohttp___init___ChunkedClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ChunkedClientResponse_read
static const byte fun_data_aiohttp___init___ChunkedClientResponse_read[157] = {
    0xca,0x41,0x24, // prelude
    0x1d,0x73,0x78, // names: read, self, sz
    0x80,0x40,0x27,0x2b,0x2b,0x29,0x47,0x2c,0x29,0x23,0x33,0x2d,0x27,0x2c,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x26, // LOAD_ATTR 'chunk_size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x7e, // POP_JUMP_IF_FALSE 62
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x27, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x28, // LOAD_METHOD 'split'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc2, // STORE_FAST 2
    0x12,0x7a, // LOAD_GLOBAL 'int'
    0xb2, // LOAD_FAST 2
    0x90, // LOAD_CONST_SMALL_INT 16
    0x34,0x02, // CALL_FUNCTION 2
    0xb0, // LOAD_FAST 0
    0x18,0x26, // STORE_ATTR 'chunk_size'
    0xb0, // LOAD_FAST 0
    0x13,0x26, // LOAD_ATTR 'chunk_size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x20, // LOAD_METHOD 'readexactly'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x29, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x20, // LOAD_METHOD 'readexactly'
    0x12,0x7b, // LOAD_GLOBAL 'min'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x26, // LOAD_ATTR 'chunk_size'
    0x34,0x02, // CALL_FUNCTION 2
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x26, // LOAD_ATTR 'chunk_size'
    0x12,0x7c, // LOAD_GLOBAL 'len'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0xe6, // BINARY_OP 15 __isub__
    0x5a, // ROT_TWO
    0x18,0x26, // STORE_ATTR 'chunk_size'
    0xb0, // LOAD_FAST 0
    0x13,0x26, // LOAD_ATTR 'chunk_size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x55, // POP_JUMP_IF_FALSE 21
    0xb0, // LOAD_FAST 0
    0x13,0x13, // LOAD_ATTR 'content'
    0x14,0x20, // LOAD_METHOD 'readexactly'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x29, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x14,0x17, // LOAD_METHOD '_decode'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ChunkedClientResponse_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ChunkedClientResponse_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 157,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 29,
        .line_info = fun_data_aiohttp___init___ChunkedClientResponse_read + 6,
        .line_info_top = fun_data_aiohttp___init___ChunkedClientResponse_read + 21,
        .opcodes = fun_data_aiohttp___init___ChunkedClientResponse_read + 21,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ChunkedClientResponse_read fun_data_aiohttp___init___ChunkedClientResponse_read[0]
#endif

// child of aiohttp___init___ChunkedClientResponse
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ChunkedClientResponse___repr__
static const byte fun_data_aiohttp___init___ChunkedClientResponse___repr__[18] = {
    0x19,0x08, // prelude
    0x24,0x73, // names: __repr__, self
    0x80,0x51, // code info
    0x23,0x08, // LOAD_CONST_OBJ 8
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR 'status'
    0xb0, // LOAD_FAST 0
    0x13,0x15, // LOAD_ATTR 'headers'
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ChunkedClientResponse___repr__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ChunkedClientResponse___repr__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 36,
        .line_info = fun_data_aiohttp___init___ChunkedClientResponse___repr__ + 4,
        .line_info_top = fun_data_aiohttp___init___ChunkedClientResponse___repr__ + 6,
        .opcodes = fun_data_aiohttp___init___ChunkedClientResponse___repr__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ChunkedClientResponse___repr__ fun_data_aiohttp___init___ChunkedClientResponse___repr__[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init___ChunkedClientResponse[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ChunkedClientResponse___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ChunkedClientResponse_read,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ChunkedClientResponse___repr__,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ChunkedClientResponse = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ChunkedClientResponse,
    .children = (void *)&children_aiohttp___init___ChunkedClientResponse,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 39,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_aiohttp___init___ChunkedClientResponse + 3,
        .line_info_top = fun_data_aiohttp___init___ChunkedClientResponse + 9,
        .opcodes = fun_data_aiohttp___init___ChunkedClientResponse + 9,
    },
    #endif
    #endif
};

// child of aiohttp___init____lt_module_gt_
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init____RequestContextManager
static const byte fun_data_aiohttp___init____RequestContextManager[30] = {
    0x00,0x0c, // prelude
    0x0d, // names: _RequestContextManager
    0x88,0x55,0x64,0x20,0x64, // code info
    0x11,0x70, // LOAD_NAME '__name__'
    0x16,0x71, // STORE_NAME '__module__'
    0x10,0x0d, // LOAD_CONST_STRING '_RequestContextManager'
    0x16,0x72, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x12, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2c, // STORE_NAME '__aenter__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2d, // STORE_NAME '__aexit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init____RequestContextManager
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init____RequestContextManager___init__
static const byte fun_data_aiohttp___init____RequestContextManager___init__[19] = {
    0x23,0x0e, // prelude
    0x12,0x73,0x2b,0x7d, // names: __init__, self, client, request_co
    0x80,0x56,0x24, // code info
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 'reqco'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x2b, // STORE_ATTR 'client'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init____RequestContextManager___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init____RequestContextManager___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_aiohttp___init____RequestContextManager___init__ + 6,
        .line_info_top = fun_data_aiohttp___init____RequestContextManager___init__ + 9,
        .opcodes = fun_data_aiohttp___init____RequestContextManager___init__ + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init____RequestContextManager___init__ fun_data_aiohttp___init____RequestContextManager___init__[0]
#endif

// child of aiohttp___init____RequestContextManager
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init____RequestContextManager___aenter__
static const byte fun_data_aiohttp___init____RequestContextManager___aenter__[14] = {
    0x91,0x40,0x08, // prelude
    0x2c,0x73, // names: __aenter__, self
    0x80,0x5a, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'reqco'
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init____RequestContextManager___aenter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init____RequestContextManager___aenter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_aiohttp___init____RequestContextManager___aenter__ + 5,
        .line_info_top = fun_data_aiohttp___init____RequestContextManager___aenter__ + 7,
        .opcodes = fun_data_aiohttp___init____RequestContextManager___aenter__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init____RequestContextManager___aenter__ fun_data_aiohttp___init____RequestContextManager___aenter__[0]
#endif

// child of aiohttp___init____RequestContextManager
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init____RequestContextManager___aexit__
static const byte fun_data_aiohttp___init____RequestContextManager___aexit__[34] = {
    0xa1,0xc0,0x80,0x40,0x0a, // prelude
    0x2d,0x73, // names: __aexit__, self
    0x80,0x5d,0x2d, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x2b, // LOAD_ATTR 'client'
    0x13,0x2e, // LOAD_ATTR '_reader'
    0x14,0x2f, // LOAD_METHOD 'aclose'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x12,0x02, // LOAD_GLOBAL 'asyncio'
    0x14,0x30, // LOAD_METHOD 'sleep'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init____RequestContextManager___aexit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init____RequestContextManager___aexit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 5,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_aiohttp___init____RequestContextManager___aexit__ + 7,
        .line_info_top = fun_data_aiohttp___init____RequestContextManager___aexit__ + 10,
        .opcodes = fun_data_aiohttp___init____RequestContextManager___aexit__ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init____RequestContextManager___aexit__ fun_data_aiohttp___init____RequestContextManager___aexit__[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init____RequestContextManager[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init____RequestContextManager___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init____RequestContextManager___aenter__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init____RequestContextManager___aexit__,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init____RequestContextManager = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init____RequestContextManager,
    .children = (void *)&children_aiohttp___init____RequestContextManager,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 30,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_aiohttp___init____RequestContextManager + 3,
        .line_info_top = fun_data_aiohttp___init____RequestContextManager + 8,
        .opcodes = fun_data_aiohttp___init____RequestContextManager + 8,
    },
    #endif
    #endif
};

// child of aiohttp___init____lt_module_gt_
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession
static const byte fun_data_aiohttp___init___ClientSession[142] = {
    0x30,0x30, // prelude
    0x0e, // names: ClientSession
    0x88,0x62,0x8d,0x07,0x64,0x64,0x40,0x8d,0x2e,0x84,0x08,0x8b,0x44,0x8d,0x0e,0x64,0x64,0x64,0x64,0x64,0x64,0x64,0x68, // code info
    0x11,0x70, // LOAD_NAME '__name__'
    0x16,0x71, // STORE_NAME '__module__'
    0x10,0x0e, // LOAD_CONST_STRING 'ClientSession'
    0x16,0x72, // STORE_NAME '__qualname__'
    0x10,0x11, // LOAD_CONST_STRING ''
    0x2c,0x00, // BUILD_MAP 0
    0x11,0x6d, // LOAD_NAME 'HttpVersion10'
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x12, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2c, // STORE_NAME '__aenter__'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2d, // STORE_NAME '__aexit__'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2c,0x00, // BUILD_MAP 0
    0x2a,0x05, // BUILD_TUPLE 5
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x39, // STORE_NAME '_request'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2c,0x00, // BUILD_MAP 0
    0x50, // LOAD_CONST_FALSE
    0x51, // LOAD_CONST_NONE
    0x2a,0x07, // BUILD_TUPLE 7
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x3a, // STORE_NAME 'request_raw'
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2c,0x00, // BUILD_MAP 0
    0x2a,0x05, // BUILD_TUPLE 5
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x50, // STORE_NAME 'request'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x53, // STORE_NAME 'get'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x54, // STORE_NAME 'post'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x55, // STORE_NAME 'put'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x57, // STORE_NAME 'patch'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x59, // STORE_NAME 'delete'
    0x32,0x0b, // MAKE_FUNCTION 11
    0x16,0x5b, // STORE_NAME 'head'
    0x32,0x0c, // MAKE_FUNCTION 12
    0x16,0x5d, // STORE_NAME 'options'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0d, // MAKE_FUNCTION_DEFARGS 13
    0x16,0x5f, // STORE_NAME 'ws_connect'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0e, // MAKE_FUNCTION_DEFARGS 14
    0x16,0x60, // STORE_NAME '_ws_connect'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession___init__
static const byte fun_data_aiohttp___init___ClientSession___init__[56] = {
    0xc0,0x85,0x01,0x16, // prelude
    0x12,0x73,0x7e,0x15,0x7f, // names: __init__, self, base_url, headers, version
    0x80,0x63,0x24,0x24,0x2f,0x2c, // code info
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x18,0x2e, // STORE_ATTR '_reader'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x31, // STORE_ATTR '_base_url'
    0x2c,0x02, // BUILD_MAP 2
    0x10,0x32, // LOAD_CONST_STRING 'close'
    0x10,0x33, // LOAD_CONST_STRING 'Connection'
    0x62, // STORE_MAP
    0x10,0x34, // LOAD_CONST_STRING 'compat'
    0x10,0x35, // LOAD_CONST_STRING 'User-Agent'
    0x62, // STORE_MAP
    0xb0, // LOAD_FAST 0
    0x18,0x36, // STORE_ATTR '_base_headers'
    0xb0, // LOAD_FAST 0
    0x13,0x36, // LOAD_ATTR '_base_headers'
    0x14,0x37, // LOAD_METHOD 'update'
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x00, // CALL_METHOD_VAR_KW 256
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x38, // STORE_ATTR '_http_version'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 56,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_aiohttp___init___ClientSession___init__ + 9,
        .line_info_top = fun_data_aiohttp___init___ClientSession___init__ + 15,
        .opcodes = fun_data_aiohttp___init___ClientSession___init__ + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession___init__ fun_data_aiohttp___init___ClientSession___init__[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession___aenter__
static const byte fun_data_aiohttp___init___ClientSession___aenter__[9] = {
    0x89,0x40,0x08, // prelude
    0x2c,0x73, // names: __aenter__, self
    0x80,0x6a, // code info
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession___aenter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession___aenter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 9,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_aiohttp___init___ClientSession___aenter__ + 5,
        .line_info_top = fun_data_aiohttp___init___ClientSession___aenter__ + 7,
        .opcodes = fun_data_aiohttp___init___ClientSession___aenter__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession___aenter__ fun_data_aiohttp___init___ClientSession___aenter__[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession___aexit__
static const byte fun_data_aiohttp___init___ClientSession___aexit__[20] = {
    0xa1,0xc0,0x80,0x40,0x08, // prelude
    0x2d,0x73, // names: __aexit__, self
    0x80,0x6d, // code info
    0x12,0x02, // LOAD_GLOBAL 'asyncio'
    0x14,0x30, // LOAD_METHOD 'sleep'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession___aexit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession___aexit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 20,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 5,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_aiohttp___init___ClientSession___aexit__ + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession___aexit__ + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession___aexit__ + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession___aexit__ fun_data_aiohttp___init___ClientSession___aexit__[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession__request
static const byte fun_data_aiohttp___init___ClientSession__request[340] = {
    0xcc,0xd1,0x84,0x01,0x65, // prelude
    0x39,0x73,0x81,0x00,0x3e,0x51,0x03,0x4a,0x52,0x15, // names: _request, self, method, url, data, json, ssl, params, headers
    0x80,0x72,0x22,0x23,0x31,0x23,0x29,0x28,0x28,0x22,0x20,0x29,0x29,0x23,0x27,0x26,0x29,0x26,0x24,0x29,0x57,0x33,0x24,0x29,0x22,0x48,0x23,0x49,0x27,0x25,0x25,0x25,0x24,0x1f,0x21,0x22,0x42,0x75,0x23,0x24,0x06, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc8, // STORE_FAST 8
    0x42,0xa8,0x81, // JUMP 168
    0xb0, // LOAD_FAST 0
    0x14,0x3a, // LOAD_METHOD 'request_raw'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x25,0x06, // LOAD_DEREF 6
    0xb7, // LOAD_FAST 7
    0x36,0x07, // CALL_METHOD 7
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xc9, // STORE_FAST 9
    0x2b,0x00, // BUILD_LIST 0
    0xca, // STORE_FAST 10
    0xb9, // LOAD_FAST 9
    0x14,0x27, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xcb, // STORE_FAST 11
    0xbb, // LOAD_FAST 11
    0x14,0x28, // LOAD_METHOD 'split'
    0x51, // LOAD_CONST_NONE
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0xcb, // STORE_FAST 11
    0x12,0x7a, // LOAD_GLOBAL 'int'
    0xbb, // LOAD_FAST 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xcc, // STORE_FAST 12
    0x50, // LOAD_CONST_FALSE
    0xcd, // STORE_FAST 13
    0xb9, // LOAD_FAST 9
    0x14,0x27, // LOAD_METHOD 'readline'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0xce, // STORE_FAST 14
    0xbe, // LOAD_FAST 14
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xbe, // LOAD_FAST 14
    0x23,0x06, // LOAD_CONST_OBJ 6
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x42,0xc0,0x80, // JUMP 64
    0xba, // LOAD_FAST 10
    0x14,0x3b, // LOAD_METHOD 'append'
    0xbe, // LOAD_FAST 14
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xbe, // LOAD_FAST 14
    0x14,0x16, // LOAD_METHOD 'lower'
    0x36,0x00, // CALL_METHOD 0
    0xcf, // STORE_FAST 15
    0xbf, // LOAD_FAST 15
    0x14,0x3c, // LOAD_METHOD 'startswith'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x36,0x01, // CALL_METHOD 1
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0xbe, // LOAD_FAST 14
    0xdd, // BINARY_OP 6 <in>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x52, // LOAD_CONST_TRUE
    0xcd, // STORE_FAST 13
    0x42,0x5d, // JUMP 29
    0xbf, // LOAD_FAST 15
    0x14,0x3c, // LOAD_METHOD 'startswith'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x36,0x01, // CALL_METHOD 1
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xbe, // LOAD_FAST 14
    0x14,0x3d, // LOAD_METHOD 'rstrip'
    0x36,0x00, // CALL_METHOD 0
    0x14,0x28, // LOAD_METHOD 'split'
    0x51, // LOAD_CONST_NONE
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x14,0x22, // LOAD_METHOD 'decode'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x42,0x40, // JUMP 0
    0x42,0xab,0x7f, // JUMP -85
    0x22,0x82,0x2d, // LOAD_CONST_SMALL_INT 301
    0xbc, // LOAD_FAST 12
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x06, // JUMP_IF_FALSE_OR_POP 6
    0x22,0x82,0x2f, // LOAD_CONST_SMALL_INT 303
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb8, // LOAD_FAST 8
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc8, // STORE_FAST 8
    0xb9, // LOAD_FAST 9
    0x14,0x2f, // LOAD_METHOD 'aclose'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x46, // JUMP 6
    0xb8, // LOAD_FAST 8
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd7, // BINARY_OP 0 __lt__
    0x43,0xd2,0x7e, // POP_JUMP_IF_TRUE -174
    0xbd, // LOAD_FAST 13
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x0c, // LOAD_GLOBAL 'ChunkedClientResponse'
    0xb9, // LOAD_FAST 9
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x10, // STORE_FAST_N 16
    0x42,0x47, // JUMP 7
    0x12,0x0b, // LOAD_GLOBAL 'ClientResponse'
    0xb9, // LOAD_FAST 9
    0x34,0x01, // CALL_FUNCTION 1
    0x26,0x10, // STORE_FAST_N 16
    0xbc, // LOAD_FAST 12
    0x24,0x10, // LOAD_FAST_N 16
    0x18,0x25, // STORE_ATTR 'status'
    0xba, // LOAD_FAST 10
    0x24,0x10, // LOAD_FAST_N 16
    0x18,0x15, // STORE_ATTR 'headers'
    0xb2, // LOAD_FAST 2
    0x24,0x10, // LOAD_FAST_N 16
    0x18,0x3e, // STORE_ATTR 'url'
    0x25,0x06, // LOAD_DEREF 6
    0x44,0x60, // POP_JUMP_IF_FALSE 32
    0x24,0x10, // LOAD_FAST_N 16
    0x57, // DUP_TOP
    0x13,0x3e, // LOAD_ATTR 'url'
    0x10,0x3f, // LOAD_CONST_STRING '?'
    0x10,0x40, // LOAD_CONST_STRING '&'
    0x14,0x41, // LOAD_METHOD 'join'
    0xb6, // LOAD_FAST 6
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x12,0x81,0x01, // LOAD_GLOBAL 'sorted'
    0x25,0x06, // LOAD_DEREF 6
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0xf2, // BINARY_OP 27 __add__
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x3e, // STORE_ATTR 'url'
    0x48,0x0f, // SETUP_EXCEPT 15
    0x32,0x01, // MAKE_FUNCTION 1
    0x32,0x02, // MAKE_FUNCTION 2
    0xba, // LOAD_FAST 10
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x24,0x10, // LOAD_FAST_N 16
    0x18,0x15, // STORE_ATTR 'headers'
    0x4a,0x0b, // POP_EXCEPT_JUMP 11
    0x57, // DUP_TOP
    0x12,0x81,0x02, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb9, // LOAD_FAST 9
    0xb0, // LOAD_FAST 0
    0x18,0x2e, // STORE_ATTR '_reader'
    0x24,0x10, // LOAD_FAST_N 16
    0x63, // RETURN_VALUE
};
// child of aiohttp___init___ClientSession__request
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession__request__lt_genexpr_gt_
static const byte fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_[34] = {
    0xda,0x40,0x0e, // prelude
    0x65,0x81,0x08,0x81,0x08, // names: <genexpr>, *, *
    0x80,0x94, // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0xc2, // STORE_FAST 2
    0x10,0x66, // LOAD_CONST_STRING '{}={}'
    0x14,0x67, // LOAD_METHOD 'format'
    0xb2, // LOAD_FAST 2
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x55, // LOAD_SUBSCR
    0x36,0x02, // CALL_METHOD 2
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession__request__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_ + 8,
        .line_info_top = fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_ + 10,
        .opcodes = fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession__request__lt_genexpr_gt_ fun_data_aiohttp___init___ClientSession__request__lt_genexpr_gt_[0]
#endif

// child of aiohttp___init___ClientSession__request
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession__request__lt_dictcomp_gt_
static const byte fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_[43] = {
    0x59,0x0a, // prelude
    0x68,0x81,0x08, // names: <dictcomp>, *
    0x80,0x97, // code info
    0x2c,0x00, // BUILD_MAP 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x1d, // FOR_ITER 29
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x28, // LOAD_METHOD 'split'
    0x10,0x48, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x14,0x69, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0xb1, // LOAD_FAST 1
    0x14,0x28, // LOAD_METHOD 'split'
    0x10,0x48, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x2f,0x19, // STORE_COMP 25
    0x42,0x21, // JUMP -31
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession__request__lt_dictcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 43,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 104,
        .line_info = fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_ + 5,
        .line_info_top = fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_ + 7,
        .opcodes = fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession__request__lt_dictcomp_gt_ fun_data_aiohttp___init___ClientSession__request__lt_dictcomp_gt_[0]
#endif

// child of aiohttp___init___ClientSession__request
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession__request__lt_listcomp_gt_
static const byte fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_[28] = {
    0x41,0x0a, // prelude
    0x6a,0x81,0x08, // names: <listcomp>, *
    0x80,0x98, // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x0e, // FOR_ITER 14
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x22, // LOAD_METHOD 'decode'
    0x36,0x00, // CALL_METHOD 0
    0x14,0x69, // LOAD_METHOD 'strip'
    0x36,0x00, // CALL_METHOD 0
    0x2f,0x14, // STORE_COMP 20
    0x42,0x30, // JUMP -16
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession__request__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 106,
        .line_info = fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_ + 5,
        .line_info_top = fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_ + 7,
        .opcodes = fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession__request__lt_listcomp_gt_ fun_data_aiohttp___init___ClientSession__request__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init___ClientSession__request[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession__request__lt_genexpr_gt_,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession__request__lt_dictcomp_gt_,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession__request__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession__request = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession__request,
    .children = (void *)&children_aiohttp___init___ClientSession__request,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 340,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 26,
        .n_exc_stack = 1,
        .scope_flags = 1,
        .n_pos_args = 8,
        .n_kwonly_args = 0,
        .n_def_pos_args = 5,
        .qstr_block_name_idx = 57,
        .line_info = fun_data_aiohttp___init___ClientSession__request + 15,
        .line_info_top = fun_data_aiohttp___init___ClientSession__request + 55,
        .opcodes = fun_data_aiohttp___init___ClientSession__request + 56,
    },
    #endif
    #endif
};

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_request_raw
static const byte fun_data_aiohttp___init___ClientSession_request_raw[470] = {
    0xd6,0xd1,0x85,0x01,0x77, // prelude
    0x3a,0x73,0x81,0x00,0x3e,0x51,0x03,0x4a,0x52,0x15,0x81,0x03,0x7f, // names: request_raw, self, method, url, data, json, ssl, params, headers, is_handshake, version
    0x80,0xab,0x2e,0x28,0x2c,0x23,0x24,0x3a,0x22,0x58,0x2d,0x46,0x26,0x26,0x26,0x24,0x25,0x44,0x4a,0x26,0x2c,0x46,0x74,0x40,0x25,0x24,0x27,0x2a,0x23,0x65,0x20,0x1f,0x63,0x23,0x30,0x2b,0x52,0x46,0x33,0x65,0x20,0x79,0x23,0x2c,0x42,0x2c,0x06, // code info
    0xb4, // LOAD_FAST 4
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x12,0x81,0x04, // LOAD_GLOBAL 'isinstance'
    0xb4, // LOAD_FAST 4
    0x12,0x81,0x05, // LOAD_GLOBAL 'dict'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x6c, // LOAD_GLOBAL '_json'
    0x14,0x42, // LOAD_METHOD 'dumps'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb1, // LOAD_FAST 1
    0x10,0x43, // LOAD_CONST_STRING 'GET'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x10,0x44, // LOAD_CONST_STRING 'POST'
    0xc1, // STORE_FAST 1
    0x25,0x06, // LOAD_DEREF 6
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0xb2, // LOAD_FAST 2
    0x10,0x3f, // LOAD_CONST_STRING '?'
    0x10,0x40, // LOAD_CONST_STRING '&'
    0x14,0x41, // LOAD_METHOD 'join'
    0xb6, // LOAD_FAST 6
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x12,0x81,0x01, // LOAD_GLOBAL 'sorted'
    0x25,0x06, // LOAD_DEREF 6
    0x34,0x01, // CALL_FUNCTION 1
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0xf2, // BINARY_OP 27 __add__
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x48,0x10, // SETUP_EXCEPT 16
    0xb2, // LOAD_FAST 2
    0x14,0x28, // LOAD_METHOD 'split'
    0x10,0x45, // LOAD_CONST_STRING '/'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x36,0x02, // CALL_METHOD 2
    0x30,0x04, // UNPACK_SEQUENCE 4
    0xca, // STORE_FAST 10
    0xcb, // STORE_FAST 11
    0xcc, // STORE_FAST 12
    0xcd, // STORE_FAST 13
    0x4a,0x1b, // POP_EXCEPT_JUMP 27
    0x57, // DUP_TOP
    0x12,0x81,0x06, // LOAD_GLOBAL 'ValueError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x53, // POP_JUMP_IF_FALSE 19
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x14,0x28, // LOAD_METHOD 'split'
    0x10,0x45, // LOAD_CONST_STRING '/'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xca, // STORE_FAST 10
    0xcb, // STORE_FAST 11
    0xcc, // STORE_FAST 12
    0x10,0x11, // LOAD_CONST_STRING ''
    0xcd, // STORE_FAST 13
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xba, // LOAD_FAST 10
    0x10,0x46, // LOAD_CONST_STRING 'http:'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x22,0x80,0x50, // LOAD_CONST_SMALL_INT 80
    0xce, // STORE_FAST 14
    0x42,0x5d, // JUMP 29
    0xba, // LOAD_FAST 10
    0x10,0x47, // LOAD_CONST_STRING 'https:'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x22,0x83,0x3b, // LOAD_CONST_SMALL_INT 443
    0xce, // STORE_FAST 14
    0xb5, // LOAD_FAST 5
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x52, // LOAD_CONST_TRUE
    0xc5, // STORE_FAST 5
    0x42,0x4a, // JUMP 10
    0x12,0x81,0x06, // LOAD_GLOBAL 'ValueError'
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0xba, // LOAD_FAST 10
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x10,0x48, // LOAD_CONST_STRING ':'
    0xbc, // LOAD_FAST 12
    0xdd, // BINARY_OP 6 <in>
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xbc, // LOAD_FAST 12
    0x14,0x28, // LOAD_METHOD 'split'
    0x10,0x48, // LOAD_CONST_STRING ':'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xcc, // STORE_FAST 12
    0xce, // STORE_FAST 14
    0x12,0x7a, // LOAD_GLOBAL 'int'
    0xbe, // LOAD_FAST 14
    0x34,0x01, // CALL_FUNCTION 1
    0xce, // STORE_FAST 14
    0x12,0x02, // LOAD_GLOBAL 'asyncio'
    0x14,0x49, // LOAD_METHOD 'open_connection'
    0xbc, // LOAD_FAST 12
    0xbe, // LOAD_FAST 14
    0x10,0x4a, // LOAD_CONST_STRING 'ssl'
    0xb5, // LOAD_FAST 5
    0x36,0x82,0x02, // CALL_METHOD 258
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xcf, // STORE_FAST 15
    0x26,0x10, // STORE_FAST_N 16
    0xb9, // LOAD_FAST 9
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0xb0, // LOAD_FAST 0
    0x13,0x38, // LOAD_ATTR '_http_version'
    0xc9, // STORE_FAST 9
    0x10,0x4b, // LOAD_CONST_STRING 'Host'
    0xb7, // LOAD_FAST 7
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb7, // LOAD_FAST 7
    0x14,0x37, // LOAD_METHOD 'update'
    0x10,0x4b, // LOAD_CONST_STRING 'Host'
    0xbc, // LOAD_FAST 12
    0x36,0x82,0x00, // CALL_METHOD 256
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x43,0x67, // POP_JUMP_IF_TRUE 39
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0xb1, // LOAD_FAST 1
    0xbd, // LOAD_FAST 13
    0xb9, // LOAD_FAST 9
    0xb7, // LOAD_FAST 7
    0x44,0x55, // POP_JUMP_IF_FALSE 21
    0x10,0x4c, // LOAD_CONST_STRING '\r\n'
    0x14,0x41, // LOAD_METHOD 'join'
    0x32,0x01, // MAKE_FUNCTION 1
    0xb7, // LOAD_FAST 7
    0x14,0x4d, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x10,0x4c, // LOAD_CONST_STRING '\r\n'
    0xf2, // BINARY_OP 27 __add__
    0x42,0x42, // JUMP 2
    0x10,0x11, // LOAD_CONST_STRING ''
    0x2a,0x04, // BUILD_TUPLE 4
    0xf8, // BINARY_OP 33 __mod__
    0x26,0x11, // STORE_FAST_N 17
    0x42,0xe7,0x80, // JUMP 103
    0xb4, // LOAD_FAST 4
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0xb7, // LOAD_FAST 7
    0x14,0x37, // LOAD_METHOD 'update'
    0x53, // LOAD_NULL
    0x2c,0x01, // BUILD_MAP 1
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0x23,0x0f, // LOAD_CONST_OBJ 15
    0x62, // STORE_MAP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x00, // CALL_METHOD_VAR_KW 256
    0x59, // POP_TOP
    0x12,0x81,0x04, // LOAD_GLOBAL 'isinstance'
    0xb3, // LOAD_FAST 3
    0x12,0x81,0x07, // LOAD_GLOBAL 'bytes'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0xb7, // LOAD_FAST 7
    0x14,0x37, // LOAD_METHOD 'update'
    0x53, // LOAD_NULL
    0x2c,0x01, // BUILD_MAP 1
    0x23,0x10, // LOAD_CONST_OBJ 16
    0x23,0x0f, // LOAD_CONST_OBJ 15
    0x62, // STORE_MAP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x00, // CALL_METHOD_VAR_KW 256
    0x59, // POP_TOP
    0x42,0x46, // JUMP 6
    0xb3, // LOAD_FAST 3
    0x14,0x4e, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc3, // STORE_FAST 3
    0xb7, // LOAD_FAST 7
    0x14,0x37, // LOAD_METHOD 'update'
    0x53, // LOAD_NULL
    0x2c,0x01, // BUILD_MAP 1
    0x12,0x7c, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x23,0x11, // LOAD_CONST_OBJ 17
    0x62, // STORE_MAP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x00, // CALL_METHOD_VAR_KW 256
    0x59, // POP_TOP
    0x23,0x12, // LOAD_CONST_OBJ 18
    0xb1, // LOAD_FAST 1
    0xbd, // LOAD_FAST 13
    0xb9, // LOAD_FAST 9
    0x10,0x4c, // LOAD_CONST_STRING '\r\n'
    0x14,0x41, // LOAD_METHOD 'join'
    0x32,0x02, // MAKE_FUNCTION 2
    0xb7, // LOAD_FAST 7
    0x14,0x4d, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x10,0x4c, // LOAD_CONST_STRING '\r\n'
    0xf2, // BINARY_OP 27 __add__
    0xb3, // LOAD_FAST 3
    0x2a,0x05, // BUILD_TUPLE 5
    0xf8, // BINARY_OP 33 __mod__
    0x26,0x11, // STORE_FAST_N 17
    0xb8, // LOAD_FAST 8
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x24,0x10, // LOAD_FAST_N 16
    0x14,0x4f, // LOAD_METHOD 'awrite'
    0x24,0x11, // LOAD_FAST_N 17
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0xbf, // LOAD_FAST 15
    0x63, // RETURN_VALUE
    0x24,0x10, // LOAD_FAST_N 16
    0x14,0x4f, // LOAD_METHOD 'awrite'
    0x24,0x11, // LOAD_FAST_N 17
    0x36,0x01, // CALL_METHOD 1
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0xbf, // LOAD_FAST 15
    0x24,0x10, // LOAD_FAST_N 16
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of aiohttp___init___ClientSession_request_raw
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_
static const byte fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_[34] = {
    0xda,0x40,0x0e, // prelude
    0x65,0x81,0x08,0x81,0x08, // names: <genexpr>, *, *
    0x80,0xb0, // code info
    0x53, // LOAD_NULL
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0xc2, // STORE_FAST 2
    0x10,0x66, // LOAD_CONST_STRING '{}={}'
    0x14,0x67, // LOAD_METHOD 'format'
    0xb2, // LOAD_FAST 2
    0x25,0x00, // LOAD_DEREF 0
    0xb2, // LOAD_FAST 2
    0x55, // LOAD_SUBSCR
    0x36,0x02, // CALL_METHOD 2
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_ + 8,
        .line_info_top = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_ + 10,
        .opcodes = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_ + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_ fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_[0]
#endif

// child of aiohttp___init___ClientSession_request_raw
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2
static const byte fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2[32] = {
    0xd1,0x40,0x0a, // prelude
    0x65,0x81,0x08, // names: <genexpr>, *
    0x80,0xd2, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0x10,0x6b, // LOAD_CONST_STRING '{}: {}'
    0x14,0x67, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2 = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2 + 6,
        .line_info_top = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2 + 8,
        .opcodes = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2 + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2 fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2[0]
#endif

// child of aiohttp___init___ClientSession_request_raw
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3
static const byte fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3[32] = {
    0xd1,0x40,0x0a, // prelude
    0x65,0x81,0x08, // names: <genexpr>, *
    0x80,0xe1, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x10, // FOR_ITER 16
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0x10,0x6b, // LOAD_CONST_STRING '{}: {}'
    0x14,0x67, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2e, // JUMP -18
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3 = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 101,
        .line_info = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3 + 6,
        .line_info_top = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3 + 8,
        .opcodes = fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3 + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3 fun_data_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init___ClientSession_request_raw[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_2,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_request_raw__lt_genexpr_gt_3,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_request_raw = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession_request_raw,
    .children = (void *)&children_aiohttp___init___ClientSession_request_raw,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 470,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 27,
        .n_exc_stack = 1,
        .scope_flags = 1,
        .n_pos_args = 10,
        .n_kwonly_args = 0,
        .n_def_pos_args = 7,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_aiohttp___init___ClientSession_request_raw + 18,
        .line_info_top = fun_data_aiohttp___init___ClientSession_request_raw + 64,
        .opcodes = fun_data_aiohttp___init___ClientSession_request_raw + 65,
    },
    #endif
    #endif
};

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_request
static const byte fun_data_aiohttp___init___ClientSession_request[66] = {
    0xe0,0x91,0x84,0x01,0x20, // prelude
    0x50,0x73,0x81,0x00,0x3e,0x51,0x03,0x4a,0x52,0x15, // names: request, self, method, url, data, json, ssl, params, headers
    0x80,0xec,0x43,0x44,0x73,0x40, // code info
    0x12,0x0d, // LOAD_GLOBAL '_RequestContextManager'
    0xb0, // LOAD_FAST 0
    0xb0, // LOAD_FAST 0
    0x14,0x39, // LOAD_METHOD '_request'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR '_base_url'
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0x10,0x51, // LOAD_CONST_STRING 'data'
    0xb3, // LOAD_FAST 3
    0x10,0x03, // LOAD_CONST_STRING 'json'
    0xb4, // LOAD_FAST 4
    0x10,0x4a, // LOAD_CONST_STRING 'ssl'
    0xb5, // LOAD_FAST 5
    0x10,0x52, // LOAD_CONST_STRING 'params'
    0xb6, // LOAD_FAST 6
    0x10,0x15, // LOAD_CONST_STRING 'headers'
    0x12,0x81,0x05, // LOAD_GLOBAL 'dict'
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x13,0x36, // LOAD_ATTR '_base_headers'
    0x53, // LOAD_NULL
    0xb7, // LOAD_FAST 7
    0x80, // LOAD_CONST_SMALL_INT 0
    0x35,0x84,0x00, // CALL_FUNCTION_VAR_KW 512
    0x36,0x8a,0x02, // CALL_METHOD 1282
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_request = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_request,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 66,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 29,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 8,
        .n_kwonly_args = 0,
        .n_def_pos_args = 5,
        .qstr_block_name_idx = 80,
        .line_info = fun_data_aiohttp___init___ClientSession_request + 15,
        .line_info_top = fun_data_aiohttp___init___ClientSession_request + 21,
        .opcodes = fun_data_aiohttp___init___ClientSession_request + 21,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_request fun_data_aiohttp___init___ClientSession_request[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_get
static const byte fun_data_aiohttp___init___ClientSession_get[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x53,0x73,0x3e, // names: get, self, url
    0x80,0xfa, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x43, // LOAD_CONST_STRING 'GET'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_get = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_get,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 83,
        .line_info = fun_data_aiohttp___init___ClientSession_get + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_get + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_get + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_get fun_data_aiohttp___init___ClientSession_get[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_post
static const byte fun_data_aiohttp___init___ClientSession_post[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x54,0x73,0x3e, // names: post, self, url
    0x80,0xfd, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x44, // LOAD_CONST_STRING 'POST'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_post = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_post,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 84,
        .line_info = fun_data_aiohttp___init___ClientSession_post + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_post + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_post + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_post fun_data_aiohttp___init___ClientSession_post[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_put
static const byte fun_data_aiohttp___init___ClientSession_put[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x55,0x73,0x3e, // names: put, self, url
    0x90,0x00, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x56, // LOAD_CONST_STRING 'PUT'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_put = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_put,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 85,
        .line_info = fun_data_aiohttp___init___ClientSession_put + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_put + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_put + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_put fun_data_aiohttp___init___ClientSession_put[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_patch
static const byte fun_data_aiohttp___init___ClientSession_patch[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x57,0x73,0x3e, // names: patch, self, url
    0x90,0x03, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x58, // LOAD_CONST_STRING 'PATCH'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_patch = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_patch,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 87,
        .line_info = fun_data_aiohttp___init___ClientSession_patch + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_patch + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_patch + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_patch fun_data_aiohttp___init___ClientSession_patch[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_delete
static const byte fun_data_aiohttp___init___ClientSession_delete[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x59,0x73,0x3e, // names: delete, self, url
    0x90,0x06, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x5a, // LOAD_CONST_STRING 'DELETE'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_delete = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_delete,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 89,
        .line_info = fun_data_aiohttp___init___ClientSession_delete + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_delete + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_delete + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_delete fun_data_aiohttp___init___ClientSession_delete[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_head
static const byte fun_data_aiohttp___init___ClientSession_head[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x5b,0x73,0x3e, // names: head, self, url
    0x90,0x09, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x5c, // LOAD_CONST_STRING 'HEAD'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_head = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_head,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 91,
        .line_info = fun_data_aiohttp___init___ClientSession_head + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_head + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_head + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_head fun_data_aiohttp___init___ClientSession_head[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_options
static const byte fun_data_aiohttp___init___ClientSession_options[22] = {
    0xca,0x80,0x40,0x0a, // prelude
    0x5d,0x73,0x3e, // names: options, self, url
    0x90,0x0c, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x50, // LOAD_METHOD 'request'
    0x10,0x5e, // LOAD_CONST_STRING 'OPTIONS'
    0xb1, // LOAD_FAST 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0x37,0x82,0x02, // CALL_METHOD_VAR_KW 258
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_options = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_options,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 93,
        .line_info = fun_data_aiohttp___init___ClientSession_options + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_options + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_options + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_options fun_data_aiohttp___init___ClientSession_options[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession_ws_connect
static const byte fun_data_aiohttp___init___ClientSession_ws_connect[25] = {
    0xcb,0x01,0x0c, // prelude
    0x5f,0x73,0x3e,0x4a, // names: ws_connect, self, url, ssl
    0x90,0x0f, // code info
    0x12,0x04, // LOAD_GLOBAL '_WSRequestContextManager'
    0xb0, // LOAD_FAST 0
    0xb0, // LOAD_FAST 0
    0x14,0x60, // LOAD_METHOD '_ws_connect'
    0xb1, // LOAD_FAST 1
    0x10,0x4a, // LOAD_CONST_STRING 'ssl'
    0xb2, // LOAD_FAST 2
    0x36,0x82,0x01, // CALL_METHOD 257
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession_ws_connect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession_ws_connect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 95,
        .line_info = fun_data_aiohttp___init___ClientSession_ws_connect + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession_ws_connect + 9,
        .opcodes = fun_data_aiohttp___init___ClientSession_ws_connect + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession_ws_connect fun_data_aiohttp___init___ClientSession_ws_connect[0]
#endif

// child of aiohttp___init___ClientSession
// frozen bytecode for file aiohttp/__init__.py, scope aiohttp___init___ClientSession__ws_connect
static const byte fun_data_aiohttp___init___ClientSession__ws_connect[55] = {
    0xd3,0x41,0x12, // prelude
    0x60,0x73,0x3e,0x4a, // names: _ws_connect, self, url, ssl
    0x90,0x12,0x2c,0x33,0x26, // code info
    0x12,0x06, // LOAD_GLOBAL 'WebSocketClient'
    0xb0, // LOAD_FAST 0
    0x13,0x36, // LOAD_ATTR '_base_headers'
    0x14,0x61, // LOAD_METHOD 'copy'
    0x36,0x00, // CALL_METHOD 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x62, // LOAD_METHOD 'connect'
    0xb1, // LOAD_FAST 1
    0x10,0x4a, // LOAD_CONST_STRING 'ssl'
    0xb2, // LOAD_FAST 2
    0x10,0x63, // LOAD_CONST_STRING 'handshake_request'
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'request_raw'
    0x36,0x84,0x01, // CALL_METHOD 513
    0x5e, // GET_ITER
    0x51, // LOAD_CONST_NONE
    0x68, // YIELD_FROM
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x13,0x64, // LOAD_ATTR 'reader'
    0xb0, // LOAD_FAST 0
    0x18,0x2e, // STORE_ATTR '_reader'
    0x12,0x05, // LOAD_GLOBAL 'ClientWebSocketResponse'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession__ws_connect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_aiohttp___init___ClientSession__ws_connect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 96,
        .line_info = fun_data_aiohttp___init___ClientSession__ws_connect + 7,
        .line_info_top = fun_data_aiohttp___init___ClientSession__ws_connect + 12,
        .opcodes = fun_data_aiohttp___init___ClientSession__ws_connect + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_aiohttp___init___ClientSession__ws_connect fun_data_aiohttp___init___ClientSession__ws_connect[0]
#endif

static const mp_raw_code_t *const children_aiohttp___init___ClientSession[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession___init__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession___aenter__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession___aexit__,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession__request,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_request_raw,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_request,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_get,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_post,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_put,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_patch,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_delete,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_head,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_options,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession_ws_connect,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession__ws_connect,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init___ClientSession = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init___ClientSession,
    .children = (void *)&children_aiohttp___init___ClientSession,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 142,
    .n_children = 15,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_aiohttp___init___ClientSession + 3,
        .line_info_top = fun_data_aiohttp___init___ClientSession + 26,
        .opcodes = fun_data_aiohttp___init___ClientSession + 26,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_aiohttp___init____lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientResponse,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ChunkedClientResponse,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init____RequestContextManager,
    (const mp_raw_code_t *)&proto_fun_aiohttp___init___ClientSession,
};

static const mp_raw_code_truncated_t proto_fun_aiohttp___init____lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_aiohttp___init____lt_module_gt_,
    .children = (void *)&children_aiohttp___init____lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 113,
    .n_children = 4,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_aiohttp___init____lt_module_gt_ + 3,
        .line_info_top = fun_data_aiohttp___init____lt_module_gt_ + 19,
        .opcodes = fun_data_aiohttp___init____lt_module_gt_ + 19,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_aiohttp___init__[137] = {
    MP_QSTR_aiohttp_slash___init___dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_asyncio,
    MP_QSTR_json,
    MP_QSTR__WSRequestContextManager,
    MP_QSTR_ClientWebSocketResponse,
    MP_QSTR_WebSocketClient,
    MP_QSTR_WSMsgType,
    MP_QSTR_aiohttp_ws,
    MP_QSTR_HTTP_slash_1_dot_0,
    MP_QSTR_HTTP_slash_1_dot_1,
    MP_QSTR_ClientResponse,
    MP_QSTR_ChunkedClientResponse,
    MP_QSTR__RequestContextManager,
    MP_QSTR_ClientSession,
    MP_QSTR_0_dot_0_dot_8,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR_,
    MP_QSTR___init__,
    MP_QSTR_content,
    MP_QSTR__get_header,
    MP_QSTR_headers,
    MP_QSTR_lower,
    MP_QSTR__decode,
    MP_QSTR_deflate,
    MP_QSTR_io,
    MP_QSTR_DeflateIO,
    MP_QSTR_BytesIO,
    MP_QSTR_ZLIB,
    MP_QSTR_read,
    MP_QSTR_gzip,
    MP_QSTR_GZIP,
    MP_QSTR_readexactly,
    MP_QSTR_text,
    MP_QSTR_decode,
    MP_QSTR_loads,
    MP_QSTR___repr__,
    MP_QSTR_status,
    MP_QSTR_chunk_size,
    MP_QSTR_readline,
    MP_QSTR_split,
    MP_QSTR_AssertionError,
    MP_QSTR_reqco,
    MP_QSTR_client,
    MP_QSTR___aenter__,
    MP_QSTR___aexit__,
    MP_QSTR__reader,
    MP_QSTR_aclose,
    MP_QSTR_sleep,
    MP_QSTR__base_url,
    MP_QSTR_close,
    MP_QSTR_Connection,
    MP_QSTR_compat,
    MP_QSTR_User_hyphen_Agent,
    MP_QSTR__base_headers,
    MP_QSTR_update,
    MP_QSTR__http_version,
    MP_QSTR__request,
    MP_QSTR_request_raw,
    MP_QSTR_append,
    MP_QSTR_startswith,
    MP_QSTR_rstrip,
    MP_QSTR_url,
    MP_QSTR__question_,
    MP_QSTR__amp_,
    MP_QSTR_join,
    MP_QSTR_dumps,
    MP_QSTR_GET,
    MP_QSTR_POST,
    MP_QSTR__slash_,
    MP_QSTR_http_colon_,
    MP_QSTR_https_colon_,
    MP_QSTR__colon_,
    MP_QSTR_open_connection,
    MP_QSTR_ssl,
    MP_QSTR_Host,
    MP_QSTR__0x0d__0x0a_,
    MP_QSTR_items,
    MP_QSTR_encode,
    MP_QSTR_awrite,
    MP_QSTR_request,
    MP_QSTR_data,
    MP_QSTR_params,
    MP_QSTR_get,
    MP_QSTR_post,
    MP_QSTR_put,
    MP_QSTR_PUT,
    MP_QSTR_patch,
    MP_QSTR_PATCH,
    MP_QSTR_delete,
    MP_QSTR_DELETE,
    MP_QSTR_head,
    MP_QSTR_HEAD,
    MP_QSTR_options,
    MP_QSTR_OPTIONS,
    MP_QSTR_ws_connect,
    MP_QSTR__ws_connect,
    MP_QSTR_copy,
    MP_QSTR_connect,
    MP_QSTR_handshake_request,
    MP_QSTR_reader,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR__brace_open__brace_close__equals__brace_open__brace_close_,
    MP_QSTR_format,
    MP_QSTR__lt_dictcomp_gt_,
    MP_QSTR_strip,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR__brace_open__brace_close__colon__space__brace_open__brace_close_,
    MP_QSTR__json,
    MP_QSTR_HttpVersion10,
    MP_QSTR_HttpVersion11,
    MP_QSTR___version__,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_keyname,
    MP_QSTR_default,
    MP_QSTR_ImportError,
    MP_QSTR_print,
    MP_QSTR_sz,
    MP_QSTR_encoding,
    MP_QSTR_int,
    MP_QSTR_min,
    MP_QSTR_len,
    MP_QSTR_request_co,
    MP_QSTR_base_url,
    MP_QSTR_version,
    MP_QSTR_method,
    MP_QSTR_sorted,
    MP_QSTR_Exception,
    MP_QSTR_is_handshake,
    MP_QSTR_isinstance,
    MP_QSTR_dict,
    MP_QSTR_ValueError,
    MP_QSTR_bytes,
    MP_QSTR__star_,
};

// constants
static const mp_rom_obj_tuple_t const_obj_aiohttp___init___1 = {{&mp_type_tuple}, 3, {
    MP_ROM_QSTR(MP_QSTR_gzip),
    MP_ROM_QSTR(MP_QSTR_deflate),
    MP_ROM_QSTR(MP_QSTR_gzip_comma_deflate),
}};
static const mp_obj_str_t const_obj_aiohttp___init___2 = {{&mp_type_str}, 62397, 32, (const byte*)"\x57\x41\x52\x4e\x49\x4e\x47\x3a\x20\x64\x65\x66\x6c\x61\x74\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x72\x65\x71\x75\x69\x72\x65\x64"};
static const mp_obj_str_t const_obj_aiohttp___init___5 = {{&mp_type_bytes}, 46494, 1, (const byte*)"\x3b"};
static const mp_obj_str_t const_obj_aiohttp___init___6 = {{&mp_type_bytes}, 27298, 2, (const byte*)"\x0d\x0a"};
static const mp_obj_str_t const_obj_aiohttp___init___8 = {{&mp_type_str}, 7088, 29, (const byte*)"\x3c\x43\x68\x75\x6e\x6b\x65\x64\x43\x6c\x69\x65\x6e\x74\x52\x65\x73\x70\x6f\x6e\x73\x65\x20\x25\x64\x20\x25\x73\x3e"};
static const mp_obj_str_t const_obj_aiohttp___init___9 = {{&mp_type_bytes}, 8890, 18, (const byte*)"\x74\x72\x61\x6e\x73\x66\x65\x72\x2d\x65\x6e\x63\x6f\x64\x69\x6e\x67\x3a"};
static const mp_obj_str_t const_obj_aiohttp___init___10 = {{&mp_type_bytes}, 3583, 7, (const byte*)"\x63\x68\x75\x6e\x6b\x65\x64"};
static const mp_obj_str_t const_obj_aiohttp___init___11 = {{&mp_type_bytes}, 674, 9, (const byte*)"\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x3a"};
static const mp_obj_str_t const_obj_aiohttp___init___13 = {{&mp_type_bytes}, 10026, 15, (const byte*)"\x25\x73\x20\x2f\x25\x73\x20\x25\x73\x0d\x0a\x25\x73\x0d\x0a"};
static const mp_obj_str_t const_obj_aiohttp___init___18 = {{&mp_type_bytes}, 38492, 17, (const byte*)"\x25\x73\x20\x2f\x25\x73\x20\x25\x73\x0d\x0a\x25\x73\x0d\x0a\x25\x73"};

// constant table
static const mp_rom_obj_t const_obj_table_data_aiohttp___init__[19] = {
    MP_ROM_QSTR(MP_QSTR_content_hyphen_encoding),
    MP_ROM_PTR(&const_obj_aiohttp___init___1),
    MP_ROM_PTR(&const_obj_aiohttp___init___2),
    MP_ROM_QSTR(MP_QSTR_content_hyphen_length),
    MP_ROM_QSTR(MP_QSTR__lt_ClientResponse_space__percent_d_space__percent_s_gt_),
    MP_ROM_PTR(&const_obj_aiohttp___init___5),
    MP_ROM_PTR(&const_obj_aiohttp___init___6),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_aiohttp___init___8),
    MP_ROM_PTR(&const_obj_aiohttp___init___9),
    MP_ROM_PTR(&const_obj_aiohttp___init___10),
    MP_ROM_PTR(&const_obj_aiohttp___init___11),
    MP_ROM_QSTR(MP_QSTR_Unsupported_space_protocol_colon__space_),
    MP_ROM_PTR(&const_obj_aiohttp___init___13),
    MP_ROM_QSTR(MP_QSTR_application_slash_json),
    MP_ROM_QSTR(MP_QSTR_Content_hyphen_Type),
    MP_ROM_QSTR(MP_QSTR_application_slash_octet_hyphen_stream),
    MP_ROM_QSTR(MP_QSTR_Content_hyphen_Length),
    MP_ROM_PTR(&const_obj_aiohttp___init___18),
};

static const mp_frozen_module_t frozen_module_aiohttp___init__ = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_aiohttp___init__,
        .obj_table = (mp_obj_t *)&const_obj_table_data_aiohttp___init__,
    },
    .proto_fun = &proto_fun_aiohttp___init____lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// collection of all frozen modules

const char mp_frozen_names[] = {
    #ifdef MP_FROZEN_STR_NAMES
    MP_FROZEN_STR_NAMES
    #endif
    "asyncio/__init__.py\0"
    "asyncio/core.py\0"
    "asyncio/event.py\0"
    "asyncio/funcs.py\0"
    "asyncio/lock.py\0"
    "asyncio/stream.py\0"
    "neopixel.py\0"
    "requests/__init__.py\0"
    "ssl.py\0"
    "websocket.py\0"
    "upip.py\0"
    "mip/__init__.py\0"
    "umqtt/simple.py\0"
    "umqtt/robust.py\0"
    "aiohttp/aiohttp_ws.py\0"
    "aiohttp/__init__.py\0"
    "\0"
};

const mp_frozen_module_t *const mp_frozen_mpy_content[] = {
    &frozen_module_asyncio___init__,
    &frozen_module_asyncio_core,
    &frozen_module_asyncio_event,
    &frozen_module_asyncio_funcs,
    &frozen_module_asyncio_lock,
    &frozen_module_asyncio_stream,
    &frozen_module_neopixel,
    &frozen_module_requests___init__,
    &frozen_module_ssl,
    &frozen_module_websocket,
    &frozen_module_upip,
    &frozen_module_mip___init__,
    &frozen_module_umqtt_simple,
    &frozen_module_umqtt_robust,
    &frozen_module_aiohttp_aiohttp_ws,
    &frozen_module_aiohttp___init__,
};

#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("asyncio", "asyncio/__init__.py")
MICROPY_FROZEN_LIST_ITEM("asyncio/core", "asyncio/core.py")
MICROPY_FROZEN_LIST_ITEM("asyncio/event", "asyncio/event.py")
MICROPY_FROZEN_LIST_ITEM("asyncio/funcs", "asyncio/funcs.py")
MICROPY_FROZEN_LIST_ITEM("asyncio/lock", "asyncio/lock.py")
MICROPY_FROZEN_LIST_ITEM("asyncio/stream", "asyncio/stream.py")
MICROPY_FROZEN_LIST_ITEM("neopixel", "neopixel.py")
MICROPY_FROZEN_LIST_ITEM("requests", "requests/__init__.py")
MICROPY_FROZEN_LIST_ITEM("ssl", "ssl.py")
MICROPY_FROZEN_LIST_ITEM("websocket", "websocket.py")
MICROPY_FROZEN_LIST_ITEM("upip", "upip.py")
MICROPY_FROZEN_LIST_ITEM("mip", "mip/__init__.py")
MICROPY_FROZEN_LIST_ITEM("umqtt/simple", "umqtt/simple.py")
MICROPY_FROZEN_LIST_ITEM("umqtt/robust", "umqtt/robust.py")
MICROPY_FROZEN_LIST_ITEM("aiohttp/aiohttp_ws", "aiohttp/aiohttp_ws.py")
MICROPY_FROZEN_LIST_ITEM("aiohttp", "aiohttp/__init__.py")
#endif

/*
byte sizes:
qstr content: 441 unique, 5558 bytes
bc content: 16936
const str content: 1306
const int content: 10
const obj content: 832
const table qstr content: 0 entries, 0 bytes
const table ptr content: 114 entries, 456 bytes
raw code content: 275 * 4 = 4400
mp_frozen_mpy_names_content: 256
mp_frozen_mpy_content_size: 64
total: 29818
*/
