#include <stdio.h>

int value[1000005];
long long int sum[1000005];

int main()
{
    int n, q, l, r, m;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value[i]);
        if (value[i] < 0)
            value[i] = 0;
        sum[i + 1] = sum[i] + value[i];
    }
    while (q--)
    {
        scanf("%d %d %d", &l, &r, &m);
        printf("%lld\n", sum[l + m - 1] - sum[l - 1]);
    }
    return 0;
}