#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#define MAX_STUDENTS 100  // define the maximum number of students to avoid magic numbers

struct Student {
    char name[100];
    char major[50];
    char studentCode[20];
    char dateOfBirth[20];
};

struct Student studentList[MAX_STUDENTS];  // create an array to store students
int studentCount = 0;  // keep track of the number of students
int input;

void printMenu();
void addStudent();
void displayStudent();

int main() {
    do {
        printMenu();

        switch (input) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudent();
                break;
            case 3:
                printf("Search student\n");
                break;
            case 4:
                printf("Delete student\n");
                break;
            case 5:
                printf("Sort student\n");
                break;
            case 6:
                printf("Change the list of student\n");
                break;
            case 7:
                printf("Exit\n");
                break;
            default:
                printf("Invalid input\n");
        }
    } while (input != 7); // continue the loop until the user chooses to exit (option 7)

    return 0;
}
void printMenu() {
    printf("\t*-------------------Management Student------------------*\n");
    printf("\t| 1. Add student\t\t\t\t\t|\n");
    printf("\t| 2. Display the list of student\t\t\t|\n");
    printf("\t| 3. Search student\t\t\t\t\t|\n");
    printf("\t| 4. Delete student\t\t\t\t\t|\n");
    printf("\t| 5. Sort student\t\t\t\t\t|\n");
    printf("\t| 6. Change the list of student\t\t\t\t|\n");
    printf("\t| 7. Exit\t\t\t\t\t\t|\n");
    printf("\t*-------------------------------------------------------*\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &input);
}

void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        struct Student newStudent;
        printf("Enter student name: ");
        scanf("%s", newStudent.name);
        printf("Enter major: ");
        scanf("%s", newStudent.major);
        printf("Enter student code: ");
        scanf("%s", newStudent.studentCode);
        printf("Enter date of birth: ");
        scanf("%s", newStudent.dateOfBirth);

        // add the new student to the array
        studentList[studentCount] = newStudent;
        studentCount++;

        printf("Student added successfully!\n");
    } else {
        printf("Maximum number of students reached. Cannot add more students.\n");
    }
}

void displayStudent() {
    printf("\nList of students:\n");
    if (studentCount == 0) {
        printf("No students added yet.\n");
    } else {
        for (int i = 0; i < studentCount; i++) {
            printf("Student %d:\n", i + 1);
            printf("Name: %s\n", studentList[i].name);
            printf("Major: %s\n", studentList[i].major);
            printf("Student Code: %s\n", studentList[i].studentCode);
            printf("Date of Birth: %s\n", studentList[i].dateOfBirth);
        }
    }
}