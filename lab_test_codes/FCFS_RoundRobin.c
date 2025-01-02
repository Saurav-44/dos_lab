#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    int remainingTime; // For RR
} Process;

void printGanttChart(int *processOrder, int *timePoints, int size) {
    printf("\nGantt Chart:\n");

    // Print top border
    printf(" ");
    for (int i = 0; i < size; i++) {
        printf("-------");
    }
    printf("-\n");

    // Print process labels
    printf("|");
    for (int i = 0; i < size; i++) {
        printf(" P%-3d |", processOrder[i]);
    }
    printf("\n");

    // Print bottom border
    printf(" ");
    for (int i = 0; i < size; i++) {
        printf("-------");
    }
    printf("-\n");

    // Print time points
    for (int i = 0; i <= size; i++) {
        printf("%-6d", timePoints[i]);
    }
    printf("\n");
}

void fcfs(Process processes[], int n) {
    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    int processOrder[n];
    int timePoints[n + 1];

    timePoints[0] = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime; // Wait for the process to arrive

        processes[i].responseTime = currentTime - processes[i].arrivalTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        totalResponseTime += processes[i].responseTime;

        processOrder[i] = i + 1;
        currentTime += processes[i].burstTime;
        timePoints[i + 1] = currentTime;
    }

    printGanttChart(processOrder, timePoints, n);

    printf("\nAverage Waiting Time: %.2f ms\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f ms\n", totalTurnaroundTime / n);
    printf("Average Response Time: %.2f ms\n", totalResponseTime / n);
}

void roundRobin(Process processes[], int n, int timeQuantum) {
    int currentTime = 0, remainingProcesses = n;
    int queue[n], front = 0, rear = 0;
    bool inQueue[n];
    float totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    int processOrder[100];
    int timePoints[101];
    int orderIndex = 0;

    for (int i = 0; i < n; i++) inQueue[i] = false;

    // Start with the first process
    queue[rear++] = 0;
    inQueue[0] = true;

    timePoints[0] = 0;

    while (remainingProcesses > 0) {
        int i = queue[front++ % n]; // Dequeue

        if (processes[i].remainingTime > 0) {
            if (currentTime < processes[i].arrivalTime)
                currentTime = processes[i].arrivalTime; // Wait if no process is ready

            if (processes[i].remainingTime > timeQuantum) {
                processOrder[orderIndex] = i + 1;
                currentTime += timeQuantum;
                processes[i].remainingTime -= timeQuantum;
            } else {
                processOrder[orderIndex] = i + 1;
                currentTime += processes[i].remainingTime;
                processes[i].remainingTime = 0;
                processes[i].completionTime = currentTime;
                processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                processes[i].responseTime = processes[i].waitingTime;

                totalWaitingTime += processes[i].waitingTime;
                totalTurnaroundTime += processes[i].turnaroundTime;
                totalResponseTime += processes[i].responseTime;
                remainingProcesses--;
            }
            timePoints[orderIndex + 1] = currentTime;
            orderIndex++;
        }

        // Add newly arrived processes to the queue
        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0) {
                queue[rear++ % n] = j;
                inQueue[j] = true;
            }
        }

        // Requeue the current process if it has remaining time
        if (processes[i].remainingTime > 0) {
            queue[rear++ % n] = i;
        }
    }

    printGanttChart(processOrder, timePoints, orderIndex);

    printf("\nAverage Waiting Time: %.2f ms\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f ms\n", totalTurnaroundTime / n);
    printf("Average Response Time: %.2f ms\n", totalResponseTime / n);
}

int main() {
    int choice, n, timeQuantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    printf("Enter process details (Arrival Time, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    while (true) {
        printf("\nCPU Scheduling Menu:\n");
        printf("1. First-Come-First-Served (FCFS)\n");
        printf("2. Round Robin (RR)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(processes, n);
                break;
            case 2:
                printf("Enter time quantum: ");
                scanf("%d", &timeQuantum);
                roundRobin(processes, n, timeQuantum);
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
