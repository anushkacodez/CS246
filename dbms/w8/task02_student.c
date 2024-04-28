#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void trimenewline(char *str)
{
    size_t len=strlen(str);
    if(len>0 && str[len-1]=='\n')
    {
        str[len-1]='\0';
    }

}
int main()
{
    FILE *f1 = fopen("student.csv", "r");
    FILE *f2 = fopen("task02_student.sql", "w");
    fprintf(f2, "USE week08;\n");

    // int i = 0;
    // while (i < 700)
    // {
    //     int roll_no;
    //     char name[21],program[21];
        
    //     fscanf(f1, "%d,%20[^,],%20[^,]\n", &roll_no, name, program);
    //     fprintf(f2, "INSERT INTO T01 (roll_number, student_name, program) VALUES (%d, \"%s\",\"%s\");\n", roll_no, name, program);     
    //     i++;
    // }    
    char buffer[2000];

    for(int i=0; i<700; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char roll_no[40];
        char name[21],program[21];

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(roll_no, token);
            }
            else if(column==1)
            {
                strcpy(name, token);
                trimenewline(name);
            }
            else if(column==2)
            {
                strcpy(program, token);
                trimenewline(program);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO student (roll_number, student_name, program) VALUES (%s, '%s','%s');\n", roll_no, name, program);     

    }
    fclose(f2);
}