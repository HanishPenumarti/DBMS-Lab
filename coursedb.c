#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "coursedb.h"
struct CoursedbInfo cdb_info;
void coursedb_init()
{
    cdb_info.dbfile=NULL;
    strcpy(cdb_info.dbname,"");
    cdb_info.status=0;
}
int create_coursedb(char * dbname)
{
    cdb_info.dbfile = fopen(dbname,"rb+");
    strcpy(cdb_info.dbname,dbname);
    fclose(cdb_info.dbfile);
}
int open_coursedb(char* dbname)
{
    fopen(dbname,"rb+");
}
int store_coursedb(struct Course* c)
{
    fseek(cdb_info.dbfile,0,SEEK_END);
    fwrite(c,sizeof(struct Course),1,cdb_info.dbfile);
}
//return 0 if found and 1 if not
//fseek to beginning and then iterate over each record until course number matches
int get_coursedb(struct Course* coutput, int course_number)
{
    fseek(cdb_info.dbfile,0,SEEK_SET);
    while(fread(coutput,sizeof(struct Course), 1, cdb_info.dbfile))
    {
        if (coutput->course_number==course_number) return SUCCESS;
    }
    return REC_NOT_FOUND;
}
int update_coursedb(struct Course* new, int course_number)
{
    struct Course* temp = malloc(sizeof(struct Course));
    int result = get_coursedb(temp, course_number);
    if(result==REC_NOT_FOUND) return REC_NOT_FOUND;
    long int curr_loc = ftell(cdb_info.dbfile);
    curr_loc-= sizeof(struct Course);
    fseek(cdb_info.dbfile,curr_loc,SEEK_SET);
    fwrite(new,sizeof(struct Course),1,cdb_info.dbfile);
    return SUCCESS;
}
int close_coursedb(FILE* fptr)
{
    fclose(fptr);
}