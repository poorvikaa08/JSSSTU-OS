#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid, AT, BT, ST, FT, TAT, WT, RT;
    int isCompleted;
} Process;

void sjfPremptiveScheduling(Process *p, int n){
    int currTime = 0, completedCount = 0;
    int totalWT = 0, totalTAT = 0;
    int prevProcess = -1;

    printf("\nGantt Chart:\n");

    while(completedCount < n){
        int idx = -1, minRT = INT_MAX;
        
        // Find process with shortest remaining time
        for(int i = 0; i < n; i++){
            if(p[i].AT <= currTime && !p[i].isCompleted && p[i].RT < minRT){
                minRT = p[i].RT;
                idx = i;
            }
        }

        if(idx == -1) {
            // No process is ready, CPU is idle
            currTime++;
        }
        else {
            // Set start time for first execution
            if(p[idx].ST == -1){
                p[idx].ST = currTime;
            }
            // Print Gantt chart entry when process changes
            if(prevProcess != idx && prevProcess != -1){
                printf("| (%d)  P-%d  ", currTime - 1, p[prevProcess].pid);
            }
            
            // Execute process for 1 time unit
            p[idx].RT--;
            currTime++;
            
            // Check if process is completed
            if(p[idx].RT == 0){
                p[idx].FT = currTime;
                p[idx].TAT = p[idx].FT - p[idx].AT;
                p[idx].WT = p[idx].TAT - p[idx].BT;
                p[idx].isCompleted = 1;
                completedCount++;
                
                printf("| (%d)  P-%d  (%d) ", p[idx].ST, p[idx].pid, p[idx].FT);
                
                totalWT += p[idx].WT;
                totalTAT += p[idx].TAT;
            }
            
            prevProcess = idx;
        }
    }

    printf("|\n\n");

    // Print observation table
    printf("Observation Table:\n");
    printf("Process ID\tAT\tBT\tST\tFT\tTAT\tWT\n");

    for(int i = 0; i < n; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].FT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT/n);
}

void main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));

    for(int i=0; i<n; i++){
        printf("\nEnter the process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter the arrival time and burst time: ");
        scanf("%d %d", &p[i].AT, &p[i].BT);

        p[i].isCompleted = 0; // Initialize completed status
        p[i].ST = -1;
        p[i].RT = p[i].BT; // Initialize remaining time
        printf("\n");
    }

    sjfPremptiveScheduling(p, n);
    free(p);
}