#include <stdio.h>

int x[1005], y[1005];
int visited[1005] = {0};
int n, r, count, alone, group;

int dist(int left, int right)
{
    return (x[right] - x[left]) * (x[right] - x[left]) + (y[right] - y[left]) * (y[right] - y[left]);
}
void DFS(int now)
{
    if (visited[now])
        return;
    visited[now] = 1;
    count++;
    for (int i = 0; i < n; i++)
    {
        if (i == now)
            continue;
        if (visited[i] == 1)
            continue;
        if (dist(now, i) <= r * r)
        {
            DFS(i);
        }
    }
}
int main()
{
    scanf("%d %d", &n, &r);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &x[i], &y[i]);
    group = 0;
    alone = 0;
    for (int i = 0; i < n; i++)
    {
        count = 0;
        if (!visited[i])
        {
            DFS(i);
            if (count > 1)
                group++;
            else
                alone++;
        }
    }
    printf("%d %d\n", alone, group);
}