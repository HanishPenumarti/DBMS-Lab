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
    course1->course_number=2;
    strcpy(course1->course_name,"ca");
    strcpy(course1->instructor,"karthikeyan");
    store_coursedb(course1,2);
    course1->course_number=3;
    strcpy(course1->course_name,"cn");
    strcpy(course1->instructor,"bakre");
    store_coursedb(course1,3);
    course1->course_number=4;
    strcpy(course1->course_name,"calculus");
    strcpy(course1->instructor,"jaya");
    store_coursedb(course1,4);
    course1->course_number=5;
    strcpy(course1->course_name,"prob");
    strcpy(course1->instructor,"chatto");
    store_coursedb(course1,5);
    close_coursedb(dbname);
}
int round2(char* dbname)
{
    open_coursedb(dbname);
    struct Course* cptr = malloc(sizeof(struct Course));
    int result = get_coursedb(cptr,4);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr->course_number,cptr->course_name,cptr->instructor);
    if(result==REC_NOT_FOUND) printf("Record not found in first get\n");
    cptr->course_number=4;
    strcpy(cptr->course_name,"os");
    strcpy(cptr->instructor,"badri");
    result = update_coursedb(cptr,4);
    if(result==REC_NOT_FOUND) printf("Record not found in update\n");
    struct Course* cptr1 = malloc(sizeof(struct Course));
    result = get_coursedb(cptr1,4);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr1->course_number,cptr1->course_name,cptr1->instructor);
    else if(result==REC_NOT_FOUND) printf("Record not found in get\n");
    result = get_coursedb(cptr,3);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr->course_number,cptr->course_name,cptr->instructor);
    if(result==REC_NOT_FOUND) printf("Record not found in first get\n");
    cptr->course_number=3;
    strcpy(cptr->course_name,"la");
    strcpy(cptr->instructor,"manisha");
    result = update_coursedb(cptr,3);
    if(result==REC_NOT_FOUND) printf("Record not found in update\n");
    cptr1 = malloc(sizeof(struct Course));
    result = get_coursedb(cptr1,3);
    if(result==SUCCESS)
        printf("%d\n%s\n%s\n",cptr1->course_number,cptr1->course_name,cptr1->instructor);
    else if(result==REC_NOT_FOUND) printf("Record not found in get\n");
    return close_coursedb(dbname);
}
int main()
{
    char* db = "penumarti";
    printf("Enter round:\n");
    int n;
    scanf("%d",&n);
    if (n==1)      round1(db);
    else if (n==2) round2(db);
    return 0;
}