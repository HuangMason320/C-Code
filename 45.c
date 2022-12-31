//I got a perfect body
#include <stdio.h>
#include <stdlib.h>

int arr[300005]={0}, pre[300005]={0};

int cmp(const void *A,const void *B)
{
    int *a = (int *)A;
    int *b = (int *)B;
    return *(int *)a - *(int *)b;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (t; t > 0; t--)
    {
        int n, k, p, ans=0;
        scanf("%d %d %d", &n, &p, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i]);
        qsort(arr + 1, n, sizeof(int), cmp);
        for (int i = 1; i <= n; i++)
        {
            pre[i] += arr[i];
            if(i>=k)
                pre[i] += pre[i - k];
            else
                pre[i] += pre[i - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            if(p>=pre[i])
            {
                ans = i;
            }       
        }
        printf("%d\n", ans);
        for (int i = 1; i <= n; i++) // array return 0
        {
            arr[i] = 0;
            pre[i] = 0;
        }    
    }
    return 0;
}