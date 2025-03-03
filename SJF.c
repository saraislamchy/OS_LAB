#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id, arrival, burst, completion, waiting, turnaround;
    bool completed;
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void calculateTimes(struct Process p[], int n) {
    int completed = 0, time = 0;

    while (completed < n) {
        int shortest = -1, minBurst = __INT_MAX__;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time && p[i].burst < minBurst) {
                shortest = i;
                minBurst = p[i].burst;
            }
        }
        if (shortest == -1) {
            time++;
            continue;
        }
        // Process execution
        p[shortest].completion = time + p[shortest].burst;
        p[shortest].turnaround = p[shortest].completion - p[shortest].arrival;
        p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;
        p[shortest].completed = true;

        time = p[shortest].completion;
        completed++;
    }
}

void printTable(struct Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival,
               p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    struct Process p[] = {
        {0, 1, 2, 0, 0, 0, false},
        {1, 2, 1, 0, 0, 0, false},
        {2, 0, 4, 0, 0, 0, false},
        {3, 3, 3, 0, 0, 0, false}
    };
    int n = sizeof(p) / sizeof(p[0]);

    sortByArrival(p, n);
    calculateTimes(p, n);
    printTable(p, n);

    return 0;
}

