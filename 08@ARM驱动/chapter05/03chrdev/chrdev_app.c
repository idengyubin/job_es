#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEV_NAME "/dev/chrdev_drv"

int main(int argc, char* argv[]) {
    int fd;
    int ret = 0;

    unsigned char recv_buf[1024] = {0};
    unsigned char send_buf[1024] = {1,2,3,4,5};

    fd = open(DEV_NAME, O_RDWR);

    if(fd < 0) {
        perror("open()"); 
        exit(EXIT_FAILURE);
   }

    ret = read(fd, recv_buf, 100);
    printf("read ret = %d\n", ret);

    ret = write(fd, send_buf, 100);
    printf("write ret = %d\n", ret);

    ret = lseek(fd, 10, SEEK_SET);
    printf("lseek ret = %d\n", ret);

    ret = ioctl(fd, 1, 0);
    printf("ioctl ret = %d\n", ret);

    close(fd);

    return 0;
}

