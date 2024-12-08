#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//shape of input
#define SIZE 140
char matrix[SIZE][SIZE];

//define supporting functions
void readFile(const char *filename, char matrix[SIZE][SIZE]);
void printMatrix(char matrix[SIZE][SIZE]);

//Check all X's MAS in each direction in a matrix
int main(void) {
    const char *filename = "input.txt";
    // Read the file
    readFile(filename, matrix);
    //print matrix to verify it read correctly
    printMatrix(matrix);

    return 0;
}


void readFile(const char *filename, char matrix[SIZE][SIZE]){
    FILE *file = fopen(filename,"r");
    
    //initialize the matrix with spaces
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = ' ';
        }
    }
    int row = 0, col = 0;
    char ch;
    
    //read characters from the file
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            continue; //skip newline characters
        }
        
        //store the character
        matrix[row][col] = ch;

        //move to the next column
        col++;
        if (col >= SIZE) {
            col = 0;
            row++;
            if (row >= SIZE) {
                break;
            }
        }
    }
    fclose(file);
}

void printMatrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}