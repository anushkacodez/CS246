#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>




void stripBlanks(char *input) {
    int i, j;
    int len = strlen(input);

    // Iterate through the characters in the input string
    for (i = j = 0; i < len; i++) {
        // Check if the current character is not a blank character
        if (input[i] != '\t' && input[i] != '\n') {
            // If not a blank character, copy it to the new string
            input[j++] = input[i];
        }
    }

    // Null-terminate the new string
    input[j] = '\0';
}

char** splitString(const char *input, char delimiter, int *numTokens) {
    // Copy the input string to avoid modifying the original
    char *buffer = strdup(input);
    
    // Count the number of tokens
    *numTokens = 1;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == delimiter) {
            (*numTokens)++;
        }
    }

    // Allocate memory for the array of strings
    char **tokens = (char **)malloc((*numTokens) * sizeof(char *));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Tokenize the string using strtok
    int i = 0;
    char *token = strtok(buffer, &delimiter);
    while (token != NULL) {
        // Strip blanks from each token
        stripBlanks(token);

        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, &delimiter);
    }

    // Free the temporary buffer
    free(buffer);

    return tokens;
}


void main(){
    FILE *file1= fopen("employee-languages.csv", "r");
    FILE *file2= fopen("task2_4.sql", "w");
    fprintf(file2,"USE week13;\n");



    char line[1000];
   
    while (fgets(line, sizeof(line), file1) != NULL) {
    
        
    
        char delimiter = ',';
        int numTokens;
        char **token = splitString(line, delimiter, &numTokens);
        fprintf(file2,"INSERT INTO languages VALUES ('%s','%s');\n",token[0],token[1]);
       
        
    }


    return ;
}