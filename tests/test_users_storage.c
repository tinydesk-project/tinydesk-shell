/* Execute the production ESP account store against in-memory NVS and real
 * SHA-256: migration, rights escalation, remember proofs and failed writes. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../ports/esp_idf/components/tdsh/src/tdsh_users.c"
typedef struct {char key[24];unsigned char value[4096];size_t size;} item_t;
static item_t store[8];
static int fail_writes,lock_depth;
static item_t *item(const char *key,bool create){for(int i=0;i<8;i++)if(!strcmp(store[i].key,key))return &store[i];if(create)for(int i=0;i<8;i++)if(!store[i].key[0]){snprintf(store[i].key,24,"%s",key);return &store[i];}return NULL;}
esp_err_t nvs_open(const char *ns,int mode,nvs_handle_t *h){(void)ns;(void)mode;*h=1;return ESP_OK;}
void nvs_close(nvs_handle_t h){(void)h;}
esp_err_t nvs_get_blob(nvs_handle_t h,const char *key,void *data,size_t *n){(void)h;item_t *e=item(key,false);if(!e)return ESP_ERR_NVS_NOT_FOUND;if(*n<e->size)return ESP_FAIL;memcpy(data,e->value,e->size);*n=e->size;return ESP_OK;}
esp_err_t nvs_set_blob(nvs_handle_t h,const char *key,const void *data,size_t n){(void)h;if(fail_writes)return ESP_FAIL;item_t *e=item(key,true);assert(e&&n<=sizeof(e->value));memcpy(e->value,data,n);e->size=n;return ESP_OK;}
esp_err_t nvs_get_str(nvs_handle_t h,const char *key,char *data,size_t *n){return nvs_get_blob(h,key,data,n);}
esp_err_t nvs_set_str(nvs_handle_t h,const char *key,const char *data){return nvs_set_blob(h,key,data,strlen(data)+1);}
esp_err_t nvs_get_u8(nvs_handle_t h,const char *key,uint8_t *data){size_t n=1;return nvs_get_blob(h,key,data,&n);}
esp_err_t nvs_set_u8(nvs_handle_t h,const char *key,uint8_t data){return nvs_set_blob(h,key,&data,1);}
esp_err_t nvs_commit(nvs_handle_t h){(void)h;return fail_writes?ESP_FAIL:ESP_OK;}
esp_err_t nvs_erase_key(nvs_handle_t h,const char *key){(void)h;if(fail_writes)return ESP_FAIL;item_t *e=item(key,false);if(!e)return ESP_ERR_NVS_NOT_FOUND;memset(e,0,sizeof(*e));return ESP_OK;}
void esp_fill_random(void *p,size_t n){static unsigned char sequence=1;unsigned char *b=p;while(n--)*b++=sequence++;}
SemaphoreHandle_t xSemaphoreCreateRecursiveMutex(void){return (void*)1;}
int xSemaphoreTakeRecursive(SemaphoreHandle_t h,unsigned t){(void)h;(void)t;lock_depth++;return pdTRUE;}
int xSemaphoreGiveRecursive(SemaphoreHandle_t h){(void)h;assert(lock_depth>0);lock_depth--;return pdTRUE;}
int tdsh_console_readline(const char *p,char *s,size_t n,bool echo){(void)p;(void)s;(void)n;(void)echo;return -1;}
int tdsh_session_set_user(tdsh_session_t *s,const char *u){snprintf(s->username,sizeof(s->username),"%s",u);return 0;}
int tdsh_session_set_user_generation(tdsh_session_t *s,const char *u,uint32_t generation){s->user_generation=generation;return tdsh_session_set_user(s,u);}
int tdsh_run_user_startup(tdsh_session_t *s){(void)s;return 0;}
bool tdsh_is_local_console_task(void){return false;}
bool tdsh_console_begin_recovery(void){return false;}
void tdsh_console_end_recovery(void){}
void tdsh_netmount_remove_owner(const char *u){(void)u;}
static void reboot_store(void){s_ready=false;assert(tdsh_users_init()==ESP_OK);assert(lock_depth==0);}
int main(void)
{
    char remembered[32];reboot_store();
    tdsh_core_config_t config=TDSH_CORE_CONFIG_DEFAULT();config.user_generation=tdsh_user_generation;config.user_role=tdsh_user_role;config.user_rights=tdsh_user_rights;assert(!tdsh_core_init(&config));
    assert(tdsh_user_authenticate("root",DEFAULT_ROOT_PASSWORD));
    assert(!tdsh_boot_user_default("root"));assert(!tdsh_user_remember_allowed("root"));
    assert(!tdsh_remembered_user(remembered,sizeof(remembered)));
    assert(!tdsh_user_authenticate("root","wrong"));
    assert(!tdsh_user_create("root","alice","password-a",TDSH_ROLE_USER,TDSH_RIGHT_APPS));
    assert(!tdsh_user_create("root",".legacy","pw",TDSH_ROLE_USER,TDSH_RIGHT_APPS));
    tdsh_session_t alice;assert(!tdsh_session_init(&alice,"alice",true));assert(tdsh_session_valid(&alice));
    assert(!tdsh_user_create("root","admin","password-b",TDSH_ROLE_ADMIN,TDSH_RIGHTS_ADMIN));
    assert(tdsh_user_create("alice","hacker","pw",TDSH_ROLE_ADMIN,TDSH_RIGHT_ALL)==-EACCES);
    assert(tdsh_user_create("admin","escalated","pw",TDSH_ROLE_ADMIN,TDSH_RIGHT_ALL)==-EACCES);
    assert(!tdsh_user_create("admin","operator","pw",TDSH_ROLE_USER,TDSH_RIGHT_APPS|TDSH_RIGHT_SHARED));
    unsigned char password_db[4096];item_t *password_item=item("db",false);size_t password_bytes=password_item->size;memcpy(password_db,password_item->value,password_bytes);
    assert(!tdsh_user_access_set("admin","operator",TDSH_ROLE_USER,TDSH_RIGHT_APPS|TDSH_RIGHT_SHARED|TDSH_RIGHT_NETWORK));
    assert(password_item->size==password_bytes&&!memcmp(password_db,password_item->value,password_bytes));
    fail_writes=1;assert(tdsh_user_access_set("root","operator",TDSH_ROLE_ADMIN,TDSH_RIGHT_ALL)==-EIO);assert(tdsh_user_role("operator")==TDSH_ROLE_USER);fail_writes=0;
    assert(tdsh_user_access_set("admin","root",TDSH_ROLE_USER,0)==-EACCES);
    assert(tdsh_user_access_set("admin","admin",TDSH_ROLE_ADMIN,TDSH_RIGHT_ALL)==-EACCES);
    assert(tdsh_user_create("root","..","pw",TDSH_ROLE_USER,0)==-EINVAL);
    assert(tdsh_user_create("root","bad/name","pw",TDSH_ROLE_USER,0)==-EINVAL);
    assert(!tdsh_boot_user_set("alice"));assert(!tdsh_remembered_user(remembered,sizeof(remembered)));
    assert(tdsh_user_authenticate("alice","password-a"));assert(!tdsh_remembered_user(remembered,sizeof(remembered))); /* checks alone do not mint proof */
    assert(!tdsh_user_login("alice","wrong"));assert(tdsh_user_login("alice","password-a"));assert(tdsh_remembered_user(remembered,sizeof(remembered)));assert(!strcmp(remembered,"alice"));
    reboot_store();assert(tdsh_remembered_user(remembered,sizeof(remembered)));
    assert(tdsh_user_role("admin")==TDSH_ROLE_ADMIN);assert(tdsh_user_rights("operator")== (TDSH_RIGHT_APPS|TDSH_RIGHT_SHARED|TDSH_RIGHT_NETWORK));
    assert(tdsh_user_password_set("alice","root","", "new-password")==-EACCES);
    assert(tdsh_user_password_set("alice","alice","wrong","new-password")==-EACCES);
    assert(!tdsh_user_password_set("alice","alice","password-a","new-password"));assert(!tdsh_remembered_user(remembered,sizeof(remembered)));
    assert(!tdsh_session_valid(&alice));assert(tdsh_session_rights(&alice)==0);char *command[]={"anything"};assert(tdsh_execute_argv(&alice,1,command)==126);
    fail_writes=1;assert(tdsh_user_password_set("root","alice",NULL,"failed-password")==-EIO);assert(tdsh_user_authenticate("alice","new-password"));
    assert(tdsh_user_create("root","failed","pw",TDSH_ROLE_USER,0)==-EIO);assert(!tdsh_user_exists("failed"));
    fail_writes=0;assert(!tdsh_boot_login_require_password());assert(!tdsh_boot_user_set("alice"));assert(!tdsh_remembered_user(remembered,sizeof(remembered)));
    assert(!item("proof",false));
    assert(tdsh_user_login("alice","new-password"));assert(tdsh_remembered_user(remembered,sizeof(remembered)));assert(!tdsh_boot_login_require_password());
    /* Password hints: self or a manager sets them, they outlive password
     * changes and restarts, and never pass to a new account of the name. */
    char hint[TDSH_HINT_MAX];
    assert(!tdsh_user_hint_get("alice",hint,sizeof(hint))&&!hint[0]);
    assert(!tdsh_user_hint_set("alice","alice","first pet"));
    assert(!tdsh_user_hint_get("alice",hint,sizeof(hint))&&!strcmp(hint,"first pet"));
    assert(tdsh_user_hint_set("operator","alice","x")==-EACCES);
    assert(tdsh_user_hint_set("admin","root","x")==-EACCES);
    assert(tdsh_user_hint_set("nobody","nobody","x")==-ENOENT);
    assert(!tdsh_user_hint_set("root","operator","blue"));
    assert(tdsh_user_hint_set("alice","alice","two\nlines")==-EINVAL);
    char long_hint[TDSH_HINT_MAX+1];memset(long_hint,'a',TDSH_HINT_MAX);long_hint[TDSH_HINT_MAX]=0;
    assert(tdsh_user_hint_set("alice","alice",long_hint)==-EINVAL);
    fail_writes=1;assert(tdsh_user_hint_set("alice","alice","lost")==-EIO);fail_writes=0;
    assert(!tdsh_user_password_set("alice","alice","new-password","newer-password"));
    reboot_store();assert(!tdsh_user_hint_get("alice",hint,sizeof(hint))&&!strcmp(hint,"first pet"));
    assert(tdsh_hint_reveals("my NEWER-password!","newer-password")&&!tdsh_hint_reveals("first pet","newer-password"));
    assert(tdsh_hint_reveals("pw","pw")&&!tdsh_hint_reveals("pwn","pw")&&!tdsh_hint_reveals("","pw"));
    tdsh_session_t root_session;assert(!tdsh_session_init(&root_session,"root",true));
    char *del[]={"userdel","operator","-f"};assert(!tdsh_cmd_userdel(&root_session,3,del));
    assert(!tdsh_user_create("root","operator","pw2",TDSH_ROLE_USER,TDSH_RIGHT_APPS));
    assert(!tdsh_user_hint_get("operator",hint,sizeof(hint))&&!hint[0]);
    assert(!tdsh_user_hint_set("alice","alice",""));assert(!tdsh_user_hint_get("alice",hint,sizeof(hint))&&!hint[0]);
    /* Legacy password DB without sidecar keeps passwords and defaults to User. */
    item("access",false)->key[0]=0;reboot_store();assert(tdsh_user_authenticate("admin","password-b"));assert(tdsh_user_role("admin")==TDSH_ROLE_USER);assert(tdsh_user_rights("admin")==TDSH_RIGHT_APPS);
    item_t *db=item("db",false);db->value[0]^=1;s_ready=false;assert(tdsh_users_init()==ESP_ERR_INVALID_STATE);assert(!tdsh_user_authenticate("root",DEFAULT_ROOT_PASSWORD));
    assert(lock_depth==0);puts("PASS: production account store, legacy credentials, roles, escalation denial, NVS errors, remember proofs, password hints and corrupt-store fail-closed.");return 0;
}
