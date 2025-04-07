#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime;
    int waitingTime = 0, turnaroundTime = 0, completionTime = 0;
    bool completed = false;
};

void resetProcesses(vector<Process>& original, vector<Process>& target) {
    target = original;
    for (auto& p : target) {
        p.waitingTime = 0;
        p.turnaroundTime = 0;
        p.completionTime = 0;
        p.completed = false;
    }
}

// FCFS Scheduling
void fcfs(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;
    float totalWait = 0, totalTurn = 0;

    for (auto& p : processes) {
        if (time < p.arrivalTime)
            time = p.arrivalTime;

        p.waitingTime = time - p.arrivalTime;
        time += p.burstTime;
        p.turnaroundTime = p.waitingTime + p.burstTime;
        p.completionTime = time;

        totalWait += p.waitingTime;
        totalTurn += p.turnaroundTime;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "ID\tAT\tBT\tWT\tTAT\n";
    for (auto p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "Avg Waiting Time: " << totalWait / processes.size() << endl;
    cout << "Avg Turnaround Time: " << totalTurn / processes.size() << endl;
}

// SJF Non-Preemptive Scheduling
void sjf(vector<Process> processes) {
    int time = 0, completed = 0;
    float totalWait = 0, totalTurn = 0;
    int n = processes.size();

    cout << "\n--- SJF (Non-Preemptive) Scheduling ---\n";

    while (completed < n) {
        int idx = -1;
        int shortest = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= time) {
                if (processes[i].burstTime < shortest) {
                    shortest = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        Process &p = processes[idx];
        p.waitingTime = time - p.arrivalTime;
        time += p.burstTime;
        p.turnaroundTime = p.waitingTime + p.burstTime;
        p.completionTime = time;
        p.completed = true;

        totalWait += p.waitingTime;
        totalTurn += p.turnaroundTime;
        completed++;
    }

    cout << "ID\tAT\tBT\tWT\tTAT\n";
    for (auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "Avg Waiting Time: " << totalWait / n << endl;
    cout << "Avg Turnaround Time: " << totalTurn / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> original(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "ID: ";
        cin >> original[i].id;
        cout << "Arrival Time: ";
        cin >> original[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> original[i].burstTime;
    }

    vector<Process> fcfsList, sjfList;

    resetProcesses(original, fcfsList);
    resetProcesses(original, sjfList);

    fcfs(fcfsList);
    sjf(sjfList);

    return 0;
}
