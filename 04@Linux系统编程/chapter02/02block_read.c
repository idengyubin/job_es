#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char buf[10];
    int fd, len;

    len = read(STDIN_FILENO, buf, 10);
    if(len < 0) {
        perror("read()"); 
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO, buf, len);
    return 0;
}
