#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 16000 // Define the maximum number of products

// Struct to hold product information
struct Product {
    char productNumber[20];
    char stepDates[10][20];
    char region[20];
};

// Function to read the CSV file and store data in the Product struct
int readCSVFile(struct Product products[], int *numProducts) {
    FILE *file = fopen("week02.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[1024];
    *numProducts = 0;

    while (fgets(line, 1024, file) && *numProducts < MAX_PRODUCTS) {
        char *token = strtok(line, ",");
        int col = 0;
        while (token != NULL) {
            if (col == 0) {
                strcpy(products[*numProducts].productNumber, token);
            } 
            else if (col >= 1 && col <= 10) {
                strcpy(products[*numProducts].stepDates[col - 1], token);
            } 
            else if (col == 11) {
                strcpy(products[*numProducts].region, token);
            }
            token = strtok(NULL, ",");
            col++;
        }
        (*numProducts)++;
    }

    fclose(file);
    return 1;
}



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







void dateswap(char **dateStrings){
    for (int i = 0; i < 5; i++)
    {
        char temp[13];
        strcpy(temp, dateStrings[i]);
        strcpy(dateStrings[i], dateStrings[10-i-1]);
        strcpy(dateStrings[10-i-1], temp);
    }
    
}


void sortInstallation(int i, struct Product products[]){
    char **dateStrings = (char **)malloc(10 * sizeof(char *));
    for (int j = 0; j < 10; ++j) {
        dateStrings[j] = (char *)malloc(30);  // Adjust the buffer size as needed
    }
    for (int j = 0; j < 10; j++)
    {
        strcpy(dateStrings[j], products[i].stepDates[j]);
    }

    bubbleSortDates(dateStrings, 10);
    
    if(products[i].region[0] == 'N'){
        for (int j = 0; j < 10; j++)
        {
            strcpy(products[i].stepDates[j], dateStrings[j]);
        }
    }
    else if(products[i].region[0] == 'S'){
        for (int j = 0; j < 10; j++)
        {
            strcpy(products[i].stepDates[j], dateStrings[10-j-1]);
        }
    }
    else if(products[i].region[0] == 'E'){
        dateswap(dateStrings);
        int j = 5;
        while(j<10 && strcmp(dateStrings[j], dateStrings[j-1]) == 0){
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            strcpy(products[i].stepDates[k], dateStrings[j-k-1]);
        }
        
        for(int k = j; k<10; k++){
            strcpy(products[i].stepDates[k], dateStrings[k]);
        }
    }
    else if(products[i].region[0] == 'W'){
        dateswap(dateStrings);
        int j = 5;
        while(j<10 && strcmp(dateStrings[j], dateStrings[j-1]) == 0){
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            strcpy(products[i].stepDates[k], dateStrings[k]);
        }




        for(int k = j; k<10; k++){
            strcpy(products[i].stepDates[k], dateStrings[10+j-k-1]);
        }
    }
}







int main() {
    struct Product products[MAX_PRODUCTS];
    int numProducts = 0;

    FILE *f1;
    f1 = fopen("output.csv", "w");


    if (readCSVFile(products, &numProducts)) {
        fprintf(f1, "%s", products[0].productNumber);
        for (int j = 0; j < 10; j++) {
            fprintf(f1, ",%s", products[0].stepDates[j]);
        }
        // Printing read data (for verification)
        for (int i = 1; i < numProducts; i++) {

            sortInstallation(i, products);

            fprintf(f1, "%s,", products[i].productNumber);
            for (int j = 0; j < 10; j++) {
                fprintf(f1, "%s,", products[i].stepDates[j]);
            }
            fprintf(f1, "%s", products[i].region);
        }

    }
    fclose(f1);

    return 0;
}