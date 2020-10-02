#include <stdio.h>

int main(int argc, char* argv[]) {
    fprintf(stdout, "%s", "This is stdout:HelloWorld!\n");
    fprintf(stderr, "%s", "This is stderr:HelloWorld!\n");

    return 0;
}
