#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
    FILE* fp;
    fp = fopen("test.txt","w+b");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fclose(fp);    
    return 0;
}
