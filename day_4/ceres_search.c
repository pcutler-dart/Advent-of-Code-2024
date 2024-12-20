#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//shape of input
#define SIZE 140
#define M (N + 1)  // +newline
#define X (('M' + 'S') << 1)  // X-MAS corners for part 2

char matrix[SIZE][SIZE];

//define supportinmatrix functions
void readFile(const char *filename, char matrix[SIZE][SIZE]);
void printMatrix(char matrix[SIZE][SIZE]);

//Check all X's MAS in each direction in a matrix
int main(void) {
    const char *filename = "input.txt";
    // Read the file
    readFile(filename, matrix);
    //print matrix to verify it read correctly
    //printMatrix(matrix);
    int sum = 0;
    //scan each adjacent value for conditions of char in matrix
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (matrix[i][j] == 'X') {
                sum += j > 2      && matrix[i][j-1] == 'M' && matrix[i][j-2] == 'A' && matrix[i][j-3] == 'S';
                sum += j < SIZE-3 && matrix[i][j+1] == 'M' && matrix[i][j+2] == 'A' && matrix[i][j+3] == 'S';
                sum += i > 2      && matrix[i-1][j] == 'M' && matrix[i-2][j] == 'A' && matrix[i-3][j] == 'S';
                sum += i > 2      && j > 2 && matrix[i-1][j-1] == 'M' && matrix[i-2][j-2] == 'A' && matrix[i-3][j-3] == 'S';
                sum += i > 2      && j < SIZE-3 && matrix[i-1][j+1] == 'M' && matrix[i-2][j+2] == 'A' && matrix[i-3][j+3] == 'S';
                sum += i < SIZE-3 && matrix[i+1][j] == 'M' && matrix[i+2][j] == 'A' && matrix[i+3][j] == 'S';
                sum += i < SIZE-3 && j > 2 && matrix[i+1][j-1] == 'M' && matrix[i+2][j-2] == 'A' && matrix[i+3][j-3] == 'S';
                sum += i < SIZE-3 && j < SIZE-3 && matrix[i+1][j+1] == 'M' && matrix[i+2][j+2] == 'A' && matrix[i+3][j+3] == 'S';
            }
    printf("%d\n", sum);
    sum = 0;
    for (int i = 1; i < SIZE - 1; ++i)
        for (int j = 1; j < SIZE - 1; ++j)
            if (matrix[i][j] == 'A')
                sum += matrix[i-1][j-1] + matrix[i-1][j+1] + matrix[i+1][j-1] + matrix[i+1][j+1] == X && matrix[i-1][j-1] != matrix[i+1][j+1];
    printf("%d\n", sum);

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