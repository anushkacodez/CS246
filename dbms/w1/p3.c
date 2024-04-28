#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_STEPS 10
#define MAX_DATE_LENGTH 12
#define REGION_LENGTH 10
#define PRODUCT_NUMBER_LENGTH 10
#define FILENAME_LENGTH 50

struct Installation {
    char productNumber[PRODUCT_NUMBER_LENGTH];
    char steps[MAX_STEPS][10];
    char dates[MAX_STEPS][MAX_DATE_LENGTH];
    int day;
    char month[3];
    int imonth;
    int year;
    char region[REGION_LENGTH];
};




int totalProducts = 0;


// Function to read input from CSV file
int main(){
struct Installation products[MAX_PRODUCTS];
    FILE *file = fopen("/home/arya_n/Desktop/DBMS Lab/week01.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("file read\n");
    }


    char line[1000];
    fgets(line, sizeof(line), file); // Skipping header line

    // fscanf(file,"%s",line);
    // fscanf(file,"%s",line);
    int t = 1;
    while (fgets(line, sizeof(line), file)) {
        
        char *token = strtok(line, ",");
        strcpy(products[totalProducts].productNumber, token);
        printf("%s\n" , products[totalProducts].productNumber);
        for (int i = 0; i < 10; ++i) {
            token = strtok(NULL, ",");
            if (token == NULL) break;
            strcpy(products[totalProducts].dates[i], token);
        }
        for (int i = 0; i < 10; ++i) {
            // printf("%s\n" , products[totalProducts].dates[i]);

            sscanf(products[totalProducts].dates[i], "%d-%3s-%d", &products[totalProducts].day,products[totalProducts].month,&products[totalProducts].year);
        //     const char months[12][3] = [['J','a','n'],['F','e','b'],['M','a','r'],['A','p','r'],['M','a','y'],['J','u','n'],['J','u','l'],['A','u','g'],['S','e','p'],['O','c','t'],['N','o','v'],['D','e','c']];
        //     for (int i = 0; i < 12; ++i) {
        //     if (months[i][1] == products[totalProducts].month[1] && months[i][1] == products[totalProducts].month[2] && months[i][0] == products[totalProducts].month[0]) {
        //     products[totalProducts].imonth = i + 1;
        //     break;

        // switch(products[totalProducts].month){
        //     case "Jan" : products[totalProducts].imonth = 1; break;
        //     case "Feb" : products[totalProducts].imonth = 2; break;
        //     case "Mar" : products[totalProducts].imonth = 3; break;
        //     case "Apr" : products[totalProducts].imonth = 4; break;
        //     case "May" : products[totalProducts].imonth = 5; break;
        //     case "Jun" : products[totalProducts].imonth = 6; break;
        //     case "Jul" : products[totalProducts].imonth = 7; break;
        //     case "Aug" : products[totalProducts].imonth = 8; break;
        //     case "Sep" : products[totalProducts].imonth = 9; break;
        //     case "Oct" : products[totalProducts].imonth = 10; break;
        //     case "Nov" : products[totalProducts].imonth = 11; break;
        //     case "Dec" : products[totalProducts].imonth = 12; break;
            
        // }
            printf("%d  %3s  %d\n", products[totalProducts].day, products[totalProducts].month, products[totalProducts].year);
    }
        
        token = strtok(NULL, ",");
        strcpy(products[totalProducts].region, token);
        printf("%s\n" , products[totalProducts].region);
        // totalProducts++;
    }
}