#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "coursedb.h"
int round1(char* dbname)
{
    coursedb_init();
    create_coursedb(dbname);
    open_coursedb(dbname);
    struct Course* course1 = malloc(sizeof(struct Course));
    course1->course_number=1;
    strcpy(course1->course_name,"dsa");
    strcpy(course1->instructor,"murali");
    store_coursedb(course1,1);
    for(int i=0;i<cdb_info.rec_count;i++)
    {
        printf("key is: %ld\n and location is: %ld\n",
        cdb_info.indexarr[i].key,cdb_info.indexarr[i].loc);
    }
    close_coursedb(dbname);
}
int round2(char* dbname)
{
    open_coursedb(dbname);
    struct Course* cptr = malloc(sizeof(struct Course));
    int result = get_coursedb(cptr,1);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr->course_number,cptr->course_name,cptr->instructor);
    if(result==REC_NOT_FOUND) printf("Record not found in first get\n");
    cptr->course_number=1;
    strcpy(cptr->course_name,"os");
    strcpy(cptr->instructor,"badri");
    result = update_coursedb(cptr,1);
    if(result==REC_NOT_FOUND) printf("Record not found in update\n");
    struct Course* cptr1 = malloc(sizeof(struct Course));
    result = get_coursedb(cptr1,1);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr1->course_number,cptr1->course_name,cptr1->instructor);
    else if(result==REC_NOT_FOUND) printf("Record not found in get\n");
    return close_coursedb(dbname);
}
int main()
{
    char* db = "hanish";
    printf("The result of round is: %d\n",round2(db));
    return 0;
}