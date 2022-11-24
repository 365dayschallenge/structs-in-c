#include <stdio.h>
#include <stdlib.h>

int main(){

    struct Student
    {
        char name[10];
        char course[30];
        char reg_no[10];
        char home[ 10];
    };

    // Declaring a variable of type struct Student
    struct Student student1 = {"John", "Bsc Computer Science", "1234", "Nairobi"};
    struct Student student2 = {"Mary", "Bsc BBIT", "5678", "Nakuru"};
    struct Student student3 = {"Peter", "Bsc IT", "9104", "Narok"};
    struct Student student4 = {"Jane", "Bsc Computer Science", "1121", "Nairobi"};
    struct Student student5 = {"James", "Bsc Computer Science", "3141", "Kisii"};

    // loop through all students
    struct Student students[] = {student1, student2, student3, student4, student5};
    for (int i = 0; i < 5; i++)
    {
        // print student details
        
        printf("Name of student"[i],"%s", i,students[i].name);
        printf("Course of student"[i], "%s", i,students[i].course);
        printf("Reg. No of student"[i], "%s",i, students[i].reg_no);
        printf("Home ofstudent"[i], "%s",i, students[i].home);
    }


    return 0;
}