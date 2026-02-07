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
    cdb_info.rec_count=0;
}
int create_coursedb(char * dbname)
{
    char arr1[50];
    strcpy(arr1,dbname);
    char arr2[50];
    strcpy(arr2,dbname);
    strcat(arr1,".dat");
    strcat(arr2,".ndx");
    int result;
    cdb_info.dbfile = fopen(arr1,"wb");
    cdb_info.indexfile = fopen(arr2,"wb");
    if(!cdb_info.dbfile || !cdb_info.indexfile) return FAILURE;
    int nr = 0;
    fwrite(&nr,sizeof(int),1,cdb_info.indexfile);
    strcpy(cdb_info.dbname,dbname);
    fclose(cdb_info.dbfile);
    fclose(cdb_info.indexfile);
    return SUCCESS;

}
int open_coursedb(char* dbname)
{
    char arr1[50];
    strcpy(arr1,dbname);
    char arr2[50];
    strcpy(arr2,dbname);
    strcat(arr1,".dat");
    strcat(arr2,".ndx");
    cdb_info.dbfile = fopen(arr1,"rb+");
    cdb_info.indexfile = fopen(arr2,"rb+");
    if(!cdb_info.dbfile || !cdb_info.indexfile) return FAILURE;
    fread(&cdb_info.rec_count,sizeof(int),1,cdb_info.indexfile);
    fread(cdb_info.indexarr,sizeof(struct Course_Ndx),cdb_info.rec_count,cdb_info.indexfile);
    fclose(cdb_info.indexfile);
    return SUCCESS;
}
int store_coursedb(struct Course* c, int key)
{
    if(cdb_info.rec_count==MAX) return FAILURE;
    fseek(cdb_info.dbfile,0,SEEK_END);
    long int loc = ftell(cdb_info.dbfile);
    struct Course_Ndx temp = {key,loc};
    cdb_info.indexarr[cdb_info.rec_count] = temp;
    cdb_info.rec_count++;
    int num = key;
    fwrite(&num,sizeof(int),1,cdb_info.dbfile);
    fwrite(c,sizeof(struct Course),1,cdb_info.dbfile);
    return SUCCESS;
}
int get_coursedb(struct Course* coutput, int course_number)
{
    long int reqLoc = -1;
    for(int i=0;i<cdb_info.rec_count;i++)
    {
        if(cdb_info.indexarr[i].key==course_number)
        {
            reqLoc = cdb_info.indexarr[i].loc;
            break;
        }
    }
    if(reqLoc == -1) return REC_NOT_FOUND;
    fseek(cdb_info.dbfile,reqLoc,SEEK_SET);
    int num = 0;
    fread(&num,sizeof(int),1,cdb_info.dbfile);
    fread(coutput,sizeof(struct Course),1,cdb_info.dbfile);
    if(num==coutput->course_number) return SUCCESS;
    return FAILURE; 
}
int update_coursedb(struct Course* new, int course_number)
{
    long int reqLoc = -1;
    for(int i=0;i<cdb_info.rec_count;i++)
    {
        if(cdb_info.indexarr[i].key==course_number)
        {
            reqLoc = cdb_info.indexarr[i].loc;
            break;
        }
    }
    if(reqLoc == -1) return REC_NOT_FOUND;
    fseek(cdb_info.dbfile,reqLoc,SEEK_SET);
    int num = course_number;
    fwrite(&num,sizeof(int),1,cdb_info.dbfile);
    fwrite(new,sizeof(struct Course),1,cdb_info.dbfile);
    return SUCCESS;
}
int close_coursedb(char* dbname)
{
    char arr2[50];
    strcpy(arr2,dbname);
    strcat(arr2,".ndx");
    cdb_info.indexfile = fopen(arr2,"rb+");
    fwrite(&cdb_info.rec_count,sizeof(int),1,cdb_info.indexfile);
    fwrite(cdb_info.indexarr,sizeof(struct Course_Ndx),cdb_info.rec_count,cdb_info.indexfile);
    fclose(cdb_info.indexfile);
    fclose(cdb_info.dbfile);
}