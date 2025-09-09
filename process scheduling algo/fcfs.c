#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int pid, AT, BT, CT, TAT, WT;
}Process;

void fcfs(Process *p, int n){
    int elapsedTime = 0, totalWT = 0, totalTAT = 0;

    printf("\nGantt Chart:\n");
    for(int i=0; i<n; i++){
        if(elapsedTime < p[i].AT){
            elapsedTime = p[i].AT;
        }

        p[i].WT = elapsedTime - p[i].AT;
        elapsedTime += p[i].BT;
        p[i].TAT = elapsedTime - p[i].AT;
        p[i].CT = elapsedTime;

        
        printf("| (%d)  P-%d  (%d)", elapsedTime-p[i].BT, p[i].pid, elapsedTime);

    }
    printf(" |\n");

    printf("\nObservation Table:\n");
    printf("Process ID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0; i<n; i++){ 
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT/n);
}


void main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *p = (Process *)malloc(n * sizeof(Process));

    for(int i=0; i<n; i++){
        printf("\nEnter the process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter the arrival time and burst time: ");
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }

    // Sort processes by arrival time
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].AT > p[j+1].AT){
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    fcfs(p, n);
    free(p);
}

