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
void printMajorOptions();
void displayStudent();
void generateTableHead();
void generateTableLine(int id, char *name, char *major, char *studentCode, char *dateOfBirth);
void generateTableTail();

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

        int majorChoice;

        while (1) {
            // display and select major options
            printMajorOptions();

            // check if scanf successfully reads an integer
            if (scanf("%d", &majorChoice) != 1) {
                int c;
                // clear the input buffer if a non-integer input is detected
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid input. Please enter a number (1-3) for the major choice: ");
            } else if (majorChoice >= 1 && majorChoice <= 3) {
                // valid major choice
                break;
            } else {
                printf("Invalid major choice. Please try again.\n");
            }
        }

        switch (majorChoice) {
            case 1:
                strcpy(newStudent.major, "KTPM");
                break;
            case 2:
                strcpy(newStudent.major, "MS");
                break;
            case 3:
                strcpy(newStudent.major, "NNA");
                break;
        }

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



void printMajorOptions() {
    printf("Select a major:\n");
    printf("1. KTPM (Ky thuat phan mem)\n");
    printf("2. MS (Marketing so)\n");
    printf("3. NNA (Ngon ngu Anh)\n");
    printf("Enter the number corresponding to the major: ");
}



void displayStudent() {
    if (studentCount == 0) {
        printf("No students added yet.\n");
    } else {
        printf("\nList of students:\n");
        generateTableHead();
        for (int i = 0; i < studentCount; i++) {
            // printf("Student %d:\n", i + 1);
            // printf("Name: %s\n", studentList[i].name);
            // printf("Major: %s\n", studentList[i].major);
            // printf("Student Code: %s\n", studentList[i].studentCode);
            // printf("Date of Birth: %s\n", studentList[i].dateOfBirth);
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].studentCode, studentList[i].dateOfBirth);
        }
        generateTableTail();
    }
}

void generateTableHead() {
    printf("+------+--------------------+----------------+----------------+----------------+\n");
    printf("|  ID  | Student Name       | Major          | Student Code   | Date of Birth  |\n");
    printf("+------+--------------------+----------------+----------------+----------------+\n");
}

void generateTableLine(int id, char *name, char *major, char *studentCode, char *dateOfBirth) {
    printf("| %2d   | %-18s | %-14s | %-14s | %-14s |\n", id, name, major, studentCode, dateOfBirth);
}

void generateTableTail() {
    printf("+------+--------------------+----------------+----------------+----------------+\n");
}