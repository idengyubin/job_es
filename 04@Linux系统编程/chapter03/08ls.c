#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* dp;
    struct dirent* item;
    int cnt = 0;

    if(argc == 1) {
        dp = opendir("."); 
        if(NULL == dp) {
            perror("opendir"); 
            exit(EXIT_FAILURE);
        }
    } else if(argc == 2) {
        dp = opendir(argv[1]); 
        if(NULL == dp) {
            perror("opendir"); 
            exit(EXIT_FAILURE);
        }
    }

    while(item = readdir(dp)) {
        if(item->d_name[0] != '.') {
            printf("%-10s%c", item->d_name, ++cnt % 5 ?'\t': '\n'); 
        }
    }
    
    putchar('\n');

    closedir(dp);
    return 0;
}
