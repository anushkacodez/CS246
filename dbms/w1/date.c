#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent a date
struct Date {
    int day;
    int month;
    int year;
};

void parseDate(const char *dateStr, struct Date *date) {
    char monthStr[4];
    sscanf(dateStr, "%d-%3s-%d", &date->day, monthStr, &date->year);

    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i) {
        if (strcmp(monthStr, months[i]) == 0) {
            date->month = i + 1;
            break;
        }
    }
}

int compareDates(const void *a, const void *b) {
    const struct Date *dateA = (const struct Date *)a;
    const struct Date *dateB = (const struct Date *)b;

    if (dateA->year != dateB->year) return dateA->year - dateB->year;
    if (dateA->month != dateB->month) return dateA->month - dateB->month;
    return dateA->day - dateB->day;
}

void bubbleSortDates(char **dates, int size) {
    struct Date *dateArray = (struct Date *)malloc(size * sizeof(struct Date));
    for (int i = 0; i < size; ++i) {
        parseDate(dates[i], &dateArray[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (compareDates(&dateArray[j], &dateArray[j + 1]) > 0) {
                char *temp = dates[j];
                dates[j] = dates[j + 1];
                dates[j + 1] = temp;

                struct Date tempDate = dateArray[j];
                dateArray[j] = dateArray[j + 1];
                dateArray[j + 1] = tempDate;
            }
        }
    }

    free(dateArray);
}

void measureAndWriteTime(FILE *summaryFile, const char *filename, double sortTime, double totalTime) {
    if (summaryFile != NULL) {
        fprintf(summaryFile, "File: %s, Sort Time: %f seconds, Total Time (Sorting + Writing): %f seconds\n", filename, sortTime, totalTime);
    }
}

int main() {
    FILE *summaryFile = fopen("roll_number.txt", "w");
    if (summaryFile == NULL) {
        perror("Error opening summary file");
        return 1;
    }

    char filePrefix[] = "d";
    int fileSuffix[] = {10, 20};
    //40, 80, 160, 320, 640, 1280, 2560, 5120};

    for (int i = 0; i < sizeof(fileSuffix) / sizeof(fileSuffix[0]); ++i) {
        char inputFilename[20];
        sprintf(inputFilename, "%s%dK.txt", filePrefix, fileSuffix[i]);

        FILE *inputFile = fopen(inputFilename, "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            return 1;
        }

        // Determine the number of lines in the file
        char line[30];
        int size = 0;
        while (fgets(line, sizeof(line), inputFile)) {
            size++;
        }
        rewind(inputFile); // Reset file pointer to the beginning of the file

        // Allocate memory for date strings
        char **dateStrings = (char **)malloc(size * sizeof(char *));
        for (int j = 0; j < size; ++j) {
            dateStrings[j] = (char *)malloc(30);  // Adjust the buffer size as needed
        }

        // Read date strings from the file
        int k = 0;
        while (fgets(line, sizeof(line), inputFile) && k < size) {
            strcpy(dateStrings[k], line);
            dateStrings[k][strlen(dateStrings[k]) - 1] = '\0';  // Remove newline character
            k++;
        }
        fclose(inputFile);

        clock_t startSort = clock();
        bubbleSortDates(dateStrings, size);
        clock_t endSort = clock();
        double sortTime = ((double)(endSort - startSort)) / CLOCKS_PER_SEC;

        char outputFilename[20];
        sprintf(outputFilename, "qd%dK.txt", fileSuffix[i]);

        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            return 1;
        }

        for (int j = 0; j < size; ++j) {
            fprintf(outputFile, "%s\n", dateStrings[j]);
        }
        fclose(outputFile);

        for (int j = 0; j < size; ++j) {
            free(dateStrings[j]);
        }
        free(dateStrings);

        clock_t endProcess = clock();
        double totalTime = ((double)(endProcess - startSort)) / CLOCKS_PER_SEC;

        measureAndWriteTime(summaryFile, inputFilename, sortTime, totalTime);

        printf("Sorted Dates written to %s\n", outputFilename);
    }

    fclose(summaryFile);

    return 0;
}
