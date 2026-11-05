/* Sidecar roles bind to the legacy username and salt. A mismatched sidecar
 * fails closed to User; the version-1 password database is never rewritten
 * into a format that older firmware would mistake for an empty database. */
typedef struct {char name[TDSH_USERNAME_MAX];uint8_t salt[USER_SALT_LEN];uint32_t role,rights;} access_entry_t;
typedef struct {uint32_t magic;access_entry_t entries[USER_MAX];} access_db_t;
#define ACCESS_MAGIC 0x54444131u
static void access_load(void)
{
    access_db_t db;size_t size=sizeof(db);nvs_handle_t h;
    if(nvs_open(USER_NS,NVS_READONLY,&h)!=ESP_OK)return;
    esp_err_t err=nvs_get_blob(h,"access",&db,&size);nvs_close(h);
    if(err!=ESP_OK||size!=sizeof(db)||db.magic!=ACCESS_MAGIC)return;
    for(int i=0;i<USER_MAX;i++){
        const access_entry_t *e=&db.entries[i];
        if(!s_db.entries[i].used||memcmp(e->name,s_db.entries[i].name,sizeof(e->name))||memcmp(e->salt,s_db.entries[i].salt,sizeof(e->salt))||(e->role!=TDSH_ROLE_USER&&e->role!=TDSH_ROLE_ADMIN)||(e->rights&~TDSH_RIGHT_ALL))continue;
        s_roles[i]=(uint8_t)e->role;s_rights[i]=e->rights;
    }
}
static esp_err_t access_save(nvs_handle_t h)
{
    access_db_t db={.magic=ACCESS_MAGIC};
    for(int i=0;i<USER_MAX;i++)if(s_db.entries[i].used){access_entry_t *e=&db.entries[i];memcpy(e->name,s_db.entries[i].name,sizeof(e->name));memcpy(e->salt,s_db.entries[i].salt,sizeof(e->salt));e->role=s_roles[i];e->rights=s_rights[i];}
    return nvs_set_blob(h,"access",&db,sizeof(db));
}
static esp_err_t access_save_current(void)
{
    nvs_handle_t h;esp_err_t err=nvs_open(USER_NS,NVS_READWRITE,&h);
    if(err!=ESP_OK)return err;
    err=access_save(h);if(err==ESP_OK)err=nvs_commit(h);nvs_close(h);return err;
}
tdsh_role_t tdsh_user_role(const char *name)
{
    USERS_GUARD;
    int i=find_user(name);if(!s_ready||i<0)return TDSH_ROLE_USER;
    return !strcmp(name,"root")?TDSH_ROLE_ROOT:s_roles[i]==TDSH_ROLE_ADMIN?TDSH_ROLE_ADMIN:TDSH_ROLE_USER;
}
uint32_t tdsh_user_rights(const char *name)
{
    USERS_GUARD;
    int i=find_user(name);if(!s_ready||i<0)return 0;
    return !strcmp(name,"root")?TDSH_RIGHT_ALL:s_rights[i]&TDSH_RIGHT_ALL;
}
uint32_t tdsh_user_generation(const char *name)
{
    USERS_GUARD;
    int i=find_user(name);if(!s_ready||i<0)return 0;
    /* Identity generation, not a password verifier. The full salted hash
     * still authenticates; this inexpensive fingerprint revokes old sessions. */
    uint32_t value=2166136261u;
    for(unsigned j=0;j<USER_SALT_LEN;j++)value=(value^s_db.entries[i].salt[j])*16777619u;
    return value?value:1;
}
int tdsh_user_list(int index,tdsh_user_info_t *out)
{
    USERS_GUARD;
    if(!s_ready||!out||index<0)return -EINVAL;
    for(int i=0;i<USER_MAX;i++)if(s_db.entries[i].used&&index--==0){snprintf(out->name,sizeof(out->name),"%s",s_db.entries[i].name);out->role=tdsh_user_role(out->name);out->rights=tdsh_user_rights(out->name);return 0;}
    return -ENOENT;
}
static bool access_can_manage(const char *actor,const char *name)
{
    if(!s_ready||!actor||!name)return false;
    if(!strcmp(actor,"root"))return tdsh_user_exists(actor);
    if(!strcmp(name,"root")||!strcmp(name,actor)||tdsh_user_role(actor)!=TDSH_ROLE_ADMIN||!(tdsh_user_rights(actor)&TDSH_RIGHT_USERS))return false;
    return !tdsh_user_exists(name)||!(tdsh_user_rights(name)&~tdsh_user_rights(actor));
}
int tdsh_user_create(const char *actor,const char *name,const char *password,tdsh_role_t role,uint32_t rights)
{
    USERS_GUARD;
    if(!access_can_manage(actor,name))return -EACCES;
    if(!valid_username(name)||!password||!password[0]||strlen(password)>128||(role!=TDSH_ROLE_USER&&role!=TDSH_ROLE_ADMIN)||(rights&~TDSH_RIGHT_ALL))return -EINVAL;
    if(rights&~tdsh_user_rights(actor))return -EACCES;
    if(find_user(name)>=0)return -EEXIST;
    int i=0;while(i<USER_MAX&&s_db.entries[i].used)i++;if(i==USER_MAX)return -ENOSPC;
    user_entry_t *e=&s_db.entries[i];memset(e,0,sizeof(*e));e->used=1;snprintf(e->name,sizeof(e->name),"%s",name);esp_fill_random(e->salt,USER_SALT_LEN);
    s_roles[i]=(uint8_t)role;s_rights[i]=rights;s_verified[i]=false;s_db.count++;
    if(make_hash(password,e->salt,e->hash)||save_db()!=ESP_OK){memset(e,0,sizeof(*e));s_roles[i]=0;s_rights[i]=TDSH_RIGHTS_USER;s_db.count--;return -EIO;}
    hint_forget(name);ensure_user_startup_file(name);return 0;
}
int tdsh_user_access_set(const char *actor,const char *name,tdsh_role_t role,uint32_t rights)
{
    USERS_GUARD;
    if(!access_can_manage(actor,name)||!strcmp(name,"root")||(rights&~tdsh_user_rights(actor)))return -EACCES;
    int i=find_user(name);if(i<0)return -ENOENT;
    if((role!=TDSH_ROLE_USER&&role!=TDSH_ROLE_ADMIN)||(rights&~TDSH_RIGHT_ALL))return -EINVAL;
    uint8_t old_role=s_roles[i];uint32_t old_rights=s_rights[i];s_roles[i]=(uint8_t)role;s_rights[i]=rights;
    if(access_save_current()!=ESP_OK){s_roles[i]=old_role;s_rights[i]=old_rights;return -EIO;}return 0;
}
int tdsh_user_password_set(const char *actor,const char *name,const char *old_password,const char *password)
{
    USERS_GUARD;
    if(!actor||!name||!password||!password[0]||strlen(password)>128)return -EINVAL;
    int i=find_user(name);if(i<0)return -ENOENT;
    if(!strcmp(actor,name)){if(!old_password||!check_password(i,old_password))return -EACCES;}
    else if(!access_can_manage(actor,name))return -EACCES;
    return set_password_idx(i,password)==ESP_OK?0:-EIO;
}
/* bootuser is still root-controlled. The remembered proof is minted only
 * after a successful password check and invalidates on password change. */
