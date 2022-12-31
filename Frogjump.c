#include <stdio.h>
#include <math.h>

int h[100005];
int dp[100005];

int main()
{
    int n, temp;
    scanf("%d", &n);
    dp[0] = 1000000;
    scanf("%d", &h[1]);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &h[i]);
        temp = h[i] - h[i - 1];
        if(dp[i-1]+abs(h[i] - h[i - 1])>dp[i-2]+abs(h[i] - h[i - 2]))
            dp[i] = dp[i - 2] + abs(h[i] - h[i - 2]);
        else
            dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
    }
    printf("%d\n", dp[n]);
    return 0;
}