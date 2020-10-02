#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define SIZE 100

int main(int argc, char* argv[]) {
    int fd;

    if((fd = open("test.txt", O_WRONLY | O_CREAT, 0666)) < 0) {
        perror("open"); 
        exit(EXIT_FAILURE);
    }

    lseek(fd, SIZE, SEEK_END);
    write(fd, "Test", 5);

    close(fd);
    return 0;
}
