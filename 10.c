// knuckle's name
#include <stdio.h>
#include <string.h>
typedef struct
{
    int ol, str[26];
} Point;
Point p[2001];

int search[26];

void DFS(int n, int now)
{
    for (int i = 0; i < 26; i++)
    {
        if (p[now].str[i] != 0 && search[i] == 0)
        {
            p[now].ol++; // 記已經算過的字串
            search[i]++; // 記已經算過的字母
            for (int j = 0; j < n; j++)
            {
                if (p[j].str[i] != 0 && p[j].ol == 0)
                {
                    p[j].ol++; // 記已經算過的字串(一定要加，不然最後一個字串會跑不到)
                    DFS(n, j);
                }
            }
        }
    }
}
int main()
{
    int t, n;
    scanf("%d\n", &t);
    while (t--)
    {
        int ans = 0;
        scanf("%d\n", &n);
        for (int i = 0; i < n; i++)
        {
            char c[1003];
            scanf("%s", c);
            int len = strlen(c);
            for (int j = 0; j < len && c[j] != '\0'; j++)
                p[i].str[c[j] - 97]++;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i].ol == 0)
            {
                ans++;
                DFS(n, i);
            }
        }
        printf("%d\n", ans);
        for (int i = 0; i < n; i++)
        {
            p[i].ol = 0;
            for (int j = 0; j < 26; j++)
                p[i].str[j] = 0;
        }
        for (int i = 0; i < 26; i++)
            search[i] = 0;
    }
}