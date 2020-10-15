#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPATH 100

int main(int argc, char* argv[]) {
    char buffer[MAXPATH] = {0};
    getcwd(buffer, sizeof(buffer));

    printf("The current path is: %s\n", buffer);

    return 0;
}
