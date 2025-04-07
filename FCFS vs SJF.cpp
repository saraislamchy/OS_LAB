#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // for setprecision
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int waiting = 0;
    int turnAr = 0;
    int completion = 0;
    bool completed = false; // for SJF only
};

// ------------------- FCFS -----------------------
void fcfs(vector<Process>& processes) {
    sort(processes.begin(), processes.end(),
        [](Process a, Process b) {
            return a.arrival < b.arrival;
        });

    int currentTime = 0;
    float totalWait = 0, totalTurnAr = 0;
    cout << "\n--- FCFS Scheduling ---\n";
    cout << "Gantt Chart:\n";

    for (auto& p : processes) {
        if (currentTime < p.arrival)
            currentTime = p.arrival;

        cout << "|P" << p.id << " ";

        currentTime += p.burst;
        p.completion = currentTime;
        p.turnAr = p.completion - p.arrival;
        p.waiting = p.turnAr - p.burst;

        totalWait += p.waiting;
        totalTurnAr += p.turnAr;
    }

    cout << "|\n0";
    currentTime = 0;
    for (auto& p : processes) {
        if (currentTime < p.arrival)
            currentTime = p.arrival;
        currentTime += p.burst;
        cout << " " << currentTime;
    }

    cout << "\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnAround\n";
    for (auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t\t" << p.waiting << "\t" << p.turnAr << "\n";
    }

    int n = processes.size();
    cout << fixed << setprecision(2);
    cout << "Avg Waiting: " << totalWait / n << endl;
    cout << "Avg TurnAr: " << totalTurnAr / n << endl;
}

// ------------------- SJF (Non-Preemptive) -----------------------
void sjf(vector<Process> processes) {
    int time = 0, completed = 0;
    float totalWait = 0, totalTurn = 0;
    int n = processes.size();

    cout << "\n--- SJF (Non-Preemptive) Scheduling ---\n";

    while (completed < n) {
        int idx = -1;
        int shortest = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time) {
                if (processes[i].burst < shortest) {
                    shortest = processes[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        Process& p = processes[idx];
        p.waiting = time - p.arrival;
        time += p.burst;
        p.turnAr = p.waiting + p.burst;
        p.completion = time;
        p.completed = true;

        totalWait += p.waiting;
        totalTurn += p.turnAr;
        completed++;
    }

    cout << "Process\tArrival\tBurst\tCompletion\tWaiting\tTurnAround\n";
    for (auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t\t" << p.waiting << "\t" << p.turnAr << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "Avg Waiting Time: " << totalWait / n << endl;
    cout << "Avg Turnaround Time: " << totalTurn / n << endl;
}

int main() {
    int n;
    cout << "Enter number of Processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout << "Process ID: ";
        cin >> processes[i].id;
        cout << "Arrival Time: ";
        cin >> processes[i].arrival;
        cout << "Burst Time: ";
        cin >> processes[i].burst;
    }

    fcfs(processes);
    sjf(processes);

    return 0;
}
