#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    int dp[2][3] = {0};
    int n, ans;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &dp[0][0], &dp[0][1], &dp[0][2]);
        int a = dp[0][0] + max(dp[1][1], dp[1][2]);
        int b = dp[0][1] + max(dp[1][0], dp[1][2]);
        int c = dp[0][2] + max(dp[1][1], dp[1][0]);
        dp[1][0] = a;
        dp[1][1] = b;
        dp[1][2] = c;
    }
    ans = max(dp[1][0], dp[1][1]);
    ans = max(dp[1][2], ans);
    printf("%d\n", ans);
}