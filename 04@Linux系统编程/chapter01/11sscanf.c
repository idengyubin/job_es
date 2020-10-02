#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int a,b,c,d;
    char* ip = "192.168.1.1";
    FILE* fp = fopen("test1.txt", "w+");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    sscanf(ip, "%d.%d.%d.%d",&a, &b, &c, &d);
    fprintf(fp, "%d %d %d %d", a, b, c, d);
    fclose(fp);

    return 0;
}
