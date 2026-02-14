#define SUCCESS 0
#define FAILURE -1
#define MAX 1000
#define REC_NOT_FOUND 1
#define OPEN 1
#define CLOSED 0
#define DELETED 0
#define NOT_DELETED 1
struct Rec_Ndx
{
    long int key;
    long int loc;
    int is_deleted;
    int old_key;
};
struct dbInfo
{
    FILE* dbfile;
    FILE* indexfile;
    struct Rec_Ndx indexarr[MAX];
    int rec_count;
    char dbname[50];
    int status;
    int rec_size;
};
extern struct dbInfo cdb_info;
void db_init();
int create_db(char * dbname);
int open_db(char* dbname, int rec_size);
int store_db(int key, void* c);
int get_db(int key,void* coutput);
int update_db(int key,void* new);
int delete_db(int key);
int close_db();