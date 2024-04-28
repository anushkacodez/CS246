#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Date {
    int day;
    int month;
    int year;
};



int cmp(const void *a, const void *b) {
    const struct Date *date1 = (const struct Date *)a;
    const struct Date *date2 = (const struct Date *)b;

    if(date1->year != date2->year) 
    {
        return date1->year - date2->year;
    }
    if(date1->month != date2->month) 
    {
        return date1->month - date2->month;
    }
    return date1->day - date2->day;
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



void swapTheDates(char **date_str){
    for (int i = 0; i < 5; i++)
    {
        char temp[13]; //character array for storing the date temporarily
        strcpy(temp, date_str[i]);
        strcpy(date_str[i], date_str[10-i-1]); //we will swap the latest date with the first one and the second latest with the second one and so on acc to the question
        strcpy(date_str[10-i-1], temp);
    }
    
}

