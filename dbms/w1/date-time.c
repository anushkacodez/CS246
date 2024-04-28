#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct DateTime {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
};

void parseDateTime(const char *dateTimeStr, struct DateTime *dateTime) {
    char monthStr[4];
    sscanf(dateTimeStr, "%d-%3s-%d %d:%d:%d", &dateTime->day, monthStr, &dateTime->year, &dateTime->hour, &dateTime->minute, &dateTime->second);

    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i) {
        if (strcmp(monthStr, months[i]) == 0) {
            dateTime->month = i + 1;
            break;
        }
    }
}

int compareDateTimes(const void *a, const void *b) {
    const struct DateTime *dtA = (const struct DateTime *)a;
    const struct DateTime *dtB = (const struct DateTime *)b;

    if (dtA->year != dtB->year) return dtA->year - dtB->year;
    if (dtA->month != dtB->month) return dtA->month - dtB->month;
    if (dtA->day != dtB->day) return dtA->day - dtB->day;
    if (dtA->hour != dtB->hour) return dtA->hour - dtB->hour;
    if (dtA->minute != dtB->minute) return dtA->minute - dtB->minute;
    return dtA->second - dtB->second;
}

void quickSortDateTimes(char **dateTimes, int low, int high) {
    if (low < high) {
        int pivot = partition(dateTimes, low, high);
        quickSortDateTimes(dateTimes, low, pivot - 1);
        quickSortDateTimes(dateTimes, pivot + 1, high);
    }
}

int partition(char **dateTimes, int low, int high) {
    struct DateTime pivot;
    parseDateTime(dateTimes[high], &pivot);

    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        struct DateTime currentDateTime;
        parseDateTime(dateTimes[j], &currentDateTime);

        if (compareDateTimes(&currentDateTime, &pivot) <= 0) {
            i++;
            swap(dateTimes, i, j);
        }
    }

    swap(dateTimes, i + 1, high);
    return i + 1;
}

void swap(char **dateTimes, int i, int j) {
    char *temp = dateTimes[i];
    dateTimes[i] = dateTimes[j];
    dateTimes[j] = temp;
}

int main() {
    char filePrefix[] = "dt";
    int fileSuffix[] = {10, 20};
    // 40, 80, 160, 320, 640, 1280, 2560, 5120};
    FILE *timeFile = fopen("roll_number.txt", "w");

    if (timeFile == NULL) {
        perror("Error opening roll_number.txt");
        return 1;
    }

    for (int i = 0; i < sizeof(fileSuffix) / sizeof(fileSuffix[0]); ++i) {
        char inputFilename[20];
        sprintf(inputFilename, "%s%dK.txt", filePrefix, fileSuffix[i]);

        FILE *inputFile = fopen(inputFilename, "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            return 1;
        }

        char line[30];
        int size = 0;
        while (fgets(line, sizeof(line), inputFile)) {
            size++;
        }
        rewind(inputFile);

        char **dateTimeStrings = (char **)malloc(size * sizeof(char *));
        for (int j = 0; j < size; ++j) {
            dateTimeStrings[j] = (char *)malloc(30);
        }

        int k = 0;
        while (fgets(line, sizeof(line), inputFile) && k < size) {
            strcpy(dateTimeStrings[k], line);
            dateTimeStrings[k][strlen(dateTimeStrings[k]) - 1] = '\0';
            k++;
        }
        fclose(inputFile);

        clock_t start, end;
        double sortingTime, totalTime;

        start = clock();
        quickSortDateTimes(dateTimeStrings, 0, size - 1);
        end = clock();
        sortingTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        char outputFilename[20];
        sprintf(outputFilename, "qdt%dK.txt", fileSuffix[i]);

        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            return 1;
        }

        start = clock();
        for (int j = 0; j < size; ++j) {
            fprintf(outputFile, "%s\n", dateTimeStrings[j]);
        }
        fclose(outputFile);
        end = clock();
        totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(timeFile, "File: %s, Sorting Time: %f seconds, Total Time: %f seconds\n", inputFilename, sortingTime, totalTime);

        for (int j = 0; j < size; ++j) {
            free(dateTimeStrings[j]);
        }
        free(dateTimeStrings);

        printf("Sorted Date-Time written to %s\n", outputFilename);
    }

    fclose(timeFile);
    return 0;
}
