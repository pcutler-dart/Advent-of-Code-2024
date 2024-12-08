#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("input.txt", "r");

    char content[20000];
    fread(content, 1, 20000, file);
    fclose(file);
    int len = strlen(content);

    int do_check = 1;

    int sum = 0;
    if(!do_check){
        for (int i = 0; i < len - 4; i++) {
            if (strncmp(content + i, "mul(", 4) == 0) {
                i += 4;
                int a = 0;
                int b = 0;
                while (content[i] >= '0' && content[i] <= '9') {
                a *= 10;
                a += content[i] - '0';
                i ++;
                }
                if (content[i] == ',') {
                    i ++;
                    while (content[i] >= '0' && content[i] <= '9') {
                        b *= 10;
                        b += content[i] - '0';
                        i ++;
                    }
                }
                if (content[i] != ')') {
                    a = 0;
                }
                sum += a * b;
            }
        }
    }
    else{
        int enable = 1;
        for (int i = 0; i < len - 4; i++) {
            if (strncmp(content + i, "do()", 4) == 0) {
                enable = 1;
            }
            if (i < len - 7 && strncmp(content + i, "don't()", 7) == 0) {
                enable = 0;
            }
            if (strncmp(content + i, "mul(", 4) == 0) {
                i += 4;
                int a = 0;
                int b = 0;
                while (content[i] >= '0' && content[i] <= '9') {
                a *= 10;
                a += content[i] - '0';
                i ++;
                }
                if (content[i] == ',') {
                    i ++;
                    while (content[i] >= '0' && content[i] <= '9') {
                        b *= 10;
                        b += content[i] - '0';
                        i ++;
                    }
                }
                if (content[i] != ')') {
                    a = 0;
                }
                sum += a * b * enable;
            }
        }
    }

    printf("%d\n", sum);
}