#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int is_alpha(char c) {
    if((c > 'a' && c < 'z') || (c > 'A' && c < 'Z')) 
        return 1;
    else 
        return 0;
}

int main(int argc, char* argv[]) {
    FILE* fp;
    char c;
    fp = fopen("test.txt", "r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while((c = (char)fgetc(fp)) != EOF) {
        if(is_alpha(c)) 
            fputc(c, stdout);
    }

    fclose(fp);

    return 0;
}
