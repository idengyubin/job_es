#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DEV_NAME "dev/chrdev_btn"

int main(int argc, char* argv[]) {
    int fd = 0;
    int ret = 0;

    unsigned char recv_buf[10] = {"0000"};
    
    fd = open(DEV_NAME, O_RDONLY);
    if(fd < 0) {
        perror("open"); 
        exit(EXIT_FAILURE);
    }

    while(1) {
        strcpy(recv_buf, "0000"); 
        ret = read(fd, recv_buf, 4);
        if(ret < 0 && (errno != EAGAIN)) {
            perror("read"); 
            exit(EXIT_FAILURE);
        }

        printf("recv_buf = %s\n", recv_buf);
    }

    return 0;
}
