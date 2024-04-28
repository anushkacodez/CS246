#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(char roll_number[11], MYSQL *conn)
{
    char query[400];
    sprintf(query, "SELECT* from course18 natural join grade18 where roll_number='%s'", roll_number);
    //printf("%s\n", query);
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

    
    //6
    

    compute_spi(conn);

}