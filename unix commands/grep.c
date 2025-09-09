#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
    char filename[20], pattern[20], temp[30];
    FILE *fp;

    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the pattern to search: ");
    scanf("%s", pattern);

    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    while(!feof(fp)) {
        fgets(temp, 30, fp);
        if(strstr(temp, pattern) != NULL) {
            printf("%s", temp);
        }
    }
    fclose(fp);
    printf("\n");
}