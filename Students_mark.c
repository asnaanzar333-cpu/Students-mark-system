#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};

void addStudent() {
    FILE *fp;
    struct student s;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter marks of 3 subjects: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll Number: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f %.2f %.2f", s.m1, s.m2, s.m3);
        printf("\nTotal: %.2f\n", s.total);
    }

    fclose(fp);
}

void rankList() {
    FILE *fp;
    struct student s[100], temp;
    int count = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s[count], sizeof(s[count]), 1, fp)) {
        count++;
    }
    fclose(fp);

    // Sorting (Descending order of total)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (s[i].total < s[j].total) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (int i = 0; i < count; i++) {
        printf("Rank %d: %s (Total: %.2f)\n", i + 1, s[i].name, s[i].total);
    }
}

int main() {
    int choice;

    do {
        printf("\n====== Student Management System ======\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Generate Rank List\n");
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
                rankList();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
