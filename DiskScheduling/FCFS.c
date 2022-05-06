// Write a program to demonstrate the concept of FCFS disk scheduling algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform FCFS Disk Scheduling (Returns the sum of seek times)
int FCFS(int refStringLength, int *refString, int currPos, int maxCapacity) {
    int seekTime = 0;

    // Compute seek time
    for (int i = 0; i < refStringLength; i++) {
        seekTime += abs(refString[i] - currPos);
        currPos = refString[i];
    }

    return seekTime;
}

// Main function takes a command line argument for the reference string
int main(int argc, char *argv[]) {
    // End program if no argument is passed
    if (argc == 0) {
        exit(1);
    } else if (argc < 5) {
        // Too less arguments
        // Print Expected input
        printf("Expected input : ./FCFS <number of positions> <reference string> <current position> <max capacity>\n");
        exit(1);
    }

    int numberOfPositions = atoi(argv[1]);
    int currentPosition = atoi(argv[3]);
    int maxCapacity = atoi(argv[4]);

    // If the current position is greater than the max capacity, or less than 0, print error
    if (currentPosition > maxCapacity || currentPosition < 0) {
        printf("Error: Current position is greater than max capacity or less than 0\n");
        exit(1);
    }

    // Convert the reference string to an array of integers using strtok
    int *refString = (int *)malloc(sizeof(int) * numberOfPositions);
    char *token = strtok(argv[2], " ");
    int i = 0;
    while (token != NULL) {
        refString[i] = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }

    // If any of the reference string is greater than the max capacity, or less than 0, print error
    for (int i = 0; i < numberOfPositions; i++) {
        if (refString[i] > maxCapacity || refString[i] < 0) {
            printf("Error: Reference string is greater than max capacity or less than 0\n");
            exit(1);
        }
    }

    // Print the seek time
    printf("Seek time : %d\n", FCFS(numberOfPositions, refString, currentPosition, maxCapacity));

    // Free the memory allocated to the reference string
    free(refString);

    return 0;
}
