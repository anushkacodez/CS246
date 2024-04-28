#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    FILE *f1 = fopen("/home/anushka/Desktop/Anooshka/dbms/w5/database/t01.csv", "r");

    FILE *f2 = fopen("task02.sql", "w");
    fprintf(f2, "USE week06;\n");

    int i = 0;
    while (i < 1000)
    {
        int a,b,c,d,e;
        
        fscanf(f1, "%d,%d,%d,%d,%d\n", &a, &b, &c, &d, &e);
        fprintf(f2, "INSERT INTO T01 (a,b,c,d,e) VALUES (%d, %d,%d,%d,%d);\n", a, b, c, d, e);     
        i++;
    }    
}