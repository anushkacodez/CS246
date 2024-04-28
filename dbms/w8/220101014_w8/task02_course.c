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
    FILE *f1 = fopen("course.csv", "r");
    FILE *f2 = fopen("task02_course.sql", "w");
    fprintf(f2, "USE week08;\n");

    char buffer[2000];

    for(int i=0; i<4; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char cid[6];
        char cname[101];

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(cid, token);
                trimenewline(cid);
            }
            else if(column==1)
            {
                strcpy(cname, token);
                trimenewline(cname);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO course (cid, cname) VALUES ('%s', '%s');\n", cid, cname);     

    }
    fclose(f2);
}