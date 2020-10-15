#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int ret;
    char* p;
    struct stat buf;

    ret = lstat(argv[1], &buf);

    if(-1 == ret) {
        perror("lstat"); 
        exit(EXIT_FAILURE);
    }

    switch(buf.st_mode & S_IFMT) {
        case S_IFSOCK:
            p = "socket";
            break;
        case S_IFLNK:
            p = "link";
            break;
        case S_IFREG:
            p = "regular";
            break;
        case S_IFDIR:
            p = "dir";
            break;
        case S_IFCHR:
            p = "char";
            break;
        case S_IFBLK:
            p = "block";
            break;
        case S_IFIFO:
            p = "fifo";
            break;
        default:
            break;
    }

    printf("%s\n", p);
    return 0;
}
