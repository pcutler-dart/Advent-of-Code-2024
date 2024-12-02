#include <stdio.h>
#include <stdlib.h>

// takes the file of 1000 numbers and reads each line into 2 arrays (arr0 and arr1)
void read_to_arrays(FILE *file, int *arr0, int *arr1, int lines);

// quick sort algorithm to sort the array
int partition(int *arr,int low, int high);
void quick_sort(int *arr, int low, int high);

//get the total of distances
int diff_distances(int *arr0, int *arr1, int arr_len);

//get the similarity score, sum of values in array 0 multiplied by the number of occurrences of that value in array 1
int similarity_score(int *arr0, int *arr1, int arr_len);

int main(void){
    int num_lines = 1000;
    int arr0[num_lines], arr1[num_lines];

    FILE *file = fopen("input.txt","r");
    //checks to ensure file is valid
    if (file == NULL){
        printf("Error opening file \n");
        return 1;
    }
    //read file and save to arrays
    read_to_arrays(file,arr0,arr1,num_lines);

    fclose(file);

    //sort the 2 arrays
    quick_sort(arr0,0,num_lines-1);
    quick_sort(arr1,0,num_lines-1);

    //compute the distance between each value and sum them
    int distances = diff_distances(arr0,arr1,num_lines);
    printf("Sum of Distances: %d\n",distances);

    int similarity = similarity_score(arr0,arr1,num_lines);
    printf("Similarity Score: %d\n",similarity);
    
    return 0;
}

void read_to_arrays(FILE *file, int *arr0, int *arr1, int lines){
    //create temporary numbers
    int a , b;
    //i to track current index
    int i = 0;

    //read the file while there are 2 numbers on each line
    while(fscanf(file, "%d %d", &a, &b) == 2){
        arr0[i] = a;
        arr1[i] = b;
        i++;
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int temp = partition(arr, low, high);
        quick_sort(arr, low, temp - 1);
        quick_sort(arr, temp + 1, high);
    }
}

int diff_distances(int *arr0, int *arr1, int arr_len){
    int sum_distances = 0;
    for (int i = 0; i < arr_len; i++) {
        int diff = arr0[i] - arr1[i];
        sum_distances = sum_distances + abs(diff);

        //printf("%d\n",sum_distances);
    }

    return sum_distances;
}

int similarity_score(int *arr0, int *arr1, int arr_len){
    int score = 0;
    for(int i = 0; i < arr_len; i++) {
        int count = 0;
        for(int j = 0; j < arr_len;j++){
            if(arr0[i] == arr1[j]){
                count++;
            }
        }
        score = score + (arr0[i] * count);
    }
    return score;
}