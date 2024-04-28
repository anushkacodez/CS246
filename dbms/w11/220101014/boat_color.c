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
    FILE *f1 = fopen("boat_color.csv", "r");
    FILE *f2 = fopen("boat_color.sql", "w");
    fprintf(f2, "USE week11;\n");

    char buffer[2000];
    fgets(buffer, 2000, f1);

    for(int i=0; i<20; i++)
    {
        
        fgets(buffer, 2000, f1);
        char * token=strtok(buffer, ",");
        int column=0;

        char serial[4], name[21];;
        while(token!=NULL)
        {
            if(column==0)
            {
                strcpy(serial, token);
                trimenewline(serial);
            }
            else if(column==1)
            {
                strcpy(name, token);
                //printf("%s\n", bname);
                trimenewline(name);
            }
            // else if(column==2)
            // {
            //     strcpy(bcolor, token);
            //     trimenewline(bcolor);
            // }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "INSERT INTO boat_color (serial_number, name) VALUES (%s, '%s');\n", serial,name);     

    }
    fclose(f2);
}