#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *f1 = fopen("database/t02-20.csv", "r");

    FILE *f2 = fopen("task09_2.sql", "w");
    fprintf(f2, "USE week06;\n");

    int i = 0;
    while (i < 20)
    {
        int f,a,b;
        
        fscanf(f1, "%d,%d,%d\n", &f, &a, &b);
        fprintf(f2, "INSERT INTO T02c(f,a,b) VALUES (%d, %d,%d);\n", f, a, b);     
        i++;
    }    
}