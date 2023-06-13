#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_REASON_LENGTH 100

typedef struct {
    int id;
    char name[50];
    int leavesTaken;
} Student;

Student studentList[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached. Cannot add more students.\n");
        return;
    }

    Student newStudent;
    printf("Enter student name: ");
    scanf("%s", newStudent.name);

    newStudent.id = studentCount + 1;
    newStudent.leavesTaken = 0;
    studentList[studentCount++] = newStudent;

    printf("Student added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }

    printf("Student List:\n");
    printf("ID\tName\tLeaves Taken\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%s\t%d\n", studentList[i].id, studentList[i].name, studentList[i].leavesTaken);
    }
}

void applyLeave() {
    int studentId, days;
    char reason[MAX_REASON_LENGTH];

    printf("Enter your student ID: ");
    scanf("%d", &studentId);

    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == studentId) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student with ID %d not found.\n", studentId);
        return;
    }

    printf("Enter number of days for leave: ");
    scanf("%d", &days);

    printf("Enter reason for leave: ");
    scanf(" %[^\n]s", reason);

    if (studentList[studentIndex].leavesTaken + days > 30) {
        printf("Leave application rejected. Maximum leaves exceeded for the student.\n");
        return;
    }

    studentList[studentIndex].leavesTaken += days;
    printf("Leave application submitted successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nLeave Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Apply Leave\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                applyLeave();
                break;
            case 4:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
