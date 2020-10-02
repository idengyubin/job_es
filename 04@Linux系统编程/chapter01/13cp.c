#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp1;
    FILE* fp2;
    int len;
    char buf[1024];
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <srcfile> <dstfile>\n",argv[0]); 
        exit(EXIT_FAILURE);
    }

    fp1 = fopen(argv[1], "r");
    if(fp1 == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fp2 = fopen(argv[2], "w");
    if(fp2 == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }
    
    while((len = fread(buf, sizeof(char), sizeof(buf), fp1)) != 0)
        fwrite(buf, sizeof(char), len, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
