#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SUCCESS 0
#define FAILURE -1
#define REC_NOT_FOUND 1
struct Course
{
    int course_number;
    char course_name[50];
    char instructor[50];
};
struct CoursedbInfo
{
    FILE* dbfile;
    char dbname[50];
    int status;
};
extern struct CoursedbInfo cdb_info;
void coursedb_init();
int create_coursedb(char * dbname);
//fopen in wb mode and then immediately fclose it
int open_coursedb(char* dbname);
//fopen in rb+
int store_coursedb(struct Course* c);
//fseek to EOF and then fwrite
int get_coursedb(struct Course* coutput, int course_number);
//return 0 if found and 1 if not
int update_coursedb(struct Course* new, int course_number);
//fseek to beginning and then iterate over each record until course number matches
int close_coursedb(FILE* fptr);
//fclose