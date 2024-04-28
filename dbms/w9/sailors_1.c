#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';  // Remove the newline character
    }
}

int main() {
    FILE *fp = fopen("sailors.csv", "r");
    FILE *f2 = fopen("sailors_1.sql", "w");

    fprintf(f2, "USE week09;\n");

    if (!fp) {
        printf("Can't open file\n");
    } 
    
    else {
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
            // if(row == 1) continue;
            while (value) {
                // Column 1
                if (column == 0) {
                    double num1 = strtod(value, NULL);
                    sid = (int)num1;
                }

                if (column == 1) {
                    strcpy(sname, value);
                    trimNewline(sname);
                }

                if (column == 2) {
                    double num3 = strtod(value, NULL);
                    rating = (int)num3;
                }
                if (column == 3) {
                    double num3 = strtod(value, NULL);
                    age = num3;
                }
            

                value = strtok(NULL, ",");
                column++;
            }

            fprintf(f2, "INSERT INTO sailors_1(sid, sname, rating, age) VALUES (%d, \"%s\", %d, %f);\n", sid, sname, rating, age);
        }
        
     
        fclose(fp);
        fclose(f2);
    }
    return 0;
}