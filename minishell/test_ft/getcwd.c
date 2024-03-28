#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // for printf

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 100);
    printf("pwd: %s\n", pwd);
	free(pwd);
    return (0);
}