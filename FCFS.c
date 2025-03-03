#include <stdio.h>

struct Process {
    int id, arrival, burst, completion, waiting, turnaround;
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
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
    }
}

void printTable(struct Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival,
p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    struct Process p[] = {
        {0, 1, 2, 0, 0, 0},
        {1, 2, 1, 0, 0, 0},
        {2, 0, 4, 0, 0, 0},
        {3, 3, 3, 0, 0, 0}
    };
    int n = sizeof(p) / sizeof(p[0]);

    sortByArrival(p, n);
    calculateTimes(p, n);
    printTable(p, n);

    return 0;
}
