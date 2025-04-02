#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    bool completed;
};

struct GanttNode {
    int pid;
    int startTime;
    int endTime;
};

vector<GanttNode> ganttChart;

bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

void sjfNonPreemptive(vector<Process> &processes) {
    int currentTime = 0;
    int completedProcesses = 0;
    int n = processes.size();

    sort(processes.begin(), processes.end(), compareArrival);

    while (completedProcesses < n) {
        int shortestIndex = -1;
        int shortestBurst = INT_MAX;

        // Find process with shortest burst time that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    shortestIndex = i;
                }
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Execute the process to completion
        Process &currentProcess = processes[shortestIndex];
        int startTime = currentTime;
        currentTime += currentProcess.burstTime;

        // Add to Gantt chart
        ganttChart.push_back({currentProcess.id, startTime, currentTime});

        currentProcess.turnaroundTime = currentTime - currentProcess.arrivalTime;
        currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
        currentProcess.completed = true;
        completedProcesses++;
    }
}

void printGanttChart() {
    cout << "\nGantt Chart:\n";
    cout << "-----------\n";

    // Print the top bar
    for (const auto &node : ganttChart) {
        cout << "|  P" << node.pid << "  ";
    }
    cout << "|\n";

    // Print the time markers
    cout << "0";
    for (const auto &node : ganttChart) {
        cout << "      " << node.endTime;
    }
    cout << "\n";
}

void printResults(const vector<Process> &processes) {
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    cout << "\nProcess ID | Burst Time | Arrival Time | Waiting Time | Turnaround Time\n";
    cout << "----------------------------------------------------------------\n";

    for (const auto &p : processes) {
        cout << setw(10) << p.id << " | "
             << setw(10) << p.burstTime << " | "
             << setw(12) << p.arrivalTime << " | "
             << setw(12) << p.waitingTime << " | "
             << setw(15) << p.turnaroundTime << endl;

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaitingTime / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout << "Process ID: ";
        cin >> processes[i].id;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;

        processes[i].completed = false;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    sjfNonPreemptive(processes);
    printGanttChart();
    printResults(processes);

    return 0;
}
