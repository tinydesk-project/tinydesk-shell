#ifndef TDSH_PERMISSIONS_H
#define TDSH_PERMISSIONS_H
#include <stdint.h>
#include <stdbool.h>
typedef enum { TDSH_ROLE_USER=0, TDSH_ROLE_ADMIN=1, TDSH_ROLE_ROOT=2 } tdsh_role_t;
#define TDSH_RIGHT_USERS    (1u<<0)
#define TDSH_RIGHT_SYSTEM   (1u<<1)
#define TDSH_RIGHT_NETWORK  (1u<<2)
#define TDSH_RIGHT_HARDWARE (1u<<3)
#define TDSH_RIGHT_SHARED   (1u<<4)
#define TDSH_RIGHT_TIME     (1u<<5)
#define TDSH_RIGHT_APPS     (1u<<6)
#define TDSH_RIGHT_ALL      127u
#define TDSH_RIGHTS_USER    TDSH_RIGHT_APPS
#define TDSH_RIGHTS_ADMIN   (TDSH_RIGHT_ALL & ~TDSH_RIGHT_HARDWARE)
/* Reserved roles are derived from authenticated identity, never variables. */
struct tdsh_session;
bool tdsh_session_valid(const struct tdsh_session *session);
tdsh_role_t tdsh_session_role(const struct tdsh_session *session);
uint32_t tdsh_session_rights(const struct tdsh_session *session);
bool tdsh_session_has_right(const struct tdsh_session *session,uint32_t right);
#endif
