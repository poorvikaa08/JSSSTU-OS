#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int ID, AT, BT, CT, TAT, WT, flag;
} Process;

Process p[15];
int tempBurstTime[15];  // Store original burst times

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                swap(&p[j], &p[j+1]);
            }
        }
    }
}

void roundRobin(int n, int quantum) {
    int completed = 0, curindex, curtime = p[0].AT;
    int *waitqueue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    
    int total_wt = 0, total_tat = 0;
    // Add first process to queue
    waitqueue[rear] = 0;
    p[0].flag = 1;
    
    printf("\nGantt Chart:\n");
    
    while(completed != n) {
        curindex = waitqueue[front];
        front = (front + 1) % n;
        
        if(p[curindex].BT > quantum) {
            // Process runs for full quantum
            p[curindex].BT -= quantum;
            curtime += quantum;
            printf("| P%d (%d) %d ", p[curindex].ID, quantum, curtime);
        } else {
            // Process completes
            curtime += p[curindex].BT;
            printf("| P%d (%d) %d ", p[curindex].ID, p[curindex].BT, curtime);
            
            p[curindex].CT = curtime;
            p[curindex].TAT = p[curindex].CT - p[curindex].AT;
            p[curindex].WT = p[curindex].TAT - tempBurstTime[p[curindex].ID - 1];
            
            total_tat += p[curindex].TAT;
            total_wt += p[curindex].WT;
            
            p[curindex].BT = 0;
            completed++;
        }
        
        // Add newly arrived processes to queue
        for(int i = 0; i < n && p[i].AT <= curtime; i++) {
            if(i == curindex || p[i].flag == 1 || p[i].BT == 0)
                continue;
            rear = (rear + 1) % n;
            p[i].flag = 1;
            waitqueue[rear] = i;
        }
        
        // Re-add current process if not completed
        if(p[curindex].BT > 0) {
            rear = (rear + 1) % n;
            waitqueue[rear] = curindex;
        }
    }
    
    printf("|\n\n");
    
    // Calculate averages
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    
    // Display results
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].ID, p[i].AT, tempBurstTime[i], p[i].CT, p[i].TAT, p[i].WT);
    }
    
    printf("\nAverage TAT = %.2f\n", avg_tat);
    printf("Average WT = %.2f\n", avg_wt);
    
    free(waitqueue);
}

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter arrival time and burst time:\n");
    printf("AT BT\n");
    for(int i = 0; i < n; i++) {
        p[i].ID = i + 1;
        scanf("%d %d", &p[i].AT, &p[i].BT);
        tempBurstTime[i] = p[i].BT;  // Store original burst time
        p[i].flag = 0;  // Not in queue
    }
    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    
    sort(n);  // Sort by arrival time
    
    roundRobin(n, quantum);
    return 0;
}