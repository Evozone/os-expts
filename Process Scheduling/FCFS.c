// FCFS algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store processes
typedef struct Process {
    char name[2];
    // Different parameters of a process
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
} Prcs;

// Swaps two processes
void swap(Prcs *x, Prcs *y) {
    Prcs *temp = (Prcs *)malloc(sizeof(Prcs));
    *temp = *x;
    *x = *y;
    *y = *temp;
}

// Structure to store a Gantt chart
typedef struct Gantt {
    char name[2];
    int completion;
} Gantt;

// A function that prints the Gantt chart, with parameters as the Gantt chart and the number of states
void printGanttChart(Gantt chart[], int N) {

    // Tells the user the Gantt chart
    printf("\nGantt Chart:\n");

    // Variable 'unit' to indicate block (How much space to give to each state in terms of ascii chars)
    // Variable 'size' to indicate the size of the block, as per the completion time of the state
    int unit = 4, size;

    // The top line
    for (short i = 0; i < N; i++) {
        if (i != 0) {
            size = unit * (chart[i].completion - chart[i - 1].completion);
        } else {
            size = unit * chart[i].completion;
        }
        printf("+");
        // print as many dashes as per size
        printf("%.*s", size, "---------------------------------------");
    }
    printf("+\n");

    // Labels for the different sections
    for (short i = 0; i < N; i++) {
        if (i != 0) {
            size = unit * (chart[i].completion - chart[i - 1].completion);
        } else {
            size = unit * chart[i].completion;
        }
        printf("|");
        int num = size;

        // print as many spaces as per num
        printf("%*c", (num - 2) / 2, ' ');

        // print the name of the state
        printf("%1s", chart[i].name);

        // print as many spaces as per num
        if (num & 1 == 1) {
            printf("%*c", ((num - 2) / 2) + 1, ' ');
        } else {
            printf("%*c", ((num - 2) / 2), ' ');
        }
    }
    printf("|\n");

    // The bottom line
    for (short i = 0; i < N; i++) {
        if (i != 0) {
            size = unit * (chart[i].completion - chart[i - 1].completion);
        } else {
            size = unit * chart[i].completion;
        }
        printf("+");
        printf("%.*s", size, "---------------------------------------");
    }
    printf("+\n");

    // Print the completion time of the state, adjusted for multiple digits
    printf("%d", 0);
    for (short i = 0; i < N; i++) {
        if (i != 0) {
            size = unit * (chart[i].completion - chart[i - 1].completion);
        } else {
            size = unit * chart[i].completion;
        }
        // Adjust spaces if digits is more than 1
        if (chart[i].completion > 9) {
            printf("%*c", size - 1, ' ');
        } else {
            printf("%*c", size, ' ');
        }

        printf("%d", chart[i].completion);
    }
    printf("\n");
}

// Calculates the total waiting time of all processes
int totalWaitingTime(Prcs *processes, int N) {
    int total = 0;
    for (int i = 0; i < N; i++) {
        total += processes[i].waiting;
    }
    return total;
}

// Calculates the total turnaround time of all processes
int totalTurnaroundTime(Prcs *processes, int N) {
    int total = 0;
    for (int i = 0; i < N; i++) {
        total += processes[i].turnaround;
    }
    return total;
}

// Function to perform FCFS algorithm
void firstComeSchedule(Prcs *processes, int N) {
    // Copy N for later use
    int n = N;

    // Sort the processes according to their arrival time
    for (short i = 0; i < N - 1; i++) {
        for (short j = 0; j < N - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    // Initialize the Gantt chart dynamically
    Gantt *chart = (Gantt *)malloc(sizeof(Gantt) * 2 * N);
    // Index to keep track of the Gantt chart
    int index = 0;

    // Remember to account for when no process has arrived
    int time = 0;

    // Iterate through the processes
    for (short i = 0; i < n; i++) {
        // If the process has arrived
        if (processes[i].arrival <= time) {
            // Add the process to the Gantt chart
            strcpy(chart[index].name, processes[i].name);
            chart[index].completion = processes[i].burst + time;
            // Update completion time for process
            processes[i].completion = chart[index].completion;

            // Update Gantt chart index
            index++;

            time += processes[i].burst;
        } else {
            // If the process has not arrived, add a blank state to the Gantt chart
            strcpy(chart[index].name, "  ");
            chart[index].completion = time = processes[i].arrival;
            // Decrease the counter by 1, as the process has not arrived
            i--;
            // Increase N to account for the blank state
            N++;

            // Update Gantt chart index
            index++;
        }
    }

    // Print the Gantt chart if the size is reasonable
    if (N <= 20) {
        printGanttChart(chart, N);
    } else {
        printf("Gantt chart too large to print\n");
    }

    // Print all the times for each process :
    // Arrival time, Burst time, Completion time, Turnaround time, Waiting time
    // Print column headers
    printf("\n\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("\n");
    for (short i = 0; i < n; i++) {
        // Calculate the turnaround time and waiting time
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;

        // Adjust the format of the times as per length of headers
        printf("%s\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }

    // Print Average Turnaround Time and Average Waiting Time after a newline
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime(processes, n) / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime(processes, n) / n);
}

int main() {
    // input for number of processs
    int N, res, i;
    // An array to store fgets input
    char input[50];
    // Array to store processes
    Prcs *A;

    // Tell the user the expected input format
    printf("\n\nEnter the number of processes, then enter the processes in the following format:\n");
    printf("Process Name\tArrival Time\tBurst Time\t");
    // Show an example
    printf("ex. P1 0 5\n");

    // take input and check if it is valid
    if (!(scanf("%d", &N) == 1)) {
        printf("Failed to read integer.\n");
        return 1;
    }

    // Eat the newline
    getchar();

    // allocate memory for the process
    A = (Prcs *)malloc(N * sizeof(Prcs));

    // take input for each process using fgets
    for (i = 0; i < N; i++) {
        if (fgets(input, sizeof input, stdin) != NULL) {
            res = sscanf(input, "%s%d%d", A[i].name, &A[i].arrival, &A[i].burst);
            if (res != 3) {
                printf("\nAn error has occured.\n");
                break;
            }
        }
    }

    // Verify input :
    printf("\nVerifying input :\n");
    for (i = 0; i < N; i++) {
        printf("%s %d %d\n", A[i].name, A[i].arrival, A[i].burst);
    }

    // Call function to schedule
    firstComeSchedule(A, N);

    return 0;
}