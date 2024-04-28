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

  if (mysql_real_connect(con, "localhost", "", "",
          "week09", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "DROP TABLE IF EXISTS sailors")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "CREATE TABLE sailors3(sid INT PRIMARY KEY, sname VARCHAR(255), rating INT, age DOUBLE)")) {
      finish_with_error(con);
  }

  FILE *fp = fopen("sailors.csv", "r");

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
      int sid;
      char sname[51];
      int rating;
      double age;
      while (value) {
          if (column == 0) {
              sid = atoi(value);
          }

          if (column == 1) {
              strcpy(sname, value);
              trimNewline(sname);
          }

          if (column == 2) {
              rating = atoi(value);
          }
          if (column == 3) {
              age = atof(value);
          }
          value = strtok(NULL, ",");
          column++;
      }
      char query[256];
      sprintf(query, "INSERT INTO sailors3(sid, sname, rating, age) VALUES (%d, \"%s\", %d, %f)", sid, sname, rating, age);
      if (mysql_query(con, query)) {
          finish_with_error(con);
      }
  }

  fclose(fp);
  mysql_close(con);
  exit(0);
}