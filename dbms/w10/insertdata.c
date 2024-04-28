#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

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
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", NULL, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Connected to MySQL server\n");

    if (mysql_query(conn, "create database week10"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_query(conn, "use week10"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    FILE *f1 = fopen("boats.csv", "r");
    // FILE *f2 = fopen("boats.sql", "w");
    // fprintf(f2, "USE week09;\n");

    char buffer[2000];
    char query[2000];

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
        
        sprintf(query, "INSERT INTO boats (bid, bname, bcolor) VALUES (%s, '%s', '%s');\n", bid, bname, bcolor);     
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }

    }
    //fclose(f2);
}