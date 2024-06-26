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
    FILE *fp = fopen("delete-sailors02.csv", "r");
    FILE *f2 = fopen("delete_sailors.sql", "w");

    fprintf(f2, "USE week12;\n");

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

                value = strtok(NULL, ",");
                column++;
            }

            fprintf(f2, "DELETE FROM sailors where sid=%d;\n", sid);
        }
        
     
        fclose(fp);
        fclose(f2);
    }
    return 0;
}