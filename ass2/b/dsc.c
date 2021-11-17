#include <stdio.h>
#include <stdlib.h>
void dsc(int *a, int nElem)
{
    int i, j, temp;
    for (i = 0; i < nElem; i++)
    {
        for (j = i + 1; j < nElem; j++)
        {
            if (a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int nElem = argc - 1;
    int i, elem;
    int a[nElem];
    int j = 0;
    for (i = 1; i <= nElem; i++)
    {
        elem = atoi(argv[i]);
        a[j] = elem;
        j++;
    }
    dsc(a, nElem);
    printf("sorted in descending order\n");
    for (i = 0; i < nElem; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}