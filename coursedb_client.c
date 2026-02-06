#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "coursedb.h"
int main()
{
    coursedb_init();
    char dbn[]= {"hello"};
    create_coursedb(dbn);
    open_coursedb(dbn);
    struct Course* course1 = malloc(sizeof(struct Course));
    course1->course_number=1;
    strcpy(course1->course_name,"dsa");
    strcpy(course1->instructor,"murali");
    store_coursedb(course1);
    struct Course* cptr = malloc(sizeof(struct Course));
    cptr->course_number=2;
    strcpy(cptr->course_name,"os");
    strcpy(cptr->instructor,"badri");
    int result = update_coursedb(cptr,1);
    if(result==REC_NOT_FOUND) printf("Record not found in update\n");
    struct Course* cptr1 = malloc(sizeof(struct Course));
    result = get_coursedb(cptr1,2);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr1->course_number,cptr1->course_name,cptr1->instructor);
    else if(result==REC_NOT_FOUND) printf("Record not found in get\n");
    close_coursedb(cdb_info.dbfile);
    return 0;
}