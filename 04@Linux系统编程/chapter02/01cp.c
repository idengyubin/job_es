#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int fd1,fd2;
    char buf[1024];
    int len;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s <srcfile> <dstfile>\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    if((fd1 = open(argv[1], O_RDONLY)) < 0) {
        perror("open()"); 
        exit(EXIT_FAILURE);
    }

    if((fd2 = open(argv[2], O_CREAT | O_WRONLY, 0666)) < 0) {
        perror("open()"); 
        exit(EXIT_FAILURE);
    }

    while((len = read(fd1, buf, sizeof(buf))) != 0)
        write(fd2, buf, len);
    
    close(fd1);
    close(fd2);
}
