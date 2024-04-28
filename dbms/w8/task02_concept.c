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
    FILE *f1 = fopen("concept.csv", "r");
    FILE *f2 = fopen("task02_concept.sql", "w");
    fprintf(f2, "USE week08;\n");

    char buffer[2000];

    for(int i=0; i<96; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char cid[6], qn[6];
        char desc[101];

        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(cid, token);
                trimenewline(cid);
            }
            else if(column==1)
            {
                strcpy(qn, token);
                trimenewline(qn);
            }
            else if(column==2)
            {
                strcpy(desc, token);
                trimenewline(desc);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO concept (cid, qn, description) VALUES ('%s', '%s','%s');\n", cid, qn, desc);     

    }
    fclose(f2);
}