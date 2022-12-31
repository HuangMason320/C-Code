#include<stdio.h>

#define N 41
#define M 3
int a[N];

void shift_left(int i, int n)
{
    int j;
    for (j = i + 1; j < n; j++)
    {
        a[j - 1] = a[j];
    }
}
void show(int n)
{
    for (int i = 0; i < N; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int main()
{
    int n = N;
    for (int i = 0; i < N; i++)
    {
        a[i] = i + 1;
    }
    int i = 0;
    while(n>1)
    {
        i = (i + M - 1) % n;
        //printf("%d ", a[i]);
        shift_left(i,n);
        --n;
    }
    printf("%d", a[0]);
    //show(N);
}