#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Process{
    int id;
    int arrival;
    int burst;
    int waiting;
    int turnAr;
    int completion;

};

void fcfs(vector<Process> &processes){
sort(processes.begin(), processes.end(),
     [](Process a, Process b){
     return a.arrival< b.arrival;
     });

     int currentTime =0;
     float totalWait=0, totalTurnAr=0;
     cout<<"Gantt Chart:"<<endl;

     for(auto &p: processes){
        if(currentTime<p.arrival)
            currentTime=p.arrival;

        int start= currentTime;
        currentTime += p.burst;

        p.completion = currentTime;
        p.turnAr = p.completion - p.arrival;
        p.waiting = p.turnAr - p.burst;

        totalWait += p.waiting;
        totalTurnAr +=p.turnAr;
        cout<<"|p" << p.id<<" ";
     }
             cout<<"\n";
             currentTime=0;
             cout<<"0";

             for(auto &p :processes){
                if(currentTime <p.arrival)
                    currentTime = p.arrival;
                currentTime += p.burst;
                cout<<" "<< currentTime;
             }

             cout<<"\n";
             cout<<"\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnAround\n";

             for(auto &p :processes){
                cout<<"p"<<p.id<<"\t"<<p.arrival<<"\t"<<p.burst<<"\t"<<p.completion<<"\t"<<p.waiting<<"\t"<<p.turnAr<<"\n";
             }
             int n= processes.size();
             cout<<"Avg Waiting:"<<totalWait;
             cout<<"Avg TurnAr: "<<totalTurnAr;
}
oid sjf(vector<Process> processes) {
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



int main(){
int n;
cout<<"Enter num of Processes:";
cin>>n;
vector<Process>processes(n);



for(int i=0;i<n;i++){
cout << "Enter details for process " << i + 1 << ":\n";

cout<<"Process ID:";
cin>>processes[i].id;
cout<<"Process Arrival:";
cin>>processes[i].arrival;
cout<<"Burst Time:";
cin>>processes[i].burst;

}
fcfs(processes);
sjf(processes);
return 0;
}
