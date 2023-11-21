#include <stdio.h>

#define MAX_RESOURCES 3
#define MAX_PROCESSES 3

int available[MAX_RESOURCES] = {10, 5, 7};  
int max_claim[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2}
};  
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2}
};  
int need[MAX_PROCESSES][MAX_RESOURCES];  

int isSafe(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i]) {
            return 0;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) {
            return 0;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    return 1;
}

void resourceRequest(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return;
        }
    }

    if (isSafe(process, request)) {
        printf("Request granted. Executing process %d.\n", process);
    } else {
        printf("Request denied. Process %d must wait to avoid deadlock.\n", process);
    }
}

int main() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }

    int process;
    int request[MAX_RESOURCES];

    process = 0;
    printf("Enter resource request for process %d: ", process);
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }
    resourceRequest(process, request);

    process = 1;
    printf("Enter resource request for process %d: ", process);
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }
    resourceRequest(process, request);

    process = 2;
    printf("Enter resource request for process %d: ", process);
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }
    resourceRequest(process, request);

    return 0;
}
