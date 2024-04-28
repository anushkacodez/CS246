#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course {
    int sem;
    int L, T, P, C;
    char title[100];
};

struct student {
    char roll_no[20];
    char name[100];
};

struct grade {
    char roll[20];
    char id[20];
    char g[3];
};

typedef struct {
    char grades[20][20];
    struct course courses[20];
    struct student students[20];
    int gtoi[10];
} UniversityData;

void readStudents(FILE *fin, UniversityData *data) {
    int i = 0;
    while (fscanf(fin, "%[^,],%[^\n]\n", data->students[i].name, data->students[i].roll_no) != EOF) {
        i++;
    }
}

void readCourses(FILE *fin, UniversityData *data) {
    int i = 0;
    while (fscanf(fin, "%d,%[^,],%[^,],%d,%d,%d,%d,%[^\n]\n",
                  &data->courses[i].sem, data->courses[i].title, data->courses[i].id,
                  &data->courses[i].L, &data->courses[i].T, &data->courses[i].P, &data->courses[i].C) != EOF) {
        i++;
    }
}

void readGrades(FILE *fin, UniversityData *data) {
    int i = 0;
    while (fscanf(fin, "%[^,],%[^,],%[^\n]\n", data->grades[i].roll, data->grades[i].id, data->grades[i].g) != EOF) {
        i++;
    }
}

int main() {
    FILE *fin, *fout;
    fin = fopen("students.csv", "r");
    // Check if the file opened successfully

    UniversityData data;

    readStudents(fin, &data);
    fclose(fin);

    fin = fopen("courses.csv", "r");
    // Check if the file opened successfully

    readCourses(fin, &data);
    fclose(fin);

    fin = fopen("grades.csv", "r");
    // Check if the file opened successfully

    readGrades(fin, &data);
    fclose(fin);

    // Rest of your code goes here with necessary modifications

    return 0;
}