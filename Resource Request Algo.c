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

// Resource Request Algorithm
bool requestResources(int processID, int request[], int max[][MAX_RESOURCES],
                      int allocation[][MAX_RESOURCES], int available[],
                      int numProcesses, int numResources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    // Calculate Need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check if request is within need and available resources
    for (int i = 0; i < numResources; i++) {
        if (request[i] > need[processID][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources are not available right now.\n");
            return false;
        }
    }

    // Simulate allocation
    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    // Check if the system is in a safe state
    if (isSafeState(max, allocation, available, numProcesses, numResources, safeSequence)) {
        printf("Request can be granted safely.\n");
        return true;
    } else {
        // Revert allocation if not safe
        for (int i = 0; i < numResources; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
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

    int processID, request[MAX_RESOURCES];
    printf("Enter the process ID making the request: ");
    scanf("%d", &processID);
    printf("Enter the request vector:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &request[i]);
    }

    // Check if the request can be granted
    if (requestResources(processID, request, max, allocation, available, numProcesses, numResources)) {
        printf("System is in a safe state after granting the request.\n");
    } else {
        printf("System would be in an unsafe state if the request is granted.\n");
    }

    return 0;
}

