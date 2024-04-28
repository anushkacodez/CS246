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

void write(FILE*f2)
{
    fprintf(f2,"{\n");
    fprintf(f2, "fprintf(stderr, '%s\n', mysql_error(conn));\n");
    fprintf(f2, "mysql_close(conn);\n");
    fprintf(f2, "exit(1)\n");
    fprintf(f2,"}\n");
    
}

void closewrite(FILE*f2)
{
    fprintf(f2, "mysql_close(conn);\n");
    fprintf(f2,"return EXIT_SUCCESS;\n");
    fprintf(f2,"}\n");
}
int main()
{
    
    FILE *f1 = fopen("boats.csv", "r");
    FILE *f2 = fopen("insertdata.c", "a");

    
    fprintf(f2,"\n");

    fprintf(f2, "if (mysql_query(conn, 'use week10'))");
    write(f2);
   

    char buffer[2000];

    for(int i=0; i<4; i++)
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
                strcpy(bname, token);
                //printf("%s\n", bname);
                trimenewline(bname);
            }
            else if(column==2)
            {
                strcpy(bcolor, token);
                trimenewline(bcolor);
            }
            token = strtok(NULL, ",");
            column++;
        }
        
        fprintf(f2, "if (mysql_query(conn, 'INSERT INTO boats (bid, bname, bcolor) VALUES (%s, '%s', '%s');\n', bid, bname, bcolor)'))\n");     
        write(f2);
    }
    closewrite(f2);
    fclose(f2);
}