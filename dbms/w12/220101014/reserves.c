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
    FILE *f1 = fopen("reserves01.csv", "r");
    FILE *f2 = fopen("reserves.sql", "w");
    fprintf(f2, "USE week12;\n");

    char buffer[2000];

    for(int i=0; i<10; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char bid[4], sid[4], day[11];
        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(sid, token);
                trimenewline(sid);
            }
            else if(column==1)
            {
                strcpy(bid, token);
                //printf("%s\n", bname);
                trimenewline(bid);
            }
            else if(column==2)
            {
                strcpy(day, token);
                trimenewline(day);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO reserves (sid, bid, day) VALUES (%s, %s, '%s');\n", sid, bid, day);     

    }
    fclose(f2);
}