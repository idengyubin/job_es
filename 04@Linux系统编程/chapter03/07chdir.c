#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char buf[1024] ;

    if(chdir("/") == -1) {
        perror("chdir"); 
        exit(EXIT_FAILURE);
    }

    if(getcwd(buf, 1024) == NULL) {
        perror("getcwd"); 
        exit(EXIT_FAILURE);
    }

    printf("pwd = %s\n", buf);

    return 0;
}
