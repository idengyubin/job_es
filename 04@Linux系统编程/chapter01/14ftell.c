#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    int size;
    fp = fopen("test.txt", "r");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    printf("size = %d\n", size);
    fclose(fp);
    return 0;
}
