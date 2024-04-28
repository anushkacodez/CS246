#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *f1 = fopen("database/t04.csv", "r");

    FILE *f2 = fopen("task05.sql", "w");
    fprintf(f2, "USE week06;\n");

    int j = 0;
    while (j < 200)
    {
        int k,h;
        
        fscanf(f1, "%d,%d\n", &k, &h);
        fprintf(f2, "INSERT INTO T04 (k,h) VALUES (%d, %d);\n", k,h);     
        j++;
    }    
}