#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *f1 = fopen("t01.csv", "r");
    FILE *f2 = fopen("task02.sql", "w");
    fprintf(f2, "USE week07;\n");

    char a,b,c,d,e;
    fscanf(f1, "%c,%c,%c,%c,%c\n", &a, &b, &c, &d, &e);

    int i = 0;
    while (i < 500)
    {
        int a,b,c,d; 
        char e[21];
        
        fscanf(f1, "%d,%d,%d,%d,%s\n", &a, &b, &c, &d, e);
        fprintf(f2, "INSERT INTO T01 (a,b,c,d,e) VALUES (%d, %d,%d,%d,\"%s\");\n", a, b, c, d, e);     
        i++;
    }    
}