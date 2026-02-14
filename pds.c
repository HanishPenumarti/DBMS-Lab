#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pds.h"
struct dbInfo cdb_info;
void db_init()
{
    cdb_info.dbfile=NULL;
    strcpy(cdb_info.dbname,"");
    cdb_info.status=CLOSED;
    cdb_info.rec_count=0;
}
int create_db(char * dbname)
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
    cdb_info.status=CLOSED;
    return SUCCESS;

}
int open_db(char* dbname, int rec_size)
{
    char arr1[50];
    strcpy(arr1,dbname);
    char arr2[50];
    strcpy(arr2,dbname);
    strcat(arr1,".dat");
    strcat(arr2,".ndx");
    cdb_info.rec_size=rec_size;
    cdb_info.indexfile = fopen(arr2,"rb+");
    if(cdb_info.status==CLOSED)
    {
        cdb_info.dbfile = fopen(arr1,"rb+");
        cdb_info.status=OPEN;
    }
    if(!cdb_info.dbfile || !cdb_info.indexfile) return FAILURE;
    fread(&cdb_info.rec_count,sizeof(int),1,cdb_info.indexfile);
    fread(cdb_info.indexarr,sizeof(struct Rec_Ndx),cdb_info.rec_count,cdb_info.indexfile);
    fclose(cdb_info.indexfile);
    return SUCCESS;
}
int store_db(int key,void* c)
{
    if(cdb_info.status==OPEN)
    {
        if(cdb_info.rec_count==MAX)
        {
            printf("The database is full\n");
            return FAILURE;
        }
        fseek(cdb_info.dbfile,0,SEEK_END);
        long int loc = ftell(cdb_info.dbfile);
        struct Rec_Ndx temp = {key,loc,NOT_DELETED,key};
        cdb_info.indexarr[cdb_info.rec_count] = temp;
        cdb_info.rec_count++;
        int num = key;
        fwrite(&num,sizeof(int),1,cdb_info.dbfile);
        fwrite(c,cdb_info.rec_size,1,cdb_info.dbfile);
        return SUCCESS;
    }
    return FAILURE;
}
int get_db(int key,void* coutput)
{
    if(cdb_info.status==OPEN)
    {
        long int reqLoc = -1;
        for(int i=0;i<cdb_info.rec_count;i++)
        {
            if(cdb_info.indexarr[i].key==key)
            {
                reqLoc = cdb_info.indexarr[i].loc;
                break;
            }
        }
        if(reqLoc == -1) return REC_NOT_FOUND;
        fseek(cdb_info.dbfile,reqLoc,SEEK_SET);
        int num = 0;
        fread(&num,sizeof(int),1,cdb_info.dbfile);
        fread(coutput,cdb_info.rec_size,1,cdb_info.dbfile);
        return SUCCESS;
    }
    return FAILURE;
}
int update_db(int key,void* new)
{
    if(cdb_info.status==OPEN)
    {
        long int reqLoc = -1;
        for(int i=0;i<cdb_info.rec_count;i++)
        {
            if(cdb_info.indexarr[i].key==key)
            {
                reqLoc = cdb_info.indexarr[i].loc;
                break;
            }
        }
        if(reqLoc == -1) return REC_NOT_FOUND;
        fseek(cdb_info.dbfile,reqLoc,SEEK_SET);
        int num = key;
        fwrite(&num,sizeof(int),1,cdb_info.dbfile);
        fwrite(new,cdb_info.rec_size,1,cdb_info.dbfile);
        return SUCCESS;
    }
    return FAILURE;
}
int delete_db(int key)
{
    if(cdb_info.status==OPEN)
    {
        int found = 0;
        for(int i=0;i<cdb_info.rec_count;i++)
        {
            if(cdb_info.indexarr[i].key==key)
            {
                found = 1;
                cdb_info.indexarr[i].is_deleted = DELETED;
                cdb_info.indexarr[i].key = -1;
            }
        }
        if(found) return SUCCESS;
    }
    return FAILURE;
}
int undelete_db(int key)
{
    if(cdb_info.status==OPEN)
    {
        int found = 0;
        for(int i=0;i<cdb_info.rec_count;i++)
        {
            if(cdb_info.indexarr[i].old_key==key && cdb_info.indexarr[i].key==-1)
            {
                found = 1;
                cdb_info.indexarr[i].is_deleted = NOT_DELETED;
                cdb_info.indexarr[i].key = key;
            }
        }
        if(!found) return REC_NOT_FOUND;
        return SUCCESS;
    }
    return FAILURE;
}
int close_db()
{
    if(cdb_info.status==OPEN)
    {
        char arr2[50];
        strcpy(arr2,cdb_info.dbname);
        strcat(arr2,".ndx");
        cdb_info.indexfile = fopen(arr2,"wb");
        fwrite(&cdb_info.rec_count,sizeof(int),1,cdb_info.indexfile);
        fwrite(cdb_info.indexarr,sizeof(struct Rec_Ndx),cdb_info.rec_count,cdb_info.indexfile);
        fclose(cdb_info.indexfile);
        fclose(cdb_info.dbfile);
        cdb_info.status=CLOSED;
        return SUCCESS;
    }
    return FAILURE;
}