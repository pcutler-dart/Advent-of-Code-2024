#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void){
    //counter for number of safe lines
    int safe_count = 0;

    FILE *file = fopen("input.txt","r");
    //checks to ensure file is valid
    if (file == NULL){
        printf("Error opening file \n");
        return 1;
    }

    //create a string to store the current line for parsing values
    char line[1024];

    //read each line with fgets
    while(fgets(line,sizeof(line),file)){
        //remove new line characters
        line[strcspn(line, "\n")] = 0;

        //evaluate the changing value 
        int value_change = 0;
        int current_tok = 0;
        int prev_tok = 0;
        //flags for initial and increasing or decreasing
        bool initial = 1;
        bool increasing = 0;
        bool decreasing = 0;
        bool unsafe = 0;
        bool corrected = 0;

        //tokenize the line, separating tokens by spaces
        char *token = strtok(line, " ");
        while (token != NULL){
            //set token to integer
            current_tok = atoi(token);
            
            //initial token case
            if(initial){
                initial = 0;
                prev_tok = current_tok;
                printf("initial token\n");
                token = strtok(NULL, " ");
                continue;
            }
            //Set increasing or decreasing flag
            if(increasing == 0 && decreasing == 0){
                //check if equal
                if(current_tok == prev_tok){
                    printf("%d %d values equal\n",current_tok,prev_tok);
                    if(corrected){
                        printf("unsafe\n");
                        unsafe = 1;
                        break;
                    }
                    printf("dampened\n");
                    corrected = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
                //set decreasing
                else if (current_tok < prev_tok){
                    decreasing = 1;
                }
                //set increasing
                else{
                    increasing = 1;
                }
            }

            //check if value is increasing from prior
            if(increasing){
                //check if value is not increasing
                if (current_tok < prev_tok || current_tok == prev_tok){
                    printf("%d %d value not consistent increasing\n",current_tok,prev_tok);
                    if(corrected){
                        printf("unsafe\n");
                        unsafe = 1;
                        break;  
                    }
                    printf("dampened\n");
                    corrected = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
                //calculate difference
                value_change = abs(current_tok - prev_tok);
                //printf("value increasing difference: %d\n",value_change);
                if((value_change == 0) || (value_change > 3)){
                    printf("%d less than 1 or greater than 3\n",value_change);
                    if(corrected){
                        printf("unsafe\n");
                        unsafe = 1;
                        break;  
                    }
                    printf("dampened\n");
                    corrected = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
            }
            else{
                //check if value is not decreasing
                if (current_tok > prev_tok || current_tok == prev_tok){
                    //value increased
                    printf("%d %d value not consistent decreasing\n",current_tok,prev_tok);
                    if(corrected){
                        printf("unsafe\n");
                        unsafe = 1;
                        break;  
                    }
                    printf("dampened\n");
                    corrected = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
                //calculate difference
                value_change = abs(current_tok - prev_tok);
                //printf("value decreasing difference: %d\n",value_change);
                if((value_change == 0) || (value_change > 3)){
                    printf("%d less than 1 or greater than 3\n",value_change);
                    if(corrected){
                        printf("unsafe\n");
                        unsafe = 1;
                        break;  
                    }
                    printf("dampened\n");
                    corrected = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
            }
            prev_tok = current_tok;
            //printf("line is safe\n");
            token = strtok(NULL, " ");
        }
        //unsafe equal false
        if(unsafe == false){
            safe_count++;
            printf("%d\n",safe_count);
        }
        printf("New line\n");
    }
    printf("Safe Count:%d\n",safe_count);
    fclose(file);

    return 0;
}