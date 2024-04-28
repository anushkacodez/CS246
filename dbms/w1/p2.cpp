#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Installation {
    char date[12];
    int step;
};

struct Product {
    char productNumber[10];
    struct Installation steps[10];
    char region[5];
};

// Function prototypes
void readInputFile(struct Product products[], int *numProducts);
void printProduct(struct Product *product);

int main() {
    struct Product products[100];
    int numProducts = 0;

    // Task 01: Read the input file into the appropriate data structure
    readInputFile(products, &numProducts);

    // Example: Print the read products
    for (int i = 0; i < numProducts; i++) {
        printProduct(&products[i]);
    }

    return 0;
}

// Function to read the CSV file row-wise
void readInputFile(struct Product products[], int *numProducts) {
    FILE *file = fopen("week01.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Assuming your CSV file structure is like "P0001,1,22-Mar-2024,...,West"
    while (fscanf(file, "%9[^,],%d,%11[^,],%9[^,],", products[*numProducts].productNumber,
                  &products[*numProducts].steps[0].step, products[*numProducts].steps[0].date,
                  products[*numProducts].region) != EOF) {
        // Read the rest of the installation steps
        for (int i = 1; i < 10; i++) {
            fscanf(file, "%d,%11[^,],", &products[*numProducts].steps[i].step, products[*numProducts].steps[i].date);
        }

        (*numProducts)++;
    }

    fclose(file);
}

// Function to print a product for testing purposes
void printProduct(struct Product *product) {
    printf("Product: %s\n", product->productNumber);
    for (int i = 0; i < 10; i++) {
        printf("Step %d: %d, Date: %s\n", i + 1
