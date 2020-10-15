#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
 * unlink()函数是删除一个dentry
 * */

int main(int argc, char* argv[]) {
    int fd;
    int ret;
    const char* p = "unlink testing\n";
    const char* p2 = "after write something\n";

    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if(fd < 0) {
        perror("open"); 
        exit(EXIT_FAILURE);
    }

    ret = unlink("test.txt");  // 具备了被释放的条件

    if(ret < 0) {
        perror("unlink"); 
        exit(EXIT_FAILURE);
    }

    ret = write(fd, p, strlen(p));

    if(ret == -1) {
        perror("write"); 
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("---------------------DEBUG1------------\n");
    ret = write(fd, p2, strlen(p2));
    if(ret == -1) {
        perror("write"); 
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("----------------------DEBUG2------------\n");
    
    getchar();
    close(fd);

    return 0;
}
