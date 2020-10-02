#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd, len;
    char buf[10];

    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if(fd < 0) {
        perror("open()"); 
        exit(EXIT_FAILURE);
    }

tryagain:
    len = read(fd, buf, 10);
    if(len < 0) {
        if(errno != EAGAIN) {
            perror("read()"); 
            exit(EXIT_FAILURE);
        }
        sleep(3);
        write(STDOUT_FILENO, "Try again", strlen("Try again"));
        goto tryagain;
    }

    write(STDOUT_FILENO, buf, len);

    return 0;
}
