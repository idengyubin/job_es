#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(access("test.txt", F_OK)==0)   
        printf("File exist\n");
    else
        printf("File not exist\n");

    if(access("test.txt", R_OK)==0)  
        printf("File can read\n");
    else
        printf("File can not read\n");

    if(access("test.txt", W_OK)==0)  
        printf("File can write\n");
    else
        printf("File can not write\n");

    if(access("test.txt", X_OK)==0)  
        printf("File can exec\n");
    else
        printf("File can not exec\n");

    return 0;
}






























