#include <stdio.h>

int main() {
    int n, i, j;
    int burst_time[20], process[20], wait_time[20], turnaround_time[20];
    float avg_wait_time = 0, avg_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &burst_time[i]);
        process[i] = i + 1; // Store process ID
    }

    // Sort by burst time (Selection sort)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burst_time[i] > burst_time[j]) {
                // Swap burst time
                int temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process ID
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    wait_time[0] = 0; // First process has 0 waiting time

    // Calculate waiting time
    for (i = 1; i < n; i++) {
        wait_time[i] = wait_time[i - 1] + burst_time[i - 1];
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        turnaround_time[i] = wait_time[i] + burst_time[i];
    }

    // Output and averages
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\n", process[i], burst_time[i], wait_time[i], turnaround_time[i]);
        avg_wait_time += wait_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_wait_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wait_time);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turnaround_time);

    return 0;
}
