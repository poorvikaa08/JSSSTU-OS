#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;

    if (argc < 2){
        printf("\nError! You are not passing the directory\n");
        printf("Usage: %s <directory_path>\n", argv[0]);
        exit(1);
    }

    dp = opendir(argv[1]);
    if (dp == NULL){
        printf("\nFailed to open directory %s\n", argv[1]);
        exit(1);
    }

    printf("Contents of directory %s:\n", argv[1]);
    
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    
    closedir(dp);
    return 0;
}