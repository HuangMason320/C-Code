#include <stdio.h>
#include <stdlib.h>
#define LL long long int
#define IO_BOOST                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(0)
LL arr[(int)2e5 + 2], n, m;

LL cal(int day)
{
    LL sum = 0;
    for (int i = 0; i < day; i++)
    {
        sum += arr[i];
    }
    LL count = 0, times = 1;
    for (int i = day; i < n; i++)
    {
        count++;
        if (arr[i] - times > 0)
            sum += (arr[i] - times);
        if (count == day)
            times++, count = 0;
    }
    return sum;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }
        LL l = 1, r = n + 1, ans = -1;
        while (l < r)
        {
            LL mid = (l + r) / 2;
            if (cal(mid) >= m)
                ans = mid, r = mid;
            else
                l = mid + 1;
        }
        printf("%lld\n", ans);
    }
}