// Gey cool~
#include <stdio.h>
long long int pre[2000003];
int main()
{
    pre[0] = 0;
    int n, q, a, b, left, right;
    while (scanf("%d", &n) != EOF)
    {
        long long int max = 0;
        scanf("%d", &q);
        for (int i = 0; i < n; i++)
        {
            long long int temp_num;
            scanf("%lld", &temp_num);
            pre[i + 1] = temp_num + pre[i];
        }
        for (int i = 0; i < q; i++)
        {
            scanf("%d %d", &a, &b);
            if (b > a && pre[b] - pre[a - 1] > max)
            {
                left = a;
                right = b;
                max = pre[b] - pre[a - 1];
            }
            else if (b < a && pre[n] - pre[a - 1] + pre[b] > max)
            {
                left = a;
                right = b;
                max = pre[n] - pre[a - 1] + pre[b];
            }
            else if (b == a && pre[a] - pre[a - 1] > max)
            {
                left = a;
                right = b;
                max = pre[a] - pre[a - 1];
            }
        }
        printf("Max_range: (%d,%d); Value: %lld\n", left, right, max);
    }
}