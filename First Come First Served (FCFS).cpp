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
    int completionTime;
};

struct GanttNode {
    int pid;
    int startTime;
    int endTime;
};

void fcfsScheduling(vector<Process>& processes) {
    // Sort processes by arrival time (FCFS)
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

    vector<GanttNode> ganttChart;
    int currentTime = 0;

    for (auto& p : processes) {
        // If process arrives after current time, wait for it
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }

        // Record start time
        int startTime = currentTime;

        // Execute process to completion (non-preemptive)
        currentTime += p.burstTime;

        // Calculate metrics
        p.completionTime = currentTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;

        // Add to Gantt chart
        ganttChart.push_back({p.id, startTime, currentTime});
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
    int n = processes.size();

    cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n";
    cout << "--------------------------------------------------------------------------------\n";

    for (const auto& p : processes) {
        cout << setw(10) << p.id << " | "
             << setw(12) << p.arrivalTime << " | "
             << setw(10) << p.burstTime << " | "
             << setw(15) << p.completionTime << " | "
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
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i+1 << ":\n";
        cout << "Enter Process ID: ";
        cin >> processes[i].id;
        cout << "Enter Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time: ";
        cin >> processes[i].burstTime;
    }

    fcfsScheduling(processes);

    return 0;
}
