#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc,char* argv[]) {
    FILE* fp;
    fp = fopen("test1.txt","rb");
    if(NULL == fp) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fclose(fp);    
    return 0;
}
