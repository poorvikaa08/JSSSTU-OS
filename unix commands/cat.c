#include<stdio.h>
#include<stdlib.h>

void main(int argc, char *argv[]) {
    FILE *fp;
    char ch;

    if(argc < 2) {
        printf("Error: File name not provided\n");
        exit(1);
    } else {
        fp = fopen(argv[1], "r");
        if(fp == NULL) {
            printf("Error: Could not open file %s\n", argv[1]);
            exit(1);
        }

        while((ch = fgetc(fp)) != EOF) {
            printf("%c", ch);
        }

        fclose(fp);
        pritf("\n");
    }
}