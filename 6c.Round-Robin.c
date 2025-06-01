#include <stdio.h>

int main() {
    int n, i, time = 0, tq;
    int remaining[20], bt[20], wt[20] = {0}, tat[20], ct[20];
    int completed = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        remaining[i] = bt[i]; // Initialize remaining burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (remaining[i] <= tq) {
                    time += remaining[i];
                    remaining[i] = 0;
                    ct[i] = time;
                    completed++;
                } else {
                    time += tq;
                    remaining[i] -= tq;
                }
            }
        }
    }

    // Calculate turnaround time and waiting time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
    }

    float avg_wt = 0, avg_tat = 0;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
