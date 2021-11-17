#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

void *reader(void *);
void *writer(void *);

int getItemforBuff();
void readItemfromBuff(int buffer);

int buffer;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;

int flag = 0;
int read_count = 0;

int main()
{
    pthread_t rd1_tid;
    pthread_t wr_tid;
    pthread_t rd2_tid;

    pthread_create(&wr_tid, NULL, writer, NULL);
    pthread_create(&rd1_tid, NULL, reader, NULL);
    pthread_create(&rd2_tid, NULL, reader, NULL);

    pthread_join(wr_tid, NULL);
    pthread_join(rd1_tid, NULL);
    pthread_join(rd2_tid, NULL);

    return 0;
}

void *reader(void *argp)
{
    while (1)
    {
        pthread_mutex_lock(&mutex1);
        read_count++;

        if (read_count == 1)
        {
            pthread_mutex_lock(&wrt);
        }

        pthread_mutex_unlock(&mutex1);

        if (flag == 1)
        {
            readItemfromBuff(buffer);
            sleep(1);
            flag = 0;
        }

        pthread_mutex_lock(&mutex1);
        read_count--;
        if (read_count == 0)
        {
            pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex1);
    }
}

void *writer(void *argp)
{
    while (1)
    {
        pthread_mutex_lock(&mutex1);
        if (flag == 0)
        {
            buffer = getItemforBuff();
            flag = 1;
        }
        pthread_mutex_unlock(&mutex1);
    }
}

int getItemforBuff()
{
    int item;

    printf("writer:enter an item into buffer\n");
    scanf("%d", &item);

    return item;
}

void readItemfromBuff(int buffer)
{
    printf("thread=%ld\n", syscall(SYS_gettid));
    printf("reader:read item from buffer=%d\n", buffer);
}

/*     output
 
 (base) student@student-OptiPlex-390:~$ gcc assg5.c -lpthread
(base) student@student-OptiPlex-390:~$ ./a.out
writer:enter an item into buffer
4
thread=2752
reader:read item from buffer=4
thread=2751
reader:read item from buffer=4
writer:enter an item into buffer
4
thread=2751
thread=2752
reader:read item from buffer=4
reader:read item from buffer=4
writer:enter an item into buffer
6
thread=2752
reader:read item from buffer=6
thread=2751
reader:read item from buffer=6
writer:enter an item into buffer
^C
*/
