/* Password hints: one optional line per account, shown at sign-in to
 * anyone at the device, so it must not give the password away. Kept in
 * NVS ("hints") by account name and read only when needed (no RAM while
 * idle). Creating or deleting an account forgets a hint left under its
 * name. */
typedef struct {char name[TDSH_USERNAME_MAX];char hint[TDSH_HINT_MAX];} hint_entry_t;
typedef struct {uint32_t magic;hint_entry_t entries[USER_MAX];} hint_db_t;
#define HINT_MAGIC 0x54444831u

/* The stored hints, or an empty table; NULL only without memory. */
static hint_db_t *hint_load(void)
{
    hint_db_t *db=calloc(1,sizeof(*db));if(!db)return NULL;
    nvs_handle_t h;size_t size=sizeof(*db);
    if(nvs_open(USER_NS,NVS_READONLY,&h)==ESP_OK){
        if(nvs_get_blob(h,"hints",db,&size)!=ESP_OK||size!=sizeof(*db)||db->magic!=HINT_MAGIC)memset(db,0,sizeof(*db));
        nvs_close(h);
    }
    db->magic=HINT_MAGIC;
    for(int i=0;i<USER_MAX;i++){db->entries[i].name[TDSH_USERNAME_MAX-1]=0;db->entries[i].hint[TDSH_HINT_MAX-1]=0;}
    return db;
}
static esp_err_t hint_store(const hint_db_t *db)
{
    nvs_handle_t h;esp_err_t err=nvs_open(USER_NS,NVS_READWRITE,&h);if(err!=ESP_OK)return err;
    err=nvs_set_blob(h,"hints",db,sizeof(*db));if(err==ESP_OK)err=nvs_commit(h);nvs_close(h);return err;
}
static hint_entry_t *hint_find(hint_db_t *db,const char *name)
{
    for(int i=0;i<USER_MAX;i++)if(db->entries[i].hint[0]&&!strcmp(db->entries[i].name,name))return &db->entries[i];
    return NULL;
}
static void hint_forget(const char *name)
{
    hint_db_t *db=hint_load();if(!db)return;
    hint_entry_t *e=hint_find(db,name);
    if(e){memset(e,0,sizeof(*e));(void)hint_store(db);}
    free(db);
}
static bool hint_valid(const char *hint)
{
    if(strlen(hint)>=TDSH_HINT_MAX)return false;
    for(const unsigned char *p=(const unsigned char *)hint;*p;p++)if(*p<0x20||*p==0x7f)return false;
    return true;
}
bool tdsh_hint_reveals(const char *hint,const char *password)
{
    if(!hint||!password||!password[0]||!hint[0])return false;
    size_t n=strlen(password),m=strlen(hint);
    if(n<3)return n==m&&!strcasecmp(hint,password);
    for(size_t i=0;i+n<=m;i++)if(!strncasecmp(hint+i,password,n))return true;
    return false;
}
/* root still has the factory password, which is printed in every manual. */
static bool root_has_factory_password(int idx)
{
    uint8_t hash[USER_HASH_LEN];
    return make_hash(DEFAULT_ROOT_PASSWORD,s_db.entries[idx].salt,hash)==0&&hash_equal(hash,s_db.entries[idx].hash,USER_HASH_LEN);
}
int tdsh_user_hint_get(const char *name,char *out,size_t size)
{
    USERS_GUARD;
    if(!out||!size)return -EINVAL;
    out[0]=0;
    int idx=s_ready&&name?find_user(name):-1;
    if(idx<0)return -ENOENT;
    /* Until it is changed, the factory password is the hint: a hint left
     * from before a reset would be wrong. */
    if(!strcmp(name,"root")&&root_has_factory_password(idx)){snprintf(out,size,"%s",TDSH_FACTORY_HINT);return 0;}
    hint_db_t *db=hint_load();if(!db)return -ENOMEM;
    hint_entry_t *e=hint_find(db,name);if(e)snprintf(out,size,"%s",e->hint);
    free(db);return 0;
}
int tdsh_user_hint_set(const char *actor,const char *name,const char *hint)
{
    USERS_GUARD;
    if(!s_ready||!actor||!name||!hint)return -EINVAL;
    if(find_user(name)<0)return -ENOENT;
    if(!(!strcmp(actor,name)&&tdsh_user_exists(actor))&&!access_can_manage(actor,name))return -EACCES;
    if(!hint_valid(hint))return -EINVAL;
    hint_db_t *db=hint_load();if(!db)return -ENOMEM;
    hint_entry_t *e=hint_find(db,name);
    if(!e&&hint[0])for(int i=0;i<USER_MAX&&!e;i++)if(!db->entries[i].hint[0])e=&db->entries[i];
    int rc=0;
    if(!e&&hint[0])rc=-ENOSPC;
    else if(e){
        memset(e,0,sizeof(*e));
        if(hint[0]){snprintf(e->name,sizeof(e->name),"%s",name);snprintf(e->hint,sizeof(e->hint),"%s",hint);}
        rc=hint_store(db)==ESP_OK?0:-EIO;
    }
    free(db);return rc;
}
