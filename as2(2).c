#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char *name;
    int roll;
    char telephone[11];
    char *address;
} Student;
typedef struct SReg
{
    int count;
    Student **arrStudPtr;
} SReg;
Student *createStudentRecord()
{
    char tstr[100];
    Student *stu = (Student *)malloc(sizeof(Student));
    if (stu == NULL)
    {
        printf("Memory allocation Failure! \n");
        return NULL;
    }
    getchar();
    printf("Enter the name of the student: ");
    fgets(tstr, 100, stdin);
    stu->name = (char *)malloc(sizeof(tstr) - 1);
    strcpy(stu->name, tstr);
    printf("Enter his/her roll number: ");
    scanf("%d", &stu->roll);
    printf("Enter his/her telephone number: ");
    scanf("%s", stu->telephone);
    getchar();
    printf("Enter his/her address: ");
    fgets(tstr, 100, stdin);
    stu->address = (char *)malloc(sizeof(tstr));
    strcpy(stu->address, tstr);
    if (stu->name == NULL || stu->address == NULL)
    {
        printf("Memory allocation Failure! \n");
        free(stu);
        return NULL;
    }
    return stu;
}
void freeStudentRecord(Student *sp)
{
    free(sp->name);
    free(sp->address);
    free(sp);
}
Student *createStudentRecordFromFile(FILE *fp)
{
    Student *newstu = (Student *)malloc(sizeof(Student));
    if (newstu == NULL)
    {
        printf("Memory allocation Failure!! \n");
        return NULL;
    }
    char tempostd[100];
    fscanf(fp, "%d", &newstu->roll);
    fgetc(fp);
    fscanf(fp, " %s", tempostd);
    newstu->name = (char *)malloc(sizeof(tempostd));
    strcpy(newstu->name, tempostd);
    fscanf(fp, "%s", newstu->telephone);
    fgetc(fp);
    fscanf(fp, " %s", tempostd);
    newstu->address = (char *)malloc(sizeof(tempostd));
    strcpy(newstu->address, tempostd);
    if (newstu->name == NULL || newstu->address == NULL)
    {
        printf("Memory allocation error due to name/address in the given students recorded.\n");
        free(newstu);
        return NULL;
    }
    return newstu;
}
int add(SReg *sr, Student *s)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == s->roll)
        {
            return 0;
        }
    }
    sr->count++;
    sr->arrStudPtr = (Student **)realloc(sr->arrStudPtr, sr->count * sizeof(Student *));
    if (sr->arrStudPtr == NULL)
    {
        printf("Memory reallocation Failure!\n");
        return 0;
    }
    sr->arrStudPtr[sr->count - 1] = s;
    return 1;
}
Student *get(SReg *sr, int r)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == r)
        {
            return sr->arrStudPtr[i];
        }
    }
    return NULL;
}
int modify(SReg *sr, Student *s)
{
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == s->roll)
        {
            free(sr->arrStudPtr[i]->name);
            free(sr->arrStudPtr[i]->address);

            sr->arrStudPtr[i]->name = strdup(s->name);
            sr->arrStudPtr[i]->roll = s->roll;
            strcpy(sr->arrStudPtr[i]->telephone, s->telephone);
            sr->arrStudPtr[i]->address = strdup(s->address);
            return 1;
        }
    }
    return 0;
}
int delete(SReg *sr, int r)
{
    int flag = -1;
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->arrStudPtr[i]->roll == r)
        {
            flag = i;
            break;
        }
    }
    if (flag == -1)
    {
        return 0;
    }
    freeStudentRecord(sr->arrStudPtr[flag]);
    sr->arrStudPtr[flag] = sr->arrStudPtr[sr->count - 1];
    sr->count--;
    sr->arrStudPtr = (Student **)realloc(sr->arrStudPtr, sr->count * sizeof(Student *));
    return 1;
}
void sortStudents(SReg *sr)
{
    int num = sr->count;
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (strcmp(sr->arrStudPtr[j]->name, sr->arrStudPtr[j + 1]->name) > 0)
            {
                Student *temp = sr->arrStudPtr[j];
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
                sr->arrStudPtr[j + 1] = temp;
            }
        }
    }
}
int getCount(SReg *sr)
{
    return sr->count;
}
void export(SReg *sr, const char *fname)
{
    FILE *t = fopen(fname, "w");
    if (t == NULL)
    {
        printf("Error opening file for writing: %s\n", fname);
        return;
    }
    fprintf(t, "%d\n", sr->count);
    for (int i = 0; i < sr->count; i++)
    {
        fprintf(t, "%d\n", sr->arrStudPtr[i]->roll);
        fprintf(t, "%s\n", sr->arrStudPtr[i]->name);
        fprintf(t, "%s\n", sr->arrStudPtr[i]->telephone);
        fprintf(t, "%s\n", sr->arrStudPtr[i]->address);
    }
    fclose(t);
    printf("Student register has been exported to %s.\n", fname);
}
void load(SReg *sr, const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("Error in opening file: %s\n", fname);
        return;
    }
    int ct;
    fscanf(fp, "%d", &ct);
    for (int i = 0; i < ct; i++)
    {
        Student *newStudent = createStudentRecordFromFile(fp);
        if (newStudent != NULL)
        {
            sr->count++;
            sr->arrStudPtr = (Student **)realloc(sr->arrStudPtr, sr->count * sizeof(Student *));
            sr->arrStudPtr[sr->count - 1] = newStudent;
        }
    }
    fclose(fp);
    printf("Students have been loaded from %s.\n", fname);
}
int main()
{
    SReg sr;
    sr.count = 0;
    sr.arrStudPtr = NULL;
    int opt;
    do
    {
        printf("\nStudent Register\n");
        printf("1. Add Student details\n");
        printf("2. Get Student information by entering Roll Number\n");
        printf("3. Delete Student information by entering Roll Number\n");
        printf("4. Change Student Details\n");
        printf("5. Sorting Students by Names\n");
        printf("6. Display the Count of Student(s)\n");
        printf("7. Export Students to File\n");
        printf("8. Load Students from File\n");
        printf("9. Exit Code.\n");
        printf("Enter your desired choice: ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
        {
            Student *students = createStudentRecord();
            if (students != NULL)
            {
                if (add(&sr, students))
                {
                    printf("Student added successfully.\n");
                }
                else
                {
                    printf("Roll number exists beforehand.\n");
                    freeStudentRecord(students);
                }
            }
            break;
        }
        case 2:
        {
            int roll_no;
            printf("Enter Roll number of the student you want: ");
            scanf("%d", &roll_no);
            Student *foundS1 = get(&sr, roll_no);
            if (foundS1 != NULL)
            {
                printf("\nStudent Details:\n");
                printf("Name: %s", foundS1->name);
                printf("Roll Number: %d\n", foundS1->roll);
                printf("Telephone Number: %s\n", foundS1->telephone);
                printf("Address: %s\n", foundS1->address);
            }
            else
            {
                printf("Student Not found.\n");
            }
            break;
        }
        case 3:
        {
            int rolln;
            printf("Enter roll number of student to be deleted: ");
            scanf("%d", &rolln);
            if (delete (&sr, rolln))
            {
                printf("Student deleted successfully.\n");
            }
            else
            {
                printf("Student not found.\n");
            }
            break;
        }
        case 4:
        {
            Student *newS = createStudentRecord();
            if (newS != NULL)
            {
                if (modify(&sr, newS))
                {
                    printf("Student details modified successfully.\n");
                }
                else
                {
                    printf("Student not found.\n");
                }
            }
            break;
        }
        case 5:
        {
            sortStudents(&sr);
            printf("Students sorted according to their names.\n");
            break;
        }
        case 6:
        {
            int cd = getCount(&sr);
            printf("No of students in the Register given: %d\n", cd);
            break;
        }
        case 7:
        {
            char fname[100];
            printf("Enter the filename where you want to export the student register: ");
            scanf("%s", fname);
            export(&sr, fname);
            sr.count = 0;
            printf("Student has been register exported to %s.\n", fname);
            break;
        }
        case 8:
        {
            char file[100];
            printf("Enter the filename to load students from: ");
            scanf("%s", file);
            load(&sr, file);
            printf("Students loaded from %s.\n", file);
            break;
        }
        case 9:
        {
            for (int i = 0; i < sr.count; i++)
            {
                freeStudentRecord(sr.arrStudPtr[i]);
            }
            free(sr.arrStudPtr);
            printf("Code Exited\n");
            break;
        }
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (opt != 9);
    return 0;
}