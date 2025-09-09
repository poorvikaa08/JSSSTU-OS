#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid, AT, BT, ST, FT, TAT, WT, RT;
    int priority;
}Process;

void priorityPremptiveScheduling(Process *p, int n) {
    int currTime = 0, completedProcesses = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Gantt Chart:\n");

    while (completedProcesses != n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= currTime && p[i].RT > 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
                if (p[i].priority == highestPriority) {
                    if (p[i].AT < p[idx].AT) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Set start time when process first executes
            if (p[idx].RT == p[idx].BT) {  // if(p[idx].ST == 0)
                p[idx].ST = currTime;
            }

            // Execute for 1 time unit
            p[idx].RT--;
            currTime++;

            // Check if process completedProcesses
            if (p[idx].RT == 0) {
                p[idx].FT = currTime;
                p[idx].TAT = p[idx].FT - p[idx].AT;
                p[idx].WT = p[idx].TAT - p[idx].BT;

                totalWT += p[idx].WT;
                totalTAT += p[idx].TAT;
                completedProcesses++;
            }
        } else {
            // CPU idle
            currTime++;
        }
        
        // Print Gantt chart
        if (idx != -1) {
            printf("| (%d)  P%d  (%d)  ", currTime-1, p[idx].pid, currTime);
        }
    }
    printf(" | \n\n");

    printf("Observation Table:\n");
    printf("PID\tAT\tBT\tPRIORITY\tST\tFT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].AT, p[i].BT, p[i].priority, p[i].ST, p[i].FT, p[i].WT, p[i].TAT);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}


int main() {
    int n;
    printf("Enter the number of processes: ");  
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));

    for(int i = 0; i < n; i++){
        printf("\nProcess %d:\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].BT);
        printf("Enter Priority: ");
        scanf("%d", &p[i].priority);
        
        p[i].pid = i + 1;
        p[i].RT = p[i].BT;      // Remaining time = Burst time initially
        p[i].ST = 0;            // Start time
        p[i].FT = 0;            // Finish time
    }
    printf("\n");

    priorityPremptiveScheduling(p, n);
    free(p);

    return 0;
}