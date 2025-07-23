#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct {
    int pid, AT, BT, ST, FT, TAT, WT;
    int priority;
} Process;
 
void priorityScheduling(Process *p, int n){
    int currTime = 0, idleTime = 0, completedCount = 0;
    int totalWT = 0, totalTAT = 0;

    printf("\nGantt Chart:\n");

    while(completedCount != n){
        int idx = -1;
        int highestPriority = INT_MAX; // or 1e9

        for(int i=0; i<n; i++){
            if(p[i].AT <= currTime && p[i].FT == 0){
                if(p[i].priority < highestPriority){
                    highestPriority = p[i].priority;
                    idx = i;
                } else if(p[i].priority == highestPriority){
                    if(idx == -1 || p[i].AT < p[idx].AT){
                        idx = i;
                    }
                }
            }
        }

        if(idx == -1){
            currTime++;
            idleTime++;
        } else {
            if(idleTime > 0){
                printf("Idle time from %d to %d\n", currTime - idleTime, currTime);
                idleTime = 0;
            }

            p[idx].ST = currTime;
            p[idx].FT = currTime + p[idx].BT;
            p[idx].WT = p[idx].ST - p[idx].AT;
            p[idx].TAT = p[idx].FT - p[idx].AT;

            currTime += p[idx].BT;

            totalTAT += p[idx].TAT;
            totalWT += p[idx].WT;
            completedCount++;

            printf("| (%d) P-%d (%d) ", p[idx].ST, p[idx].pid, currTime);
        }
    }

    printf("| \nObservation Table:\n");
    printf("PID\tAT\tBT\tST\tFT\tTAT\tWT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].FT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT/n);   
}

int main(){
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);


    Process *p = (Process*) malloc(n * sizeof(Process));

    for(int i=0; i<n; i++){
        printf("\nEnter the process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter the priority (lower number means higher priority): ");
        scanf("%d", &p[i].priority);

        printf("Enter the arrival time and burst time: ");
        scanf("%d %d", &p[i].AT, &p[i].BT);

        p[i].pid = i+1;
        p[i].ST = 0;
        p[i].FT = 0; 

        printf("\n");
    }

    priorityScheduling(p, n);
    free(p);

    return 0;
}
