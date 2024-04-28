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
    FILE *f1 = fopen("update-boats02.csv", "r");
    FILE *f2 = fopen("update_boats.sql", "w");
    fprintf(f2, "USE week12;\n");

    char buffer[2000];
    fgets(buffer, 2000, f1);
    for(int i=0; i<20; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char bid[4], bname[51], bcolor[51];
        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(bid, token);
                trimenewline(bid);
            }

            else if(column==1)
            {
                strcpy(bcolor, token);
                trimenewline(bcolor);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "UPDATE boats set bcolor='%s' where bid=%s;\n", bcolor, bid);     

    }
    fclose(f2);
}