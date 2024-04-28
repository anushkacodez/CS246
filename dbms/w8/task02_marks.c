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
    FILE *f1 = fopen("marks.csv", "r");
    FILE *f2 = fopen("task02_marks.sql", "w");
    fprintf(f2, "USE week08;\n");

    char buffer[4000];

    for(int i=0; i<28008; i++)
    {
        
        fgets(buffer, 4000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char roll_no[40],cid[6],set1[6], set1_marks[4], set2[6], set2_marks[4];

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(roll_no, token);
                trimenewline(roll_no);
            }
            else if(column==1)
            {
                strcpy(cid, token);
                trimenewline(cid);
            }
            else if(column==2)
            {
                strcpy(set1, token);
                trimenewline(set1);
            }
            else if(column==3)
            {
                strcpy(set1_marks, token);
                trimenewline(set1_marks);
            }
            else if(column==4)
            {
                strcpy(set2, token);
                trimenewline(set2);
            }
            else if(column==5)
            {
                strcpy(set2_marks, token);
                trimenewline(set2_marks);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO marks (roll_number, cid, set1, set1_marks, set2, set2_marks) VALUES (%s, '%s','%s','%s', '%s','%s');\n", roll_no, cid, set1, set1_marks, set2, set2_marks);     

    }
    fclose(f2);
}