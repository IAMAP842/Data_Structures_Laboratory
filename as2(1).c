#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef struct student
{
    char *name;
    int roll;
    int ph;
    char *addr;
} Student;

typedef struct reg
{
    int size;
    int count;
    Student **A;
} Sreg;

void Readstdinfo(Sreg *sr)
{
    Student *ptr = (Student *)malloc(sizeof(Student));
    char ar[100];
    printf("Enter the Name of the student:");
    fgets(ar, 100, stdin);
    ptr->name = (char *)malloc(strlen(ar) + 1);
    strcpy(ptr->name, ar);

    printf("Enter the Roll of the student:");
    scanf("%d", &ptr->roll);

    printf("Enter the contact of the student:");
    scanf("%d", &ptr->ph);

    getchar();
    printf("Enter the address of the student:");
    fgets(ar, 100, stdin);
    ptr->addr = (char *)malloc(strlen(ar) + 1);
    strcpy(ptr->addr, ar);

    sr->A[sr->count] = ptr;
    sr->count++;
}

int Printstdinfo(Sreg *sr)
{
    int x;
    printf("Enter the Roll of the student which you want to print:");
    scanf("%d", &x);
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->A[i]->roll == x)
        {
            if (sr->A[i] == NULL)
            {
                printf("Error: NULL student pointer.");
                return 0;
            }
            printf("\nName:");
            fputs(sr->A[i]->name, stdout);
            printf("\nRoll:%d", sr->A[i]->roll);
            printf("\nContact:%d", sr->A[i]->ph);
            printf("\nAddress:");
            fputs(sr->A[i]->addr, stdout);
            return 1;
        }
    }
    printf("Student with Roll %d not found.\n", x);
    return 0;
}

void DisplayAllstd(Sreg *sr)
{
    for (int i = 0; i < sr->count; i++)
    {
        printf("Name:");
        fputs(sr->A[i]->name, stdout);
        printf("Roll:%d", sr->A[i]->roll);
        printf("\nContact:%d", sr->A[i]->ph);
        printf("\nAddress:");
        fputs(sr->A[i]->addr, stdout);
        printf("\n");
    }
}

void Delete(Sreg *sr)
{
    int x = 0;
    printf("Enter the roll of the student which you want to delete:");
    scanf("%d", &x);
    for (int i = 0; i < sr->count; i++)
    {
        if (sr->A[i]->roll == x)
        {
            for (; i < sr->count; i++)
            {
                sr->A[i] = sr->A[i + 1];
            }
            sr->count--;
            /* free(sr->A[i]->name);
             free(sr->A[i]->addr);
             free(sr->A[i]);*/
        }
    }
    DisplayAllstd(sr);
}

void Addstd(Sreg *sr)
{
    printf("Add a new student :");
    Student *ptr = (Student *)malloc(sizeof(Student));
    char ar[100];
    getchar();
    printf("\nEnter the Name of the student:");
    fgets(ar, 100, stdin);
    ptr->name = (char *)malloc(strlen(ar) + 1);
    strcpy(ptr->name, ar);

    printf("\nEnter the Roll of the student:");
    scanf("%d", &ptr->roll);

    printf("\nEnter the contact of the student:");
    scanf("%d", &ptr->ph);

    getchar();
    printf("\nEnter the address of the student:");
    fgets(ar, 100, stdin);
    ptr->addr = (char *)malloc(strlen(ar) + 1);
    strcpy(ptr->addr, ar);

    sr->A[sr->count] = ptr;
    sr->count++;
}

void Modify(Sreg *sr)
{
    int x;
    printf("Enter the Roll of the student which you want to modify:");
    scanf("%d", &x);
    getchar();
    for (int i = 0; i < sr->count; i++)
    {
        if (x == sr->A[i]->roll)
        {
            char ar[100];
            printf("Enter the Name of the student:");
            fgets(ar, 100, stdin);
            strcpy(sr->A[i]->name, ar);

            printf("Enter the Roll of the student:");
            scanf("%d", &sr->A[i]->roll);

            printf("Enter the contact of the student:");
            scanf("%d", &sr->A[i]->ph);

            getchar();
            printf("Enter the address of the student:");
            fgets(ar, 100, stdin);
            strcpy(sr->A[i]->addr, ar);
        }
    }
}

void Arrangestd(Sreg *sr)
{
    Student *ptr;
    for (int i = 0; i < sr->count - 1; i++)
    {
        for (int j = i + 1; j < sr->count; j++)
        {
            if (strcmp(sr->A[i]->name, sr->A[j]->name) > 0)
            {
                ptr = sr->A[i];
                sr->A[i] = sr->A[j];
                sr->A[j] = ptr;
            }
        }
    }
    DisplayAllstd(sr);
}

void Export(Sreg *sr)
{
    FILE *fp = fopen("fname.data", "wb");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < sr->count; i++)
    {
        fwrite(sr->A[i], sizeof(Student), 1, fp);
    }

    fclose(fp);
    printf("Data exported to file successfully.\n");
}

void Load(Sreg *sr)
{
    FILE *fp = fopen("fname.data", "rb");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    while (1)
    {
        Student *ptr = (Student *)malloc(sizeof(Student));
        if (fread(ptr, sizeof(Student), 1, fp) != 1)
        {
            free(ptr);
            break;
        }
        sr->A[sr->count] = ptr;
        sr->count++;
    }
    fclose(fp);
    printf("Data loaded from file successfully.\n");
}

int main()
{
    Sreg sr;
    sr.A = (Student **)malloc(MAX_SIZE * sizeof(Student *));
    sr.size = MAX_SIZE;
    sr.count = 0;
    int x = 0;
    printf("Enter the number of students (up to %d):", MAX_SIZE);
    scanf("%d", &x);
    getchar();

    if (x > MAX_SIZE)
    {
        printf("Number of students exceeds the maximum limit. Setting it to %d.\n", MAX_SIZE);
        return 0;
    }

    for (int i = 0; i < x; i++)
    {
        Readstdinfo(&sr);
    }
    printf("\nEnter the choice\n1.Display all\n2.Delete\n3.Get\n4.Modify\n5.sortStudents\n6.Add new student\n7.Export\n8.Load");
    printf("\nEnter how many operation you want to perform:");
    int z;
    scanf("%d", &z);
    for (int j = 1; j <= z; j++)
    {
        printf("\nenter the serial number of the operation you want to perform:");
        int y;
        scanf("%d", &y);
        switch (y)
        {
        case 1:
            DisplayAllstd(&sr);
            break;
        case 2:
            Delete(&sr);
            break;
        case 3:
            Printstdinfo(&sr);
            break;
        case 4:
            Modify(&sr);
            break;
        case 5:
            Arrangestd(&sr);
            break;
        case 6:
            Addstd(&sr);
            break;
        case 7:
            Export(&sr);
            break;
        case 8:
            Load(&sr);
            break;
        default:
            printf(" Invalid choice.");
        }
    }
    for (int i = 0; i < sr.count; i++)
    {
        free(sr.A[i]->name);
        free(sr.A[i]->addr);
        free(sr.A[i]);
    }

    free(sr.A);
    return 0;
}