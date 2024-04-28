#include <stdio.h>
#include <string.h>

int main(){
    

    while(1){
        char s[7];
        scanf("%s", s);
        if(strcmp(s, "quit") == 0) break;
        FILE *inp = fopen("week01.csv", "r");
        FILE *out = fopen("output.csv", "r");
        char line[1024];
        int flag = 0;

        while (fgets(line, 1024, inp)) {
            char temp[1024];
            strcpy(temp, line);
            char *token = strtok(line, ",");
            if(strcmp(token, s) == 0) {
                printf("%s", temp);
                flag = 1;
            }
        }
        while (fgets(line, 1024, out)) {
            char temp[1024];
            char *token = strtok(line, ",");
            if(strcmp(token, s) == 0) {
               printf("%s", temp);
               flag = 1;
            }
        }
        if(!flag){
            printf("The given number product is not found!\n");
        }

        fclose(inp);
        fclose(out);
    }
}