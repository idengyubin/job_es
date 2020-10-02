#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char buf[64] = {0};

    int i;
    fp = fopen("test.txt", "w+b");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fwrite(a, sizeof(a[0]), sizeof(a) / sizeof(a[0]), fp);

    fclose(fp);
    return 0;
}
