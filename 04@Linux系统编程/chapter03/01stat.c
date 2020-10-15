#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    struct stat buf;
    int ret;

    ret = stat("a.txt", &buf);
    if(-1 == ret) {
        perror("stat"); 
        exit(EXIT_FAILURE);
    }

    printf("st_ino = %d\n", buf.st_ino);
    printf("st_size = %d\n", buf.st_size);
    printf("st_nlink = %d\n", buf.st_nlink);
    printf("st_uid = %d\n", buf.st_uid);
    printf("st_gid = %d\n", buf.st_gid);
    printf("st_mode = %d\n", buf.st_mode);

    return 0;
}
