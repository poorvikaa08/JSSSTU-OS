#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pid, AT, BT, ST, FT, TAT, WT;
    int isCompleted;
} Process;

void sjfNonPremptiveScheduling(Process *p, int n);

int main(){
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);


    Process *p = (Process*) malloc(n * sizeof(Process));

    for(int i=0; i<n; i++){
        printf("\nEnter the process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter the arrival time and burst time: ");
        scanf("%d %d", &p[i].AT, &p[i].BT);

        p[i].isCompleted = 0; // Initialize completed status
        printf("\n");
    }

    sjfNonPremptiveScheduling(p, n);
    free(p);

    return 0;
}

void sjfNonPremptiveScheduling(Process *p, int n){
    int currTime = 0, completedCount = 0;
    int totalWT = 0, totalTAT = 0;

    printf("\nGantt Chart:\n");

    while(completedCount < n){
        int idx = -1, minBT = INT_MAX; //or 1e9
        
        for(int i=0; i<n; i++){
            if(p[i].AT <= currTime && !p[i].isCompleted && p[i].BT < minBT){
                minBT = p[i].BT;
                idx = i;
            }
        }

        if(idx == -1)
            currTime++; // No process is ready, increment time
        else {
            p[idx].ST = currTime;
            p[idx].FT = currTime + p[idx].BT;
            p[idx].WT = p[idx].ST - p[idx].AT;
            p[idx].TAT = p[idx].FT - p[idx].AT;
            p[idx].isCompleted = 1; // Mark process as completed
            currTime = p[idx].FT;
            completedCount++;

            printf("| (%d)  P-%d  (%d) ", p[idx].ST, p[idx].pid, p[idx].FT);
            totalWT += p[idx].WT;
            totalTAT += p[idx].TAT;
        }
    }

    printf("|\n\n");
    printf("Observation Table:\n");
    printf("Process ID\tAT\tBT\tST\tFT\tTAT\tWT\n");

    for(int i=0; i<n; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].FT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT/n);
}