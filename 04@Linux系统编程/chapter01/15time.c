#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char buf[64];
    time_t t;
    if((fp = fopen("test.txt","w+")) == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while(1) {
        t = time(NULL);
        fprintf(fp, "%s",asctime(localtime(&t)));
        fflush(NULL);
        printf("%s",asctime(localtime(&t)));
        sleep(1);
    }
    fclose(fp);

    return 0;
}
