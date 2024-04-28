#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    //task1

    MYSQL *coni=mysql_init(NULL);
    if (coni == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(coni, "localhost", "root", NULL, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(coni));
        mysql_close(coni);
        exit(1);
    }
    if (mysql_query(coni, "create database if not exists week10"))
    {
        fprintf(stderr, "%s\n", mysql_error(coni));
        mysql_close(coni);
        exit(1);
    }
    mysql_close(coni);
    printf("Connected to MySQL server\n");




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

    



    // task 02
    // if (mysql_query(conn, "use week10"))
    // {
    //     fprintf(stderr, "%s\n", mysql_error(conn));
    //     mysql_close(conn);
    //     exit(1);
    // }

    if (mysql_query(conn, "create table student18(name char(100),roll_number char(10), primary key(roll_number))"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "create table course18(semester int, cid char(7), name char(100), l int, t int, p int, c int, primary key(cid))"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "create table grade18(roll_number char(10), cid char(7), letter_grade char(2), primary key(roll_number, cid))"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_query(conn, "create table curriculum(dept char(3), number int, cid char(7))"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    printf("%s","task 2 completed\n");

    // if (mysql_query(conn, "drop database week10"))
    // {
    //     fprintf(stderr, "%s\n", mysql_error(conn));
    //     mysql_close(conn);
    //     exit(1);
    // }



    //task 3
    //done in other files


   

}