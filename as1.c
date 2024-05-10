#include <stdio.h>
#include <string.h>
#define MAXIMUMSIZE 400

typedef struct
{
    char name[200];
    int roll;
    char telephone[100];
    char address[500];
} Student;
typedef struct
{
    Student stu[MAXIMUMSIZE];
    int len;
} SReg;
int add(SReg *sr, Student s)
{
    int n = sr->len;
    for (int i = 0; i < n; i++)
    {
        if (sr->stu[i].roll == s.roll)
        {
            return 0;
        }
    }
    sr->stu[n] = s;
    sr->len++;
    return 1;
}
Student get(SReg sr, int r)
{
    int n = sr.len;
    for (int i = 0; i < n; i++)
    {
        if (sr.stu[i].roll == r)
        {
            return sr.stu[i];
        }
    }
    Student v;
    v.roll = 0;
    return v;
}
int delete(SReg *sr, int r)
{
    int n = sr->len;
    int k = -1;
    for (int i = 0; i < n; i++)
    {
        if (sr->stu[i].roll == r)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
        return 0;
    else
    {
        printf("Deleted Successfully\n");
        for (int i = k; i < n - 1; i++)
        {
            sr->stu[i] = sr->stu[i + 1];
        }
        sr->len = n - 1;
        return 1;
    }
}
int modify(SReg *sr, Student s)
{
    int n = sr->len;
    for (int i = 0; i < n; i++)
    {
        if (sr->stu[i].roll == s.roll)
        {
            sr->stu[i] = s;
            return 1;
        }
    }
    return 0;
}
int getCount(SReg sr)
{
    return sr.len;
}
void sortStudents(SReg *sr)
{
    int n = sr->len;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(sr->stu[j].name, sr->stu[j + 1].name) > 0)
            {
                Student tempo = sr->stu[j];
                sr->stu[j] = sr->stu[j + 1];
                sr->stu[j + 1] = tempo;
            }
        }
    }
}
void export(SReg sr, char *fname)
{
    FILE *file = fopen(fname, "wb");
    if (file != NULL)
    {
        fwrite(&sr, sizeof(SReg), 1, file);
        fclose(file);
        printf("Register Exported Successfully!");
    }
    else
    {
        printf("Export Failed!");
    }
}
void load(SReg *sr, char *fname)
{
    FILE *file = fopen(fname, "rb");
    if (file != NULL)
    {
        fread(sr, sizeof(SReg), 1, file);
        fclose(file);
        printf("Register Loaded Successfully!");
    }
    else
    {
        printf("Loading Failed!");
    }
}
int main()
{
    SReg sr;
    sr.len = 0;
    int totalstudents;
    printf("Enter how many students you want to be added here: ");
    scanf("%d", &totalstudents);
    char name[20];
    int roll;
    char telephone[11];
    char address[20];
    for (int i = 0; i < totalstudents; i++)
    {
        printf("Enter detail of Student %d: \n", i + 1);
        printf("Name: ");
        scanf(" %s", name);
        printf("Roll: ");
        scanf("%d", &roll);
        printf("%d", roll);
        printf("\nTelephone number: ");
        scanf(" %s", telephone);
        printf("Address: ");
        scanf(" %s", address);
        Student s1;
        strcpy(s1.name, name);
        s1.roll = roll;
        strcpy(s1.telephone, telephone);
        strcpy(s1.address, address);
        if ((add(&sr, s1) == 1))
        {
            printf("Added Successfully\n");
        }
        else
        {
            printf("Student already exists\n");
        }
    }
    for (int i = 0; i < sr.len; i++)
    {
        printf("\n%s \n%d \n%s\n%s\n", sr.stu[i].name, sr.stu[i].roll, sr.stu[i].telephone, sr.stu[i].address);
    }
    int rollno;
    printf("\nEnter Roll no of the student whose details you want to access: ");
    scanf("%d", &rollno);
    Student sget = get(sr, rollno);
    printf("\n%s\n", sget.name);
    printf("\n%s \n%d \n%s \n%s\n", sget.name, sget.roll, sget.telephone, sget.address);
    char newname[20];
    int newroll;
    char newtelephone[11];
    char newaddress[20];
    printf("\n\nEnter the new  details of him/her: ");
    printf("\nEnter his/her name: ");
    scanf(" %s", newname);
    printf("Enter his/her RollNo: ");
    scanf("%d", &newroll);
    printf("%d", newroll);
    printf("\nEnter his/her Telephone number: ");
    scanf(" %s", newtelephone);
    printf("\nEnter his/her Address: ");
    scanf(" %s", newaddress);
    Student modify_s;
    strcpy(modify_s.name, newname);
    modify_s.roll = newroll;
    strcpy(modify_s.telephone, newtelephone);
    strcpy(modify_s.address, newaddress);
    if ((modify(&sr, modify_s) == 1))
    {
        printf("Modification successfull\n");
    }
    else
    {
        printf("Data doesn't match with the students already registered\n");
    }
    int dltroll;
    printf("\n\nEnter Roll no of student which you want to delete: ");
    scanf("%d", &dltroll);
    if ((delete (&sr, dltroll) == 1))
    {
        printf("Deleted successfully\n");
    }
    else
    {
        printf("Data doesn't match with students who are already registered\n");
    }
    printf("\nPresent no of Students = %d\n", getCount(sr));
    printf("Students Sorted according to their name: \n", getCount(sr));
    sortStudents(&sr);
    for (int i = 0; i < sr.len; i++)
    {
        printf("\n%s \n%d \n%s \n%s \n", sr.stu[i].name, sr.stu[i].roll, sr.stu[i].telephone, sr.stu[i].address);
    }
    export(sr, "Register.txt");
    load(&sr, "Register.txt");
    for (int i = 0; i < sr.len; i++)
    {
        printf("\n%s \n%d \n%s \n%s\n", sr.stu[i].name, sr.stu[i].roll, sr.stu[i].telephone, sr.stu[i].address);
    }
    return 0;
}