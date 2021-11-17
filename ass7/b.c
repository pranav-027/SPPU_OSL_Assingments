#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    int x, y, ret, ret_v;
    long int add;
    int shmid;
    int *shmptr;
    key_t key;
    pid_t pid;

    printf("\nEnter a number:");
    scanf("%d", &x);

    key = ftok(".", 'M');

    shmid = shmget(key, sizeof(x), IPC_CREAT | 0666);
    if (shmid < 0)
    {
        printf("\nShared memory creation error!");
        _exit(-1);
    }

    printf("\nShared Memory is Created.");
    printf("\nShmid is:%d", shmid);

    shmptr = (int *)shmat(shmid, 0, 0);
    add = (int)shmptr;
    if (add != -1)
        printf("\nShared Memory is attached at address:%u", shmptr);
    else
    {
        printf("\nShared Memory not attached!");
        _exit(-1);
    }

    *shmptr = x;
    ret = shmdt((void *)shmptr);
    if (ret == 0)
        printf("\nShared Memory detached successfully\n");

    pid = fork();

    if (pid == 0)
    {
        printf("\n-----------------------------------------------\nThis is Child Process\n-----------------------------------------------");
        shmptr = (int *)shmat(shmid, 0, 0);
        add = (int)shmptr;
        if (add != -1)
            printf("\nShared Memory is attached at address:%u", shmptr);
        else
        {
            printf("\nShared Memory not attached!");
            _exit(-1);
        }
        y = *shmptr;
        printf("\nThe data read is:%d", y);
        ret = shmdt((void *)shmptr);
        if (ret == 0)
            printf("\nShared Memory detached successfully\n");
        ret_v = shmctl(shmid, IPC_RMID, 0);
        if (ret_v == 0)
            printf("\nShared Memory removed successfully!\n\n");
        printf("-----------------------------------------------\n");
    }
    else
    {
        wait(0);
    }
    return 0;
}
