#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void merge(int[], int, int, int);
void part(int[], int, int);
void quicksort(int[10], int, int);

int main()
{
    int x[10], size, i, pid;
    printf("\nEnter size of the array: ");
    scanf("%d", &size);
    printf("\nEnter %d elements: ", size);
    for (i = 0; i < size; i++)
        scanf("%d", &x[i]);

    pid = fork();
    if (pid == 0) //child process
    {
        printf("\nChild process:");
        printf("\nPid of child is:%d and that of its parent is:%d", getpid(), getppid());
        quicksort(x, 0, size - 1);
        printf("\n\nQuick sorted elements: ");
        for (i = 0; i < size; i++)
            printf(" %d ", x[i]);
        printf("\n\n");
    }
    else //parent process
    {
        sleep(10);
        wait(0);
        printf("\nParent process:");
        part(x, 0, size - 1);
        printf("\nPid of parent is:%d and that of its parent's parent is:%d", getpid(), getppid());
        printf("\n\nMerge sorted elements: ");
        for (i = 0; i < size; i++)
            printf(" %d ", x[i]);
        printf("\n\n");
    }
    return 0;
}
void quicksort(int x[10], int first, int last)
{
    int pivot, j, temp, i;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (x[i] <= x[pivot] && i < last)
                i++;
            while (x[j] > x[pivot])
                j--;
            if (i < j)
            {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }

        temp = x[pivot];
        x[pivot] = x[j];
        x[j] = temp;
        quicksort(x, first, j - 1);
        quicksort(x, j + 1, last);
    }
}
void part(int arr[], int min, int max)
{
    int mid;
    if (min < max)
    {
        mid = (min + max) / 2;
        part(arr, min, mid);
        part(arr, mid + 1, max);
        merge(arr, min, mid, max);
    }
}
void merge(int arr[], int min, int mid, int max)
{
    int tmp[30];
    int i, j, k, m;
    j = min;
    m = mid + 1;
    for (i = min; j <= mid && m <= max; i++)
    {
        if (arr[j] <= arr[m])
        {
            tmp[i] = arr[j];
            j++;
        }
        else
        {
            tmp[i] = arr[m];
            m++;
        }
    }
    if (j > mid)
    {
        for (k = m; k <= max; k++)
        {
            tmp[i] = arr[k];
            i++;
        }
    }
    else
    {
        for (k = j; k <= mid; k++)
        {
            tmp[i] = arr[k];
            i++;
        }
    }
    for (k = min; k <= max; k++)
        arr[k] = tmp[k];
}
