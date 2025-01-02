#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

// Function to calculate the need matrix
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if a request can be granted immediately
bool canRequestBeGranted(int process, int request[MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int m) {
    for (int j = 0; j < m; j++) {
        if (request[j] > need[process][j] || request[j] > available[j]) {
            return false;
        }
    }
    return true;
}

// Function to check if the system is in a safe state
bool isSafeState(int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int n, int m, int safeSequence[MAX_PROCESSES]) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // System is not in a safe state
        }
    }
    return true;
}

int main() {
    int n = 5; // Number of processes
    int m = 4; // Number of resources

    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 0, 1, 2},
        {2, 0, 0, 0},
        {0, 0, 3, 4},
        {2, 3, 5, 4},
        {0, 3, 3, 2}
    };
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 0, 1, 2},
        {2, 7, 5, 0},
        {6, 6, 5, 6},
        {4, 3, 5, 6},
        {0, 6, 5, 2}
    };

    int available[MAX_RESOURCES] = {6, 7, 12, 12};

    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, n, m);

    // Part (a): Print the Need Matrix
    printf("(a) Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Part (b): Check if the system is in a safe state
    int safeSequence[MAX_PROCESSES];
    printf("\n(b) ");
    if (isSafeState(allocation, need, available, n, m, safeSequence)) {
        printf("The system is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i] + 1);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    // Part (c): Check resource request for P3
    int process = 2; // P3 (zero-indexed)
    int request[MAX_RESOURCES] = {0, 1, 0, 0};
    printf("\n(c) Request by P3: ");
    for (int j = 0; j < m; j++) {
        printf("%d ", request[j]);
    }
    printf("\n");

    if (canRequestBeGranted(process, request, allocation, need, available, m)) {
        // Temporarily allocate resources
        for (int j = 0; j < m; j++) {
            available[j] -= request[j];
            allocation[process][j] += request[j];
            need[process][j] -= request[j];
        }

        if (isSafeState(allocation, need, available, n, m, safeSequence)) {
            printf("The request can be granted immediately.\n");
        } else {
            printf("The request cannot be granted immediately as it leads to an unsafe state.\n");
        }

        // Revert temporary allocation
        for (int j = 0; j < m; j++) {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
    } else {
        printf("The request cannot be granted as it exceeds the available or needed resources.\n");
    }

    return 0;
}
