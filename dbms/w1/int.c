#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void quickSortIntegers(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void swap(int *arr, int i, int j);

void measureAndWriteTime(FILE *summaryFile, const char *filename, double sortTime, double totalTime);

int main() {
    FILE *summaryFile = fopen("roll_number-output.txt", "w");
    if (summaryFile == NULL) {
        perror("Error opening summary file");
        return 1;
    }

    char filePrefix[] = "i";
    int fileSuffix[] = {10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120};

    for (int i = 0; i < sizeof(fileSuffix) / sizeof(fileSuffix[0]); ++i) {
        char inputFilename[20];
        sprintf(inputFilename, "%s%dK.txt", filePrefix, fileSuffix[i]);

        FILE *inputFile = fopen(inputFilename, "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            return 1;
        }

        int numIntegers = 0, temp;
        while (fscanf(inputFile, "%d", &temp) == 1) {
            numIntegers++;
        }
        rewind(inputFile);

        int *integerArray = (int *)malloc(numIntegers * sizeof(int));
        for (int j = 0; j < numIntegers; ++j) {
            fscanf(inputFile, "%d", &integerArray[j]);
        }
        fclose(inputFile);

        clock_t startSort = clock();
        quickSortIntegers(integerArray, 0, numIntegers - 1);
        clock_t endSort = clock();
        double sortTime = ((double)(endSort - startSort)) / CLOCKS_PER_SEC;

        char outputFilename[20];
        sprintf(outputFilename, "qi%dK.txt", fileSuffix[i]);

        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            return 1;
        }

        for (int j = 0; j < numIntegers; ++j) {
            fprintf(outputFile, "%d\n", integerArray[j]);
        }
        fclose(outputFile);
        free(integerArray);

        clock_t endProcess = clock();
        double totalTime = ((double)(endProcess - startSort)) / CLOCKS_PER_SEC;

        measureAndWriteTime(summaryFile, inputFilename, sortTime, totalTime);
    }

    fclose(summaryFile);

    return 0;
}

void measureAndWriteTime(FILE *summaryFile, const char *filename, double sortTime, double totalTime) {
    if (summaryFile != NULL) {
        fprintf(summaryFile, "File: %s, Sort Time: %f seconds, Total Time (Sorting + Writing): %f seconds\n", filename, sortTime, totalTime);
    }
}
void quickSortIntegers(int *arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSortIntegers(arr, low, pivot - 1);
        quickSortIntegers(arr, pivot + 1, high);
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
