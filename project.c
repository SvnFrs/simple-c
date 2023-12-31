#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define MAX_STUDENTS 100 // define the maximum number of students to avoid magic numbers

struct Student
{
    char name[100];
    char major[50];
    char studentCode[20];
    char dateOfBirth[20];
};

struct Student studentList[MAX_STUDENTS]; // create an array to store students
int studentCount = 0;                     // keep track of the number of students
int input;

void printMenu();
void addStudent();
void printMajorOptions();
int isStudentCodeUnique(const char *studentCode);
int validateStudentCode(const char *major, const char *studentCode);
int isLeapYear(int year);
int validateDateOfBirth(const char *dateOfBirth);
void displayStudent();
void generateTableHead();
void generateTableLine(int id, char *name, char *major, char *studentCode, char *dateOfBirth);
void generateTableTail();
void searchStudent();
void deleteStudent();
void sortStudent();
void printSortOptions();

int main()
{
    printf("Welcome to the student management program!\n");
    do
    {
        printMenu();

        switch (input)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            sortStudent();
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
void printMenu()
{
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

void addStudent()
{
    if (studentCount < MAX_STUDENTS)
    {
        struct Student newStudent;
        printf("Enter student name: ");
        scanf("%s", newStudent.name);

        int majorChoice;

        while (1)
        {
            // display and select major options
            printMajorOptions();

            // check if scanf successfully reads an integer
            if (scanf("%d", &majorChoice) != 1)
            {
                int c;
                // clear the input buffer if a non-integer input is detected
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                printf("Invalid input. Please enter a number (1-3) for the major choice: ");
            }
            else if (majorChoice >= 1 && majorChoice <= 3)
            {
                // valid major choice
                break;
            }
            else
            {
                printf("Invalid major choice. Please try again.\n");
            }
        }

        switch (majorChoice)
        {
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

        // validate and input student code until a valid, unique format is entered
        while (1)
        {
            printf("Enter student code: ");
            scanf("%s", newStudent.studentCode);
            if (validateStudentCode(newStudent.major, newStudent.studentCode))
            {
                break; // valid and unique student code
            }
            else
            {
                printf("Invalid or non-unique student code for the chosen major. Please enter a valid and unique student code.\n");
            }
        }

        // validate and input date of birth until a valid format is entered
        while (1)
        {
            printf("Enter date of birth (dd/mm/yyyy): ");
            scanf("%s", newStudent.dateOfBirth);
            if (validateDateOfBirth(newStudent.dateOfBirth))
            {
                break; // valid date format
            }
            else
            {
                printf("Invalid date format, values, or future date. Please enter the date in 'dd/mm/yyyy' format.\n");
            }
        }

        // add the new student to the array
        studentList[studentCount] = newStudent;
        studentCount++;
        printf("Student added successfully!\n");
    }
    else
    {
        printf("Maximum number of students reached. Cannot add more students.\n");
    }
}

void printMajorOptions()
{
    printf("Select a major:\n");
    printf("1. KTPM (Ky thuat phan mem)\n");
    printf("2. MS (Marketing so)\n");
    printf("3. NNA (Ngon ngu Anh)\n");
    printf("Enter the number corresponding to the major: ");
}

int isStudentCodeUnique(const char *studentCode)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(studentList[i].studentCode, studentCode) == 0)
        {
            return 0; // student code already exists
        }
    }
    return 1; // student code is unique
}

int validateStudentCode(const char *major, const char *studentCode)
{
    if (strcmp(major, "KTPM") == 0)
    {
        // major is 'KTPM', so student code should start with 'CE'
        if (strncmp(studentCode, "CE", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
        {
            return 1; // valid and unique student code
        }
    }
    else if (strcmp(major, "MS") == 0)
    {
        // major is 'MS', so student code should start with 'BE'
        if (strncmp(studentCode, "BE", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
        {
            return 1; // valid and unique student code
        }
    }
    else if (strcmp(major, "NNA") == 0)
    {
        // major is 'NNA', so student code should start with 'LE'
        if (strncmp(studentCode, "LE", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
        {
            return 1; // valid and unique student code
        }
    }
    return 0; // invalid or non-unique student code for the chosen major
}

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1; // leap year
    }
    return 0; // not a leap year
}

int validateDateOfBirth(const char *dateOfBirth)
{
    int day, month, year;
    if (sscanf(dateOfBirth, "%d/%d/%d", &day, &month, &year) == 3)
    {
        if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12)
        {
            int maxDay = 31; // default to maximum days in a month
            if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                maxDay = 30; // April, June, September, November have 30 days
            }
            else if (month == 2)
            {
                maxDay = isLeapYear(year) ? 29 : 28; // February has 28 or 29 days depending on leap year
            }

            if (day >= 1 && day <= maxDay)
            {
                // check if the entered date is not in the future
                // stolen from https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program#1442131
                time_t current_time;
                struct tm *current_date;
                time(&current_time);
                current_date = localtime(&current_time);

                if (year < (current_date->tm_year + 1900) || (year == (current_date->tm_year + 1900) &&
                                                              (month < (current_date->tm_mon + 1) || (month == (current_date->tm_mon + 1) &&
                                                                                                      day <= current_date->tm_mday))))
                {
                    return 1; // valid date format and values
                }
            }
        }
    }
    return 0; // invalid date format or values
}

void displayStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
    }
    else
    {
        printf("\nList of students:\n");
        generateTableHead();
        for (int i = 0; i < studentCount; i++)
        {
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

void generateTableHead()
{
    printf("+------+--------------------+----------------+----------------+----------------+\n");
    printf("|  ID  | Student Name       | Major          | Student Code   | Date of Birth  |\n");
    printf("+------+--------------------+----------------+----------------+----------------+\n");
}

void generateTableLine(int id, char *name, char *major, char *studentCode, char *dateOfBirth)
{
    printf("| %2d   | %-18s | %-14s | %-14s | %-14s |\n", id, name, major, studentCode, dateOfBirth);
}

void generateTableTail()
{
    printf("+------+--------------------+----------------+----------------+----------------+\n");
}

void searchStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    char searchQuery[100];
    printf("Enter part of the student's name: ");
    scanf("%s", searchQuery);

    int found = 0;

    for (int i = 0; i < studentCount; i++)
    {
        if (strstr(studentList[i].name, searchQuery) != NULL)
        {
            if (!found)
            {
                printf("Students found:\n");
                generateTableHead();
                found = 1;
            }
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].studentCode, studentList[i].dateOfBirth);
        }
    }

    if (!found)
    {
        printf("No matching students found.\n");
    }
    else
    {
        generateTableTail();
    }
}

void deleteStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }
    generateTableHead();
    for (int i = 0; i < studentCount; i++)
    {
        generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].studentCode, studentList[i].dateOfBirth);
    }
    generateTableTail();
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);
    for (int i = id - 1; i < studentCount - 1; i++)
    {
        studentList[i] = studentList[i + 1];
    }
    studentCount--;
    printf("Student deleted successfully.\n");

    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }
    else
    {
        generateTableHead();
        for (int i = 0; i < studentCount; i++)
        {
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].studentCode, studentList[i].dateOfBirth);
        }
        generateTableTail();
    }
}

void sortStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    int option;
    printSortOptions();
    printf("Enter the number corresponding to the sorting option: ");
    scanf("%d", &option);

    if (option < 1 || option > 4)
    {
        printf("Invalid sorting option.\n");
        return;
    }

    // create a temporary list of students for sorting
    struct Student tempStudentList[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++)
    {
        tempStudentList[i] = studentList[i];
    }

    // perform sorting based on the selected option
    int swapped;
    struct Student temp;

    do
    {
        swapped = 0;
        for (int i = 0; i < studentCount - 1; i++)
        {
            int compareResult = 0;

            switch (option)
            {
            case 1:
                compareResult = strcmp(tempStudentList[i].name, tempStudentList[i + 1].name);
                break;
            case 2:
                compareResult = strcmp(tempStudentList[i].major, tempStudentList[i + 1].major);
                break;
            case 3:
                compareResult = strcmp(tempStudentList[i].studentCode, tempStudentList[i + 1].studentCode);
                break;
            case 4:
                // Compare the full date of birth (dd/mm/yyyy)
                int day1, month1, year1;
                int day2, month2, year2;
                sscanf(tempStudentList[i].dateOfBirth, "%d/%d/%d", &day1, &month1, &year1);
                sscanf(tempStudentList[i + 1].dateOfBirth, "%d/%d/%d", &day2, &month2, &year2);

                if (year1 != year2)
                {
                    compareResult = year1 - year2;
                }
                else if (month1 != month2)
                {
                    compareResult = month1 - month2;
                }
                else
                {
                    compareResult = day1 - day2;
                }
                break;
            default:
                printf("Invalid sorting option.\n");
                return;
            }

            if (compareResult > 0)
            {
                temp = tempStudentList[i];
                tempStudentList[i] = tempStudentList[i + 1];
                tempStudentList[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);

    // print the sorted results
    printf("Students sorted in ascending order:\n");
    generateTableHead();
    for (int i = 0; i < studentCount; i++)
    {
        generateTableLine(i + 1, tempStudentList[i].name, tempStudentList[i].major, tempStudentList[i].studentCode, tempStudentList[i].dateOfBirth);
    }
    generateTableTail();
}

void printSortOptions()
{
    printf("Select a sorting option:\n");
    printf("1. Name\n");
    printf("2. Major\n");
    printf("3. Student code\n");
    printf("4. Date of birth\n");
}