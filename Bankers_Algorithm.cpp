#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if resources can be allocated to a process
bool canAllocate(int need[], int available[], int numResources) {
    for (int i = 0; i < numResources; i++) {
        if (need[i] > available[i])
            return false;
    }
    return true;
}

// Safety Algorithm
bool isSafeState(int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES],
                 int available[], int numProcesses, int numResources,
                 int safeSequence[]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    // Calculate Need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work with available resources
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses) {
        bool foundProcess = false;
        
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i] && canAllocate(need[i], work, numResources)) {
                // If we can allocate to process i, assume allocation
                for (int j = 0; j < numResources; j++) {
                    work[j] += allocation[i][j];
                }
                safeSequence[count++] = i;
                finish[i] = true;
                foundProcess = true;
            }
        }

        // If no process was found in this round, we are not in a safe state
        if (!foundProcess) return false;
    }

    // If we finished all processes, we are in a safe state
    return true;
}

int main() {
    int numProcesses, numResources;
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the Max matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available resources vector:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    if (isSafeState(max, allocation, available, numProcesses, numResources, safeSequence)) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
