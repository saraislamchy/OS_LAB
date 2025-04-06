#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int lastExecutionTime;
};

struct GanttNode {
    int pid;
    int startTime;
    int endTime;
};

void roundRobin(vector<Process>& processes, int timeQuantum) {
    queue<int> readyQueue;
    vector<GanttNode> ganttChart;
    int currentTime = 0;
    int completedProcesses = 0;
    int n = processes.size();

    // Initialize processes
    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
        p.waitingTime = 0;
        p.turnaroundTime = 0;
        p.lastExecutionTime = p.arrivalTime;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

    readyQueue.push(0);
    int nextProcess = 1;

    while (completedProcesses < n) {
        if (readyQueue.empty()) {
            if (nextProcess < n) {
                currentTime = processes[nextProcess].arrivalTime;
                readyQueue.push(nextProcess);
                nextProcess++;
            } else {
                break;
            }
        }

        int currentIdx = readyQueue.front();
        readyQueue.pop();
        Process& currentProcess = processes[currentIdx];

        // Calculate waiting time before execution
        if (currentProcess.lastExecutionTime < currentTime) {
            currentProcess.waitingTime += currentTime - currentProcess.lastExecutionTime;
        }

        // Determine execution time (minimum of quantum or remaining time)
        int executionTime = min(timeQuantum, currentProcess.remainingTime);
        int startTime = currentTime;
        currentTime += executionTime;
        currentProcess.remainingTime -= executionTime;
        currentProcess.lastExecutionTime = currentTime;

        // Add to Gantt chart
        ganttChart.push_back({currentProcess.id, startTime, currentTime});

        // Add newly arrived processes to the queue
        while (nextProcess < n && processes[nextProcess].arrivalTime <= currentTime) {
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        // Re-add to queue if not finished
        if (currentProcess.remainingTime > 0) {
            readyQueue.push(currentIdx);
        } else {
            completedProcesses++;
            currentProcess.turnaroundTime = currentTime - currentProcess.arrivalTime;
        }
    }

    // Print Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "-----------\n";
    for (const auto& node : ganttChart) {
        cout << "| P" << node.pid << " ";
    }
    cout << "|\n";

    cout << "0";
    for (const auto& node : ganttChart) {
        cout << "    " << node.endTime;
    }
    cout << "\n";

    // Calculate and print results
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    cout << "\nProcess ID | Burst Time | Arrival Time | Waiting Time | Turnaround Time\n";
    cout << "----------------------------------------------------------------\n";

    for (const auto& p : processes) {
        cout << setw(10) << p.id << " | "
             << setw(10) << p.burstTime << " | "
             << setw(12) << p.arrivalTime << " | "
             << setw(12) << p.waitingTime << " | "
             << setw(15) << p.turnaroundTime << endl;

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i+1 << ":\n";
        cout << "Enter Process ID: ";
        cin >> processes[i].id;
        cout << "Enter Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Enter Arrival Time: ";
        cin >> processes[i].arrivalTime;
    }

    roundRobin(processes, timeQuantum);

    return 0;
}


