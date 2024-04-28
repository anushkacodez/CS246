#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void compute_spi(char roll_number[11], MYSQL *conn)
{
    char query[400];
    sprintf(query, "SELECT * from course18 natural join grade18 where roll_number='%s' and semester=1", roll_number);
    printf("%s\n", query);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
    int spi1=0;
    int total_cred=1;
    while ((row = mysql_fetch_row(result)))
    {
        int course_cred=atoi(row[6]);
        if(strcmp(row[8],"AA"))
        {
            spi1+=course_cred*10;
        }
        if(strcmp(row[8],"AB"))
        {
            spi1+=course_cred*9;
        }
        if(strcmp(row[8],"BB"))
        {
            spi1+=course_cred*8;
        }
        if(strcmp(row[8],"BC"))
        {
            spi1+=course_cred*7;
        }
        if(strcmp(row[8],"CC"))
        {
            spi1+=course_cred*6;
        }
        if(strcmp(row[8],"CD"))
        {
            spi1+=course_cred*5;
        }
        if(strcmp(row[8],"DD"))
        {
            spi1+=course_cred*4;
        }
        //printf("\n");
    }

    printf("%d\n", spi1);
    return;
    
}
int main() {
    

    MYSQL *conn=mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", NULL, "week10", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Connected to MySQL server with database week10\n");

    



    // task 04

    //1

    if (mysql_query(conn, "SELECT * FROM student18"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *student_res_set = mysql_store_result(conn);

    if (student_res_set == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields = mysql_num_fields(student_res_set);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(student_res_set)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }


    // 2

    if (mysql_query(conn, "SELECT * FROM course18"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *course_res_set = mysql_store_result(conn);

    if (course_res_set == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields1 = mysql_num_fields(course_res_set);

    //MYSQL_ROW row;

    while ((row = mysql_fetch_row(course_res_set)))
    {
        for(int i = 0; i < num_fields1; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    // 3

    if (mysql_query(conn, "SELECT * FROM grade18"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *grade_res_set = mysql_store_result(conn);

    if (grade_res_set == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields2 = mysql_num_fields(grade_res_set);

    //MYSQL_ROW row;

    while ((row = mysql_fetch_row(grade_res_set)))
    {
        for(int i = 0; i < num_fields2; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }


    // 4

    if (mysql_query(conn, "SELECT * FROM curriculum"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    MYSQL_RES *curr_res_set = mysql_store_result(conn);

    if (curr_res_set == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    int num_fields3 = mysql_num_fields(curr_res_set);

    //MYSQL_ROW row;

    while ((row = mysql_fetch_row(curr_res_set)))
    {
        for(int i = 0; i < num_fields3; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }


    //6

}