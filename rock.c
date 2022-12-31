#include <stdio.h>

int arr[505][505], pre[505][505];

int main()
{
    int t, m, n, q;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &m, &n);
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &arr[i][j]);
                pre[i][j] = arr[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
            }
        }
        scanf("%d", &q);
        int x1, x2, y1, y2, ans;
        for (int i = 0; i < q; i++)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            ans = pre[x2][y2] - pre[x2][y1 - 1] - pre[x1 - 1][y2] + pre[x1 - 1][y1 - 1];
            printf("%d\n", ans);
        }
    }
}