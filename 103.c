#include <stdio.h>

int main()
{
    int min, n, m, tmp;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &tmp);
            if (i == 0 && j == 0)
                min = tmp;
            if (min > tmp)
                min = tmp;
        }
    }
    printf("%d\n", min);
}