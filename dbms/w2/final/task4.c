#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRODUCTS_NUMBER 16000

struct ProductDetails{
    char productNumber[40];
    char dateArray[10][33];
    char region[27];
};

struct Date {
    int day;
    int month;
    int year;
};


void bubble_sort(char **dates, int sz);

int readCSV(struct ProductDetails productArray[], int *num);

int cmp(const void *a, const void *b);

void solve();

void swapTheDates(char **date_str);

void INSTALLATION_SORT(int i, struct ProductDetails productArray[]);

void dateToINT(const char *date_string, struct Date *date);


int main(){
    
    solve();
}




int readCSV(struct ProductDetails productArray[], int *num)
{
    FILE *f=fopen("week02.csv", "r");
    if(f==NULL)
    {
        printf("Error in opening file!\n");
        return 0;
    }

    char buffer[2000];
    *num=0;

    while(fgets(buffer, 2000, f) && *num<PRODUCTS_NUMBER)
    {
        char * token=strtok(buffer, ",");
        int column=0;

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(productArray[*num].productNumber, token);
            }
            else if(column>=1 && column<=10)
            {
                strcpy(productArray[*num].dateArray[column-1], token);
            }
            else if(column==11)
            {
                strcpy(productArray[*num].region, token);
            }
            token = strtok(NULL, ",");
            column++;
        }
        (*num)++;
    }
    fclose(f);
    return 1;
}

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


void dateToINT(const char *date_string, struct Date *date) {
    char month_string[4];
    sscanf(date_string, "%d-%3s-%d", &date->day, month_string, &date->year);

    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i) {
        if (strcmp(month_string, months[i]) == 0) {
            date->month = i + 1;
            break;
        }
    }
}


void bubble_sort(char **dates, int sz)
{
    struct Date *alltheDates=(struct Date *)malloc(sz*sizeof(struct Date));
    for(int i=0; i<sz; i++)
    {
        dateToINT(dates[i], &alltheDates[i]);
    }

    for(int i=0; i<sz-1; i++)
    {
        for(int j=0; j<sz-i-1; j++)
        {
            if(cmp(&alltheDates[j], &alltheDates[j+1])>0) //if the first date is bigger than the second date then we need to swap them
            {
                char *temp = dates[j];
                dates[j] = dates[j + 1];
                dates[j + 1] = temp;

                struct Date tempD=alltheDates[j];
                alltheDates[j]=alltheDates[j+1];
                alltheDates[j+1]=tempD;
            }
        }
    }
    free(alltheDates); //free the memory we allocated using malloc
}


void swapTheDates(char **date_str)
{
    for (int i = 0; i < 5; i++) //we need to swap the first 5 dates for east and west regions
    {
        char temp[13]; //character array for storing the date temporarily
        strcpy(temp, date_str[i]);
        strcpy(date_str[i], date_str[10-i-1]); //we will swap the latest date with the first one and the second latest with the second one and so on acc to the question
        strcpy(date_str[10-i-1], temp);
    }
    
}


void INSTALLATION_SORT(int i, struct ProductDetails productArray[])
{
    char** date_str=(char **)malloc(10*sizeof(char *));
    for (int j = 0; j < 10; ++j) {
        date_str[j] = (char *)malloc(50);  // Adjust the buffer size as needed
    }

    for(int j=0; j<10; j++)
    {
        strcpy(date_str[j], productArray[i].dateArray[j]);
    }

    bubble_sort(date_str, 10);

    if(productArray[i].region[0]=='N')
    {
        for(int j=0; j<10; j++)
        {
            strcpy(productArray[i].dateArray[j], date_str[j]);
        }
    }
    else if(productArray[i].region[0]=='S')
    {
        for(int j=0; j<10; j++)
        {
            strcpy(productArray[i].dateArray[j], date_str[10-j-1]);
        }
    }
    else if(productArray[i].region[0] == 'E'){
        swapTheDates(date_str);
        int j = 5;
        while(j<10 && strcmp(date_str[j], date_str[j-1]) == 0){
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            strcpy(productArray[i].dateArray[k], date_str[j-k-1]);
        }
        
        for(int k = j; k<10; k++){
            strcpy(productArray[i].dateArray[k], date_str[k]);
        }
    }
    else if(productArray[i].region[0] == 'W'){
        swapTheDates(date_str);
        int j = 5;
        while(j<10 && strcmp(date_str[j], date_str[j-1]) == 0){
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            strcpy(productArray[i].dateArray[k], date_str[k]);
        }
        for(int k = j; k<10; k++){
            strcpy(productArray[i].dateArray[k], date_str[10+j-k-1]);
        }
    }
}

void solve()
{
    while(1){
        char s[7];
        scanf("%s", s);

        if(strcmp(s, "quit") == 0)
        {
            break;
        } 


        FILE *input_file = fopen("week02.csv", "r");
        FILE *output_file = fopen("220101014.csv", "r");


        char buffer[2000];
        int flag = 0;

        //doing for input file
        while (fgets(buffer, 2000, input_file)) {
            char temp_string[2000];
            strcpy(temp_string, buffer);

            char *token = strtok(buffer, ",");

            if(strcmp(token, s) == 0) {
                printf("%s", temp_string);
                flag = 1;
            }
        }

        //doing for output file
        while (fgets(buffer, 2000, output_file)) {
            char temp_string[2000];
            strcpy(temp_string, buffer);

            char *token = strtok(buffer, ",");

            if(strcmp(token, s) == 0) {
               printf("%s", temp_string);
               flag = 1;
            }
        }
        if(flag==0){
            printf("The given number product is not found!\n");
        }

        fclose(input_file);
        fclose(output_file);
    }
}