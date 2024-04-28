#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct product
{
    char prod_no[10];
    date step[10];
    int zone;
}product;

product addDate(char* str, product prod, int num);
product addZone(char* str, product prod);
product addToProduct(char* row);
int swap(long int *a, long int *b);
void BSort(long int a[], int count);
date toDate(long int i);
char* DtoS(date d, char* c);
product zoneSort(product prod);
void printProd(FILE* input_file, product prod);
const int sz = 15933;  

int swap(long int *a, long int *b){
    long int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}

int main(){
    char row[10000];
    FILE* input_file = fopen("week01.csv","r");
    FILE* fp1 = fopen("220101034.csv","w");
    fscanf(input_file, "%s", row);
    int lenn = 0;
    product prod[sz];
    product sortedProd[sz];
    while(lenn<sz){
        fscanf(input_file, "%s", row);
        if (feof(input_file)) break;
        prod[lenn] = addToProduct(row);
        sortedProd[lenn] = zoneSort(prod[lenn]);
        printProd(fp1,sortedProd[lenn]);
        lenn++;
    }
    char c[10];
    printf("Enter product number or quit: ");
    while(1){
        scanf("%s", c);
        if(strcmp(c,"quit")==0) break;
        bool b = false;
        for(int i = 0; i<sz; i++){
            if (strcmp(c,prod[i].prod_no) == 0){                        
                char temp[100];
                printf("Installation date before task 2: \n");
                for(int j=0;j<10;j++){ printf("Step %d: %s\n",j+1,DtoS(prod[i].step[j],temp));}
                printf("Installation date after task 2: \n");
                for(int j=0;j<10;j++){ printf("Step %d: %s\n",j+1,DtoS(sortedProd[i].step[j],temp));}
                b = true;
                break;
            }
        }
        if ( b == false) printf("Invalid product number\n");
        printf("Enter product number or quit: ");
    }
    return 0;
}

product addZone(char* str, product prod){
    if(strcmp("North",str) == 0) prod.zone=1;
    if(strcmp("South",str) == 0) prod.zone=2;
    if(strcmp("East",str) == 0) prod.zone=3;
    if(strcmp("West",str) == 0) prod.zone=4;
    return prod;
}

product addToProduct(char* row){
    product prod;
    int j = 0;
    char a[1000] = "";
    bool haveProduct = false;
    int numStep = 0;
    for(int i = 0; row[i]!='\0'; i++){
        char c[2];
        c[0] = row[i];
        c[1] = '\0';
        if (row[i]!=',') strcat(a,c);
        else{
            if(haveProduct == false){ strcpy(prod.prod_no,a); haveProduct = true;}
            else if(numStep < 10){ prod = addDate(a,prod,numStep); numStep++; }
            strcpy(a,"");
        }
    }
    prod = addZone(a,prod);
    return prod;
}

void BSort(long int a[], int count){
    for(int i = 0; i < count-1; i++){
        int flag = 0;
        for(int j = 0; j < count-i-1; j++){
            if(a[j] > a[j+1]){ swap(&a[j+1],&a[j]); flag = 1; }
        }
        if(!flag) break;
    }
}  
date toDate(long int i){
    date d;
    d.day = i%100;
    d.month = (i/100)%100;
    d.year = i/10000;
    return d;
}  
char* DtoS(date d, char* c){
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    sprintf(c,"%d-%s-%d",d.day,months[d.month-1],d.year);
    return c;
}
product zoneSort(product prod){
    long int arr[10];
    for(int i = 0; i<10; i++){
        arr[i] = prod.step[i].day + prod.step[i].month*100+prod.step[i].year*10000;
    }
    BSort(arr,10);
    date newStep[10];
    if (prod.zone == 1){
        for(int i = 0; i<10; i++) newStep[i] = toDate(arr[i]);
    }
    if (prod.zone == 2){
        for(int i = 0; i<10; i++) newStep[10-1-i] = toDate(arr[i]);
    }
    if (prod.zone == 3){
        int i;
        for(i = 0; i<5; i++) newStep[i] = toDate(arr[i]);
        while(arr[i] == arr[i-1]){ newStep[i] = toDate(arr[i]); i++; }
        int j = 0;
        while(i+j<10){ newStep[10-1-j] = toDate(arr[i+j]);  j++; }
    }
    if (prod.zone == 4){
        int i;
        for(i = 0; i<5; i++) newStep[i] = toDate(arr[10-1-i]);
        while(arr[i] == arr[i-1]){ newStep[i] = toDate(arr[10-1-i]); i++; }
        int j = 0;
        while(i+j<10){ newStep[i+j] = toDate(arr[j]);  j++; }
    }
    for(int i =0; i<10; i++) prod.step[i] = newStep[i];
    return prod;
}
void printProd(FILE* input_file, product prod){
    fprintf(input_file, "%s,", prod.prod_no);
    for(int i = 0; i<10; i++){
        char c[100];
        fprintf(input_file, "%s,",DtoS(prod.step[i],c));
    }
    switch(prod.zone){
        case 1:
            fprintf(input_file, "North\n");
            break;
        case 2:
            fprintf(input_file, "South\n");
            break;
        case 3:
            fprintf(input_file, "East\n");
            break;
        case 4:
            fprintf(input_file, "West\n");
            break;
    }
}

product addDate(char* str, product prod, int num){
    date d;
    char monthstr[3];
    sscanf(str, "%d-%3s-%d", &d.day, monthstr, &d.year);
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i) {
        if (strcmp(monthstr, months[i]) == 0) {
            d.month = i + 1;
            break;
        }
    }
    prod.step[num] = d;
    return prod;
}