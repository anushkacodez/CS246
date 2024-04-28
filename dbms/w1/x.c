#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 16000
#define MAX_STEPS 10
#define MAX_DATE_LENGTH 12
#define REGION_LENGTH 10
#define PRODUCT_NUMBER_LENGTH 10
#define FILENAME_LENGTH 50

struct Installation {
    char productNumber[PRODUCT_NUMBER_LENGTH];
    char dates_new[MAX_STEPS][MAX_DATE_LENGTH];
    char dates[MAX_STEPS][MAX_DATE_LENGTH];
    char region[REGION_LENGTH];
};

struct Installation products[MAX_PRODUCTS];
int totalProducts = 0;

struct Date {
    int day;
    int month;
    int year;
};

void parseDate(const char dateStr[MAX_DATE_LENGTH], struct Date *date) {
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

void bubbleSortDatesFront(char dates[][MAX_DATE_LENGTH], int size) {
    struct Date *dateArray = (struct Date *)malloc(size * sizeof(struct Date));
    for (int i = 0; i < size; ++i) {
        parseDate(dates[i], &dateArray[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (compareDates(&dateArray[j], &dateArray[j + 1]) > 0) {
                char temp1[MAX_DATE_LENGTH];
                char temp2[MAX_DATE_LENGTH];
                for(int i=0; i<sizeof(dates[j]); i++)
                {
                	temp1[i]=dates[j][i];
                }
                for(int i=0; i<sizeof(dates[j+1]); i++)
                {
                	temp2[i]=dates[j+1][i];
                }
                for(int i=0; i<sizeof(temp1); i++)
                {
                	dates[j+1][i]=temp1[i];
                }
                for(int i=0; i<sizeof(temp2); i++)
                {
                	dates[j][i]=temp2[i];
                }

                struct Date tempDate = dateArray[j];
                dateArray[j] = dateArray[j + 1];
                dateArray[j + 1] = tempDate;
            }
        }
    }

    free(dateArray);
}

void bubbleSortDatesBack(char dates[][MAX_DATE_LENGTH], int size) {
    struct Date *dateArray = (struct Date *)malloc(size * sizeof(struct Date));
    for (int i = 0; i < size; ++i) {
        parseDate(dates[i], &dateArray[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (compareDates(&dateArray[j], &dateArray[j + 1]) < 0) {
                char temp1[MAX_DATE_LENGTH];
                char temp2[MAX_DATE_LENGTH];
                for(int i=0; i<sizeof(dates[j]); i++)
                {
                	temp1[i]=dates[j][i];
                }
                for(int i=0; i<sizeof(dates[j+1]); i++)
                {
                	temp2[i]=dates[j+1][i];
                }
                for(int i=0; i<sizeof(temp1); i++)
                {
                	dates[j+1][i]=temp1[i];
                }
                for(int i=0; i<sizeof(temp2); i++)
                {
                	dates[j][i]=temp2[i];
                }

                struct Date tempDate = dateArray[j];
                dateArray[j] = dateArray[j + 1];
                dateArray[j + 1] = tempDate;
            }
        }
    }

    free(dateArray);
}


void readCSVFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[1000];
    fgets(line, sizeof(line), file); // Skipping header line

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(products[totalProducts].productNumber, token);

        for (int i = 0; i < MAX_STEPS; ++i) {
            token = strtok(NULL, ",");
            if (token == NULL) break;
            strcpy(products[totalProducts].dates[i], token);
        }

        token = strtok(NULL, ",");
        strcpy(products[totalProducts].region, token);

        totalProducts++;
    }

    fclose(file);
}


void handleNorthRegion(struct Installation *product) {
    bubbleSortDatesFront(product->dates,MAX_STEPS);
}

void handleSouthRegion(struct Installation *product) {
    bubbleSortDatesBack(product->dates,MAX_STEPS);
}

void handleEastRegion(struct Installation *product) {
    bubbleSortDatesBack(product->dates,MAX_STEPS);
    int i=MAX_STEPS/2;
    while((strcmp(product->dates[i-1],product->dates[i])==0))
    {
    	i++;
    }
    bubbleSortDatesFront(product->dates,i);
}

void handleWestRegion(struct Installation *product) {
    bubbleSortDatesFront(product->dates,MAX_STEPS);
    int i=MAX_STEPS/2;
    while((strcmp(product->dates[i-1],product->dates[i])==0))
    {
    	i++;
    }
    bubbleSortDatesBack(product->dates,i);
}

void printOutputToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error creating output file!\n");
        exit(1);
    }

    for (int i = 0; i < totalProducts; ++i) {
        fprintf(file, "%s,", products[i].productNumber);
        for(int j=0; j<MAX_STEPS; j++)
    	{
    		fprintf(file,"%s,",products[i].dates[j]);
    	}
    	fprintf(file, "%s,", products[i].region);
    }

    fclose(file);
}

int main() {
    const char *filename = "/home/arushjain/Desktop/week01.csv";
    readCSVFile(filename);
    
    //printf("%s %s %s",products[0].productNumber,products[0].dates[1],products[0].region);


    for (int i = 0; i < 4; ++i) {
        if (products[i].region[0] == 'N') {
            handleNorthRegion(&products[i]);
        } else if (products[i].region[0] == 'S') {
            handleSouthRegion(&products[i]);
        } else if (products[i].region[0] == 'E') {
            handleEastRegion(&products[i]);
        } else if (products[i].region[0] == 'W') {
            handleWestRegion(&products[i]);
        }
    }
    
    for(int i=0; i<MAX_STEPS; i++)
    {
    	printf("%s ",products[0].dates[i]);
    }
    printf("\n");
    
    for(int i=0; i<MAX_STEPS; i++)
    {
    	printf("%s ",products[1].dates[i]);
    }
    printf("\n");
    for(int i=0; i<MAX_STEPS; i++)
    {
    	printf("%s ",products[2].dates[i]);
    }
    printf("\n");
    
    for(int i=0; i<MAX_STEPS; i++)
    {
    	printf("%s ",products[3].dates[i]);
    }
    printf("\n");

    const char *outputFilename = "/home/arushjain/Desktop/output.txt";
    printOutputToFile(outputFilename);

    return 0;
}