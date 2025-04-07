#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

struct Process {
    int id, bt, at, prio;
    int wt = 0, tat = 0;
};

void printTable(string algo, vector<Process>& pList) {
    float totalWT = 0, totalTAT = 0;
    cout << "\n[" << algo << "]\n";
    cout << "ID\tBT\tAT\tWT\tTAT\n";
    for (auto& p : pList) {
        cout << p.id << "\t" << p.bt << "\t" << p.at << "\t" << p.wt << "\t" << p.tat << "\n";
        totalWT += p.wt;
        totalTAT += p.tat;
    }
    cout << fixed << setprecision(2);
    cout << "Avg WT: " << totalWT / pList.size()
         << " | Avg TAT: " << totalTAT / pList.size() << "\n";
}

// FCFS
void FCFS(vector<Process> pList) {
    sort(pList.begin(), pList.end(), [](auto a, auto b) { return a.at < b.at; });
    int time = 0;
    for (auto& p : pList) {
        time = max(time, p.at);
        p.wt = time - p.at;
        time += p.bt;
        p.tat = p.wt + p.bt;
    }
    printTable("FCFS", pList);
}

// SJF (non-preemptive)
void SJF(vector<Process> pList) {
    int time = 0, completed = 0, n = pList.size();
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && pList[i].at <= time && pList[i].bt < minBT) {
                minBT = pList[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        pList[idx].wt = time - pList[idx].at;
        time += pList[idx].bt;
        pList[idx].tat = pList[idx].wt + pList[idx].bt;
        done[idx] = true;
        completed++;
    }
    printTable("SJF", pList);
}

// Round Robin
void RoundRobin(vector<Process> pList, int tq) {
    int time = 0, n = pList.size(), rem[n];
    for (int i = 0; i < n; i++) rem[i] = pList[i].bt;
    queue<int> q;
    vector<bool> visited(n, false);
    int done = 0;
    q.push(0); visited[0] = true;

    while (done < n) {
        if (q.empty()) {
            for (int i = 0; i < n; i++) {
                if (!visited[i] && pList[i].at <= time) {
                    q.push(i); visited[i] = true;
                    break;
                }
            }
            if (q.empty()) { time++; continue; }
        }

        int i = q.front(); q.pop();
        int exec = min(tq, rem[i]);
        rem[i] -= exec;
        time += exec;

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!visited[j] && pList[j].at <= time) {
                q.push(j); visited[j] = true;
            }
        }

        if (rem[i] > 0) q.push(i);
        else {
            pList[i].tat = time - pList[i].at;
            pList[i].wt = pList[i].tat - pList[i].bt;
            done++;
        }
    }
    printTable("Round Robin", pList);
}

// Priority (non-preemptive)
void Priority(vector<Process> pList) {
    int time = 0, completed = 0, n = pList.size();
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, bestP = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && pList[i].at <= time && pList[i].prio < bestP) {
                bestP = pList[i].prio;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        pList[idx].wt = time - pList[idx].at;
        time += pList[idx].bt;
        pList[idx].tat = pList[idx].wt + pList[idx].bt;
        done[idx] = true;
        completed++;
    }
    printTable("Priority", pList);
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum (for RR): ";
    cin >> tq;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i+1 << " ID: ";
        cin >> processes[i].id;
        cout << "Burst Time: ";
        cin >> processes[i].bt;
        cout << "Arrival Time: ";
        cin >> processes[i].at;
        cout << "Priority (lower is higher): ";
        cin >> processes[i].prio;
    }

    FCFS(processes);
    SJF(processes);
    RoundRobin(processes, tq);
    Priority(processes);

    return 0;
}

