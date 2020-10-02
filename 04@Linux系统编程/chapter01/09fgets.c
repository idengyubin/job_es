#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char buf[1024] = {0};

    fp = fopen("test.txt", "r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while(fgets(buf, sizeof(buf), fp) != NULL)
        fputs(buf, stdout);

    fclose(fp);
    return 0;
}
