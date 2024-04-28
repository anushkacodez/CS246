#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

static char *host = "localhost";
static char *user = "root";
static char *pass = "200704";
static char *db   = "test";
static char *socket = NULL;
unsigned int port = 3306;
unsigned int flags = 0;

/*
* brew install mysql-client
* export PATH=/usr/local/opt/mysql-client/bin:$PATH
* brew install mysql-connector-c++ (optional)
* gcc -o main $(mysql_config --cflags) main.c $(mysql_config --libs) -L/usr/local/opt/openssl/lib
*/
int main(int argc, char *argv[]) {
	MYSQL *con = mysql_init(NULL);
	
	if (!mysql_real_connect(con, host, user, pass, db, port, socket, flags)) {
		fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	printf("Connected\n");
	
	return EXIT_SUCCESS;
}