static void remember_verified(const char *name)
{
    int i=find_user(name);if(i<0||!s_verified[i])return;
    nvs_handle_t h;if(nvs_open(USER_NS,NVS_READWRITE,&h)!=ESP_OK)return;
    uint8_t enabled=0;char selected[TDSH_USERNAME_MAX];size_t n=sizeof(selected);
    if(nvs_get_u8(h,"remember",&enabled)==ESP_OK&&enabled&&nvs_get_str(h,BOOT_USER_KEY,selected,&n)==ESP_OK&&!strcmp(name,selected)){
        uint8_t old[USER_HASH_LEN];size_t bytes=sizeof(old);
        if(nvs_get_blob(h,"proof",old,&bytes)!=ESP_OK||bytes!=sizeof(old)||!hash_equal(old,s_db.entries[i].hash,sizeof(old))){if(nvs_set_blob(h,"proof",s_db.entries[i].hash,USER_HASH_LEN)==ESP_OK)(void)nvs_commit(h);}
    }nvs_close(h);
}
uint32_t tdsh_user_login(const char *name,const char *password)
{
    USERS_GUARD;
    int i=find_user(name);if(!s_ready||i<0||!password||!check_password(i,password))return 0;
    s_verified[i]=true;remember_verified(name);return tdsh_user_generation(name);
}
uint32_t tdsh_remembered_login(char *out,size_t size)
{
    USERS_GUARD;
    if(!s_ready||tdsh_boot_user_get(out,size))return false;
    int i=find_user(out);if(i<0)return false;
    nvs_handle_t h;if(nvs_open(USER_NS,NVS_READONLY,&h)!=ESP_OK)return false;
    uint8_t enabled=0,proof[USER_HASH_LEN];size_t n=sizeof(proof);
    bool ok=nvs_get_u8(h,"remember",&enabled)==ESP_OK&&enabled&&nvs_get_blob(h,"proof",proof,&n)==ESP_OK&&n==sizeof(proof)&&hash_equal(proof,s_db.entries[i].hash,sizeof(proof));nvs_close(h);if(!ok)out[0]=0;return ok?tdsh_user_generation(out):0;
}
bool tdsh_remembered_user(char *out,size_t size){return tdsh_remembered_login(out,size)!=0;}
bool tdsh_user_remember_allowed(const char *name)
{
    USERS_GUARD;
    nvs_handle_t h;if(!name||nvs_open(USER_NS,NVS_READONLY,&h)!=ESP_OK)return false;
    uint8_t enabled=0;char user[TDSH_USERNAME_MAX];size_t n=sizeof(user);
    bool ok=nvs_get_u8(h,"remember",&enabled)==ESP_OK&&enabled&&nvs_get_str(h,BOOT_USER_KEY,user,&n)==ESP_OK&&!strcmp(name,user);nvs_close(h);return ok;
}
int tdsh_boot_login_require_password(void)
{
    USERS_GUARD;
    nvs_handle_t h;if(nvs_open(USER_NS,NVS_READWRITE,&h)!=ESP_OK)return -EIO;
    esp_err_t err=nvs_set_u8(h,"remember",0);
    if(err==ESP_OK){esp_err_t erased=nvs_erase_key(h,"proof");if(erased!=ESP_OK&&erased!=ESP_ERR_NVS_NOT_FOUND)err=erased;}
    if(err==ESP_OK)err=nvs_commit(h);
    if(err==ESP_OK)memset(s_verified,0,sizeof(s_verified));
    nvs_close(h);return err==ESP_OK?0:-EIO;
}
int tdsh_cmd_userrole(tdsh_session_t *session,int argc,char **argv)
{
    if(argc<2||argc>3){printf("usage: userrole <username> [admin|user]\n");return 2;}
    if(!tdsh_user_exists(argv[1]))return 1;
    if(argc==2){printf("%s: %s\n",argv[1],tdsh_user_role(argv[1])==TDSH_ROLE_ROOT?"root":tdsh_user_role(argv[1])==TDSH_ROLE_ADMIN?"admin":"user");return 0;}
    tdsh_role_t role=!strcmp(argv[2],"admin")?TDSH_ROLE_ADMIN:TDSH_ROLE_USER;
    if(strcmp(argv[2],"admin")&&strcmp(argv[2],"user"))return 2;
    uint32_t rights=(role==TDSH_ROLE_ADMIN?TDSH_RIGHTS_ADMIN:TDSH_RIGHTS_USER)&tdsh_user_rights(session->username);
    int rc=tdsh_user_access_set(session->username,argv[1],role,rights);if(rc)printf("userrole: permission denied or account update failed (%d)\n",rc);return rc?1:0;
}
static const char *const right_names[]={"users","system","network","hardware","shared","time","apps"};
int tdsh_cmd_userrights(tdsh_session_t *session,int argc,char **argv)
{
    if(argc<2){printf("usage: userrights <username> [+right|-right ...]\n");return 2;}
    if(!tdsh_user_exists(argv[1]))return 1;
    uint32_t rights=tdsh_user_rights(argv[1]);
    for(int j=2;j<argc;j++){if((argv[j][0]!='+'&&argv[j][0]!='-')||!argv[j][1])return 2;int i=0;while(i<7&&strcmp(argv[j]+1,right_names[i]))i++;if(i==7)return 2;if(argv[j][0]=='+')rights|=1u<<i;else rights&=~(1u<<i);}
    if(argc>2){int rc=tdsh_user_access_set(session->username,argv[1],tdsh_user_role(argv[1]),rights);if(rc){printf("userrights: update refused (%d)\n",rc);return 1;}}
    printf("%s:",argv[1]);for(int i=0;i<7;i++)if(rights&(1u<<i))printf(" %s",right_names[i]);printf("\n");return 0;
}
