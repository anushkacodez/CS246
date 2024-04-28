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
  //mysql_close(con);
  //exit(1);
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


    FILE *fp = fopen("grade18.csv", "r");

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

        char roll_number[200],cid[200],letter_grade[200];
        
        while (value) {
            if (column == 0) {
                strcpy(roll_number, value);
                trimNewline(roll_number);
            }
            else if(column==1)
            {
                strcpy(cid, value);
                //printf("%s\n",cid);
                trimNewline(cid);
                //printf("%s\n",cid);
            }
            else if(column==2)
            {
                strcpy(letter_grade, value);
                trimNewline(letter_grade);
            }
            
            value = strtok(NULL, ",");
            column++;
        }
        char query[1024];
        sprintf(query, "INSERT INTO grade18(roll_number, cid, letter_grade) VALUES ('%s','%s','%s')",roll_number, cid, letter_grade);
        printf("%s\n",query);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
    }

    fclose(fp);
    mysql_close(con);
    exit(0);
}