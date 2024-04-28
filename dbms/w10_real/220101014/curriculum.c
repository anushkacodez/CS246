#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';  // Remove the newline character
    }
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}






int main(int argc, char **argv)
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", NULL,"week10", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }


    FILE *fp = fopen("curriculum.csv", "r");

    if (!fp) {
        fprintf(stderr, "Can't open file\n");
        exit(1);
    } 

    char buffer[1024];

    int row = 0;
    int column = 0;

    while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;
        char *value = strtok(buffer, ",");
        
        char dept[4], cid[8];
        int number;

        while (value) {
            if(column==0)
            {
                strcpy(dept, value);
                trimNewline(dept);
            }
            else if(column==1)
            {
                number=atoi(value);
            }
            else if(column==2)
            {
                strcpy(cid, value);
                trimNewline(cid);
            }
            
            value = strtok(NULL, ",");
            column++;
        }
        char query[256];
        sprintf(query, "INSERT INTO curriculum(dept, number, cid) VALUES ('%s',%d,'%s')",dept, number, cid);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
    }

    fclose(fp);
    mysql_close(con);
    exit(0);
}