#include <stdio.h>

// Define the struct
struct date {
    int year;
    int month;
    int day;
};

// Custom comparator for date struct
int compareDates(struct date d1, struct date d2) {
    // Compare years first
    if (d1.year != d2.year) {
        return d1.year - d2.year;
    }

    // If years are equal, compare months
    if (d1.month != d2.month) {
        return d1.month - d2.month;
    }

    // If years and months are equal, compare days
    return d1.day - d2.day;
}

// Function to perform Bubble Sort on an array with a custom comparator
void bubbleSort(struct date arr[], int n, int (*compare)(struct date, struct date)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Use the custom comparator to determine the order
            if (compare(arr[j], arr[j + 1]) > 0) {
                // Swap if the element found is greater than the next element
                struct date temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print an array of dates
void printDateArray(struct date arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d-%d-%d ", arr[i].year, arr[i].month, arr[i].day);
    }
    printf("\n");
}
struct date createDate(int year, int month, int day) {
    struct date newDate;
    newDate.year = year;
    newDate.month = month;
    newDate.day = day;
    return newDate;
}
int main() {
    struct date dates[] = {
        {2024, 1, 8},
        {2023, 12, 15},
        {2024, 2, 20},
        {2023, 12, 10},
    };

    int n = sizeof(dates) / sizeof(dates[0]);

    printf("Original array of dates: ");
    printDateArray(dates, n);

    // Perform Bubble Sort with the custom comparator
    bubbleSort(dates, n, compareDates);

    printf("Sorted array of dates: ");
    printDateArray(dates, n);

    return 0;
}