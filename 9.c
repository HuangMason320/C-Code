// Nyan Cat Crisis
#include <stdio.h>
int x[10005], y[10005], visited[10005];
int t, n, r, k, tmp;
int distance(int a, int b)
{
    if (((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b])) <= r * r)
        return 1;
    else
        return 0;
}
int dfs(int num)
{
    int size = 1;
    visited[num] = 1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance(num, i))
            size += dfs(i);
    }
    return size;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        int ans_less = 0, ans_other = 0;
        scanf("%d %d %d", &n, &r, &k);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &x[i], &y[i]);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (dfs(i) >= k)
                    ans_other++;
                else
                    ans_less++;
            }
        }
        printf("%d %d\n", ans_less, ans_other);
    }
}