#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    int nElem = argc - 3;
    char *args_1[nElem + 1];
    char *args_2[nElem + 1];
    int i, j = 3;
    printf("nElem=%d\n", nElem);
    args_1[0] = argv[1];
    args_2[0] = argv[2];
    for (i = 1; i <= nElem; i++)
    {
        args_1[i] = argv[j];
        args_2[i] = argv[j];
        j++;
    }
    args_1[i] = (char *)0;
    args_2[i] = (char *)0;
    pid = fork();
    if (pid == 0)
    {
        execv(argv[1], args_1);
    }
    else
    {
        wait(NULL);
        execv(argv[2], args_2);
    }
    return 0;
}
