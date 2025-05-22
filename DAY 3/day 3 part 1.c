#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define INPUT_FILE "day 3 data.txt"

int main() {

    char *key_token = "mul("; // This is the key token value we are looking for
    char end_token = ')';
    int answer = 0;
    int count = 0;

    FILE *filename = fopen(INPUT_FILE, "r");
    if (filename == NULL) {
        perror("Error opening file\n");
        return 1;
    }

    // Each line is of different length, so we cannot use assumptions,
    // and going char by char will likely be inefficient given the data this time around
    // (see day2 where I used getc and fseek, ftell to move through the file)

    // Instead, we will use fseek to go the end using fseek and return to the start that way,
    // and store the length via ftell. 
    fseek(filename, 0, SEEK_END);
    long file_size = ftell(filename);
    fseek(filename, 0, SEEK_SET);

    // We will also be more consciouos of memory than in day 2
    // (similar to in day 2) since we are not making these base assumptions
    // about our data.

    char *buffer = malloc(file_size * sizeof(char) + 1);

    fread(buffer, file_size, 1, filename);
    buffer[file_size] = '\0';
    char *ptr = buffer;

    if (ptr == NULL) {
        perror("Error reading file\n");
        return 1;
    }

    while ((ptr = strstr(ptr, key_token)) != NULL) {
        ptr += strlen(key_token);
        count = 0;

        char *num1 = malloc(100 * sizeof(char));
        char *num2 = malloc(100 * sizeof(char));

        if (ptr == NULL) {
            perror("Error reading file\n");
            return 1;
        }
        while(isdigit(*ptr)) {
            num1[count] = *ptr;
            ptr++;
            count++;
        }
        if (!count) {
            free(num1);
            free(num2);
            continue;} // continues if no digit
        num1[count] = '\0';

        if (*ptr != ',') {
            free(num1);
            free(num2);
            continue;} // continues if no comma after digit

        if (*ptr == ',') {
            ptr++;
            count = 0;
            if (ptr == NULL) {
                perror("Error reading file\n");
                return 1;
            }   
            while(isdigit(*ptr)) {
                num2[count] = *ptr;
                ptr++;
                count++;
            }
        }

        if (!count) {
            free(num1);
            free(num2);
            continue;} // continues if no digit
        num2[count] = '\0';

        if (*ptr != end_token) {
            free(num1);
            free(num2);
            continue;
        }
           
        answer += atoi(num1) * atoi(num2);

        ptr++;

        free(num1);
        free(num2);
    }

    printf("Answer: %d", answer);
    
    free(buffer);
    fclose(filename);

    return 0;
}
