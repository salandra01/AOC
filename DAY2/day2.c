#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// Preprocessor defintions
#define LINES 1000 // It is known the file is 1000 lines long
#define INPUT_FILE "day 2 data.txt"
#define BUFFER_SIZE 256 // Assumes there are no lines greater 256

// Part 1
int MonotonicityChecker(int *nums, int size) {

    int sign = 0;
    if (nums[0] == nums[1]) {
        return 0;
    }
    if (nums[0] < nums[1]) {
        sign = 1;
    }
    if (nums[0] > nums[1]) {
        sign = -1;
    }

  for (int i = 0; i < size; i++) {
    if (sign == 1 && i + 1 < size && (nums[i] >= nums[i + 1] || nums[i + 1] - nums[i] > 3)) {
      return 0;
    }
    if (sign == -1 && i + 1 < size && (nums[i] <= nums[i + 1] || nums[i] - nums[i + 1] > 3)) {
      return 0;
    }
  }
  return 1;
}

// Part 2
int ValidityChecker(int *nums, int size) {
    // Fastest to check if starting form is valid and then go from there
    if (MonotonicityChecker(nums, size) == 1) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        int temp[size];
        int temp_size = 0;

        for (int j = 0; j < size; j++) {
            if (j != i) {
                temp[temp_size] = nums[j];
                temp_size++;
            }
        }

        if (MonotonicityChecker(temp, temp_size) == 1) {
            return 1;
        }
    }
    return 0;

}

// I know sscanf and fopen are deprecated, trust me vscode is annyoing about it,
// but there is no reason to use a more tedious safe version for something
// like AoC; also, I don't think in my life I have ever seen someone use
// the safe versions to be fair, but also to be fair its been a while
// and I was a kid back then.

// Part 1
int ReadFileLine(FILE *file, int *nums, int line_size) {
    int i = 0;
    char line[BUFFER_SIZE];
    fgets(line, sizeof(line), file);
    char *ptr = line;
    while (i < line_size && sscanf(ptr, "%d", &nums[i]) == 1) {
    while (*ptr && *ptr >= '0' && *ptr <= '9') {
      ptr++;
    }
    if (*ptr == ' ')
      ptr++;
    i++;
  }
  return i;
}

     
int main() {

    FILE *filename = fopen(INPUT_FILE, "r");
    if (filename == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ans = 0;
    int true_line_size = 0;
    long line_start = 0;
    char c;

    for (int i = 0; i < LINES; i++) {
        true_line_size = 0;
        line_start = ftell(filename); // Get file ptr location
        // This lets us use the true line size instead of using assumptions, since it is variable
        while ((c = fgetc(filename)) != EOF) {
            true_line_size++;
            if (c == '\n') {
                break;
            }
        }
        int nums[true_line_size];
        fseek(filename, line_start, SEEK_SET); // return to location ptr from before fgetc
        int size = ReadFileLine(filename, nums, true_line_size);
        ans += ValidityChecker(nums, size);
    }

    printf("Answer: %d\n", ans);
    fclose(filename);

    return 0;
}