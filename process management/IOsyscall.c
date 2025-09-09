    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #define SIZE 30

    void main(){
        int fd, n;
        char buffer[SIZE];

        fd = open("file.txt", O_RDWR);
        printf("File descriptor: %d\n", fd);

        if(!(fd + 1)){ // fd == -1
            printf("Failed to open file\n");
            exit(1);
        }

        
        printf("Reading first 10 characters from file\n");
        n = read(fd, buffer, 10);
        write(1, buffer, n);

        printf("Skipping 5 characters from the current position\n");
        lseek(fd, 5, SEEK_CUR);

        printf("\nGoing to 5th last character in the file:\n");
        lseek(fd, -5, SEEK_END);
        n = read(fd, buffer,7);
        write(1, buffer, n);

        printf("\nGoing to 3rd character in the file:\n");
        lseek(fd, 3, SEEK_SET);
        n = read(fd,buffer,5);
        write(1, buffer, n);

        printf("\n");
        return 0;

    }

