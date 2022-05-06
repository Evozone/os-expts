// Write a program to demonstrate concept of deadlock avoidance through Banker's algorithm.

#include <stdio.h>
#include <stdlib.h>

// Function to carry out the banker’s algorithm
void bankersAlgorithm(int n, int m, int available[], int **allocated, int **requested) {
    // Calculate total allocated resources
    int *totalAllocated = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < m; i++) {
        totalAllocated[i] = 0;
        for (int j = 0; j < n; j++) {
            totalAllocated[i] += allocated[j][i];
        }
    }

    // Subtract total allocated resources from available resources
    for (int i = 0; i < m; i++) {
        available[i] -= totalAllocated[i];
    }

    // Initialize finish array
    int *finish = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Initialize safe sequence
    int *safeSequence = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        safeSequence[i] = -1;
    }

    // SafeSequence index
    int safeSequenceIndex = 0;

    // While no process has finished, keep running the algorithm
    while (1) {
        // Flag to check if all processes have finished
        int allFinished = 1;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                allFinished = 0;
                break;
            }
        }

        // If all processes have finished, break
        if (allFinished) {
            break;
        }

        // Check which processes can be executed by subtracting the requested resources from available resources
        for (int i = 0; i < n; i++) {
            // Is process already finished?
            if (finish[i]) {
                continue;
            }

            // Flag to check if process can be executed
            int isSafe = 1;

            // Is process safe? (Iterate through all resources)
            for (int j = 0; j < m; j++) {
                // Is resource available?
                if (requested[i][j] > available[j]) {
                    // Process is not safe
                    isSafe = 0;
                    break;
                }
            }

            // If process is safe, add it to safe sequence
            if (isSafe) {
                safeSequence[safeSequenceIndex++] = i;
                // Mark process as finished
                finish[i] = 1;

                // Subtract the requested resources from available resources
                for (int k = 0; k < m; k++) {
                    available[k] -= requested[i][k];
                }

                // Add back freed resources to total available resources
                for (int k = 0; k < m; k++) {
                    available[k] += allocated[i][k] + requested[i][k];
                }

                // Break out of loop
                break;
            }

            // If no process is safe, then there is a deadlock
            if (i == n - 1) {
                printf("Deadlock detected\n");
                return;
            }
        }
    }

    // Print safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < safeSequenceIndex; i++) {
        printf("P%d ", safeSequence[i]);
        printf("\n");
    }
}

// Main function
int main() {
    // Take input for number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Take input for number of resources
    int m;
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Take input for available resources
    // allocate memory for available resources dynamically
    int *available = (int *)malloc(m * sizeof(int));

    printf("Enter the available resources: \t");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Take input for allocated resources to each process
    // allocate memory for allocated resources dynamically
    int **allocated = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        allocated[i] = (int *)malloc(m * sizeof(int));
    }

    printf("Enter the allocated resources to each process: \n");
    for (int i = 0; i < n; i++) {
        // Show the process ID
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocated[i][j]);
        }
        printf("\n");
    }

    // Take input for requested resources
    // allocate memory for requested resources dynamically
    int **requested = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        requested[i] = (int *)malloc(m * sizeof(int));
    }

    printf("Enter the requested resources: \n");
    for (int i = 0; i < n; i++) {
        // Show the process ID
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &requested[i][j]);
        }
        printf("\n");
    }

    // Call function to carry out the banker’s algorithm
    bankersAlgorithm(n, m, available, allocated, requested);

    return 0;
}