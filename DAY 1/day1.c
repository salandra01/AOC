#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Preprocessor defintions
#define LINES 1000
#define MAX_LINE_SIZE 256
#define INPUT_FILE "day 1 data.txt"

// Auxillary function to compare ints needed for qsort
int Compare_Int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}


int main() {

    // Data defintions
    // int distance = 0; // Total distance between values - Day 1
    int score = 0; // Day 2 
    int similarity; // Similarity multiplier - Day 2
    int *left_list = malloc(sizeof(int) * LINES);
    int *right_list = malloc(sizeof(int) * LINES);
    char line[MAX_LINE_SIZE];

    // Open file and check
    FILE *file = fopen(INPUT_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read lines
    for (int i = 0; i < LINES; i++) {
        fgets(line, sizeof(line), file);
        left_list[i] = atoi(strtok(line, " "));
        right_list[i] = atoi(strtok(NULL, " "));
    }

    /*
    * DAY 1
    *
    // Sort
    // Technically not needed for day 2, but simplifies the processes
    // and there is no need to comment out and rewrite some sections
    qsort(left_list, LINES, sizeof(int), Compare_Int);
    qsort(right_list, LINES, sizeof(int), Compare_Int);

    // Sum distance
    for (int i = 0; i < LINES; i++) {
        distance += abs(left_list[i] - right_list[i]);
    }
    */
    
    for (int i = 0; i < LINES; i++) {
        similarity = 0;
        for (int j = 0; j < LINES; j++) {
            if (left_list[i] == right_list[j]) {
                similarity++;
            }
        }
        score += left_list[i] * similarity;
    }

    // Output
    printf("Total score: %d\n", score);

    fclose(file);
    free(left_list);
    free(right_list);

    return 0;
}
