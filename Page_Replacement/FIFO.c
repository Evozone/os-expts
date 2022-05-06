// Write a program to demonstrate concept of FIFO page replacement policy.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the results
void displayResult(char *refString, int numFrames, char **matrix, int pageFaults, int pageHits) {
    // Print the reference string as column headers
    printf("\nString: \t");
    for (int i = 0; i < strlen(refString); i++) {
        printf("%c ", refString[i]);
    }

    // Print a newline
    printf("\n");
    for (int i = 0; i < numFrames; i++) {
        printf("Frame %d: \t", i);
        for (int j = 0; j < strlen(refString); j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Print the number of page faults and page hits
    printf("\nPage Faults: %d\nPage Hits: %d\n", pageFaults, pageHits);

    // Print the percentage of successful page hits
    printf("\nSuccessful Page Hits: %.2f%%\n", (float)pageHits / (float)(pageHits + pageFaults) * 100);

    // Free the memory
    for (int i = 0; i < numFrames; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

// FIFO Page Replacement Algorithm
void FIFO(char *refString, int numFrames, char **matrix) {
    // Declare number of page faults, page hits;
    int pageFaults = 0, pageHits = 0;

    // For each character in the reference string, check if it is in the memory
    for (int i = 0; i < strlen(refString); i++) {
        // If not the first character, get initial value of frames from previous iteration
        if (i != 0) {
            for (int j = 0; j < numFrames; j++) {
                matrix[j][i] = matrix[j][i - 1];
            }
        }

        // Check if the character is in the memory
        int found = 0;
        for (int j = 0; j < numFrames; j++) {
            if (matrix[j][i] == refString[i]) {
                // If the character is in the memory, increment the page hits
                pageHits++;
                found = 1;
                break;
            }
        }
        // Leave the loop if the character is found in the memory
        if (found) {
            continue;
        } else {
            // If the character is not in the memory, increment the page faults
            pageFaults++;
        }

        // Iterate through the memory to find the oldest frame
        int oldest = 0, ageOfOldest = 0;
        for (int j = 0; j < numFrames; j++) {
            if (matrix[j][i] == ' ') {
                oldest = j;
                break;
            } else {
                // Calculate the age of the frame by checking number of previous consecutive occurrences
                int age = 0;
                for (int k = i - 1; k >= 0; k--) {
                    if (matrix[j][k] == matrix[j][i]) {
                        age++;
                    } else {
                        break;
                    }
                }
                if (age > ageOfOldest) {
                    ageOfOldest = age;
                    oldest = j;
                    // If the age of the frame is the same, check the frame number
                    if (age == ageOfOldest) {
                        if (j < oldest) {
                            oldest = j;
                        }
                    }
                }
            }
        }

        // Replace the oldest frame with the current character
        matrix[oldest][i] = refString[i];
    }

    // Function to print the results
    displayResult(refString, numFrames, matrix, pageFaults, pageHits);
}

// Driver function with arguments
int main(int argc, char *argv[]) {

    // Switch argc
    switch (argc) {
    case 0:
        printf("Critical Error: No arguments passed.\n");
        exit(0);
    case 1:
    case 2:
        printf("\nUsage: ./FIFO <Reference String> <Number of Frames> \n");
        return 0;
    case 3:
        break;
    default:
        printf("\nUsage: ./FIFO <Reference String> <Number of Frames> \n");
        return 0;
    }

    // Assuming that the refernce string only contains single characters
    int ref_string_length = (strlen(argv[1]) + 1) / 2;
    int num_frames = atoi(argv[2]);

    // Allocate memory for the reference string
    char *ref_string = (char *)malloc(ref_string_length * sizeof(char));

    // Convert the reference string to an array of characters using strtok
    char *token = strtok(argv[1], " ");
    int i = 0;
    while (token != NULL) {
        ref_string[i] = token[0];
        token = strtok(NULL, " ");
        i++;
    }

    // Create a character matrix of size numFrames x length of reference string
    char **matrix = (char **)malloc(num_frames * sizeof(char *));
    for (int i = 0; i < num_frames; i++) {
        matrix[i] = (char *)malloc(ref_string_length * sizeof(char));
        // Initialize all the elements of the matrix to ' '
        memset(matrix[i], ' ', ref_string_length);
    }

    // Call the FIFO page replacement algorithm
    FIFO(ref_string, num_frames, matrix);

    return 0;
}