#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *f1 = fopen("t02.csv", "r");
    FILE *f2 = fopen("task03.sql", "w");
    fprintf(f2, "USE week07;\n");


    int i = 0;
    while (i < 500)
    {
        int c1,c3;
        char c2[21];
        
        fscanf(f1, "%d,%20[^,],%d\n", &c1, c2, &c3);
        fprintf(f2, "INSERT INTO T02 (c1,c2,c3) VALUES (%d, \"%s\",%d);\n", c1,c2,c3);     
        i++;
    }    
}