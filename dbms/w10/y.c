#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
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


    if (mysql_query(conn, "use week09"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "SELECT * FROM boats"))
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

    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }




















    mysql_close(conn);
    return EXIT_SUCCESS;
}
