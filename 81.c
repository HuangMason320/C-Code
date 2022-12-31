//C - Stable Sort
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _T
{
    /* data */
    char name[21];
    int score,index;
}T;

T arr[(int)1e5 + 1];

int cmp(const void *A,const void *B)
{
    T a = *(T *)A, b = *(T *)B;
    if(a.score!=b.score)
        return -(a.score - b.score);
    else
        return a.index - b.index;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n;i++)
    {
        scanf("%s %d", &arr[i].name, &arr[i].score);
        arr[i].index = i;
    }
    qsort(arr, n, sizeof(T), cmp);
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", arr[i].name);
    }
    return 0;
}