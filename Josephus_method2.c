#include <stdio.h>

#define N 41
#define M 3
int a[N];

int find_next(int i)
{
    do
    {
        i = (i + 1) % N;
    } while (a[i] == -1);
    return i;
}
int main(void)
{
    int i, n = N, k;
    for (i = 0; i < N; i++)
    {
        a[i] = i + 1;
    }
    i = -1;
    while (n > 1)
    {
        k = 0;
        while (k < M)
        {
            i = find_next(i);
            k++;
        }
        a[i] = -1;
        --n;
    }
    i = find_next(i);
    printf("%d\n", a[i]);
    return 0;
}