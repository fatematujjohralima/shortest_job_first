#include <stdio.h>

struct Process {
    int pid;            
    int arrivalTime;    
    int burstTime;      
    int completionTime; 
    int turnaroundTime; 
    int waitingTime;    
};

void calculateCompletionTime(struct Process proc[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }
        currentTime += proc[i].burstTime;
        proc[i].completionTime = currentTime;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
    }
}

void calculateWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
    }
}

void displayProcesses(struct Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrivalTime,
               proc[i].burstTime,
               proc[i].completionTime,
               proc[i].turnaroundTime,
               proc[i].waitingTime);
    }
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burstTime);
        proc[i].pid = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrivalTime > proc[j + 1].arrivalTime) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    calculateCompletionTime(proc, n);

    calculateTurnaroundTime(proc, n);

    calculateWaitingTime(proc, n);

    displayProcesses(proc, n);

    float avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgTurnaroundTime += proc[i].turnaroundTime;
    }
    avgTurnaroundTime /= n;

    float avgWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += proc[i].waitingTime;
    }
    avgWaitingTime /= n;

    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}
