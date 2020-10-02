#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char c;
    fp = fopen("test.txt","r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }
    while((c = fgetc(fp)) != EOF)
        fputc(c, stdout);

    fclose(fp);
    return 0;
}
