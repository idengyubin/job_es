#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    
    if(link(argv[1], argv[2]) == -1) {
        perror("link"); 
        exit(EXIT_FAILURE);
    }

    if(unlink(argv[1]) == -1) {
        perror("unlink"); 
        exit(EXIT_FAILURE);
    }

    return 0;
}
