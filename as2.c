#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char *name;
    int roll;
    char telephone[11];
    char *address;
} Student;

typedef struct SReg {
    int maxStuds;
    int count;
    Student **arrStudPtr;
} SReg;

Student *createStudentRecord() {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation error.\n");
        return NULL;
    }

    newStudent->name = (char *)malloc(50 * sizeof(char)); // Allocate memory for name
    if (newStudent->name == NULL) {
        printf("Memory allocation error.\n");
        free(newStudent);
        return NULL;
    }

    newStudent->address = (char *)malloc(100 * sizeof(char)); // Allocate memory for address
    if (newStudent->address == NULL) {
        printf("Memory allocation error.\n");
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    printf("Enter student name: ");
    scanf("%s", newStudent->name);
    printf("Enter roll number: ");
    scanf("%d", &newStudent->roll);
    printf("Enter telephone number: ");
    scanf("%s", newStudent->telephone);
    printf("Enter address: ");
    scanf(" %[^\n]s", newStudent->address);

    return newStudent;
}

void freeStudentRecord(Student *sp) {
    free(sp->name);
    free(sp->address);
    free(sp);
}

int main() {
    SReg reg;
    printf("Enter maximum number of students: ");
    scanf("%d", &reg.maxStuds);

    reg.count = 0;
    reg.arrStudPtr = (Student **)malloc(reg.maxStuds * sizeof(Student *));
    if (reg.arrStudPtr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    int choice;
    do {
        printf("\n1. Add Student\n2. Display Students\n3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (reg.count < reg.maxStuds) {
                    reg.arrStudPtr[reg.count] = createStudentRecord();
                    if (reg.arrStudPtr[reg.count] != NULL) {
                        reg.count++;
                        printf("Student record added.\n");
                    } else {
                        printf("Failed to add student record.\n");
                    }
                } else {
                    printf("Student register is full.\n");
                }
                break;
            
            case 2:
                printf("\nStudent Records:\n");
                for (int i = 0; i < reg.count; i++) {
                    printf("Name: %s\nRoll: %d\nTelephone: %s\nAddress: %s\n\n",
                            reg.arrStudPtr[i]->name, reg.arrStudPtr[i]->roll,
                            reg.arrStudPtr[i]->telephone, reg.arrStudPtr[i]->address);
                }
                break;
            
            case 3:
                printf("Exiting program.\n");
                break;
            
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    // Free memory allocated for student records
    for (int i = 0; i < reg.count; i++) {
        freeStudentRecord(reg.arrStudPtr[i]);
    }
    free(reg.arrStudPtr);

    return 0;
}
