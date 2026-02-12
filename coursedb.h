#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SUCCESS 0
#define FAILURE -1
#define MAX 1000
#define REC_NOT_FOUND 1
#define OPEN 1
#define CLOSED 0
struct Course
{
    int course_num;
    char course_name[50];
    char instructor[50];
};
struct Course_Ndx
{
    long int key;
    long int loc;
};
struct CoursedbInfo
{
    FILE* dbfile;
    FILE* indexfile;
    struct Course_Ndx indexarr[1000];
    int rec_count;
    char dbname[50];
    int status;
};
extern struct CoursedbInfo cdb_info;
void coursedb_init();
int create_coursedb(char * dbname);
int open_coursedb(char* dbname);
int store_coursedb(int key, struct Course* c);
int get_coursedb(int course_num,struct Course* coutput);
int update_coursedb(int course_num,struct Course* new);
int close_coursedb();