#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SUCCESS 0
#define FAILURE -1
#define MAX 1000
#define REC_NOT_FOUND 1
struct Course
{
    int course_number;
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
int store_coursedb(struct Course* c, int key);
int get_coursedb(struct Course* coutput, int course_number);
int update_coursedb(struct Course* new, int course_number);
int close_coursedb(char* dbname);