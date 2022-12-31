#include <stdio.h>

int search(int num, int *post, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (post[i] == num)
            return i;
    }
}
int main()
{
    int n;
    int pre[15], post[15];
    while (~scanf("%d", &n))
    {
        int ans = 1;
        for (int i = 0; i < n; i++)
            scanf("%d", &pre[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &post[i]);
        for (int i = 0; i < n; i++)
        {
            int idx = search(pre[i], post, n);
            if (pre[i + 1] == post[idx - 1])
                ans = ans * 2;
        }
        printf("%d\n", ans);
    }
}
