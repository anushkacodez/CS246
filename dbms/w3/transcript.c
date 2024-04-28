#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Course {
    int sem;
    int L, T, P, C;
    char title[100];
};

typedef struct Course Course;

struct MapStringString {
    char key[100];
    char value[100];
};

typedef struct MapStringString MapStringString;

struct MapStringCourse {
    char key[100];
    Course value;
};

typedef struct MapStringCourse MapStringCourse;

struct MapStringMapStringString {
    char key[100];
    MapStringString value;
};

typedef struct MapStringMapStringString MapStringMapStringString;

struct MapStringInt {
    char key[100];
    int value;
};

typedef struct MapStringInt MapStringInt;

void readStudents(char *filename, MapStringString students) {
    FILE *fin = fopen(filename, "r");

    while (fgetc(fin) != EOF) {
        char roll_no[100], name[100];
        fscanf(fin, "%[^,],%[^\n]\n", name, roll_no);
        if (strcmp(name, "") != 0) {
            strcpy(students[roll_no], name);
        }
    }
    fclose(fin);
}

void readCourses(char *filename, MapStringCourse courses) {
    FILE *fin = fopen(filename, "r");
    while (fgetc(fin) != EOF) {
        Course temp;
        char sem[10], id[100], L[10], T[10], P[10], C[10];
        fscanf(fin, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", sem, id, temp.title, L, T, P, C);
        try {
            temp.sem = atoi(sem);
            temp.L = atoi(L);
            temp.T = atoi(T);
            temp.P = atoi(P);
            temp.C = atoi(C);
            if (strcmp(id, "") != 0)
                strcpy(courses[id], temp);
        } catch (const char *msg) {
            fprintf(stderr, "%s\n", msg);
        }
    }
    fclose(fin);
}

void readGrades(char *filename, MapStringMapStringString grades) {
    FILE *fin = fopen(filename, "r");
    while (fgetc(fin) != EOF) {
        char roll[100], id[100], g[100];
        fscanf(fin, "%[^,],%[^,],%[^\n]\n", roll, id, g);
        try {
            if (strcmp(roll, "") != 0) {
                strcpy(grades[roll][id], g);
            }
        } catch (const char *msg) {
            fprintf(stderr, "%s\n", msg);
        }
    }
    fclose(fin);
}

int main() {
    FILE *fout;
    MapStringString students;
    MapStringCourse courses;
    MapStringMapStringString grades;
    MapStringInt gtoi;

    readStudents("students.csv", students);
    readCourses("courses.csv", courses);
    readGrades("grades.csv", grades);

    char *semester[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII"};
    strcpy(gtoi["AS"], 10);
    strcpy(gtoi["AA"], 10);
    strcpy(gtoi["AB"], 9);
    strcpy(gtoi["BB"], 8);
    strcpy(gtoi["BC"], 7);
    strcpy(gtoi["CC"], 6);
    strcpy(gtoi["CD"], 5);
    strcpy(gtoi["DD"], 4);

    for (MapStringString::iterator student = students.begin(); student != students.end(); ++student) {
        fout = fopen(strcat(student->key, ".txt"), "w");
        fprintf(fout, "Name:%s\n", student->value);
        fprintf(fout, "Roll Number:%s\n", student->key);
        double SPI[8] = {0}, CPI[8] = {0}, credits[8] = {0};

        for (int i = 0; i < 8; i++) {
            fprintf(fout, "Semester %s\n", semester[i]);
            fprintf(fout, "%-20s|%-50s|%s|\tGrade\n", "Course Number", "Course Name", "C");
            for (MapStringStringString::iterator grade = grades[student->key].begin(); grade != grades[student->key].end(); ++grade) {
                char id[100];
                if (grade->key[5] == 'M') {
                    strcpy(id, grade->key);
                } else {
                    strncpy(id, grade->key, 5);
                    id[5] = '\0';
                }

                if (courses[id].sem == i + 1) {
                    fprintf(fout, "%-20s%-50s\t%-20d\t%s\n", id, courses[id].title, courses[id].C, grade->value);
                    credits[i] += courses[id].C;
                    SPI[i] += ((atof(gtoi[grade->value]) / 10) * courses[id].C);
                }
            }
            fprintf(fout, "\n");
        }
        fprintf(fout, "\t");
        for (int i = 0; i < 8; i++)
            fprintf(fout, "%-4s\t", semester[i]);
        fprintf(fout, "\nSPI\t");
        for (int i = 0; i < 8; i++) {
            SPI[i] = (SPI[i] / credits[i]) * 10;
            fprintf(fout, "%-4.3f\t", SPI[i]);
        }
        fprintf(fout, "\nCPI\t%-4.3f\t", SPI[0]);
        CPI[0] = SPI[0];
        double temp = credits[0];
        for (int i = 1; i < 8; i++) {
            CPI[i] = (CPI[i - 1] * temp + SPI[i] * credits[i]) / (temp + credits[i]);
            temp += credits[i];
            fprintf(fout, "%-4.3f\t", CPI[i]);
        }
        fprintf(fout, "\n");
        fclose(fout);
    }

    return 0;
}